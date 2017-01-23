#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include <sstream>

using namespace std;

typedef int To;
typedef int Cost;
typedef unordered_map<To,Cost> Edges;

class Node {
    int id;
    Edges edges;

    public:
        Node(int from):id(from){};

        void add_edge(int to_node, int cost){
            edges[to_node] = cost;
        }

        int get_id(){
            return id;
        }

        Edges* get_edges(){
            return &edges;
        }
};

typedef int Id;
typedef unordered_map<Id,Node*> Nodes;

class Graph {
    protected:
        Nodes nodes;

    public:
        Graph(){};
        void add_node(int from){
            if(nodes.find(from)==nodes.end())
                nodes[from] = new Node(from);
        }

        void add_edge(int from, int to, int cost){
            Node* node = nodes[from];
            node->add_edge(to,cost);
        }

        virtual void solve(int,int) = 0;
        virtual void show_path() = 0;
};


typedef struct ManageNode {
    Node* node;
    int cost;
    bool done;
    int from;
    ManageNode(Node *node, int cost): node(node), cost(cost), done(false), from(-1) {};
} ManageNode;

class compClass {
    public:
        bool operator() (ManageNode* a, ManageNode* b){
            return a->cost > b->cost;
        }
};

typedef unordered_map<Id,ManageNode*> ManageNodes;
typedef priority_queue<ManageNode*, vector<ManageNode*>, compClass> QueueNodes;

string reduce(vector<int>& path){
    stringstream ss;
    for(int i=0;i<path.size()-1;i++){
        ss << path[i] << " -> ";
    }
    ss << path[path.size()-1];
    return ss.str();
}

class Dijkstra : public Graph {
    ManageNodes man_nodes;
    QueueNodes pq_nodes;
    int start, goal;

    void init_man_nodes(){
        for(auto node_info: nodes){
            int node_id = node_info.first;
            Node* node = node_info.second;
            man_nodes[node_id] = new ManageNode(node,1<<30);
        }
    }

    void update_man_node(int node_id, int cost, int from){
        man_nodes[node_id]->cost = cost;
        man_nodes[node_id]->from = from;
    }

    void enque_man_node(int node_id){
        ManageNode* man_node = man_nodes[node_id];
        pq_nodes.push( man_node );
    }

    int get_man_node_cost(int node_id){
        return man_nodes[node_id]->cost;
    }

    Node* take_min_cost_node(){
        return pq_nodes.top()->node;
    }

    int take_min_cost(){
        return pq_nodes.top()->cost;
    }

    void remove_min_cost_node(){
        pq_nodes.pop();
    }

    bool judge_if_done(int node_id){
        return man_nodes[node_id]->done;
    }

    void save_done(int node_id){
        man_nodes[node_id]->done = true;
    }

    public:
        Dijkstra() {};

        void solve(int start, int goal){
            this->start = start;
            this->goal = goal;

            cout << start << " ---> " << goal << endl;

            init_man_nodes();
            update_man_node(start, 0, -1);
            enque_man_node(start);

            int to_goal_cost = 0;

            Node *node;
            int cost, node_id;
            while(!pq_nodes.empty()){
                node = take_min_cost_node();
                cost = take_min_cost();
                node_id = node->get_id();

                remove_min_cost_node();

                if(judge_if_done(node_id)){
                    continue;
                }else{
                    save_done(node_id);
                }

                if(node_id==goal){
                    to_goal_cost = cost;
                    break;
                }

                int to_node_id, to_node_cost, new_cost;
                for( auto edge: *(node->get_edges()) ){
                    to_node_id = edge.first;
                    to_node_cost = edge.second;

                    new_cost = cost+to_node_cost;
                    if(new_cost < get_man_node_cost(to_node_id)){
                        update_man_node(to_node_id, new_cost, node_id);
                        enque_man_node(to_node_id);
                    }
                }
            }
            cout << "cost : " << to_goal_cost << endl;
        }

        void show_path(){
            cout << "path : ";
            vector<int> path;
            int node_id = goal;
            for(;;){
                path.push_back(node_id);
                if(node_id==start)
                    break;
                node_id = man_nodes[node_id]->from;
            }
            reverse(path.begin(),path.end());
            cout << reduce(path) << endl;
        }
};

int main(int argc, char* argv[]) {

    int num_nodes, num_edges;
    int start_node, goal_node;

    Graph* graph = new Dijkstra();

    if(argc==2) {
        ifstream ifs(argv[1]);
        ifs >> num_nodes >> num_edges;
        ifs >> start_node >> goal_node;
    
        int from_node, to_node, edge_cost;
        while( ifs >> from_node >> to_node >> edge_cost ){
            graph->add_node(from_node);
            graph->add_node(to_node);
            graph->add_edge(from_node,to_node,edge_cost);
        }

    }else{
        cin >> num_nodes >> num_edges;
        cin >> start_node >> goal_node;

        int from_node, to_node, edge_cost;
        for(int i=0;i<num_edges;i++){
            cin >> from_node >> to_node >> edge_cost;
            graph->add_node(from_node);
            graph->add_node(to_node);
            graph->add_edge(from_node,to_node,edge_cost);
        }
    }

    graph->solve(start_node,goal_node);
    graph->show_path();

    return 0;
}

