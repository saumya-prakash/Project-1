# A small helper script to visualise things

import matplotlib.pyplot as plt

i = 0
x = []
h = []
w = []
bar_color = []
flag = 0

with open('space.txt', 'r') as fi:
    for a in fi.readlines():

        a = float(a[:-1])

        if 513.733479 <= a and flag == 0:
            flag = 1
            h.append(513.733479)
            x.append(i)
            w.append(5)
            bar_color.append('red')
            i += 1


        h.append(a)
        x.append(i)
        w.append(0.5)
        bar_color.append('black')
        i += 1



plt.bar(x, h, width=w, color=bar_color)
# plt.bar(1, 100)
plt.show()
