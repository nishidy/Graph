# -*- encoding:utf-8

import sys
import math

heap=[]
heapn=0

def heap_push(i):
	global heapn

	c=heapn
	p=(heapn-1)/2

	if len(heap)<=heapn:
		heap.append(i)
	else:
		heap[heapn]=i

	while p>=0:
		if heap[p]>=i:
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
				if heap[itob*2+1]<heap[itob*2+2]:

					# in case the value of child is smaller than parent
					if heap[itob*2+1]<heap[itob]:

						# exchange the value between parent and child
						heap[itob],heap[itob*2+1]=heap[itob*2+1],heap[itob]
						cexc+=1
						itob=itob*2+1 # Go down to this child

					else:
						break

				else:

					# in case the value of child is smaller than parent
					if heap[itob*2+2]<heap[itob]:

						# exchange the value between parent and child
						heap[itob],heap[itob*2+2]=heap[itob*2+2],heap[itob]
						cexc+=1
						itob=itob*2+2 # Go down to this child

					else:
						break

			# in case of only a child of itob exist
			elif itob*2+1<heapn:

				# in case the value of child is smaller than parent
				if heap[itob*2+1]<heap[itob]:

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
	print "Popped %d (%d times exchanged)."%(rootv,cexc)

def heap_show(n):
	if n==0: print "Show the heap tree."
	if heapn<=n: return
	print "    "*(int(math.log(n+1,2))-1)+("└---" if n>0 else "")+"%d"%heap[n]
	heap_show(n*2+1)
	heap_show(n*2+2)

for i in map(lambda x:int(x),sys.argv[1:]):
	heap_push(i)

heap_show(0)

while True:
	print "Want to (pop/push/show/stop)? : ",
	v=sys.stdin.readline().rstrip()
	print "\r",
	if v=="pop":
		heap_pop()
	elif v=="push":
		v=sys.stdin.readline().rstrip()
		heap_push(int(v))
	elif v=="stop":
		break
	elif v=="show":
		heap_show(0)
	else:
		pass

print "Bye."
