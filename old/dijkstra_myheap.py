# -*- encoding:utf-8

import sys
import math

heap=[0]
heapn=0

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


def heap_push(i):
	global heapn

	c=heapn
	p=(heapn-1)/2

	if len(heap)<=heapn:
		heap.append(i)
	else:
		heap[heapn]=i

	while p>=0:
		if heap[p].co>=i.co:
			heap[p],heap[c]=i,heap[p]
		c=p
		p=(p-1)/2

	heapn+=1

def heap_pop():
	global heapn

	rootv=heap[0] # save the top value to pop out

	itor=heapn-1 # index to root from bottom
	vofi=heap[itor] # value of the index
	cexc=0 # the count of exchange

	while itor>0:
		itor=(itor-1)/2 # get parent's index

		heap[itor],vofi=vofi,heap[itor]
		# set the value of child to parent
		# save the value of parent to vofi
		cexc+=1

		itob=itor # index to bottom from itor

		while itob<heapn:

			# in case both children of itob exist
			if itob*2+2<heapn:

				# choose smaller child to exchange the value
				if heap[itob*2+1].co<heap[itob*2+2].co:

					# in case the value of child is smaller than parent
					if heap[itob*2+1].co<heap[itob].co:

						# exchange the value between parent and child
						heap[itob],heap[itob*2+1]=heap[itob*2+1],heap[itob]
						cexc+=1
						itob=itob*2+1 # Go down to this child

					else:
						break

				else:

					# in case the value of child is smaller than parent
					if heap[itob*2+2].co<heap[itob].co:

						# exchange the value between parent and child
						heap[itob],heap[itob*2+2]=heap[itob*2+2],heap[itob]
						cexc+=1
						itob=itob*2+2 # Go down to this child

					else:
						break

			# in case of only a child of itob exist
			elif itob*2+1<heapn:

				# in case the value of child is smaller than parent
				if heap[itob*2+1].co<heap[itob].co:

					# exchange the value between parent and child
					heap[itob],heap[itob*2+1]=heap[itob*2+1],heap[itob]
					cexc+=1
					itob=itob*2+1 # Go down to this child

				else:
					break

			# in case of no child of itob exist
			else:
				break

	heapn-=1
	return rootv

def heap_show(n):
	if n==0: print "Show the heap tree."
	if heapn<=n: return
	print "    "*(int(math.log(n+1,2))-1)+("└---" if n>0 else "")+"%d(%d)"%(heap[n].n,heap[n].co)
	heap_show(n*2+1)
	heap_show(n*2+2)


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
	edges[to].append(Edge(to,fr,co))

line=sys.stdin.readline().split()
st=int(line[0])
go=int(line[1])

if st not in edges or go not in edges:
	sys.exit(1)

print "[Shortest path search by dijkstra algorithm]\n"

nodes[st].co=0
heap_push(Node_in_q(st,0))

df=False
if len(sys.argv)>1 and int(sys.argv[1])==1: df=True

while not heapn==0:
	frn=heap_pop() # from node

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
			heap_push(Node_in_q(ed.to,frn.co+ed.co))

print "Min cost is %d (%s)."%(frn.co,debug())

