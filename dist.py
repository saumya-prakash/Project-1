import requests
from sklearn.metrics.pairwise import haversine_distances
from math import radians, radians
import requests
from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import XML, fromstring, tostring


def distance(a, b):
    '''This function returns distance between 2 lat-long pairs using the Haversine distance'''
    c = list(map(radians, a))
    d = list(map(radians, b))

    res = haversine_distances([c, d]) * 6378100

    return res[0][1]



def api_distace(a, b, key):
    '''This function returns distance between 2 lat-long pairs using the HERE API.
    But, API calls are slower than using the Haversine formula.
    Refer: https://developer.here.com/documentation/routing-api/dev_guide/topics/send-request.html'''
    x1, y1 = a[0], a[1]
    x2, y2 = b[0], b[1]

    link = 'https://router.hereapi.com/v8/routes?apiKey=' + str(key) + '&transportMode=car&origin=' + str(x1) + ',' + str(y1) + '&destination=' + str(x2) + ',' + str(y2) + '&return=summary'

    info = requests.get(link)

    res = info.text

    pass
