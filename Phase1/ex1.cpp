#include <iostream>
#include <vector>
#include "team.h"
using namespace std;

int main(){
    int N,M,P,Q; 
    double x,y;
    int b,e;
    int i;

    cin>>N>>M>>P>>Q;
    //入力値のエラーメッセージ
    if(Nmax<N || Nmin>N){ 
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(1);
    }
    if(Mmax<=M || 1>=M){
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(2);
    }
    if(Qmax<Q || 0>Q){
        cout<<"ERROR: 0<=Q<="<<Qmax<<"\n";
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