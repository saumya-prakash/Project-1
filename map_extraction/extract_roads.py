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

# Refer: https://developer.here.com/documentation/traffic/dev_guide/topics/incident-data.html


KEY = 'GL4Ghj-44nBGKEZYxt8GKnQoi25c8qlFe98nX6nGJ1U'


# Get the distance funtions
from dist import *


# # small map
# top_left = '25.611141692828234, 85.07440251214753'
# bottom_right = '25.602840502150624, 85.0818697823339'


# # Gorapkhpur, UP, India
# top_left = '26.77340115409228, 83.35400937128232'
# bottom_right = '26.74836515580979, 83.38955667002368'


# # PATNA coordinates
# top_left = '25.629005146302, 85.06621735528832'
# bottom_right = '25.58068061010138, 85.1761472496063'

# # PARIS coordinates
# top_left = '49.04360881961464, 1.9663553191345908'
# bottom_right = '48.688043406029145, 2.7939035384054076' 

# New Delhi
top_left = '28.687203816391193, 77.04710350388676'
bottom_right = '28.547244344345092, 77.41867712678446'


# # Mumbai
# top_left = '19.36948637980195, 72.79233915629305'
# bottom_right = '18.963866, 73.074425'

# # Hyderabad
# top_left = '17.583876, 78.180753' 
# bottom_right = '17.235038, 78.645444'


link = 'https://traffic.ls.hereapi.com/traffic/6.2/flow.xml?apiKey=' + KEY + '&bbox=' + top_left + ';' + bottom_right + '&responseattributes=sh,fc'

page = requests.get(link)
# print(page.status_code, page.reason)


# Parse the obtained document
soup = BeautifulSoup(page.text, 'lxml')
# Extract road details
roads = soup.find_all('fi')


node_id = 0
hash1 = dict()  # coordinates to node id
hash2 = dict()  # node id to coordinates

seen_pairs = set()
edges = set()   # to store the edges of the graph; edges are undirected


epsilon = 0.01  # when the retrieved data shows no traffic on a road, then assign epsilon traffic to it


# It returns different edges for 2-way road: from point A to point b and from point B to point A.
# The traffic levels on the 2 roads can be different. But in this implemenation, we are only considering
# one of the 2 roads for NOW. Or , maybe we can try to add the traffic levels of both the road into one??
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

            c = hash1[(x1, y1)]
            d = hash1[(x2, y2)]

            a = min(c, d)
            b = max(c, d)

            if (a, b) in seen_pairs:
                continue

            edges.add((a, b, wt, name, traffic_level))
            # if a==0 and b==1:
            #     print(c, d, x1, y1, x2, y2, ' - ', name, wt, traffic_level)
            seen_pairs.add((a, b))


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


print('edges.csv file generated')



# Store the coordintates in coordinates.csv file
with open('coordinates.csv', 'w') as fi:
    print('Node_id', 'Latitude', 'Longitude', file=fi)
    for key in hash2:
        print(key, hash2[key][0], hash2[key][1], file=fi)

print('coordinates.csv file generated')

