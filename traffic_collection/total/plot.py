from matplotlib import pyplot as plt




def plot_total_traffic_level(filename):

    x = []  # to store the x coordinates
    y = []  # to store the y coordinates
    
    with open(filename, 'r') as fi:
        for line in fi.readlines():
            line = line[:-1]
            line = line.split(' ')

            x.append(line[0])
            y.append(line[1])
            

    fig, ax = plt.subplots()

    plt.plot(x, y)

    ax.set_xticklabels([])
    ax.set_ylabel('Traffic Level')

    plt.show()
    

    

if __name__ == '__main__':
    plot_total_traffic_level('28.687203816391193, 77.04710350388676_28.547244344345092, 77.41867712678446_2022-03-25')
