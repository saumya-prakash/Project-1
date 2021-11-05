'''This program finds candidate sites form the nodes. It uses the demands at each node.

    purely random
    some sort of clustering -> most promising
    probability = relative demand at a node -> won't work if there are many nodes; probability at each node
                                                will tend to 0
    based on range of the EV
'''


import pandas as pd
import math
import random
import networkx as nx
from sklearn.metrics.pairwise import haversine_distances
from tqdm import tqdm

from dist import distance


def relative_demand_probability():    

    # Read-in the demands.csv file
    demands = pd.read_csv('demands.csv', sep=' ')

    total_demand = 0
    hash = dict()

    for row in demands.itertuples():
        _, node_id, dn = row

        hash[node_id] = dn
        total_demand += dn


    viables = []

    for a in hash:
        # calculate the probability
        prob = math.log(hash[a]) - math.log(total_demand)

        if math.log(random.random()) <= prob:
            viables.append(a)

    return viables



def clustering(alpha):
    '''good alpha values - 0.01, 0.02 and likewise'''

    # Get the coordinates
    df = pd.read_csv('coordinates.csv', sep=' ')

    coordinates = {}
    
    for row in df.itertuples():
        _, node_id, lat, long = row
        coordinates[int(node_id)] = (float(lat), float(long))


    # Get the demands
    df = pd.read_csv('demands.csv', sep=' ')

    demands = {}

    for row in df.itertuples():
        _, node_id, dn = row
        demands[int(node_id)] = float(dn)


    n = len(coordinates)    # total number of nodes

    k = int(alpha*n) # number of centers to be created

    print('Number of clusters =', k)

    clusters = []    # to store the 'points'
    centers = []     # to store the centers

    points = []
    for i in range(n):
        points.append(i)
    random.shuffle(points)


    # For cluster-i, start = i*k; end = min(n, (i+1)*k)
    for i in range(k):
        size = int(n/k)
        st = i*size
        end = min(n, (i+1)*size)

        clusters.append(points[st:end])
        centers.append(points[st])
    
    # THE DISTANCE METRIC THAT WILL BE USED DURING CLUSTERING
    metric = lambda a, b, d1, d2: distance(a, b) * math.exp(abs(d1-d2))

    MAX_ITERATIONS = 100

    # Run 100 iterations
    for iter in range(MAX_ITERATIONS):    
        
        print('Iteration -', iter+1, '/', MAX_ITERATIONS)

        new_centers = []
        # calculate new center of the clusters
        for i in range(k):
            # Process cluster-i
            sumx, sumy = 0.0, 0.0
            for node in clusters[i]:
                x, y = coordinates[node]
                sumx += x
                sumy += y
            
            new_centers.append((sumx/len(clusters[i]), sumy/len(clusters[i])))


        # move the new centers to the closest point 
        centers = [0]*k

        for i in tqdm(range(len(coordinates)), desc='Recalculatng centers'):
            cur = coordinates[i]
            for j in range(k):
                if metric(new_centers[j], coordinates[centers[j]], 0, 0) > metric(new_centers[j], cur, 0, 0):
                    centers[j] = i
        

        # reassign points to new cluster centers
        clusters = [[]] * k

        for node_id in tqdm(coordinates, desc='Reassigning clusters'):
            pos = coordinates[node_id]

            ind = 0

            for i in range(k):
                if metric(pos, coordinates[centers[ind]], demands[centers[ind]], demands[node_id]) > metric(pos, coordinates[centers[i]], demands[centers[i]], demands[node_id]):
                    ind = i
            
            clusters[ind].append(node_id)
        
    return centers



if __name__ == '__main__':
    viables = clustering(0.02)
    print(viables)
