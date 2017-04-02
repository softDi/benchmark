#!/usr/bin/python

import sys, getopt
import pygraphviz as pgv
import networkx as nx
import matplotlib.pyplot as plt

Gtmp = pgv.AGraph(sys.argv[1])
G = nx.Graph(Gtmp)
nx.draw(G)
plt.show()
