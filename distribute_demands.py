'''This program computes actual demands from the extracted trafic levels.

Do some sort of demand-assignment to nodes - 
    equal distribution to 2 vertices
    inverse sqaure decay wave
    exponeential decay wave


Generates demands.csv file
'''



import pandas as pd



def equally_between_end_vertices():

    # Read in the edges.csv file
    edges = pd.read_csv('edges.csv', sep=' ')

    demand = dict()

    for row in edges.itertuples():

        _, u, v, length, traffic_level, name = row
        
        if u in demand:
            demand[u] += traffic_level/2
        else:
            demand[u] = traffic_level/2
        
        if v in demand:
            demand[v] += traffic_level/2
        else:
            demand[v] = traffic_level/2

    return demand



demand = equally_between_end_vertices()

print('Demands distributed successfully')

with open('demands.csv', 'w') as fi:
    print('Node_id', 'Demand', file=fi)
    for a in demand:
        print(a, demand[a], file=fi)


