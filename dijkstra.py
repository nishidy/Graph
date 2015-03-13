import sys
import Queue

class Edge:
	def __init__(self,fr,to,co):
		self.fr=fr
		self.to=to
		self.co=co

	def __cmp__(self,ot):
		return cmp(self.co,ot.co)

class Node:
	def __init__(self,n,co):
		self.n=n
		self.co=co

nedge=int(sys.stdin.readline())

edges={}
for _ in range(nedge):
	line=sys.stdin.readline().split()
	fr=int(line[0])
	to=int(line[1])
	co=int(line[2])

	if fr not in edges:
		edges[fr]=[]
	edges[fr].append(Edge(fr,to,co))

	if to not in edges:
		edges[to]=[]
	edges[to].append(Edge(fr,to,co))


line=sys.stdin.readline().split()
st=int(line[0])
go=int(line[1])

if st not in edges or go not in edges:
	sys.exit(1)

qu=Queue.PriorityQueue()
qu.put(Node(st,0))
fix=[]
while not qu.empty():
	node=qu.get()
	if node.n in fix: continue
	fix.append(node.n)
	if node.n==go: break
	for ed in edges[node.n]:
		qu.put(Node(ed.to,ed.co+node.co))

print node.co

