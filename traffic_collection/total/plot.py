from matplotlib import pyplot as plt
from datetime import datetime


def plot_total_traffic_level(filename):

    x = []  # to store the x coordinates
    y = []  # to store the y coordinates
    
    i = 0
    with open(filename, 'r') as fi:
        for line in fi.readlines():
            line = line[:-1]
            line = line.split(' ')

            a = datetime.strptime(line[0], "%H:%M:%S")

            x.append(a)
            i += 1
            y.append(float(line[1]))
            
    

    fig, ax = plt.subplots()

    ax.set_xlabel('Time')
    ax.set_ylabel('Traffic Level')

    # ax.set_xticklabels([])


    plt.plot(x, y)

    plt.show()
    

    

if __name__ == '__main__':
    plot_total_traffic_level('28.687203816391193, 77.04710350388676_28.547244344345092, 77.41867712678446_2022-03-25')
