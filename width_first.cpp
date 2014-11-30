#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int DEBUG=0;

class Node{
	public:
	int id;
	unsigned int cost;
	//bool visited;
	vector<pair<int,int> > to_node_cost;
	Node(){};
	Node(int id){
		this->id=id;
		this->cost=~1;
		//this->visited=false;
	}
};

typedef vector<pair<int,int> >::iterator itevpii;
typedef vector<Node>::iterator itevnode;

vector<Node> all_nodes;
queue<Node*> node_queue;
queue<int> depth_queue;

Node* get_node(int id){
	Node* node=NULL;
	itevnode ite=all_nodes.begin();
	while(ite!=all_nodes.end()){
		if(ite->id==id){
			node=&(*ite);
			break;
		}
		ite++;
	}
	return node;
}

int search(int min_cost,int goal){
	
	Node* node;
	Node* next_node;
	int next_cost,depth;
	while(!node_queue.empty()){

		node=node_queue.front();
		node_queue.pop();

		depth=depth_queue.front();
		depth_queue.pop();

		if(DEBUG==1){
			for(int i=0;i<depth;i++) cout<<"->";
			cout<<node->id<<"("<<node->cost<<")";
		}

		if(node->id==goal){
			if(DEBUG==1) cout<<"//"<<endl;
			continue;
		}else{
			if(DEBUG==1) cout<<endl;
		}

		itevpii ite=node->to_node_cost.begin();
		while(ite!=node->to_node_cost.end()){
			next_node=get_node(ite->first);
			next_cost=ite->second;
			if(next_node->cost > node->cost+next_cost){
				next_node->cost = node->cost+next_cost;
			}
			node_queue.push(next_node);
			depth_queue.push(depth+1);
			ite++;
		}
		depth++;
	}

	Node* goal_node=get_node(goal);
	return goal_node->cost;
}

int main(int argc, char* argv[]){

	if(argc==2&&atoi(argv[1])==0) DEBUG=0;
	cout<<"[Width first search]"<<endl<<endl;
	
	int num_edges;
	cin>>num_edges;
	int from,to,cost;
	Node* node;
	for(int i=0;i<num_edges;i++){
		cin>>from>>to>>cost;
		node=get_node(from);
		if(node==NULL){
			Node new_node(from);
			all_nodes.push_back(new_node);
			node=&(all_nodes.back());
		}
		node->to_node_cost.push_back(pair<int,int>(to,cost));

		node=get_node(to);
		if(node==NULL){
			Node new_node(to);
			all_nodes.push_back(new_node);
			node=&(all_nodes.back());
		}
		//node->to_node_cost.push_back(pair<int,int>(from,cost));
	}
	int start,goal;
	cin>>start>>goal;

	Node* start_node=get_node(start);
	start_node->cost=0;
	node_queue.push(start_node);
	depth_queue.push(0);

	int min_cost=search(0,goal);
	cout<<"Min cost is "<<min_cost<<"."<<endl;
	
	return 0;
}
