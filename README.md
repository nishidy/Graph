#Purpose
Try several algorithms about searching path in graph.  
Easy to generate graph by generate_graph.  
Possible to reproduce the same graph by passing the 4th argument as random seed. (Note that 0 makes it really random using time(NULL).)  

```
$ ./generate_graph
./generate_graph: num_nodes num_edges(>=num_nodes-1) cost_power rand_seed(0 means time(NULL))

$ ./generate_graph 1000 2000 100 0 | time -p ./dijkstra_cpp
[Dijkstra search]

Min cost is 1287 (0->1->2->3->4->5->6->7->8->9->10->430->798->882->964->975->993->999).
real         0.07
user         0.06
sys          0.00
$ ./generate_graph 1000 2000 100 0 | time -p ./dijkstra_cpp
[Dijkstra search]

Min cost is 2637 (0->1->2->3->4->5->6->7->8->9->10->11->12->13->14->15->16->17->18->19->20->21->22->23->24->25->512->560->936->984->999).
real         0.08
user         0.08
sys          0.00
$ ./generate_graph 1000 2000 100 10 | time -p ./dijkstra_cpp
[Dijkstra search]

Min cost is 743 (0->1->2->3->4->5->555->782->967->999).
real         0.06
user         0.06
sys          0.00
$ ./generate_graph 1000 2000 100 10 | time -p ./dijkstra_cpp
[Dijkstra search]

Min cost is 743 (0->1->2->3->4->5->555->782->967->999).
real         0.06
user         0.05
sys          0.00

```

