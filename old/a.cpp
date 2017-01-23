#include <vector>
using namespace std;

int main(){
	class V{
		public:
		vector<pair<int,int> > vpii;
	};

	//vector<int>::iterator itevi;
	//itevi=vi.begin();
	//itevi=vi.end();

	V v;
	if(v.vpii.begin()==v.vpii.end()){
		printf("Same!\n");
	}
	if(v.vpii.begin()!=v.vpii.end()){
		printf("Not same.\n");
	}

	v.vpii.push_back(pair<int,int>(1,10));
	if(v.vpii.begin()==v.vpii.end()){
		printf("Same!\n");
	}
	if(v.vpii.begin()!=v.vpii.end()){
		printf("Not same.\n");
	}
}




