#Purpose
Try several algorithms about searching path in graph.  
Easy to generate graph by genrate_graph.  
Possible to reproduce the same path by passing the 4th argument as random seed. (Note that 0 makes it really random using time(NULL).)  

```
$ ./generate_graph
./generate_graph: num_nodes num_edges(>=num_nodes-1) cost_power rand_seed(0 means time(NULL))
$ time ./generate_graph 100 100 100 100 | ./dijkstra_cpp
[Dijkstra search]  

Min cost is 5533 (0->38->39->40->41->42->43->44->45->46->47->48->49->50->51->52->53->54->55->56->57->58->59->60->61->62->63->64->65->66->67->68->69->70->71->72->73->74->75->76->77->78->79->80->81->82->83->84->85->86->87->88->89->90->91->92->93->94->95->96->97->98->99).

real	0m0.008s
user	0m0.005s
sys	0m0.004s
```

