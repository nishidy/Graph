#include <vector>
using namespace std;

int main(int argc, char* argv[]){
	vector<int> v1;

	for(int i=0;i<100000;i++){
		v1.push_back(i);
	}
	printf("size:%ld\n",v1.size());
	for(int i=0;i<100000;i++){
		v1.erase(v1.begin());
	}

	return 0;

}
