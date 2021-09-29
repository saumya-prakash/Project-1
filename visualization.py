'''This program used dash

Refer: https://towardsdatascience.com/visualizing-networks-in-python-d70f4cbeb259
'''


import dash
import visdcc
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output, State
import random
import pandas as pd


n = 0   # to store the number of nodes

df = pd.read_csv('edges.csv', sep=' ')
edges = []
for _, row in df.iterrows():
    u = row['From']
    v = row['To']
    wt = row['Weight']

    n = max(n, max(u, v))

    about = about = {'from':u, 'to':v, 'width':2,}
    edges.append(about)
    
n += 1
n = int(n)


nodes = []

for i in range(n):
    color= 'black'
    if random.random() <= 0.25:
        color = 'red'
    about = {'id': i, 'label':i, 'shape':'dot', 'size':5, 'color':color,}
    nodes.append(about)



# Create the DASH app
app = dash.Dash()
app.layout = html.Div([
    visdcc.Network(id='roads', data={'nodes':nodes, 'edges':edges}, 
    options = dict(height= '800px', width= '100%')),
])


# Run the app
app.run_server(debug=True)