from input import *
from partition import *

graph, n = get_graph('edges.csv')
coord = get_coordinates('coordinates.csv')
demands = get_demands('demands.csv')

print('Number of nodes =', n)

# # Number of partitions
# P = 6

# color = ['#000000'] * n # all the nodes are black initially

# d = disonnected_components(graph)
# print('Number of disconnected components =', len(d))


pr = GridPartition(n, coord, demands)

td = pr.totalDemand()

print('Limit =', td/6)
pr.setLimit(td/6)

pr.partition()

print(len(pr.components))


# print('Partitioning...')
# partition(graph, P, coord, demands, color)


# How to partition well???
## BFS-based
## gird baesd - draw parallel lines - divide into rectangular regions!!


# color_components(d, color)
# refine_components(d, graph, demands, color, P)

print('Plotting...')
plot_graph(graph, coord, pr.color, 'partitioned.png')
