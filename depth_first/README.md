```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | depth_first/depth_first 
0 ---> 19
cost : 12873
path : 0 -> 17 -> 1 -> 13 -> 19
```

```
$ ./tools/generate_graph_v2 20 100 0 19 10000 | python depth_first/depth_first.py 
0  ---> 19
cost :  12873
path :  0 -> 17 -> 1 -> 13 -> 19
```
