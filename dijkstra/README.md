```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | python dijkstra/dijkstra.py
0 ---> 19
cost : 12873
path : 0 -> 17 -> 1 -> 13 -> 19
```

```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | ruby dijkstra/dijkstra.rb 
0 ---> 19
cost : 12873
path : 0 -> 17 -> 1 -> 13 -> 19
```

```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | dijkstra/dijkstra
cost : 12873
path : 0 -> 17 -> 1 -> 13 -> 19
```

```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | dijkstra/dijkstra_rs
cost : 12873
path : 0 -> 17 -> 1 -> 13 -> 19

```
