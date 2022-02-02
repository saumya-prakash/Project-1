import heapq

class Tree:

    def __init__(self):
        
        self.x = 0


    def find_MST(self, graph):

        n = len(graph)

        tree = []   # to store the tree edges
        for _ in range(n):
            tree.append([])

        cnt = 0     # to count the number of edges
        cost = 0    # weight of the MST

        pq = []
        heapq.heapify(pq)   # min priority queue

        status = [0] * n

        heapq.heappush(pq, (0, 0, -1))  # push (weight, node, predecessor) into the priority queue

        while cnt != n:

            wt, cur, pre = heapq.heappop(pq)

            if status[cur] != 0:
                continue

            status[cur] = 1
            cost += wt
            if pre != -1:
                tree[cur].append((pre, wt))
                tree[pre].append((cur, wt))

            cnt += 1

            for a in graph[cur]:
                
                b = a[0]
                w = a[1]

                if status[b] != 0:
                    continue

                heapq.heappush(pq, (w, b, cur))

        
        return (tree, cost)



   

    def _find_diameter(self, cur, prede, tree):

        t1 = 0
        t2 = 0

        for a in tree[cur]:
            b = a[0]
            wt = a[1]

            if b == prede:
                continue
            
            tmp = wt + self._find_diameter(b, cur, tree)

            if tmp > t1:
                t2 = t1
                t1 = tmp
            
            elif tmp > t2:
                t2 = tmp

        self.x = max(self.x, t1+t2)

        return max(t1, t2)

        
    
    def diameter(self, tree):    
        self.x = 0
        self._find_diameter(0, -1, tree)

        return self.x




graph = [
    [(1, 10), (2, 20)],
    [(0, 10), (2, 30), (3, 30), (4, 30)],
    [(0, 20), (1, 30), (4, 70)],
    [(1, 30), (4, 40), (5, 50)],
    [(2, 70), (1, 30), (3, 40), (6, 70)], 
    [(3, 50), (6, 60)],
    [(4, 70), (5, 60)]
]


func = Tree()

# Find a MST and its cost
tree, cost = func.find_MST(graph)

# Find the diameter of the MST
diam = func.diameter(tree)

print(diam)




## For visualization

from pyvis.network import Network

net = Network(heading='Partition', height='800px', width='1800px')

n = len(graph)

for u in range(n):
    net.add_node(u)

for u in range(n):
    for v in graph[u]:
        if v[0] < u:
            continue
        net.add_edge(u, v[0])


# net.show('partition.html')

