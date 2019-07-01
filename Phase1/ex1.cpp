#include <iostream>
#include <vector>
using namespace std;

#define Nmax 4
#define Nmin 3
#define Mmax 2
#define Mmin 2
#define Qmax 0
#define Qmin 0
#define XYmax 1000
#define XYmin 0
#define INF 1e10
#define EPS 1e-8


int N,M,P,Q; 

struct Point{
    double x,y; 
};

struct Line{
    Point P,Q;
};

//交点検索
Point searchIntersection(Line L1, Line L2){
    double Z,S,T;
    
    Z = abs(((L1.Q.x-L1.P.x) * (L2.P.y-L2.Q.y)) 
            + ((L2.Q.x-L2.P.x) * (L1.Q.y-L1.P.y)));
    if(-EPS<Z && Z<EPS) return {INF,INF};
    else{
        S=abs(((L2.P.y - L2.Q.y) * (L2.P.x - L1.P.x)    
            + (L2.Q.x - L2.P.x) * (L2.P.y - L1.P.y)))/Z;
        T=abs(((L1.P.y - L1.Q.y) * (L2.P.x - L1.P.x) 
            + (L1.Q.x - L1.P.x) * (L2.P.y - L1.P.y)))/Z;
    }

    if ((0<S && S<1) && (0<T && T<1)){
            double X = L1.P.x + (L1.Q.x - L1.P.x) * S;
            double Y = L1.P.y + (L1.Q.y - L1.P.y) * S;
            return {X,Y};
    }
    else return {INF,INF};
}

int main(){
    double x,y;
    int b,e;
    int i;

    cin>>N>>M>>P>>Q;
    
    //入力値のエラーメッセージ
    if(Nmax<N || N<Nmin){ 
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(1);
    }
    if(Mmax<M || M<Mmin){
        cout<<"ERROR: "<<Nmin<<"<=M<="<<Nmax<<"\n";
        exit(2);
    }
    if(Qmax<Q || Q<Qmin){
        cout<<"ERROR: "<<Qmin<<"<=Q<="<<Qmax<<"\n";
        exit(3);
    }
    
    vector<Point> point(N);
    vector<Line>  line(M);  
    for(i=0;i<N;i++){
        cin>>x>>y;
        if((XYmax<x || XYmin>x) || (XYmax<y || XYmin>y)){
            cout<<"ERROR: "<<XYmin<<"<=x,y<="<<XYmax<<"\n";
            exit(4);
        }
        else point[i]={x,y};
    }
    for(i=0;i<M;i++){
        cin>>b>>e;
        b=--b;
        e=--e;
        line[i]={point[b],point[e]};
    }

    Point C=searchIntersection(line[0],line[1]);

    if(C.x==INF && C.y==INF) cout<<"NA\n";
    else cout<<C.x<<"\t"<<C.y<<"\n";

    return 0;
}

