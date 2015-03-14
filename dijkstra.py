import sys
import Queue

class Edge:
	def __init__(self,fr,to,co):
		self.fr=fr
		self.to=to
		self.co=co

class Node:
	def __init__(self,n):
		self.n=n # node id
		self.co=1<<30
		self.fn=-1 # from node (for debug)
		self.fix=False

class Node_in_q:
	def __init__(self,n,co):
		self.n=n
		self.co=co

	def __cmp__(self,o):
		return cmp(self.co,o.co)

nedge=int(sys.stdin.readline())

nodes={} # {node id:Node obj}
edges={} # {from node id:Edge obj}

for _ in range(nedge):
	line=sys.stdin.readline().split()
	fr=int(line[0])
	to=int(line[1])
	co=int(line[2])

	if fr not in nodes:
		nodes[fr]=Node(fr)

	if to not in nodes:
		nodes[to]=Node(to)

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

qu=Queue.PriorityQueue() # Node_in_q obj

nodes[st].co=0
qu.put(Node_in_q(st,0))

df=False
if len(sys.argv)>1 and int(sys.argv[1])==1: df=True

print "[Shortest path search by dijkstra algorithm]\n"

while not qu.empty():
	frn=qu.get() # from node

	def debug():
		nl=[]
		n=frn.n
		while n>-1:
			nl.append(nodes[n].n)
			n=nodes[n].fn
		if len(nl)>1:
			nl.reverse()
			return reduce(lambda x,y: str(x)+"->"+str(y),nl[1:],nl[0])
		else:
			return str(nl[0])

	if df: print "%s (%d)"%(debug(),frn.co)

	nodes[frn.n].fix=True
	if frn.n==go: break

	for ed in edges[frn.n]:
		if nodes[ed.to].fix: continue
		if frn.co+ed.co<nodes[ed.to].co:
			nodes[ed.to].co=frn.co+ed.co
			nodes[ed.to].fn=frn.n
			qu.put(Node_in_q(ed.to,frn.co+ed.co))

print "Min cost is %d (%s)."%(frn.co,debug())

