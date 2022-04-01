import random
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import haversine_distances
from math import radians, log, exp
import numpy as np
import time


class Placement:
    
    def __find_x_extremes(self):
        
        for i in self.component:
            x_min = self.coord[i][1]
            x_max = x_min
            break
        
        for i in self.component:
            x_min = min(x_min, self.coord[i][1])
            x_max = max(x_max, self.coord[i][1])

        # print(x_min, x_max)
        return x_min, x_max


    def __find_y_extremes(self):

        for i in self.component:
            y_min = self.coord[i][0]
            y_max = y_min
            break
        
        for i in self.component:
            y_min = min(y_min, self.coord[i][0])
            y_max = max(y_max, self.coord[i][0])

        # print(y_min, y_max)
        return y_min, y_max


    def __init__(self, _graph, _coord, _demands):
        
        self.graph = _graph
        self.n = len(_graph)

        self.coord = _coord
        self.demands = _demands
        self.component = list()

        # self.x_min, self.x_max = self.__find_x_extremes()
        # self.y_min, self.y_max = self.__find_y_extremes()

        self.bru_long = -1
        self.bru_lat = -1

        self.gen_long = -1
        self.gen_lat = -1


    def setComponent(self, _a):
        self.component = _a


    def __distance(self, a, b):
            '''This function returns distance between 2 lat-long pairs using the Haversine distance formula'''
            c = list(map(radians, a))
            d = list(map(radians, b))

            res = haversine_distances([c, d]) * (6378100/1000) # in km

            return res[0][1]


    def __objective_function(self, x):

        total = 0

        for b in self.component:
            y = self.coord[b]
            total += self.__distance(x, y)/self.demands[b]
        
        return -log(1/total)


    def __plot_points(self, arr):
        fig = plt.figure()
        plt.grid(False)
        plt.axis('off')
        # plt.title('First')
        # # plot the sub-graph
        # for u in self.component:
        #     for v, _ in self.graph[u]:
        #         if v in self.component:
        #             lats = [self.coord[u][0], self.coord[v][0]]
        #             longs = [self.coord[u][1], self.coord[v][1]]

        #             plt.plot(longs, lats, c='black', linewidth=0.5)

        # plot the points
        plt.scatter([a[1] for a in arr], [a[0] for a in arr], c='blue', s=4)

        if self.bru_lat != -1 and self.bru_long != -1:
            plt.scatter(self.bru_long, self.bru_lat, c='green', s=15)
        
        if self.gen_lat != -1 and self.gen_long != -1:
            plt.scatter(self.gen_long, self.gen_lat, c='red', s=15)

        # plt.savefig('initial_population.png')
        plt.show()



    def __mutate(self, offspring, x_min, x_max, y_min, y_max):
        
        offspring = list(offspring)

        if random.random() <= 0.5:
            delta_x = x_min - offspring[1]
        else:
            delta_x = x_max - offspring[1]

        if random.random() <= 0.5:
            delta_y = y_min - offspring[0]
        else:
            delta_y = y_max - offspring[0]
        
        alpha = 0.0001
        offspring[1] = (1-alpha)*offspring[1] + alpha*delta_x
        offspring[0] = (1-alpha)*offspring[0] + alpha*delta_y

        return tuple(offspring)



    def findLocation(self):

        # self.component = self.component[:100]
        print('Number of nodes =', len(self.component))

        start = time.time()

        # define initial population
        population = []

        x_min, x_max = self.__find_x_extremes()
        y_min, y_max = self.__find_y_extremes()

        # print(self.x_min, self.x_max, x_min, x_max)

        for _ in range(100):
            x = random.uniform(x_min, x_max)
            y = random.uniform(y_min, y_max)
            population.append((y, x))   # lat, long pushed into the population[]; don't change this order

        objective_value = []
        total = 0
        for x in population:
            a = self.__objective_function(x)
            objective_value.append(a)
            total += a        
                

        print('X-range:', x_max-x_min)
        print('Y-span:', y_max-y_min)

        cnt = 0

        # 100 iterations only
        for _ in range(200):

            ## The objecgtive values are too close. I suspect that the individuals are selected from the middle of
            # the population array[] most of the times!!!    

            # SELECT
            key = random.uniform(0, total)

            tmp = 0
            for i in range(len(objective_value)):
                tmp += objective_value[i]
                if tmp >= key:
                    ind1 = i
                    break
            
            key = random.uniform(0, total-objective_value[ind1])

            tmp = 0
            for i in range(len(objective_value)):
                
                if ind1 == i:
                    continue

                tmp += objective_value[i]
                if tmp >= key:
                    ind2 = i
                    break

            
            if(ind1 == ind2):
                print('same child selected twice in SELECTION')
                exit(1)

            print(ind1, ind2)

            child1 = population[ind1]
            child2 = population[ind2]

            offspring1 = (child1[0], child2[1])
            offspring2 = (child2[0], child1[1])

            # mutate(nudge)
            if random.random() <= 0.5:
                offspring1 = self.__mutate(offspring1, x_min, x_max, y_min, y_max)
                offspring2 = self.__mutate(offspring2, x_min, x_max, y_min, y_max)


            # print(offspring1, offspring2)
            if offspring1[1] < x_min or offspring1[1] > x_max or offspring1[0] < y_min or offspring1[0] > y_max:
                cnt += 1
                continue

            if offspring2[1] < x_min or offspring2[1] > x_max or offspring2[0] < y_min or offspring2[0] > y_max:
                cnt += 1            
                continue

            population.append(offspring1)
            a = self.__objective_function(offspring1)
            objective_value.append(a)
            total += a

            population.append(offspring2)
            a = self.__objective_function(offspring2)
            objective_value.append(a)
            total += a

        # end of for loop


        end = time.time()

        print('Total populatin size =', len(population))
        print('Number of invalid offsprings produced =', cnt)
        ind = np.argmax(objective_value)
        print('Best location:', population[i])
        print('Cost =', exp(objective_value[i]))
        print('Time taken =', end-start)

        self.gen_lat, self.gen_long = population[i]
        self.__plot_points(population)
        # self.__alt_plot_points(population)
        

    
    def bruteForce(self):
        '''This function finds the best node for placing the charging station usinf brute-force approach'''
        
        # self.component = self.component[:100]
        print('Number of nodes =', len(self.component))

        start = time.time()

        ind = self.component[0]
        cur_total = self.__objective_function(self.coord[ind])

        for i in self.component:
            
            tmp = self.__objective_function(self.coord[i])
            
            if tmp > cur_total:
                cur_total = tmp
                ind = i

        end = time.time()
        print('Best location:', self.coord[ind])
        print('Cost =', 1/cur_total)
        print('Time taken =', end-start)

        self.bru_lat, self.bru_long = self.coord[ind]


