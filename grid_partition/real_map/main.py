import pandas as pd
from utils import *


edges = pd.read_csv('edges.csv', sep=' ')

# Find the total number of nodes
n = max(max(edges['From']), max(edges['To'])) + 1

# It will store the adjacency list representation of the graph
graph = []
for _ in range(n):
    graph.append([])



