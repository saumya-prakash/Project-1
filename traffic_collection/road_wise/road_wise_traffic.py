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

import requests
from sklearn.metrics.pairwise import haversine_distances
from math import radians
import requests
from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import XML, fromstring, tostring
from datetime import datetime


def distance(a, b):
    '''This function returns distance between 2 lat-long pairs using the Haversine distance'''
    c = list(map(radians, a))
    d = list(map(radians, b))

    res = haversine_distances([c, d]) * 6378100

    return res[0][1]



def getData(top_left, bottom_right):

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
        # name = tmc['de']    # name of the road
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
                edges.add((a, b, traffic_level))


    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    current_date = now.date()

    filename = top_left + '_' + bottom_right + '_' + str(current_date)

    with open(filename, 'a') as fi:
        print(current_time, file=fi)
        for road in edges:
            n1 = road[0]
            n2 = road[1]
            traffic = road[2]

            c1 = list(map(str, hash2[n1]))
            c2 = list(map(str, hash2[n2]))

            label = c1[0] + '-' + c1[1] + '_' + c2[0] + '-' + c2[1]
            
            print(label, traffic, file=fi)

    return


if __name__ == '__main__':

    # New Delhi
    top_left = '28.687203816391193, 77.04710350388676'
    bottom_right = '28.547244344345092, 77.41867712678446'

    getData(top_left, bottom_right)