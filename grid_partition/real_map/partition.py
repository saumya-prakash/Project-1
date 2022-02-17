import numpy as np
from sklearn.metrics.pairwise import haversine_distances
from math import radians

class GridPartition:
    
    def __init__(self, _n, _coord, _demands):
        self.n = _n
        self.coord = _coord
        self.demands = _demands
        
        
        self.limit = -1 # no limit set initially
        self.range = 9999999    # range of a typical EV 
        self.color = ['#000000'] * _n   # all the nodes are black initially
        self.components = []    # will contain the partitions as a list of lists
        self.arr = []   # will be used while partitioning


    def totalDemand(self):
        return np.sum(self.demands)

    def setLimit(self, _a):
        self.limit = _a

    def setRange(self, _a):
        self.range = _a

    
    def __sub_demand(self, aux):

        tmp = 0
        for i in aux:
            tmp += self.demands[i]
        
        return tmp


    def __length(self, aux):
        
        # find the minimum longitude
        a = self.coord[aux[0]][1]
        for i in aux:
            a = min(a, self.coord[i][1])
        
        # find the maximum longitude
        b = a
        for i in aux:
            b = max(b, self.coord[i][1])

        return b-a


    def __breadth(self, aux):

        # find the minimum latitude
        a = self.coord[aux[0]][0]
        for i in aux:
            a = min(a, self.coord[i][0])

        # find the maximum latitude
        b = a
        for i in aux:
            b = max(b, self.coord[i][0])

        return b-a


    def __get_run_sum(self, aux):

        res = []

        s = self.demands[aux[0]]
        res.append(s)

        for i in range(1, len(aux)):
            s += self.demands[aux[i]]
            res.append(s)

        return res


    def __distance(self, a, b):
        '''This function returns distance between 2 lat-long pairs using the Haversine distance formula'''
        c = list(map(radians, a))
        d = list(map(radians, b))

        res = haversine_distances([c, d]) * (6378100/1000) # in km

        return res[0][1]


    def __diagonalLength(self, aux):

        # left top-most point
        p1 = self.coord[aux[0]]

        for i in aux:
            pt = self.coord[i]

            if pt[0] < p1[0]:
                p1 = pt
            
            elif pt[1] > p1[1]:
                p1 = pt


        # right bottom-most point  
        p2 = p1

        for i in aux:
            pt = self.coord[i]

            if pt[0] > p2[0]:
                p2 = pt
            
            elif pt[1] < p2[1]:
                p2 = pt

        return self.__distance(p1, p2)




    def __aux_partition(self, st, end):
        
        # focus on nodes in range arr[st:end]

        if st >= end:
            print("st >= end passed")
            return

        # first calculate the demand of this range
        d = self.__sub_demand(self.arr[st:end])

        if d <= self.limit: # this partition is fine
            
            # do the range-check
            ## estimate from diagonals
            dia = self.__diagonalLength(self.arr[st:end])
            
            if dia > self.range      and False:
                print(dia, "Range partitioning needed")
                # find the 'length'
                t1 = self.__length(self.arr[st:end])
                # find the 'breadth'
                t2 = self.__breadth(self.arr[st:end])

                if t1 >= t2:
                    # do partition parallel to longitudes
                    ## sort the points longitude-wise
                    tmp = self.arr[st:end]
                    tmp.sort(key=lambda x: self.coord[x][1])
                    self.arr[st:end] = tmp
                    
                else:
                    # partition parallel to latitudes
                    ## sort the points latitude-wise
                    tmp = self.arr[st:end]
                    tmp.sort(key=lambda x: self.coord[x][0])
                    self.arr[st:end] = tmp

                low = st
                high = end-1
                mid = low + int((high-low)/2)

                self.__aux_partition(st, mid+1)
                self.__aux_partition(mid+1, end)

            else:
                self.components.append(self.arr[st:end])

            return
        

        # otherwise, we need to refine this partition

        # find the 'length'
        t1 = self.__length(self.arr[st:end])
        # find the 'breadth'
        t2 = self.__breadth(self.arr[st:end])

        if t1 >= t2:
            # do partition parallel to longitudes
            ## sort the points longitude-wise
            tmp = self.arr[st:end]
            tmp.sort(key=lambda x: self.coord[x][1])
            self.arr[st:end] = tmp
            
        else:
            # partition parallel to latitudes
            ## sort the points latitude-wise
            tmp = self.arr[st:end]
            tmp.sort(key=lambda x: self.coord[x][0])
            self.arr[st:end] = tmp

        run_dem_sum = self.__get_run_sum(self.arr[st:end])
        
        ind = -1
        low = st
        high = end-1

        while low <= high:

            mid = low + int((high-low)/2)

            t = run_dem_sum[mid-st]
            
            if t == self.limit:
                ind = mid
                break
            
            elif t < self.limit:
                ind = mid
                low = mid+1
            
            else:
                high = mid-1


        if ind == -1:
            print(st, end)
            raise ("Couldn't find a suitable point")


        self.__aux_partition(st, ind+1)
        self.__aux_partition(ind+1, end)
        
        return
    


    def partition(self):
        self.components = []    # clear previous partitioning results, if any
        self.arr = []

        for i in range(self.n):
            self.arr.append(i)

        # call an auxiliary function
        self.__aux_partition(0, self.n)


    def colorPartitions(self):
        palatte = ['red', 'blue', 'yellow', 'green', 'orange', 'cyan', 'pink', 'magenta', 'brown', 'black', 'gold', 'silver', 'platinum']
        
        a = 0

        for arr in self.components:
            for i in arr:
                self.color[i] = palatte[a]
            a += 1

        return
    