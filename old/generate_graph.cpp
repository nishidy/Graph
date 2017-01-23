#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){

	if(argc!=5){
		cout<<argv[0]<<": num_nodes num_edges(>=num_nodes-1) cost_power rand_seed(0 means time(NULL))"<<endl;
		return 1;
	}

	vector<pair<int,int> > memo;

	int num_nodes=atoi(argv[1]);
	int num_edges=atoi(argv[2]);
	int cost_power=atoi(argv[3]);
	unsigned int rand_seed=(unsigned int)atoi(argv[4]);

	if(num_edges<num_nodes-1) return 1;
	int sum=0;
	for(int i=num_nodes-1;i>0;i--){
		sum+=i;
	}
	if(sum<num_edges) return 2;
	if(cost_power==0) cost_power=1;

	cout<<num_edges<<endl;

	int min_edges=num_nodes-1;
	int a,b,c;

	for(int i=0;i<min_edges;i++){
		a=rand()%(cost_power/3);
		b=rand()%(cost_power/2);
		c=rand()%(cost_power/1);
		cout<<i<<" "<<i+1<<" "<<a+b+c+1<<endl;
		memo.push_back(pair<int,int>(i,i+1));
	}

	int cnt_edges=min_edges;

	if(rand_seed==0){
		srand((unsigned int)time(NULL));
	}else{
		srand(rand_seed);
	}

	int i0,id;
	int j0,jd;
	while(true){
		i0=rand()%num_nodes;
		id=rand()%num_nodes+1;
		for(int i=i0;i<num_nodes;i+=id){
			j0=rand()%(num_nodes-i);
			jd=rand()%(num_nodes-i)+1;
			for(int j=i+1+j0;j<num_nodes;j+=jd){
				if(rand()%2==0) continue;
				if(find(memo.begin(),memo.end(),pair<int,int>(i,j))==memo.end()){
					a=rand()%(cost_power/3);
					b=rand()%(cost_power/2);
					c=rand()%(cost_power/1);
					cout<<i<<" "<<j<<" "<<a+b+c+1<<endl;
					cnt_edges++;
					memo.push_back(pair<int,int>(i,j));
				}
				if(cnt_edges>=num_edges) break;
			}
			if(cnt_edges>=num_edges) break;
		}
		if(cnt_edges>=num_edges) break;
	}
	cout<<"0 "<<num_nodes-1<<endl;

	return 0;
}
