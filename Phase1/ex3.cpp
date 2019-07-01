#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

//マクロ定義
#define Nmax 1000
#define Nmin 2

#define Mmax 500
#define Mm
in 1

#define Qmax 100
#define Qmin 0

#define XYmax 1000
#define XYmin 0

#define INF 1e10
#define EPS 1e-8

#define Vmax 10

//構造体,グローバル変数
//************************************************************************************
int N,M,P,Q;
vector<Node> node;

struct Point{
    double x,y; 

    bool operator<(const Point& right)const{
        return x==right.x?y<right.y:x<right.x;
  }
};

struct Line{
    Point P,Q;
};

struct Qdata{
  string s,d;
  int k; 
  int int_s, int_d;     
};

struct Node{
    vector<int> edges_to
    vector<int> edges_cost;

    bool done;
    int cost;
    int from;
}


//************************************************************************************

//関数
//************************************************************************************
//交点検索
Point searchIntersection(Line L1, Line L2){
    double Z,S,T;
    
    Z = abs(((L1.Q.x-L1.P.x) * (L2.P.y-L2.Q.y)) + ((L2.Q.x-L2.P.x) * (L1.Q.y-L1.P.y)));
    if(-EPS<Z && Z<EPS){
        addEdge(sizeof(node),sizeof(node)+1,Distance(L1));
        addEdge(sizeof(node),sizeof(node)+1,Distance(L2));
        return {INF,INF};
    }
    else{
        S=abs(((L2.P.y - L2.Q.y) * (L2.P.x - L1.P.x) + (L2.Q.x - L2.P.x) * (L2.P.y - L1.P.y)))/Z;
        T=abs(((L1.P.y - L1.Q.y) * (L2.P.x - L1.P.x) + (L1.Q.x - L1.P.x) * (L2.P.y - L1.P.y)))/Z;
    }

    if ((0<=S && S<=1) && (0<=T && T<=1)){
        double X = L1.P.x + (L1.Q.x - L1.P.x) * S;
        double Y = L1.P.y + (L1.Q.y - L1.P.y) * S;
        if ((0<S && S<1) && (0<T && T<1)) return {X,Y};
        if(X!=)
    }
    else return {INF,INF};
}

//距離計算
double Distance(Line L){
    return sqrt((L.P.x-L.Q.x)*(L.P.x-L.Q.x)
                +(L.P.y-L.Q.y)*(L.P.y-L.Q.y));
}

//文字型変換
int string_to_int(string s){
    int S;
    int i;
    if(s[0]=='C'){
        s.erase(s.begin() + 0); 
        S=atoi(s.c_str());
        return S;
    } 
    else{
        S=atoi(s.c_str());
        return S;
    }
}

//edgeの追加
void addEdge(int v, int u, int weight){
	//ノードuはノードvとつながっている情報を入れる	
	node[ u ].edges_to.push_back( v );
	//ノードuとノードvのエッジの重みを入れる
	node[ u ].edges_cost.push_back( weight );
	
	//ノードvはノードuとつながっている情報を入れる
	node[ v ].edges_to.push_back( u );
	//ノードvとノードuのエッジの重みを入れる
	node[ v ].edges_cost.push_back( weight );
}

//ダイクストラ
void dijkstra(int start, int goal) {
    int i;

    for(i=0; i<node.size();i++){
           node[i].done=false;
           node[i].cost=-1;
    }

    node[s].cost=0;

    while(1){
        int doneNode=-1;
        for( i=0; i<node.size();i++){
            if(node[i].done==true) continue;
            if(node[i].cost<0) continue; 
            if(doneNode<0 || node[i].cost < node[doneNode].cost) doneNode = i;
        }
        
        if(doneNode==-1) break;

        node[doneNode].done=true;
        for(i=0;i<doneNode.edges_to.size();i++){
            int to=node[doneNode].edges_to[i];
            int cost = node[doneNode].cost+node[doneNode].edges_cost[i];
        if(node[to].cost<0 || cost<node[to].cost){
            node[to].cost=cost;
            node[to].from=doneNode;
        }
    }
}
//************************************************************************************

//main
//************************************************************************************
int main(){
    int N,M,P,Q; 
    double x,y;
    int b,e;
    int i,j;

    vector<Point> C;
    vector<vector<double> > adjacent;

    cin>>N>>M>>P>>Q;
    //入力値のエラーメッセージ
    if(Nmax<N || N<Nmin){ 
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(1);
    }
    if(Mmax<M || M<Mmin){
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(2);
    }
    if(Qmax<Q || Q<Qmin){
        cout<<"ERROR: "<<Qmin<<"<=Q<="<<Qmax<<"\n";
        exit(3);
    }

    vector<Point> point(N);  
    vector<Line> line(M);
    for(i=0;i<N;i++){
        cin>>x>>y;
        //入力値のエラーメッセージ
        if((XYmax<x || XYmin>x) || (XYmax<y || XYmin>y)){
            cout<<"ERROR: "<<XYmin<<"<=x,y<="<<XYmax<<"\n";
            exit(4);
        }
        else point[i]={x,y};
    }
    for(i=0;i<M;i++){
        cin>>b>>e;
        --b,--e;
        line[i]={point[b],point[e]};
        
    }

    vector<Qdata> qdata(Q);
    string s,d;
    int k;
    for(i=0;i<Q;i++){
        cin>>s>>d>>k;
        qdata[i].s=s,qdata[i].d=d,qdata[i].k=k;
        qdata[i].int_s=string_to_int(qdata[i].s);
        qdata[i].int_d=string_to_int(qdata[i].d);
    }
    
    for(i=0;i<M;i++){
        for(j=i+1;j<M;j++){
            Point S=searchIntersection(line[i],line[j]);
            if(S.x==INF && S.y==INF) continue;
            C.push_back(S);
        }
    }
    sort(C.begin(),C.end());
    

    for(i=0;i<C.size();i++){
        cout<<C[i].x<<"\t"<<C[i].y<<"\n";
    }

    cout << node[end].cost << endl;

    vector<int> path;//最短経路の情報を保持するvector
    //最短経路をゴールから順にスタートまでたどる
	for(int i = end ; i != start ; i = node[i].from ){
		path.push_back(i);
	}
	path.push_back(start);

	//最短経路の出力
	cout << "最短経路は" << endl;
	for(int i = path.size()-1 ; i >= 0 ; i--){
		cout << path[i] << " ";
	}
	cout << endl;

    return 0;
}
//************************************************************************************