from utils import *


graph, n = get_graph('edges.csv')

coord = get_coordinates('coordinates.csv')

demands = get_demands('demands.csv')

# Number of partitions
P = 6

color = ['#000000'] * n # all the nodes are black initially

d = disonnected_components(graph)
print(len(d))

# print('Partitioning...')
# partition(graph, P, coord, demands, color)


# How to partition well???
## BFS-based
## gird baesd - draw parallel lines - divide into rectangular regions!!


color_components(d, color)
refine_components(d, graph, demands, color, P)

print('Plotting...')
plot_graph(graph, coord, color, 'partitioned.png')
