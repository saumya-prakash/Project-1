from input import *
from partition import GridPartition
from placement import Placement

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
pr.setRange(15)

pr.partition()

print('Number of partitions =', len(pr.components))
print()

# print('Partitioning...')
# partition(graph, P, coord, demands, color)

# How to partition well???
## BFS-based
## gird baesd - draw parallel lines - divide into rectangular regions!!

# color_components(d, color)
# refine_components(d, graph, demands, color, P)


# pr.colorPartitions()

# print('Plotting...')
# plot_graph(graph, coord, pr.color, 'partitioned.png')
# print()

# pl = Placement(graph, coord, demands)

with open('components.txt', 'w') as fi:

    cnt = 1
    for component in pr.components:
        # plot_component(graph, set(component), coord, pr.color, 'component'+str(cnt)+'.png')
        # cnt += 1

        # pl.setComponent(pr.components[0])

        # # print('Brute-force: ')
        # # pl.bruteForce()
        # # print()

        # print('Genetic algorithm: ')
        # pl.findLocation()
        # print()
        # break

        for a in component:
            print(a, file=fi, end=' ')
        print(file=fi)

        



# import matplotlib.pyplot as plt
# fig = plt.figure()
# plt.scatter([77.14811], [28.52951], color = 'blue')
# plt.scatter([77.09274965572511], [28.53104908606825], color='red')
# plt.show()