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
    
    n = len(coordinates)    # number of rows in the file

    coord = []
    for _ in range(n):
        coord.append((0.0, 0.0))

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
    
    n = len(graph)

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
    


palatte = ['red', 'blue', 'yellow', 'green', 'orange', 'cyan', 'pink', 'magenta', 'brown', 'black']

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
            # print('plot -', q, '...')
            # plot_graph(graph, coord, color, str(q)+'.png')

    return
    


def disonnected_components(graph):
    '''Returns the connected components of the graph'''
    n = len(graph)

    status = [0] * n

    components = []

    for i in range(n):

        if status[i] != 0:
            continue

        tmp = []

        qu = deque()
        qu.append(i)
        status[i] = 1
        tmp.append(i)

        while len(qu) > 0:
            cur = qu.popleft()

            for a, _ in graph[cur]:
                if status[a] == 0:
                    qu.append(a)
                    status[a] = 1
                    tmp.append(a)

            status[cur] = 2

        components.append(tmp)


    return components



def color_components(arr, color):
    '''Color the graph component-wise'''
    a = 0

    for component in arr:
        for i in component:
            color[i] = palatte[a]
        a += 1


def refine_components(arr, graph, demands, color, P):
    '''Refines the partitions: no partition will exceed the limit'''

    total_demand = np.sum(demands)
    limit = total_demand/P

    c = len(arr)

    # Check every component
    for component in arr:
        tmp = 0
        for i in component:
            tmp += demands[i]

        if tmp <= limit:    # this partition is good
            continue        

        # otherwise, we need to refine this partition
        # find the left-most, bottom-most point


        limit = tmp/2


        qu = deque()
        hash = set()

        qu.append(component[0])
        hash.add(component[0])
        tmp -= demands[component[0]]

        while len(qu) > 0:
            cur = qu.popleft()

            for a, _ in graph[cur]:
                if a not in hash and tmp > limit:
                    qu.append(a)
                    hash.add(a)
                    tmp -= demands[a]
        
        for i in hash:
            color[i] = palatte[c]

        c += 1

        l1 = []
        l2 = []

        for a in component:
            if a in hash:
                l1.append(a)
            else:
                l2.append(a)
        
        


        
