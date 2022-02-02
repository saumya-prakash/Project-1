# from math import pi, radians, sin

# # # small map
# # top_left = '25.611141692828234, 85.07440251214753'
# # bottom_right = '25.602840502150624, 85.0818697823339'

# # PATNA coordinates
# # top_left = '25.637440467866426, 85.02811064635446'
# # bottom_right = '25.582372756691644, 85.1740168271475'

# # Gorapkhpur, UP, India
# lat1 = 26.77340115409228
# long1 = 83.35400937128232

# lat2 = 26.74836515580979
# long2 = 83.38955667002368

# R = 6378
# area = (pi/180) * R**2 * abs(sin(radians(lat1))-sin(radians(lat2))) * abs(radians(long1) - radians(long2))


def parent(cur, dsu):

    if dsu[cur] == -1:
        return cur
    
    dsu[cur] = parent(dsu[cur], dsu)

    return dsu[cur]


from collections import deque

graph = [
    [1, 2],
    [0, 2, 3, 4],
    [0, 1, 5],
    [1, 4, 8],
    [1, 3, 7, 6, 5],
    [2, 4, 6],
    [5, 4, 7],
    [6, 4, 8],
    [3, 7]
]

demand = [10, 20, 10, 5, 5, 5, 4, 1, 30]

n = len(demand)

total = 0
for a in demand:
    total += a


NP = 4  # number of partitions 
average = total/NP


status = [0] * n
dsu = [-1] * n

limit = average

# Create partitions - will be stored as disjoint sets
while True:

    flag = 0

    for i in range(n):  # check all nodes one by one

        if status[i] != 0:  # if this node is already a part of a partiton
            continue

        # Create a new partition starting with this node
        flag = 1

        qu = deque()

        qu.append(i)
        status[i] = 1
        sum = demand[i]

        while len(qu) != 0:
    
            cur = qu.popleft()

            for a in graph[cur]:    # explore the neighbours

                if status[a] != 0 or sum+demand[a] > limit:
                    continue

                sum += demand[a]
                qu.append(a)
                status[a] = 1
                dsu[a] = cur
        
            status[cur] = 2

    if flag == 0:
        break


color = [0] * 9
m = 1

# flatten the trees and color the nodes
for i in range(n):
    _ = parent(i, dsu)

    if dsu[i] == -1:
        color[i] = m
        m += 1

for i in range(n):
    color[i] = color[parent(i, dsu)]

paint = {1:'red', 2:'yellow', 3:'green', 4:'blue', 5:'orange'}

print(NP, 'partitions found')


## For visualization

from pyvis.network import Network

net = Network(heading='Partition', height='800px', width='1800px')

for u in range(n):
    net.add_node(u, demand[u], color=paint[color[u]])

for u in range(n):
    for v in graph[u]:
        if v < u:
            continue
        net.add_edge(u, v)


net.show('partition.html')

