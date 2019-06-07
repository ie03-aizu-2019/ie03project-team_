#include <iostream>
#include <vector>
#include <algorithm>

#include "team.h"
using namespace std;

int main(){
    int N,M,P,Q; 
    double x,y;
    int b,e;
    int i,j;
    vector<Point> C;

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
        //入力値のエラーメッセージ
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

    return 0;
}
//交点検索
Point searchIntersection(Line L1, Line L2){
    double Z,S,T;
    
    Z = abs(((L1.Q.x-L1.P.x) * (L2.P.y-L2.Q.y)) + ((L2.Q.x-L2.P.x) * (L1.Q.y-L1.P.y)));
    if(-EPS<Z && Z<EPS) return {INF,INF};
    else{
        S= ((L2.P.y - L2.Q.y) * (L2.P.x - L1.P.x) + (L2.Q.x - L2.P.x) * (L2.P.y - L1.P.y)) / Z;
        T= ((L1.P.y - L1.Q.y) * (L2.P.x - L1.P.x) + (L1.Q.x - L1.P.x) * (L2.P.y - L1.P.y)) / Z;
    }

    if ((0<S && S<1) && (0<T && T<1)){
            double X = L1.P.x + (L1.Q.x - L1.P.x) * S;
            double Y = L1.P.y + (L1.Q.y - L1.P.y) * S;
            return {X,Y};
    }
    else return {INF,INF};
}