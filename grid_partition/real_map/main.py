from utils import *


graph, n = get_graph('edges.csv')

coord = get_coordinates('coordinates.csv')

demands = get_demands('demands.csv')

# Number of partitions
P = 6

color = ['#000000'] * n # all the nodes are black initially

partition(graph, P, coord, demands, color)

plot_graph(graph, coord, color)
