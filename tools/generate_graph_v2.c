#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int to;
    struct Node* next;
} Node;

void init(Node* memo_array, int num){
    int i;
    for(i=0;i<num;i++){
        memo_array[i].to = -1;
        memo_array[i].next = NULL;
    }
}

int save(Node* memo_array, int from, int to){
    Node* cur = &memo_array[from];
    while(1){
        if(cur->to == -1){
            cur->to = to;
            return 1;
        }
        if(cur->to == to){
            return 0;
        }
        if(cur->next == NULL){
            Node* new = malloc(sizeof(Node));
            new->to = to;
            new->next = NULL;
            cur->next = new;
            return 1;
        }else{
            cur = cur->next;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){

    if(argc!=6){
        printf("%s num_nodes num_edges start goal max_cost\n",argv[0]);
        return -1;
    }

    int num_nodes = atoi(argv[1]);
    int num_edges = atoi(argv[2]);

    if(num_edges<=num_nodes) return -1;

    int start = atoi(argv[3]);
    int goal = atoi(argv[4]);

    if(num_nodes<=goal) return -1;

    int max_cost= atoi(argv[5]);

    printf("%d %d\n",num_nodes,num_edges);
    printf("%d %d\n",start,goal);

    Node* memo_array = malloc(sizeof(Node)*num_nodes);
    init(memo_array,num_nodes);

    srand(1);

    int to, from, cost, cnt_edge=0;
    for(int i=0;i<num_nodes-1;i++){
        save(memo_array,i,i+1);
        printf("%d %d %d\n",i,i+1,max_cost);
        cnt_edge++;
    }
    while(cnt_edge<num_edges){
        do {
            from = rand()%num_nodes;
            to = rand()%num_nodes;
        } while(from==to);
        if(save(memo_array,from,to)){
            cost = rand()%max_cost;
            printf("%d %d %d\n",from,to,cost);
            cnt_edge++;
        }
    }

    return 0;

}

