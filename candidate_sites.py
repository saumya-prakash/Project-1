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

