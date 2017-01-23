#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define A 1
int main(){
	unsigned int a=1;
	printf("%u\n",a);
	printf("%u\n",~a);
	printf("%u\n",A);
	printf("%u\n",~A);
	printf("%u\n",1);
	printf("%u\n",~1);
	printf("%d\n",~1);

	vector<pair<int,int> > v;
	v.push_back(pair<int,int>(0,1));
	if(find(v.begin(),v.end(),pair<int,int>(0,1))==v.end()){
		printf("Not found.\n");
	}else{
		printf("Found.\n");
	}
	if(find(v.begin(),v.end(),pair<int,int>(1,1))==v.end()){
		printf("Not found.\n");
	}else{
		printf("Found.\n");
	}




}
