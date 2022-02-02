from utils import *


graph, n = get_graph('edges.csv')

coord = get_coordinates('coordinates.csv')

demands = get_demands('demands.csv')

# Number of partitions
P = 6

color = ['#000000'] * n # all the nodes are black initially

print('Partitioning...')
partition(graph, P, coord, demands, color)

# print('Plotting...')
# plot_graph(graph, coord, color, 'partitioned.png')
