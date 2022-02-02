""" Utility functions """

from os import posix_fallocate
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import deque


def get_graph(filename):

    # edges.csv file stores the information about the edges of the graph
    edges = pd.read_csv(filename, sep=' ')

    # Find the total number of nodes
    n = max(max(edges['From']), max(edges['To'])) + 1

    # It will store the adjacency list representation of the graph
    graph = []
    for _ in range(n):
        graph.append([])

    # Read the information about the edges of the graph
    for row in edges.itertuples():
        _, u, v, length, _, _ = row

        graph[u].append((v, length))
        graph[v].append((u, length))


    return graph, n



def get_coordinates(filename):

    # coordinates.csv file stores the coordinates of the nodes
    coordinates = pd.read_csv(filename, sep=' ')

    coord = {}
    for row in coordinates.itertuples():
        _, node, lat, long = row

        coord[node] = (lat, long)

    return coord



def get_demands(filename):
    
    # demands.csv file stores the demands at the nodes
    dem = pd.read_csv(filename, sep=' ')

    n = max(dem['Node_id']) + 1

    demands = np.zeros((n))

    for row in dem.itertuples():
        _, node, a = row

        demands[node] = a

    return demands



def plot_graph(graph, coord, color, name):
    n  =len(graph)

    fig = plt.figure()
    # plt.style.use('dark_background')

    plt.grid(False)
    

    for u in range(n):
        for v, _ in graph[u]:
            lats = [coord[u][0], coord[v][0]]
            longs = [coord[u][1], coord[v][1]]

            plt.plot(longs, lats, c=color[u], linewidth=0.5)

    plt.axis('off')
    plt.savefig(name)
    # plt.show()
    


palatte = ['red', 'blue', 'yellow', 'green', 'orange', 'cyan', 'pink', 'magenta', 'black']

def partition(graph, P, coord, demands, color):
    '''Partiotion the graph into 'np' number of components'''
    
    total_demand = np.sum(demands)
    
    limit = total_demand/P

    # Do a BFS-like search

    n = len(graph)

    status = [0]*n
    dsu = [-1]*n

    q = 0

    current = 0

    for i in range(n):
        
        if status[i] != 0:
            continue
        
        qu = deque()

        qu.append(i)
        status[i] = 1
        current += demands[i]
        color[i] = palatte[q]
        
        while len(qu) > 0:

            cur = qu.popleft()

            for a, _ in graph[cur]:
                
                if status[a] != 0 or current+demands[a] > limit:
                    continue
                
                qu.append(a)
                status[a] = 1
                current += demands[a]
                color[a] = palatte[q]
                dsu[a] = cur
            
            status[cur] = 2


        if current >= limit:
            current = 0
            q += 1
            print('plot -', q, '...')
            plot_graph(graph, coord, color, str(q)+'.png')



    return
    