#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;

typedef unsigned int UI;
typedef UI ID;
typedef UI COST;

class Node{

    public:

    ID id;
    bool depth_visited;
    unordered_map<ID,COST> to_nodes;

    Node(){}
    Node(ID id):id(id){}

};

class Graph{
    ID start, goal;
    unordered_map<ID,Node*> nodes;
    ID max_id;

    public:

    Graph(){}
    Graph(ID s, ID g):start(s), goal(g){}

    void create_node(ID id){
        if(nodes.find(id)==nodes.end()){
            nodes[max_id] = new Node(max_id);
            max_id++;
        }
    }

    void add_to_node(ID from, ID to, COST cost){
        //cout<<from<<to<<cost<<endl;
        Node* node = nodes[from];
        node->depth_visited = false;
        node->to_nodes[to] = cost;
    }

    void search(){
        vector<ID> path, best;
        cout << start << " ---> " << goal << endl;
        cout << "cost : " << do_search(start,0,1<<31,path,best) << endl;;
        cout << "path : ";
        for(auto node : best){
            cout << node;
            if(node!=best.back()){
                cout << " -> ";
            }
        }
        cout << endl;
    }

    // path is copied variable using as stack
    // while best is reference pointer
    COST do_search(ID id, COST cost, COST min, vector<ID> path, vector<ID>& best){
        path.push_back(id);

        if(id==goal){
            min = min<cost?min:cost;
            if(min==cost){
                best.clear();
                copy(path.begin(),path.end(),back_inserter(best));
            }

            /* debug
            for(auto node: path){
                cout << node;
                if(node!=path.back()){
                    cout << " -> ";
                }
            }
            cout << " : " << min << endl;
            */

            return min;
        }

        nodes[id]->depth_visited = true;
        for(auto next: nodes[id]->to_nodes){
            ID   next_id   = next.first;
            COST next_cost = cost+next.second;
            //cout<<id<<"->"<<next_id<<":"<<next_cost<<endl;
            if(nodes[next_id]->depth_visited){
                continue;
            }
            min = do_search(next_id,next_cost,min,path,best);
        }
        nodes[id]->depth_visited = false;
        return min;
    }
};


int main(){

    UI num_edges, num_nodes;
    UI start,goal;
    cin>>num_nodes>>num_edges;
    cin>>start>>goal;

    Graph graph = Graph(start,goal);

    UI from,to,cost;
    for(UI i=0;i<num_edges;i++){
        cin>>from>>to>>cost;
        graph.create_node(from);
        graph.create_node(to);
        graph.add_to_node(from,to,cost);
    }

    graph.search();

    return 0;
}

