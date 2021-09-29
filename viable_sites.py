'''This program finds viable sites form the extracted nodes. It uses the demands at each node.

    purely random
    some sort of clustering
    probability = relative demand at a node
    based on range of the EV
'''


from typing import Hashable
import pandas as pd
import math

def relative_demand_probability():

    viables = []

    # Read-in the demands.csv file
    demands = pd.read_csv('demands.csv', sep=' ')

    total_demand = 0
    hash = dict()

    for row in demands.itertuples():
        _, node_id, dn = row

        hash[node_id] = dn
        total_demand += dn

    for a in hash:
        print(hash[a]/total_demand, math.log(hash[a])-math.log(total_demand))

    return viables


print(relative_demand_probability())