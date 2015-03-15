# -*- encoding:utf-8

import sys
import math

heap=[]
heapn=0

def heap_push(i):
	global heapn

	if len(heap)==0:
		heap.append(i)
	else:
		c=heapn
		p=(heapn-1)/2

		heap.append(i)

		while True:
			if heap[p]>=i:
				heap[p],heap[c]=i,heap[p]
			if p==0: break
			c=p
			p=(p-1)/2
	heapn+=1

def heap_pop():
	global heapn

	t=heap[0]
	n=0
	while n*2+1<heapn:
		if n*2+2<heapn:
			if heap[n*2+1]<heap[n*2+2]:
				heap[n]=heap[n*2+1]
				n=n*2+1
			else:
				heap[n]=heap[n*2+2]
				n=n*2+2
		else:
			heap[n]=heap[n*2+1]
			n=n*2+1

	heapn-=1
	print "Popped %d."%t

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
	print "Want to pop? (y/n): ",
	v=sys.stdin.readline().rstrip()
	print "\r",
	if v=="y":
		heap_pop()
	elif v=="n":
		break
	else:
		pass

heap_show(0)

