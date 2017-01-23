#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
	vector<pair<int,pair<int,int> > > cost_from;

	Node(){};
	Node(int id){
		this->done=0;
		this->id=id;
		this->cost_from.push_back(make_pair(MAX,makr_pair(-1,0)));
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
		// XXX: Sorts so that this returns !false!
		return a->cost_from[a->done].first>b->cost_from[b->done].first;
	}
};

typedef priority_queue<Node*, vector<Node*>, compClass> pNode;

void show_nodes(vNode nodes){
	for(unsigned int n=0;n<nodes.size();n++){
		cout<<nodes[n].id<<";";
		cout<<nodes[n].cost_from[nodes[n].done-1].first<<";";
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
		cout<<node->id<<":"<<node->cost_from[node->done-1].first<<",";
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
	cout<<" "<<"("<<node->cost_from[node->done-1].first<<")"<<endl;
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
	node->cost_from[node->done].first=0;

	pq.push(node);

	Node* next;
	int cost;

	while(!pq.empty()){

		node=pq.top(); pq.pop();
		if(node->done>=h) continue;

		node->done+=1;
		node->cost_from.push_back(make_pair(MAX,make_pair(-1,0)));
		show_mid_result(node);

		if(node->id==g){
			if(node->done>=h) break;
		}

		for(unsigned int n=0;n<node->edges_to.size();++n){
			next = get_node(node->edges_to[n]);
			cost = node->cost_from[node->done-1].first+node->edges_cost[n];
			if(next->cost_from[next->done].first>cost){
				next->cost_from[next->done]=make_pair(cost,make_pair(node->id,));
				pq.push(next);
			}
		}
	}

	cout<<"Min cost is "<<node->cost_from[node->done-1].first<<" ";
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


