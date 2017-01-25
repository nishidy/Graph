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

    def __lt__(self,target):
        return self.cost < target.cost

    def __eq__(self,target):
        return self.cost == target.cost

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

    def updatemannode(self,tonodeid,cost,fromnodeid):
        self.mannodes[tonodeid].cost = cost
        self.mannodes[tonodeid].fromnodeid = fromnodeid

    def solve(self,start,goal):
        self.start = start
        self.goal = goal

        print("{0} ---> {1}".format(start,goal))

        self.initmannode()
        self.updatemannode(self.start,0,-1)
        heappush(self.heap, self.mannodes[self.start])

        togoalcost = 0
        while len(self.heap) > 0:
            try:
                mannode = heappop(self.heap)
            except Exception as e:
                print(len(self.heap),self.heap[:10])
                raise e
            cost = mannode.cost
            nodeid = mannode.node.no
            if mannode.done:
                continue
            if nodeid == self.goal:
                togoalcost = cost
                break
            for tonodeid,edgecost in mannode.node.edges.items():
                newcost = cost + edgecost
                tonodecost = self.mannodes[tonodeid].cost
                if newcost < tonodecost:
                    self.updatemannode(tonodeid,newcost,nodeid)
                    heappush(self.heap,self.mannodes[tonodeid])

        print("cost :", togoalcost)

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
        print("path :", reduce(lambda a,b: "{0} -> {1}".format(a,b), path))


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

