import sys
from heapq import *
from functools import reduce

class Node:

     def __init__(self,fromnodeid):
        self.no = fromnodeid
        self.edges = {}

class Graph:

    def __init__(self):
        self.nodes = {}

    def addnode(self,nodeid):
        if nodeid not in self.nodes:
            self.nodes[nodeid] = Node(nodeid)

    def addedge(self,fromnodeid,tonodeid,cost):
        self.nodes[fromnodeid].edges[tonodeid] = cost

class ManageNode:

    def __init__(self,node):
        self.node = node
        self.done = False
        self.cost = 1 << 30
        self.fromnodeid = -1

class Dijkstra(Graph):

    def __init__(self):
        super().__init__()
        self.start = 0
        self.goal= 0
        self.heap = []
        self.mannodes = {}

    def initmannode(self):
        for nodeid,node in self.nodes.items():
            self.mannodes[nodeid] = ManageNode(node)

    def solve(self,start,goal):
        self.start = start
        self.goal = goal

        print("{0} ---> {1}".format(start,goal))

        self.initmannode()
        heappush( self.heap, (0,self.mannodes[self.start]) )

        togoalcost = 0
        while len(self.heap) > 0:
            (cost,mannode) = heappop(self.heap)
            nodeid = mannode.node.no
            if mannode.done:
                continue
            if nodeid == self.goal:
                togoalcost = cost
                break
            for tonode,edgecost in mannode.node.edges.items():
                newcost = cost + edgecost
                tonodecost = self.mannodes[tonode].cost
                if newcost < tonodecost:
                    heappush(self.heap,(newcost,self.mannodes[tonode]))
                    self.mannodes[tonode].cost = newcost
                    self.mannodes[tonode].fromnodeid = nodeid

        print("cost : ", togoalcost)

    def show_path(self):
        path = []
        nodeid = self.goal
        while True:
            path.append(nodeid)
            if nodeid == self.start:
                break
            mannode = self.mannodes[nodeid]
            nodeid = mannode.fromnodeid

        path.reverse()
        print("path : ", reduce(lambda a,b: "{0} -> {1}".format(a,b), path))

def getlineno(fname):
    lineno = 1
    for line in open(sys.argv[1]):
        yield lineno, line
        lineno += 1

graph = Dijkstra()
if len(sys.argv) == 2:
    for lineno, line in getlineno(sys.argv[1]):
        if lineno == 1:
            numnode,numedge = map(lambda x: int(x),line.split())
        if lineno == 2:
            start,goal = map(lambda x: int(x),line.split())
            graph = Dijkstra(start,goal)
        if lineno > 2:
            fromnodeid,tonodeid,edgecost = map(lambda x: int(x),line.split())
            graph.addnode(fromnodeid)
            graph.addnode(tonodeid)
            graph.addedge(fromnodeid,tonodeid,edgecost)
else:
    numnode,numedge= map(lambda x: int(x), input().split())
    start,goal= map(lambda x: int(x), input().split())
    for n in range(numedge):
        fromnodeid,tonodeid,edgecost = map(lambda x: int(x),input().split())
        graph.addnode(fromnodeid)
        graph.addnode(tonodeid)
        graph.addedge(fromnodeid,tonodeid,edgecost)

graph.solve(start,goal)
graph.show_path()

