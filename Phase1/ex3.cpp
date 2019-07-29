#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <float.h>
#include <list>
using namespace std;

//マクロ定義
# define Nmax 1000
# define Nmin 2

# define Mmax 500
# define Mmin 2

# define Qmax 100
# define Qmin 0

# define XYmax 1000
# define XYmin 0

# define INF 1e10
# define EPS 1e-8

# define Vmax 10

//# define DEBUG1
# define DEBUG2
//構造体
//************************************************************************************
struct Point{
    double x,y;
    int P_ID; 

    bool operator<(const Point& right)const{
        return x==right.x?y<right.y:x<right.x;
    }
    bool operator==(const Point& right)const{
        return ( fabs( x - right.x ) < DBL_EPSILON && fabs( y - right.y ) < DBL_EPSILON ) ;
    }
};

struct Line{
    Point P,Q;
    int L_ID;

    vector<Point> Line_Cross;

};

struct Qdata{
  string s,d;
  int k; 
  int int_s, int_d;     
};

struct Node{
    vector<int> edges_to;
    vector<double> edges_cost;

    bool done;
    int cost;
    int from;
};

//グローバル変数
int N,M,P,Q;

bool resarch = false;
int cross_count = 0;              // 交点の数
int node_count = 0;               // nodeの数
vector<Point> point;            // point
vector<Line> line;              // line

Node node[Nmax];                // ダイクストラ法のnode
list<Line> road;              // ダイクストラ法のroad

//************************************************************************************

//関数
//************************************************************************************

//距離計算
double Distance(Point P1, Point P2){
    return sqrt((P1.x-P2.x)*(P1.x-P2.x)
                +(P1.y-P2.y)*(P1.y-P2.y));
}

//edgeの追加
void addEdge(int v, int u, double weight){	
	node_count++;
    node[u].edges_to.push_back( v );
	node[u].edges_cost.push_back( weight );

	node[v].edges_to.push_back( u );
	node[v].edges_cost.push_back( weight );
}

//交点検索
Point searchIntersection(Line L1, Line L2){
    double Z,S,T;
    
    Z = fabs(((L1.Q.x-L1.P.x) * (L2.P.y-L2.Q.y)) + ((L2.Q.x-L2.P.x) * (L1.Q.y-L1.P.y)));
    if( -EPS< Z && Z < EPS ) return {INF,INF};
    else{
        S=fabs(((L2.P.y - L2.Q.y) * (L2.P.x - L1.P.x) + (L2.Q.x - L2.P.x) * (L2.P.y - L1.P.y)))/Z;
        T=fabs(((L1.P.y - L1.Q.y) * (L2.P.x - L1.P.x) + (L1.Q.x - L1.P.x) * (L2.P.y - L1.P.y)))/Z;
    }

    if ((0<=S && S<=1) && (0<=T && T<=1)){
        Point cross;
        Line wl;

        cross.x = L1.P.x + (L1.Q.x - L1.P.x) * S;
        cross.y = L1.P.y + (L1.Q.y - L1.P.y) * S;
    
        //交点が端点の場合
        if(( fabs(cross.x - L1.P.x) < DBL_EPSILON && fabs(cross.y - L1.P.y) < DBL_EPSILON ) || ( fabs(cross.x - L2.P.x ) < DBL_EPSILON && fabs(cross.y - L2.P.y) < DBL_EPSILON ) 
        || ( fabs(cross.x - L1.Q.x) < DBL_EPSILON && fabs(cross.y - L1.Q.y) < DBL_EPSILON ) || ( fabs(cross.x - L2.Q.x ) < DBL_EPSILON && fabs(cross.y - L2.Q.y) < DBL_EPSILON )) {
            if((cross.x != L1.P.x && cross.y != L1.P.y) && (cross.x != L1.Q.x && cross.y != L1.Q.y)) {
                if( fabs(cross.x - L2.P.x < DBL_EPSILON) && fabs(cross.y - L2.P.y < DBL_EPSILON) ) {
                    line[ L1.L_ID ].Line_Cross.push_back(L2.P);
                    
                    return{INF, INF};
                }
                if( fabs(cross.x - L2.Q.x < DBL_EPSILON) && fabs(cross.y - L2.Q.y < DBL_EPSILON) ) {
                    line[ L1.L_ID ].Line_Cross.push_back(L2.Q);
                    
                    return{INF, INF};
                }
            }
            if((cross.x != L2.P.x && cross.y != L2.P.y) && (cross.x != L2.Q.x && cross.y != L2.Q.y)) {
                if( fabs(cross.x - L1.P.x < DBL_EPSILON) && fabs(cross.y - L1.P.y < DBL_EPSILON) ) {
                    line[ L2.L_ID ].Line_Cross.push_back(L1.P);
                    
                    return{INF, INF};
                }
                if( fabs(cross.x - L1.Q.x < DBL_EPSILON) && fabs(cross.y - L1.Q.y < DBL_EPSILON) ) {
                    line[ L2.L_ID ].Line_Cross.push_back(L1.Q);
                    
                    return{INF, INF};
                }
            }
        }
        //交点が端点でない場合
        else{
            cross_count++;
            cross.P_ID=point.size();
            point.push_back(cross);

            line[ L1.L_ID ].Line_Cross.push_back(cross);
                    
            line[ L2.L_ID ].Line_Cross.push_back(cross);
            
                          
            
            cout<<"add ("<<cross.x<<", "<<cross.y<<")"<<endl;
            cout<<"------------------------------------"<<endl;
            return{cross.x,cross.y};
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

    for(int i = 0; i < node_count; i++) {
           node[i].done = false;
           node[i].cost = -1;
    }

    node[start].cost = 0;

    while( 1 ){
        int doneNode = -1;
        for(int i = 0; i < node_count; i++) {
            if(node[i].done == true) continue;
            if(node[i].cost < 0) continue; 
            if(doneNode < 0 || node[i].cost < node[doneNode].cost) doneNode = i;
        }
        
        if(doneNode == -1) break;

        node[doneNode].done = true;
        for(int i = 0; i < node[doneNode].edges_to.size(); i++) {
            int to = node[doneNode].edges_to[i];
            int cost = node[doneNode].cost + node[doneNode].edges_cost[i];
            if(node[to].cost < 0 || cost < node[to].cost) {
            node[to].cost = cost;
            node[to].from = doneNode;
            }
        }
    }
}

bool is_eqals(const Point& left, const Point& right){
    return ( fabs( left.x - right.x ) < DBL_EPSILON && fabs( left.y - right.y ) < DBL_EPSILON ) ;
}
//************************************************************************************

//main
//************************************************************************************
int main(){
    
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

    Point Pin;
    for(int i=0;i<N;i++){
        cin>>Pin.x>>Pin.y;
        //入力値のエラーメッセージ
        if((XYmax < Pin.x || XYmin > Pin.x) || (XYmax < Pin.y || XYmin > Pin.y)){
            cout<<"ERROR: "<<XYmin<<"<=x,y<="<<XYmax<<"\n";
            exit(4);
        }
        else{
            point.push_back(Pin);
            point[i].P_ID = i;
        }
    }

    Line  Lin;
    for(int i=0;i<M;i++){
        cin>>Lin.P.P_ID>>Lin.Q.P_ID;
        Lin.P.P_ID--;
        Lin.Q.P_ID--;
        Lin.P.x = point[Lin.P.P_ID].x;
        Lin.P.y = point[Lin.P.P_ID].y;
        Lin.Q.x = point[Lin.Q.P_ID].x;
        Lin.Q.y = point[Lin.Q.P_ID].y;
        line.push_back(Lin);
        line[i].L_ID = i;
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

    //交点検索
    for(int i = 0; i < line.size(); i++){
        for(int j = i + 1; j < line.size(); j++){
#ifdef DEBUG1 
            cout<<"i = "<<i<<"\t"<<"j = "<<j;       

            cout<<"("<<line[i].P.x<<", "<<line[i].P.y<<")"
                <<" ("<<line[i].Q.x<<", "<<line[i].Q.y<<")"
                <<"\t("<<line[j].P.x<<", "<<line[j].P.y<<")"
                <<" ("<<line[j].Q.x<<", "<<line[j].Q.y<<")"
                <<endl;
#endif             
            Point S = searchIntersection(line[i],line[j]);
            if(S.x==INF && S.y==INF) continue;
        }
    }
    
    for( int i = 0; i < line.size(); i++ ){
        for( int j = 0; j < line[ i ].Line_Cross.size(); j++){
            sort( line[ i ].Line_Cross.begin(), line[ i ].Line_Cross.end() );
            line[ i ].Line_Cross.erase( unique(line[ i ].Line_Cross.begin(), line[ i ].Line_Cross.end()), line[ i ].Line_Cross.end() );
        }
    }
    
    for(int i = 0; i < 4; i++){
        //addEdge( line[ 1 ].P.P_ID, line[ 1 ].Line_Cross[ 0 ].P_ID, Distance( line[ 1 ].P, line[ 1 ].Line_Cross[ 0 ] ) );
        addEdge( line[ i ].P.P_ID, line[ i ].Line_Cross[ 0 ].P_ID, Distance( line[ i ].P, line[ i ].Line_Cross[ 0 ] ) );
        for(int j = 0; j < line[ i ].Line_Cross.size() ; j++){
            addEdge( line[ i ].Line_Cross[ j ].P_ID, line[ i ].Line_Cross[ j + 1 ].P_ID, 
                        Distance( line[ i ].Line_Cross[ j ], line[ i ].Line_Cross[ j ] ) );
        }
        addEdge( line[ i ].Q.P_ID, line[ i ].Line_Cross[ line[ i ].Line_Cross.size() ].P_ID, 
                        Distance( line[ i ].Q, line[ i ].Line_Cross[ line[ i ].Line_Cross.size() ] ) );
    }       
    
    
    
    addEdge( line[ 1 ].P.P_ID, line[ 1 ].Line_Cross[ 0 ].P_ID, Distance( line[ 1 ].P, line[ 1 ].Line_Cross[ 0 ] ) );
    
    
    for(int i = 0; i < qdata.size(); i++) {
        dijkstra(qdata[i].int_s, qdata[i].int_d);
    }
    

#ifdef DEBUG2

    cout<<"-------------"<<endl;
    cout<<"point"<<endl;
    cout<<"intersection counter -- "<<cross_count<<endl;
    for(int i=0; i<point.size(); i++){
        cout<<"<"<<point[i].P_ID<<"> "<<point[i].x<<"\t"<<point[i].y<<endl;
    }

    cout<<"-------------"<<endl;
    cout<<"line"<<endl;
    for(int i = 0; i<line.size(); i++){
        cout<<"<"<<line[i].L_ID<<"> "<<line[i].P.P_ID<<"\t"<<line[i].Q.P_ID<<endl;
    }
    
    cout<<"-------------"<<endl;
    cout<<"Line_Cross"<<endl;
    for(int i = 0; i<line.size(); i++){
        cout<<"<"<<line[ i ].L_ID<<">  "<<"Line_Cross_count = "<<line[ i ].Line_Cross.size()<<endl;
        cout<<"<"<<line[ i ].P.P_ID<<">"<<"("<<line[ i ].P.x<<",\t"<<line[ i ].P.y<<")\t";
        for( int j = 0; j < line[ i ].Line_Cross.size(); j++){
            cout<<"<"<<line[ i ].Line_Cross[ j ].P_ID<<">"<<"("<<line[ i ].Line_Cross[ j ].x<<",\t"<<line[ i ].Line_Cross[ j ].y<<")\t";
        }
        cout<<"<"<<line[ i ].Q.P_ID<<">"<<"("<<line[ i ].Q.x<<",\t"<<line[ i ].Q.y<<")\t"<<endl;
    }

    cout<<"-------------"<<endl;
    cout<<"node"<<endl;
    cout<<"node counter -- "<<node_count<<endl;
    
    for(int i = 0; i < node_count; i++){
       for(int j = 0; j < node[i].edges_to.size(); j++){
            cout<<"node["<<i<<"].edge_to["<<j<<"]="<<node[i].edges_to[j];
            cout<<"\tcost "<<node[i].edges_cost[j]<<endl;
        }
    }
#endif

    return 0;
}
//************************************************************************************