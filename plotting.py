'''This program uses netwrokX

Refer: https://towardsdatascience.com/visualizing-networks-in-python-d70f4cbeb259
'''


import matplotlib.pyplot as plt
from numpy.lib.shape_base import split
import random
import pandas as pd
from pyvis.physics import Physics
from sklearn.utils.extmath import weighted_mode

df = pd.read_csv('edges.csv', sep=' ')
cdf = pd.read_csv('coordinates.csv', sep=' ')

print(df.describe())

coord = dict()

for _, row in cdf.iterrows():
    coord[int(row[0])] = (row[1], row[2])

# import networkx as nx
# G = nx.from_pandas_edgelist(df, source='From', target='To', edge_attr='Weight')

from pyvis.network import Network

net = Network(heading='Map', height='800px', width='1800px')
# net.from_nx(G)
# net.show('Map.html')



n = max(df['From'].max(), df['To'].max()) + 1   # number of nodes

for i in range(n):
    color= 'black'
    if random.random() <= 0.25:
        color = 'red'
    net.add_node(i, i, color=color) #, x=coord[i][0], y=coord[i][1])



for _, row in df.iterrows():
    u = int(row['From'])
    v = int(row['To'])
    wt = row['Weight']
    name = row['Name']

    n = max(n, max(u, v))

    net.add_edge(source=u, to=v, title=name+'; '+str(wt), color='black', width=10)


net.toggle_drag_nodes(False)
net.toggle_physics(False)
net.show('map.html')
