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


import time
import requests
from bs4 import BeautifulSoup
from math import radians
from sklearn.metrics.pairwise import haversine_distances
from xml.etree.ElementTree import fromstring
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

    total = 0

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

        shps = road.find_all("shp")

        # shps = shps[0:1] + shps[-1:]   ---- won't work, disconnects the network

        total += traffic_level * len(shps)
            

    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    current_date = now.date()

    filename = top_left + '_' + bottom_right + '_' + str(current_date)

    with open(filename, 'a') as fi:
        print(current_time, total, file=fi)

    print('Data appended to the file', filename)
    return




if __name__ == '__main__':

    # New Delhi
    top_left = '28.687203816391193, 77.04710350388676'
    bottom_right = '28.547244344345092, 77.41867712678446'


    for _ in range(10):
        getData(top_left, bottom_right)
        time.sleep(120)