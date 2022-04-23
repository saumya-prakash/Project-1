import matplotlib.pyplot as plt

# Collect the component nodes
with open('../data/components.txt', 'r') as fi:

    a = fi.readline()
    a = a.split(' ')[:-1]   # remove the last '\n' character
    a = list(map(int, a))


# Collect the site nodes and station nodes
with open('../data/stations_location', 'r') as fi:
    c = fi.readline()
    c = c.split(' ')[:-1]
    c = list(map(int, c))
    
    b = fi.readline()
    b = b.split(' ')[:-1]
    b = list(map(int, b))


a = set(a)
c = set(c)
b = set(b)


coord = {}
sites_coord = {}
s_coord = {}


with open('../data/coordinates.csv', 'r') as fi:
    _ = fi.readline()   # consume the header line

    while len(a) > 0:

        row = fi.readline()
        row = row.split(' ')

        node, lat, lon = int(row[0]), float(row[1]), float(row[2])

        if node in a:
            coord[node] = (lon, lat)
            a.remove(node)

            if node in c:
                sites_coord[node] = (lon, lat)
                c.remove(node)

                if node in b:
                    s_coord[node] = (lon, lat)
                    b.remove(node)



fig = plt.figure()
plt.grid(False)
plt.axis('off')

with open('../data/edges.csv', 'r') as fi:
    _ = fi.readline()   # consime the header line

    for row in fi.readlines():
        row = row.split(' ')
        u = int(row[0])
        v = int(row[1])

        if u in coord and v in coord:
            p1 = coord[u]
            p2 = coord[v]

            plt.plot([p1[0], p2[0]], [p1[1], p2[1]], color='black', linewidth=1)

    


alpha = 1.00001

for key in sites_coord:
    x, y = sites_coord[key]
    plt.plot([x, alpha*x], [y, alpha*y], color='red', linewidth=5)

for key in s_coord:
    x, y = s_coord[key]
    plt.plot([x, alpha*x], [y, alpha*y], color='green', linewidth=5)


plt.show()
