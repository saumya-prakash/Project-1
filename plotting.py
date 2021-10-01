'''This program uses PyVis

Refer: https://towardsdatascience.com/visualizing-networks-in-python-d70f4cbeb259
'''


from pyvis.network import Network
import matplotlib.pyplot as plt
import random
import pandas as pd
from pyvis.physics import Physics


# import networkx as nx
# G = nx.from_pandas_edgelist(df, source='From', target='To', edge_attr='Weight')


df = pd.read_csv('edges.csv', sep=' ')
cdf = pd.read_csv('coordinates.csv', sep=' ')

print(df.describe())

coord = dict()

for _, row in cdf.iterrows():
    coord[int(row[0])] = (row[1], row[2])

    

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
    u = int(row[0])
    v = int(row[1])
    wt = row[2]
    name = row[4]

    net.add_edge(source=u, to=v, title=name+'; '+str(wt), color='black', width=0)


net.toggle_drag_nodes(False)
net.toggle_physics(False)
net.show('map.html')
