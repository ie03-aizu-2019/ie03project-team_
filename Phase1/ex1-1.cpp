#include <iostream>
#include <vector>
#include "team.h"
using namespace std;

int main(){
    int x,y;
    int b,e;
    int i;

    cin>>N>>M>>P>>Q;
    /*入力値のエラーメッセージ*/
    if(Nmax<N || Nmin>N){ 
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(1);
    }
    if(Mmax<=M || 1>=M){
        cout<<"ERROR: "<<Nmin<<"<=N<="<<Nmax<<"\n";
        exit(2);
    }
    for(i=0;i<N;i++){
        if(( XYmax<x[i] || 0>x[i] )||( XYmax<y[i] || 0>y[i] )){
            cout<<"ERROR: 0<=x,y<="<<XYmax<<"\n";
        exit(3);
        }
    }
    if(Qmax<Q || 0>Q){
        cout<<"ERROR: 0<=Q<="<<Qmax<<"\n";
        exit(4);
    }

    vector<Point> point(N);
    vector<Line>  line(M);  
    for(i=0;i<N;i++){
        cin>>x>>y;
        point[i]={x,y};
    }
    for(i=0;i<M;i++){
        cin>>b>>e;
        line[i]={point[b--],point[e--]};
    }
    

    Z = abs(((Xq[0] - Xp[0]) * (Yp[1] - Yq[1])) + ((Xq[1] - Xp[1]) * (Yq[0] - Yp[0])));
    
    if(Z==0){
        cout<<"NA"<<endl;
        exit(1);
    }
    else{
        s = ((Yp[1] - Yq[1]) * (Xp[1] - Xp[0]) + (Xq[1] - Xp[1]) * (Yp[1] - Yp[0])) / Z;
        t = ((Yp[0] - Yq[0]) * (Xp[1] - Xp[0]) + (Xq[0] - Xp[0]) * (Yp[1] - Yp[0])) / Z;
    }

    if (0 <= s && s <= 1){
        if (0 <= t && t <= 1){
            X = Xp[0] + (Xq[0] - Xp[0]) * s;
        Y = Yp[0] + (Yq[0] - Yp[0]) * s;
        cout << "交点座標は"
             << "(" << X << "," << Y << ")"
             << "です\n"
             << endl;
        }
    }
    else
    {
        cout << "NA\n"
             << endl;
        exit(2);
    } 

    return 0;
}