#Purpose
Implementation of algorithms about searching paths in a network graph.  
It makes it easy to generate a network graph by running generate_graph.  
It is possible to reproduce the same graph by passing the 4th argument to generate_graph as random seed. (Note that 0 makes it really random using time(NULL).)  
dijkstra.java is actually faster than dijkstra.cpp with large values because dijkstra.java uses HashMap to find a node while dijkstra.cpp still uses loop to find it.  
dijsktra.py is using library for PriorityQueue while dijsktra_myheap.py is not using it but my own heap tree implementation.

#Execution result

## How to use generate_graph
```
$ ./generate_graph 
./generate_graph: num_nodes num_edges(>=num_nodes-1) cost_power rand_seed(0 means time(NULL))
```

## Solving shortest path problem
```
$ ./generate_graph 10 15 100 1
15
0 1 133
1 2 120
2 3 76
3 4 110
4 5 151
5 6 86
6 7 47
7 8 74
8 9 137
0 5 110
2 4 137
6 9 58
1 6 132
0 3 63
4 9 80
0 9

$ ./generate_graph 10 15 100 1 | time -p ./dijkstra_cpp 1
[Shortest path search by dijkstra algorithm]

0 (0)
0->3 (63)
0->5 (110)
0->1 (133)
0->3->2 (139)
0->3->4 (173)
0->5->6 (196)
0->5->6->7 (243)
0->3->4->9 (253)
Min cost is 253 (0->3->4->9).
real         0.00
user         0.00
sys          0.00
$ ./generate_graph 10 15 100 1 | time -p ./depth_first 1
[Shortest path search by depth first algorithm]

0(0)
->1(133)
->->2(253)
->->->3(329)
->->->->4(439)
->->->->->5(590)
->->->->->->6(676)
->->->->->->->7(723)
->->->->->->->->8(797)
->->->->->->->->->9(934)//
->->->->->->->9(734)//
->->->->->9(519)//
->->->4(390)
->->->->3(500)
->->->->9(470)//
->->6(265)
->->->5(351)
->->->7(312)
->->->->8(386)
->->->9(323)//
->5(110)
->->4(261)
->->6(196)
->->->7(243)
->->->->8(317)
->->->9(254)//
->3(63)
->->2(139)
->->4(173)
->->->9(253)//
Min cost is 253 (0->3->4->9).
real         0.00
user         0.00
sys          0.00
$ ./generate_graph 10 15 100 1 | time -p python dijkstra.py 1
[Shortest path search by dijkstra algorithm]

0 (0)
0->3 (63)
0->5 (110)
0->1 (133)
0->3->2 (139)
0->3->4 (173)
0->5->6 (196)
0->5->6->7 (243)
0->3->4->9 (253)
Min cost is 253 (0->3->4->9).
real         0.03
user         0.01
sys          0.00
$ ./generate_graph 10 15 100 1 | time -p python dijkstra_myheap.py 1
[Shortest path search by dijkstra algorithm]

0 (0)
0->3 (63)
0->5 (110)
0->1 (133)
0->3->2 (139)
0->3->4 (173)
0->5->6 (196)
0->5->6->7 (243)
0->3->4->9 (253)
Min cost is 253 (0->3->4->9).
real         0.03
user         0.01
sys          0.01
$ ./generate_graph 10 15 100 1 | time -p java dijkstra
[Shortest path search by dijkstra algorithm]

Min cost is 253 (0->3->4->9)
real         0.10
user         0.08
sys          0.02

$ ./generate_graph 100 1000 100 10 | time -p ./dijkstra_cpp
[Shortest path search by dijkstra algorithm]

Min cost is 154 (0->92->86->99).
real         0.01
user         0.00
sys          0.00
$ ./generate_graph 100 1000 100 10 | time -p ./depth_first
[Shortest path search by depth first algorithm]

Min cost is 154 (0->92->86->99).
real         0.19
user         0.19
sys          0.00
$ ./generate_graph 100 1000 100 10 | time -p java dijkstra
[Shortest path search by dijkstra algorithm]

Min cost is 154 (0->92->86->99)
real         0.13
user         0.13
sys          0.02
$ ./generate_graph 100 1000 100 10 | time -p python dijkstra.py
[Shortest path search by dijkstra algorithm]

Min cost is 154 (0->92->86->99).
real         0.03
user         0.02
sys          0.01
$ ./generate_graph 100 1000 100 10 | time -p python dijkstra_myheap.py
[Shortest path search by dijkstra algorithm]

Min cost is 154 (0->92->86->99).
real         0.03
user         0.02
sys          0.00
```
### With large values
```
$ ./generate_graph 10000 20000 10000 999 | time -p ./dijkstra_cpp
[Shortest path search by dijkstra algorithm]

Min cost is 133499 (0->1->2->3->4->5->6->7->8->9->10->7025->7026->7027->1493->8759->5909->9999).
real         4.63
user         4.62
sys          0.00

$ ./generate_graph 10000 20000 10000 999 | time -p java dijkstra
[Shortest path search by dijkstra algorithm]

Min cost is 133499 (0->1->2->3->4->5->6->7->8->9->10->7025->7026->7027->1493->8759->5909->9999)
real         1.20
user         0.78
sys          0.07

$ ./generate_graph 10000 20000 10000 999 | time -p python dijkstra.py
[Shortest path search by dijkstra algorithm]

Min cost is 133499 (0->1->2->3->4->5->6->7->8->9->10->7025->7026->7027->1493->8759->5909->9999).
real         1.31
user         0.48
sys          0.04
$ ./generate_graph 10000 20000 10000 999 | time -p python dijkstra_myheap.py
[Shortest path search by dijkstra algorithm]

Min cost is 133499 (0->1->2->3->4->5->6->7->8->9->10->7025->7026->7027->1493->8759->5909->9999).
real         1.31
user         0.47
sys          0.04
```

## Solving maximum flow problem
```
$ ./generate_graph 10 15 100 1 | time -p ./fordfulkerson 1
[Maximum flow search by ford fulkerson algorithm]

0->1->2->3->4->5->6->7->8->9:47
0->1->2->3->4->5->6->9:29
0->1->2->4->5->6->9:10
0->1->2->4->9:34
0->1->6->5->4->9:13
0->3->2->1->6->5->4->9:33
0->3->2->1->6->9:19
Max flow is 185.
real         0.00
user         0.00
sys          0.00

$ ./generate_graph 100 1000 100 10 | time -p ./fordfulkerson
[Maximum flow search by ford fulkerson algorithm]

Max flow is 217.
real         0.06
user         0.06
sys          0.00
```

### With large values
```
$ ./generate_graph 10000 20000 10000 999 | time -p ./fordfulkerson
[Maximum flow search by ford fulkerson algorithm]

Max flow is 465.
real         1.02
user         0.26
sys          0.02
```

## Heap binary tree (my own implementation)
```
$ python myheap.py $(seq 200 3 220) $(seq 50 7 90) $(seq 10 5 20)
Show the heap tree.
10
└---20
    └---57
        └---200
            └---209
        └---203
    └---64
        └---212
        └---71
└---15
    └---85
        └---215
        └---206
    └---50
        └---218
        └---78
Want to (pop/push/show/stop)? : pop
Popped 10 (5 times exchanged).
Want to (pop/push/show/stop)? : show
Show the heap tree.
15
└---57
    └---200
        └---209
        └---203
    └---64
        └---212
        └---71
└---20
    └---85
        └---215
        └---206
    └---50
        └---218
        └---78
Want to (pop/push/show/stop)? : push
199
Want to (pop/push/show/stop)? : show
Show the heap tree.
15
└---57
    └---199
        └---200
            └---209
        └---203
    └---64
        └---212
        └---71
└---20
    └---85
        └---215
        └---206
    └---50
        └---218
        └---78
Want to (pop/push/show/stop)? : push
500
Want to (pop/push/show/stop)? : show
Show the heap tree.
15
└---57
    └---199
        └---200
            └---209
            └---500
        └---203
    └---64
        └---212
        └---71
└---20
    └---85
        └---215
        └---206
    └---50
        └---218
        └---78
Want to (pop/push/show/stop)? : pop
Popped 15 (9 times exchanged).
Want to (pop/push/show/stop)? : pop
Popped 20 (9 times exchanged).
Want to (pop/push/show/stop)? : pop
Popped 50 (3 times exchanged).
Want to (pop/push/show/stop)? : show
Show the heap tree.
57
└---71
    └---203
        └---500
        └---209
    └---199
        └---212
        └---200
└---64
    └---85
        └---215
        └---206
    └---78
        └---218
Want to (pop/push/show/stop)? : stop
Bye.
```
