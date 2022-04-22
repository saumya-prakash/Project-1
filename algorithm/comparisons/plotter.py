# reads the 'stats' and the 'comps' file, and plots graphs

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

    t1 = float(row[2])  # time vale in seconds
    t2 = float(row[3])  # time value in seconds

    x.append(m+n+m*n)
    y1.append(t1)
    y2.append(t2)


plt.xlabel('Input size')
plt.ylabel('Running time (in seconds)')
plt.plot(x, y1, label='Brute Force')
plt.plot(x, y2, label='Genetic Algortihm')
plt.legend()
plt.savefig('running_time.png')
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
    y1.append(float(row[0]))
    y2.append(float(row[1]))
    y3.append(float(row[2]))


N = 200

plt.xlabel('Testcase #')
plt.ylabel('Cost')
plt.plot(x[:N], y1[:N], label='Best Cost')
plt.plot(x[:N], y2[:N], label='Worst Case')
plt.plot(x[:N], y3[:N], label='By GA')
plt.legend()
plt.savefig('comparison_with_brute_force.png')
plt.show()


rel_dist = []
for i in range(len(x)):
    rel_dist.append(100 - (y3[i]-y1[i])*100/(y2[i]-y1[i]))


plt.xlabel('Testcase #')
plt.ylabel('Relative distance')
plt.plot(x[:N], rel_dist[:N])
plt.legend()
plt.savefig('relative_distance.png')
plt.show()


error = []
for i in range(len(x)):
    error.append(abs(y1[i]-y3[i])/y1[i])


import numpy as np

print('average relative distance =', np.mean(rel_dist), '%')
print('minimum =', np.min(error))
print('maximum =', np.max(error))
print('mean =', np.mean(error))
print('std =', np.std(error))
print('0.25 quantile =', np.quantile(error, 0.25))
print('0.50 quantile =', np.quantile(error, 0.50))
print('0.75 quantile =', np.quantile(error, 0.75))


plt.xlabel('Testcase #')
plt.ylabel('Error')
plt.plot(x[:N], error[:N])
plt.savefig('error.png')
plt.show()

