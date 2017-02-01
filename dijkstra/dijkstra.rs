use std::error::Error;
use std::env;
use std::fs::File;
use std::path::Path;
use std::io::prelude::*;
use std::collections::HashMap;
use std::io::BufReader;
use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::io;

type FromNode = i32;
type ToNode = i32;
type EdgeCost= i32;

#[derive(Clone,Eq,PartialEq)]
struct Node {
    id: i32,
    edges: HashMap<ToNode,EdgeCost>,
}

struct Graph {
    nodes: HashMap<FromNode,Box<Node>>,
}

impl Graph {
    fn add_node(&mut self,from_node:i32) {
        if !self.nodes.contains_key(&from_node) {
            let node = Box::new(Node{id:from_node, edges:HashMap::new()});
            self.nodes.insert(from_node,node); // move ownership of Box node?
        }
    }
   
    fn add_edge(&mut self,from_node:i32,to_node:i32,edge_cost:i32) {
        if self.nodes.contains_key(&from_node) {
            let node = self.nodes.get_mut(&from_node).unwrap();
            node.edges.insert(to_node,edge_cost);
        }
    }
}

#[derive(Clone,Eq,PartialEq)]
struct ManageNode {
    cost : i32,
    from : i32,
    done : bool,
    node : Box<Node>,
}

impl Ord for ManageNode {
    fn cmp(&self, other: &ManageNode) -> Ordering {
        other.cost.cmp(&self.cost)
    }
}

impl PartialOrd for ManageNode {
    fn partial_cmp(&self, other: &ManageNode) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Dijkstra {
    start : i32,
    goal : i32,
    graph : Graph, // Composition
    man_nodes: HashMap<FromNode,ManageNode>,
    heap_nodes: BinaryHeap<Box<ManageNode>>,
}

impl Dijkstra {
    fn new(start:i32, goal:i32, graph:Graph) -> Dijkstra {
        Dijkstra {
            start: start,
            goal: goal,
            graph: graph,
            man_nodes: HashMap::new(),
            heap_nodes: BinaryHeap::new(),
        }
    }

    fn init_man_nodes(&mut self){
        for (id,node) in &self.graph.nodes {
            self.man_nodes.insert(*id,ManageNode{cost:i32::max_value(),from:-1,done:false,node:node.clone()});
        }
    }

    fn enque_man_node(&mut self, id:&i32, cost:i32, from:i32){
        let mut man_node = self.man_nodes.get_mut(id).unwrap();
        man_node.cost = cost;
        man_node.from = from;
        self.heap_nodes.push(Box::new((*man_node).clone()));
    }

    fn solve(&mut self){

        self.init_man_nodes();
        let node = self.graph.nodes.get(&self.start).unwrap().clone();
        self.enque_man_node(&node.id,0,-1);

        let mut to_goal_cost = 0;
        while let Some(mut man_node) = self.heap_nodes.pop() {
            if man_node.done { continue }
            man_node.done = true;
            if man_node.node.id == self.goal {
                to_goal_cost = man_node.cost;
                break;
            }
            for (to_node, edge_cost) in &man_node.node.edges {
                let new_cost = man_node.cost + edge_cost;
                if new_cost < self.man_nodes.get(&to_node).unwrap().cost {
                    self.man_nodes.get_mut(&to_node).unwrap().cost = new_cost;
                    self.enque_man_node(&to_node,new_cost,man_node.node.id);
                }
            }
        }
        println!("cost : {}",to_goal_cost);
    }

    fn show_path(&self){
        let mut path:Vec<i32> = Vec::new();
        let mut id = self.goal;
        while id != self.start {
            path.push(id);
            let man_node = self.man_nodes.get(&id).unwrap();
            id = man_node.from;
        }
        path.push(self.start);
        path.reverse();
        println!("path : {}",path.iter().map(|x|x.to_string()).collect::<Vec<String>>().join(" -> "));
    }
}

fn main(){
    let args: Vec<String> = env::args().collect();

    let mut graph = Graph{nodes:HashMap::new()};
    let mut start = 0;
    let mut goal = 0;

    if args.len() == 2 {

        let path = Path::new(&args[1]);
        let file = match File::open(&path) {
            Err(why) => panic!("Couldn't open {}",why.description()),
            Ok(file) => file,
        };
    
        let buf = BufReader::new(file);
        for (line,n) in buf.lines().zip(1..) {
            let input:Vec<i32> = line.unwrap().split_whitespace().map(|x|x.parse::<i32>().unwrap()).collect();
            if n == 1 {
                let _ = input[0];
                let _ = input[1];
            }else if n == 2 {
                start = input[0];
                goal = input[1];
            }else if n > 2 {
                let from_node = input[0];
                let to_node = input[1];
                let edge_cost = input[2];
                graph.add_node(from_node);
                graph.add_node(to_node);
                graph.add_edge(from_node,to_node,edge_cost);
            }
        }

    } else {

        let stdin = io::stdin();
        for (line,n) in stdin.lock().lines().zip(1..) {
            let input:Vec<i32> = line.unwrap().split_whitespace().map(|x|x.parse::<i32>().unwrap()).collect();
            if n == 1 {
                let _ = input[0];
                let _ = input[1];
            }else if n == 2 {
                start = input[0];
                goal = input[1];
            }else if n > 2 {
                let from_node = input[0];
                let to_node = input[1];
                let edge_cost = input[2];
                graph.add_node(from_node);
                graph.add_node(to_node);
                graph.add_edge(from_node,to_node,edge_cost);
            }
        }

    }

    let mut dijkstra = Dijkstra::new(start,goal,graph);
    dijkstra.solve();
    dijkstra.show_path();

}

