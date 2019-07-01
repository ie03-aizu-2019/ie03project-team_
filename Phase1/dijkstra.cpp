#include <iostream>
using namespace std;

#define INF 10000000
#define SIZE 1000
#define TRUE 1
#define FALSE 0

double DIST[SIZE][SIZE];
double COST[SIZE];
int VIA[SIZE];
int N;
char USED[SIZE];

int dijkstra(int start, int goal){
    int min, target;

    COST[start] = 0;

    while(1){
        /* 未確定の中から距離が最も小さい地点(a)を選んで、その距離を その地点の最小距離として確定します */
        min=INF;
        for(int i=0;i<N;i++){
            if(!USED[i] && min>COST[i]) {
                min=COST[i];
                target=i;
            }
        }

        /* 全ての地点の最短経路が確定 */
        if(target == goal) return COST[goal];

        /* 今確定した場所から「直接つながっている」かつ「未確定の」地点に関して、
        今確定した場所を経由した場合の距離を計算し、今までの距離よりも小さければ書き直します。 */
        for(int i=0;i<N;i++){
            if(COST[i] > DIST[target][i] + COST[target]) {
                COST[i] = DIST[target][i] + COST[target];
                VIA[i] = target;
            }
        }
        USED[target] = TRUE;
    }
}

int main(){
    int r;
    int a,b,l;
    int s,d;

    /* 初期化 */
    for(int i=0;i<SIZE;i++) {
        COST[i] = INF;
        USED[i] = FALSE;
        VIA[i] = -1;
        for(int j=0;j<SIZE;j++) DIST[i][j] = INF;
    }

    /* 入力 */
    cin>>N>>r;
    for(int i=0;i<r;i++){
        cin>>a>>b>>l;
        DIST[a][b] = l;
    }
    cin>>s>>d;
    
    /* ダイクストラ法で最短経路を求める */
    cout<<dijkstra(s,d);

    /* 経路を表示(ゴールから) */
    int node = d;
    printf("%d", node);
    while(1){
        node = VIA[node];
        printf(" -> %d", node);
        if (node == s) break;
    }

    return 0;
}