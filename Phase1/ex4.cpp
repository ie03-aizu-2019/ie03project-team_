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
#define Mmin 2

#define Qmax 100
#define Qmin 0

#define XYmax 1000
#define XYmin 0

#define INF 1e10
#define EPS 1e-8

#define Vmax 10

//構造体
//************************************************************************************
struct Point{
    double x,y;
    int ID; 

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
    vector<int> edges_to;
    vector<int> edges_cost;

    bool done;
    int cost;
    int from;
};

//グローバル変数
int N,M,P,Q;
int cross_count=0;
vector<Point> point;  
vector<Line> line;
vector<Node> node;

//************************************************************************************

//関数
//************************************************************************************

//距離計算
double Distance(Point P1, Point P2){
    return sqrt((P1.x-P2.x)*(P1.x-P2.x)
                +(P1.y-P2.y)*(P1.y-P2.y));
}

//edgeの追加
void addEdge(int v, int u, int weight){	
	node[ u ].edges_to.push_back( v );
	node[ u ].edges_cost.push_back( weight );

	node[ v ].edges_to.push_back( u );
	node[ v ].edges_cost.push_back( weight );
}

//交点検索
Point searchIntersection(Line L1, Line L2){
    double Z,S,T;
    
    Z = abs(((L1.Q.x-L1.P.x) * (L2.P.y-L2.Q.y)) + ((L2.Q.x-L2.P.x) * (L1.Q.y-L1.P.y)));
    if(-EPS<Z && Z<EPS){
        addEdge(L1.P.ID, L1.Q.ID, Distance(L1.P, L1.Q));
        addEdge(L2.P.ID, L2.Q.ID, Distance(L2.P, L2.Q));
        return {INF,INF};
    }
    else{
        S=abs(((L2.P.y - L2.Q.y) * (L2.P.x - L1.P.x) + (L2.Q.x - L2.P.x) * (L2.P.y - L1.P.y)))/Z;
        T=abs(((L1.P.y - L1.Q.y) * (L2.P.x - L1.P.x) + (L1.Q.x - L1.P.x) * (L2.P.y - L1.P.y)))/Z;
    }

    if ((0<=S && S<=1) && (0<=T && T<=1)){
        double X = L1.P.x + (L1.Q.x - L1.P.x) * S;
        double Y = L1.P.y + (L1.Q.y - L1.P.y) * S;
        //交点が端点の場合
        if((X==L1.P.x&&Y==L1.P.y) || (X==L2.P.x&&Y==L2.P.y) || (X==L1.Q.x&&Y==L1.Q.y) || (X==L2.Q.x&&Y==L2.Q.y)){
            if((X!=L1.P.x&&Y!=L1.P.y)&&(X!=L1.Q.x&&Y!=L1.Q.y)){
                if(X==L2.P.x&&Y==L2.P.y){
                    
                }
                if(X==L2.Q.x&&Y==L2.Q.y){
                    
                }
            }
            if((X!=L2.P.x&&Y!=L2.P.y)&&(X!=L2.Q.x&&Y!=L2.Q.y)){
                if(X==L1.P.x&&Y==L1.P.y){
                    
                }
                if(X==L1.Q.x&&Y==L1.Q.y){
                   
                }
            }
        //交点が端点でない場合
            cross_count++;
            return{X,Y};

        }
    }
    else return {INF,INF};
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

//ダイクストラ法
void dijkstra(int start, int goal) {
    int i;

    for(i=0; i<node.size();i++){
           node[i].done=false;
           node[i].cost=-1;
    }

    node[start].cost=0;

    while(1){
        int doneNode=-1;
        for( i=0; i<node.size();i++){
            if(node[i].done==true) continue;
            if(node[i].cost<0) continue; 
            if(doneNode<0 || node[i].cost < node[doneNode].cost) doneNode = i;
        }
        
        if(doneNode==-1) break;

        node[doneNode].done=true;
        for(i=0;i<node[doneNode].edges_to.size();i++){
            int to=node[doneNode].edges_to[i];
            int cost = node[doneNode].cost+node[doneNode].edges_cost[i];
            if(node[to].cost<0 || cost<node[to].cost){
            node[to].cost=cost;
            node[to].from=doneNode;
            }
        }
    }
}
//************************************************************************************

//main
//************************************************************************************
int main(){
    Point Pin;
    Line  Lin;
    int i;

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

    
    for(int i=0;i<N;i++){
        cin>>Pin.x>>Pin.y;
        //入力値のエラーメッセージ
        if((XYmax < Pin.x || XYmin > Pin.x) || (XYmax < Pin.y || XYmin > Pin.y)){
            cout<<"ERROR: "<<XYmin<<"<=x,y<="<<XYmax<<"\n";
            exit(4);
        }
        else{
            point.push_back(Pin);
            point[i].ID=i;
        }
    }

    for(i=0;i<point.size();i++) {
        cout<<point[i].ID<<" "<<point[i].x<<"\t"<<point[i].y<<endl;
        
    }
    cout<<"-----------------"<<endl;

    for(i=0;i<M;i++){
        cin>>Lin.P.ID>>Lin.Q.ID;
        Lin.P.ID--;
        Lin.Q.ID--;
        Lin.P.x=point[Lin.P.ID].x;
        Lin.P.y=point[Lin.P.ID].y;
        Lin.Q.x=point[Lin.Q.ID].x;
        Lin.Q.y=point[Lin.Q.ID].y;
        line.push_back(Lin);
    }
    for(i=0;i<line.size();i++) {
        cout<<line[i].P.ID<<"("<<line[i].P.x<<" "<<line[i].P.y<<")"<<"\t"<<line[i].Q.ID<<endl;
    }

    vector<Qdata> qdata(Q);
    string s,d;
    int k;
    for(int i=0;i<Q;i++){
        cin>>s>>d>>k;
        qdata[i].s=s,qdata[i].d=d,qdata[i].k=k;
        qdata[i].int_s=string_to_int(qdata[i].s);
        qdata[i].int_d=string_to_int(qdata[i].d);
    }    
    vector<Point> C;
    for(int i=0;i<M;i++){
        for(int j=i+1;j<M;j++){
            Point S=searchIntersection(line[i],line[j]);
            if(S.x==INF && S.y==INF) continue;
            C.push_back(S);
        }
    }
    sort(C.begin(),C.end());

    for(i=0;i<C.size();i++){
        cout<<C[i].x<<"\t"<<C[i].y<<"\n";
    }


    vector<int> path;//最短経路の情報を保持するvector
    //最短経路をゴールから順にスタートまでたどる
	for(int i = qdata[i].int_d ; i != qdata[i].int_s ; i = node[i].from ){
		path.push_back(i);
	}
	path.push_back(qdata[i].int_s);

	//最短経路の出力
	cout << "最短経路は" << endl;
	for(int i = path.size()-1 ; i >= 0 ; i--){
		cout << path[i] << " ";
	}
	cout << endl;

    return 0;
}
//************************************************************************************