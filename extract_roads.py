# NOTE: If the keys do not work, then visit the site https://www.here.com/ and sign-up/login to generate
# keys.

##########
# From a temporary email:

# REST
# rUhReCkKrUOJ4gortgnh - API ID
# GL4Ghj-44nBGKEZYxt8GKnQoi25c8qlFe98nX6nGJ1U - API key
# omfXtntSCXNZQF853JHKhc11nk358zd0KuijFzqMktg - API key


# Javascript
# g7cd7dz8PyWOP2PWjZh7 - API ID
# lr7WcuX8HoJX4GxNu7SfnK_3tqUjdY9t7iN_m8sEJaI - API code


############
# From my own account

# REST
# CXTu1XJBiDGIGjTEjtWi
# ZBy-Dm53Rx8aPe5YCcxQr9kCOI00TdN2v8dXMJDNifo


# For REST APIs, refer: https://developer.here.com/develop/rest-apis


KEY = 'GL4Ghj-44nBGKEZYxt8GKnQoi25c8qlFe98nX6nGJ1U'


# Get the distance funtions
from dist import *


# # Gorapkhpur, UP, India
# top_left = '26.77340115409228, 83.35400937128232'
# bottom_right = '26.74836515580979, 83.38955667002368'

# PATNA coordinates
top_left = '25.637440467866426, 85.02811064635446'
bottom_right = '25.582372756691644, 85.1740168271475'


# # small map
# top_left = '25.611141692828234, 85.07440251214753'
# bottom_right = '25.602840502150624, 85.0818697823339'


# Refer: https://developer.here.com/documentation/traffic/dev_guide/topics/incident-data.html

link = 'https://traffic.ls.hereapi.com/traffic/6.2/flow.xml?apiKey=' + KEY + '&bbox=' + top_left + ';' + bottom_right + '&responseattributes=sh,fc'

# Do the API call
page = requests.get(link)
print(page.status_code, page.reason)


# Parse the obtained document
soup = BeautifulSoup(page.text, 'lxml')
# Extract road details
roads = soup.find_all('fi')


node_id = 0
hash1 = dict()  # coordinates to node id
hash2 = dict()  # node id to coordinates

edges = set()   # to store the edges of the graph; edges are undirected


epsilon = 0.01  # when the retrieved data shows no traffic on a road, then assign epsilon traffic to it


# Consider all the roads, even the smaller ones
for road in roads:

    myxml = fromstring(str(road))

    for child in myxml:
        
        if('su' in child.attrib):   # get the average speed
            su = float(child.attrib['su'])
        if('ff' in child.attrib):   # get the 'free-flow' on the road
            ff = float(child.attrib['ff'])

    # Divide the average speed by 'free flow' possible on this road
    # If traffic_index == 1, then normal conditions
    # If traffic_index < 1, then congestion
    # If traffic_index > 1, then road is free!
    traffic_index = su/ff

    if traffic_index == 0:
        traffic_index = epsilon
    
    traffic_level = 1.0/traffic_index

    tmc = road.find('tmc')
    name = tmc['de']    # name of the road
    shps = road.find_all("shp")

    # shps = shps[0:1] + shps[-1:]   ---- won't work, disconnects the network

    for j in range(0, len(shps)):
        
        # latlong[] is a list of latitudes and longitudes
        latlong=shps[j].text.replace(',',' ').split()

        lim = int(len(latlong)/2)

        # Extract the edges
        for i in range(0, lim-1):
            x1, y1 = float(latlong[2*i]), float(latlong[2*i+1])
            x2, y2 = float(latlong[2*(i+1)]), float(latlong[2*(i+1)+1])

            wt = distance([x1, y1], [x2, y2])   # using formula - fast, acceptable accuracy
            # wt = api_distace([x1, y1], [x2, y2], key)   # via api call; SLOW.....

            if (x1, y1) in hash1 and (x2, y2) in hash1:
                pass
            else:
                # at least one of the coordinates is a new node
                if (x1, y1) not in hash1:
                    hash1[(x1, y1)] = node_id
                    hash2[node_id] = (x1, y1)
                    node_id += 1
                
                if (x2, y2) not in hash1:
                    hash1[(x2, y2)] = node_id
                    hash2[node_id] = (x2, y2)
                    node_id += 1

            a = hash1[(x1, y1)]
            b = hash1[(x2, y2)]

            a, b = min(a, b), max(a, b)
            edges.add((a, b, wt, name, traffic_level))



print('Number of nodes (Number of intersections) =', node_id)
print('Number of edges (Number of roads) =', len(edges))



# All the edges and associated information is in edges[]


# Store the edges in edges.csv file
with open('edges.csv', 'w') as fi:
    print('From', 'To', 'Length(meter)', 'Traffic_level', 'Name', file=fi)    
    for tup in edges:
        a, b, wt, name, traffic_level = tup
        print(a, b, wt, traffic_level, '"', file=fi, end='')
        print(name, '"', file=fi, sep='')


# Store the coordintates in coordinates.csv file
with open('coordinates.csv', 'w') as fi:
    print('Node_id', 'Latitude', 'Longitude', file=fi)
    for key in hash2:
        print(key, hash2[key][0], hash2[key][1], file=fi)



