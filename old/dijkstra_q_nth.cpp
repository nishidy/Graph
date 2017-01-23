#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef vector<int> vint;
typedef vector<int>::iterator itevi;

#define MAX 1<<20

int DEBUG=0;

class Node{
  public:
	int id;
	vint edges_to;
	vint edges_cost;

	int done;
	int cost;
	int from_id;

	Node(){};
	Node(int id){
		this->done=0;
		this->id=id;
		this->from_id=-1;
		this->cost=MAX;
	};
};

typedef vector<Node> vNode;
vNode nodes;

Node* get_node(int id){
	for(vNode::iterator it=nodes.begin();\
		it!=nodes.end();++it){
		if(it->id==id){
			return &(*it);
		}
	}

	return NULL;
}

class compClass{
  public:
	bool operator() (Node* a, Node* b){
		// XXX: Sorts so that this returns !!false!!
		return a->cost>b->cost;
	}
};

typedef priority_queue<Node*, vector<Node*>, compClass> pNode;

void show_nodes(vNode nodes){
	for(int n=0;n<nodes.size();n++){
		cout<<nodes[n].id<<";";
		cout<<nodes[n].cost<<";";
		cout<<nodes[n].edges_to.size()<<";";
		cout<<nodes[n].edges_cost.size()<<";";
		cout<<endl;
	}
}

void show_queue(pNode pq){
	Node* node;
	cout<<"pq: ";
	while(!pq.empty()){
		node=pq.top();
		cout<<node->id<<":"<<node->cost<<",";
		pq.pop();
	}
	cout<<endl;
}

void show_mid_result(Node* node){
	if(DEBUG==0) return;

	vector<int> min_path_nodes;
	Node* tmp_node=node;
	while(true){
		min_path_nodes.push_back(tmp_node->id);
		if(tmp_node->from_id!=-1){
			tmp_node=get_node(tmp_node->from_id);
		}else{
			reverse(min_path_nodes.begin(),min_path_nodes.end());
			itevi ite=min_path_nodes.begin();
			while(ite!=min_path_nodes.end()){
				if(ite!=min_path_nodes.begin()) cout<<"->";
				cout<<*ite;
				ite++;
			}
			break;
		}
	}
	cout<<" "<<"("<<node->cost<<")"<<endl;
}

int main(int argc, char* argv[]){
	printf("[Shortest path search by dijkstra algorithm]\n\n");
	if(argc!=3) exit(1);
	if(argc==3&&1==atoi(argv[2])) DEBUG=1;
	int h=atoi(argv[1]);

	int n_edges;
	cin>>n_edges;

	int f,t,c;
	Node *node,*tnode;
	for(int n=0;n<n_edges;++n){
		cin>>f>>t>>c;

		node=get_node(f);
		if(node==NULL){
			Node newnode(f);
			nodes.push_back(newnode);
			node=&nodes.back();
		}
		node->edges_to.push_back(t);
		node->edges_cost.push_back(c);

		tnode=get_node(t);
		if(tnode==NULL){
			Node newnode(t);
			nodes.push_back(newnode);
			tnode=&nodes.back();
		}
		tnode->edges_to.push_back(f);
		tnode->edges_cost.push_back(c);
	}

	int s,g;
	cin>>s>>g;

	pNode pq;

	node=get_node(s);
	if(node==NULL) exit(100);
	node->cost=0;
	node->done=1;
	show_mid_result(node);

	Node* next;
	int cost;
	while(true){

		for(int n=0;n<node->edges_to.size();++n){

			next = get_node(node->edges_to[n]);
			if(next==NULL) exit(100);
			if(next->done>=h) continue;

			cost = node->cost+node->edges_cost[n];
			if(next->cost > cost){
				next->cost=cost;
				next->from_id=node->id; // The shortest path backforward to start node
				pq.push(next);
				show_mid_result(next);
			}
		}

		//show_nodes(nodes);
		//show_queue(pq);

		node=pq.top(); pq.pop();
		node->done=node->done+1;
		if(node->id==g) break;
	}

	cout<<"Min cost is "<<node->cost<<" ";
	vector<int> min_path_nodes;
	while(true){
		min_path_nodes.push_back(node->id);
		node=get_node(node->from_id);
		if(node==NULL){
			reverse(min_path_nodes.begin(),min_path_nodes.end());
			itevi ite=min_path_nodes.begin();
			cout<<"(";
			while(ite!=min_path_nodes.end()){
				if(ite!=min_path_nodes.begin()) cout<<"->";
				cout<<*ite;
				ite++;
			}
			cout<<")."<<endl;
			break;
		}
	}

	return 0;

}

