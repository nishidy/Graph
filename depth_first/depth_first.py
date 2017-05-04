import sys
from functools import reduce

class Node:
    def __init__(self,node_id):
        self.node_id=node_id
        self.to_nodes = {}
        self.visited = False

class Graph:
    def __init__(self,start,goal):
        self.start=start
        self.goal=goal
        self.nodes = {}

    def create_node(self,node_id):
        if node_id not in self.nodes:
            self.nodes[node_id] = Node(node_id)

    def add_to_node(self,fr,to,cost):
        self.nodes[fr].to_nodes[to] = cost

    def search(self):
        print(self.start," --->", self.goal)
        best = []
        print("cost : ",self.do_search(start,0,1<<31,[],best))
        print("path : ",reduce(lambda a,b:str(a)+" -> "+str(b),best))

    def do_search(self,node_id,cost,min_cost,path,best):
        path.append(node_id)
        if node_id == self.goal:
            if cost<min_cost:
                min_cost=cost
                best[:]=path.copy()
            return min_cost
        #print(path)
        self.nodes[node_id].visited=True
        for next_ in self.nodes[node_id].to_nodes.items():
            next_id   = next_[0]
            next_cost = cost+next_[1]
            if self.nodes[next_id].visited:
                continue
            min_cost = self.do_search(next_id,next_cost,min_cost,path.copy(),best)
        self.nodes[node_id].visited=False
        return min_cost

num_nodes,num_edges=map(lambda x:int(x),input().split())
start,goal=map(lambda x:int(x),input().split())

graph=Graph(start,goal)
for n in range(num_edges):
    fr,to,cost=map(lambda x:int(x),input().split())
    graph.create_node(fr)
    graph.create_node(to)
    graph.add_to_node(fr,to,cost)

graph.search()

