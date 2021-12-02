import matplotlib.pyplot as plt

with open('stats', 'r') as fi:
    data = fi.read()

data = data.split('\n')
data = data[:-1]

x = []
y1 = []
y2 = []

for row in data:
    row = row.split(' ')
    
    m = int(row[0])
    n = int(row[1])

    t1 = float(row[2])
    t2 = float(row[3])

    x.append(m+n+m*n)
    y1.append(t1)
    y2.append(t2)

plt.xlabel('Input size')
plt.ylabel('Running time (in seconds)')
plt.plot(x, y1, label='Brute Force')
plt.plot(x, y2, label='Genetic Algortihm')
plt.legend()
plt.show()



with open('comps', 'r') as fi:
    data = fi.read()

data = data.split('\n')
data = data[:-1]

x = []
y1 = []
y2 = []
y3 = []

i = 0
for row in data:
    row = row.split(' ')

    x.append(i)
    i += 1
    y1.append(int(row[0]))
    y2.append(int(row[1]))
    y3.append(int(row[2]))


N = 200

plt.xlabel('Testcase #')
plt.ylabel('Cost')
plt.plot(x[:N], y1[:N], label='Best Cost')
plt.plot(x[:N], y2[:N], label='Worst Case')
plt.plot(x[:N], y3[:N], label='By GA')
plt.legend()
plt.show()

error = []
for i in range(len(x)):
    error.append(abs(y1[i]-y3[i])/y1[i])

import numpy as np

print(np.mean(error))

plt.xlabel('Testcase #')
plt.ylabel('Error')
plt.plot(x[:N], error[:N])
plt.show()

