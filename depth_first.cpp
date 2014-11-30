#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef vector<int>::iterator itevi;
typedef vector<pair<int,int> >::iterator itevpii;

int DEBUG=0;

class Node{
	public:
	static vector<Node> all_nodes;
	int id;
	//int cost;
	Node* min_from_node;
	bool visited;
	vector<pair<int,int> > to_node_cost;
	Node(){};
	Node(int id){
		this->id=id;
		//this->cost=0;
		this->visited=false;
		this->min_from_node=NULL;
	};
};

vector<Node> Node::all_nodes;
map<int,map<int,int> > memo;

typedef vector<Node>::iterator itevnode;

Node* get_node(int id){
	Node* node=NULL;
	itevnode ite=Node::all_nodes.begin();
	while(ite!=Node::all_nodes.end()){
		if(ite->id==id){
			node=&(*ite);
			break;
		}
		ite++;
	}
	return node;
}

int search(int cost,int min_cost, Node* node, Node* goal_node, int depth){

	if(DEBUG==1){
		for(int i=0;i<depth;i++) printf("->");
		printf("%d(%d)",node->id,cost);
	}

	int return_cost;
	node->visited=true;
	if(node->id==goal_node->id){
		if(DEBUG==1) printf("//\n");
		return_cost=cost;

	}else{
		if(DEBUG==1) printf("\n");

		int tmp_min_cost,next_cost;
		Node* next_node;
		itevpii ite=node->to_node_cost.begin();
		while(ite!=node->to_node_cost.end()){
			next_node=get_node(ite->first);
			next_cost=cost+ite->second;
			if(next_node->visited==false){
				if(min_cost<next_cost){

				}else{
					if(memo.find(next_node->id)!=memo.end() &&\
					   memo[next_node->id].find(next_cost)!=memo[next_node->id].end()){
						tmp_min_cost=memo[next_node->id][next_cost];
					}else{
						tmp_min_cost=search(next_cost,min_cost,next_node,goal_node,depth+1);
						memo[next_node->id][next_cost]=tmp_min_cost;
					}
					if(min_cost>tmp_min_cost){
						next_node->min_from_node=node;
						min_cost=tmp_min_cost;
					}
				}
			}
			ite++;
		}
		return_cost=min_cost;

	}

	node->visited=false;
	return return_cost;
}

void search_path(Node* node,vector<int> min_path_nodes){
	min_path_nodes.push_back(node->id);
	if(node->min_from_node==NULL){
		sort(min_path_nodes.begin(),min_path_nodes.end());
		itevi ite=min_path_nodes.begin();
		printf("(");
		while(ite!=min_path_nodes.end()){
			if(ite!=min_path_nodes.begin()) printf("->");
			printf("%d",*ite);
			ite++;
		}
		printf(").\n");
		return;
	}
	search_path(node->min_from_node,min_path_nodes);
}

int main(int argc, char* argv[]){
	printf("[Depth first search]\n\n");
	if(argc==2&&1==atoi(argv[1])) DEBUG=1;

	int num_edges;
	int from,to,cost;
	Node* node;
	cin>>num_edges;
	for(int i=0;i<num_edges;i++){
		cin>>from>>to>>cost;
		node=get_node(from);
		if(node==NULL){
			Node new_node(from);
			Node::all_nodes.push_back(new_node);
			node=&(Node::all_nodes.back());
		}
		node->to_node_cost.push_back(pair<int,int>(to,cost));

		node=get_node(to);
		if(node==NULL){
			Node new_node(to);
			Node::all_nodes.push_back(new_node);
			node=&(Node::all_nodes.back());
		}
		node->to_node_cost.push_back(pair<int,int>(from,cost));
	}

	int start,goal;
	cin>>start>>goal;

	from=start;

	int min_cost=1<<20;
	printf("Min cost is %d ",search(0,min_cost,get_node(from),get_node(goal),0));
	vector<int> min_path_nodes;
	search_path(get_node(goal),min_path_nodes);

	return 0;
}


