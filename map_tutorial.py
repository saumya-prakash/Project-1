'''
Refer: https://towardsdatascience.com/visualizing-networks-in-python-d70f4cbeb259
'''

from matplotlib import pyplot as plt
import numpy as np
import matplotlib.cm as cm

import requests
from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET
from xml.etree.ElementTree import XML, fromstring, tostring


KEY = 'GL4Ghj-44nBGKEZYxt8GKnQoi25c8qlFe98nX6nGJ1U'

# # PARIS coordinates
# top_left = '49.04360881961464, 1.9663553191345908'
# bottom_right = '48.688043406029145, 2.7939035384054076' 

# # PATNA coordinates
# top_left = '25.629005146302, 85.06621735528832'
# bottom_right = '25.58068061010138, 85.1761472496063'


# Gorapkhpur, UP, India
top_left = '26.77340115409228, 83.35400937128232'
bottom_right = '26.74836515580979, 83.38955667002368'


# # New Delhi
# top_left = '28.687203816391193, 77.04710350388676'
# bottom_right = '28.547244344345092, 77.41867712678446'

# # small map
# top_left = '25.611141692828234, 85.07440251214753'
# bottom_right = '25.602840502150624, 85.0818697823339'


link = 'https://traffic.ls.hereapi.com/traffic/6.2/flow.xml?apiKey=' + KEY + '&bbox=' + top_left + ';' + bottom_right + '&responseattributes=sh,fc'

# Do the API call
page = requests.get(link)

print(page.status_code, page.reason)

soup = BeautifulSoup(page.text, 'lxml')
# Extract road details
roads = soup.find_all('fi')

lats = list()
longs = list()
sus = list()
ffs = list()

for road in roads:

    myxml = fromstring(str(road))
    
    for child in myxml:
        if('su' in child.attrib):
            su = float(child.attrib['su'])
        if('ff' in child.attrib):
            ff = float(child.attrib['ff'])

    shps = road.find_all("shp")
    for j in range(0,len(shps)):
        
        # latlong[] is a list of latitudes and longitudes
        latlong=shps[j].text.replace(',',' ').split()

        la = list() # to store the latitudes
        lo = list() # to store the longitudes
        su1 = list()
        ff1 = list()

        for i in range(0, int(len(latlong)/2)):  # process each latitude-longitude pair in the list

            x = float(latlong[2*i])
            y = float(latlong[2*i+1])
            
            la.append(x)
            lo.append(y)

            su1.append(float(su))
            ff1.append(float(ff))
            
        lats.append(la)
        longs.append(lo)
        sus.append(np.mean(su1))
        ffs.append(np.mean(ff1))


fig = plt.figure()
# plt.style.use('dark_background')

plt.grid(False)

for i in range(0,len(lats)):

    plt.plot(longs[i], lats[i], c='black',linewidth=0.5)
    continue    

    if(sus[i]/ffs[i]<0.25):
        plt.plot(longs[i], lats[i], c='brown',linewidth=0.5)

    elif(sus[i]/ffs[i]<0.5):
        plt.plot(longs[i], lats[i], c='red',linewidth=0.5)

    elif(sus[i]/ffs[i]<0.75):
        plt.plot(longs[i], lats[i], c='yellow',linewidth=0.5)

    else:
        plt.plot(longs[i], lats[i], c='green',linewidth=0.5)


plt.axis('off')
plt.show()



# link_legacy = 'https://traffic.api.here.com/traffic/6.2/flow.xml?app_id=rUhReCkKrUOJ4gortgnh&app_code=GL4Ghj-44nBGKEZYxt8GKnQoi25c8qlFe98nX6nGJ1U&bbox=39.039696,-77.222108;38.775208,-76.821107&responseattributes=sh,fc'

# linka = 'https://traffic.ls.hereapi.com/traffic/6.3/incidents/xml/8/134/86?apiKey=omfXtntSCXNZQF853JHKhc11nk358zd0KuijFzqMktg'
