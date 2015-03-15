#Purpose
Try several algorithms about searching path in graph.  
Easy to generate graph by generate_graph.  
Possible to reproduce the same graph by passing the 4th argument as random seed. (Note that 0 makes it really random using time(NULL).)  
dijkstra.java is actually faster than dijkstra.cpp with large values because dijkstra.java uses HashMap to find a node while dijkstra.cpp still uses loop to find it.

#Execution result

## How to use genera_grah
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
$ ./generate_graph 100 1000 100 10 | time -p java dijkstra
[Shortest path search by dijkstra algorithm]

Min cost is 154 (0->92->86->99)
real         0.13
user         0.13
sys          0.02
$ ./generate_graph 100 1000 100 10 | time -p ./depth_first
[Shortest path search by depth first algorithm]

Min cost is 154 (0->92->86->99).
real         0.19
user         0.19
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

## Heap binary tree
```
$ python dijkstra_heap.py $(seq 20 30) $(seq 10 15)
Show the heap tree.
10
└---14
    └---15
        └---21
            └---27
            └---23
        └---28
    └---24
        └---29
        └---30
└---11
    └---20
        └---25
        └---22
    └---12
        └---26
        └---13
Want to pop? (y/n): y
Popped 10.
Want to pop? (y/n): y
Popped 11.
Want to pop? (y/n): y
Popped 12.
Want to pop? (y/n): n
Show the heap tree.
13
└---14
    └---15
        └---21
        └---28
    └---24
        └---29
        └---30
└---13
    └---20
        └---25
        └---22
    └---13
        └---26
```
