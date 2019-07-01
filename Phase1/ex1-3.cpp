#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "team.h"
#include <iomanip>
using namespace std;

int main(){
    int N,M,P,Q;

    int x[Nmax],y[Nmax];
    double Xp[Nmax],Yp[Nmax];
    double Xq[Nmax],Yq[Nmax];
    int b[Mmax],e[Mmax];

    double Cx[Nmax],Cy[Nmax];
    double X,Y;
    double Z;
    double S,T;
    
    string s[Mmax],d[Mmax],g[Mmax];
    int int_s[100],int_d[100],int_g[100];
    double Distance[Qmax][Qmax];
    double rx1=0,ry1=0,rx2=0,ry2=0;
    int re1,re2;
    

    int i,j,k=0,l,m=0;  //カウンタ変数

    
    /*データ入力*/
    cin>>N>>M>>P>>Q;
    for(i=0;i<N;i++){
        cin>>x[i];
        cin>>y[i];
    }
    for(i=0;i<M;i++){
        cin>>b[i];
        cin>>e[i];
    }
    for(i=0;i<Q;i++){
        cin>>s[i];
        cin>>d[i];
        cin>>g[i];
    }
    /*----------*/
    
    /*入力値のエラーメッセージ*/
    if(Nmax<=N || 2>=N){ 
        cout<<"ERROR: 2<=N<="<<Nmax<<"\n";
        exit(1);
    }
    if(Mmax<=M || 1>=M){
        cout<<"ERROR: 1<=M<="<<Mmax<<"\n";
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
    /*-----------------------*/

    for(i=0;i<N;i++){          //重み付き隣接行列を-1で初期化
        for(j=0;j<N;j++){
            Distance[i][j]=-1;   
        }
    }

    /*辺の端点を格納*/
    for(i=0;i<M;i++){
        Xp[i]=x[b[i]-1];
        Yp[i]=y[b[i]-1];
        Xq[i]=x[e[i]-1];
        Yq[i]=y[e[i]-1];

        //既存の点での隣接行列作成（辺で隣接してる点同士に１を代入）
        Distance[b[i]-1][e[i]-1]=1;
        Distance[e[i]-1][b[i]-1]=1;
    }
    /*-------------*/

    for(i=0;i<M;i++){
        cout<<"Xp "<<Xp[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M;i++){
        cout<<"Yp "<<Yp[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M;i++){
        cout<<"Xq "<<Xq[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M;i++){
        cout<<"Yq "<<Yq[i]<<"\t";
    }
    cout<<"\n";

    cout<<"-------------------------------------\n";
    //M+m
    for(i=0;i<M+m;i++){
        for(j=0;j<M+m;j++){
            //cout<<"j="<<j<<"\t";
            Z = 0;
            S = 0;
            T = 0;
            Z = abs(((Xq[i] - Xp[i]) * (Yp[j] - Yq[j])) + ((Xq[j] - Xp[j]) * (Yq[i] - Yp[i])));
            //cout<<"S="<<S<<"T="<<T<<"Z="<<Z<<"\n";
           
            if(EPS<=Z && Z<=EPS) continue;
            else{
                S = ((Yp[j] - Yq[j]) * (Xp[j] - Xp[i]) + (Xq[j] - Xp[j]) * (Yp[j] - Yp[i])) / Z;
                T = ((Yp[i] - Yq[i]) * (Xp[j] - Xp[i]) + (Xq[i] - Xp[i]) * (Yp[j] - Yp[i])) / Z;
                //s = ((Yp[1] - Yq[1]) * (Xp[1] - Xp[0]) + (Xq[1] - Xp[1]) * (Yp[1] - Yp[0])) / Z;
                //t = ((Yp[0] - Yq[0]) * (Xp[1] - Xp[0]) + (Xq[0] - Xp[0]) * (Yp[1] - Yp[0])) / Z;
            }
            
            if ((0 <= S && S <= 1) && (0 <= T && T <= 1)){
                X = Xp[i] + (Xq[i] - Xp[i]) * S;
                Y = Yp[i] + (Yq[i] - Yp[i]) * S;
                
               if((X==Xp[i]&&Y==Yp[i]) || (X==Xp[j]&&Y==Yp[j]) || (X==Xq[i]&&Y==Yq[i]) || (X==Xq[j]&&Y==Yq[j])){
                    /*交点が端点の場合の隣接行列を更新*/
                    if((X!=Xp[i]&&Y!=Yp[i])&&(X!=Xq[i]&&Y!=Yq[i])){
                        //cout<<"in1\n";
                        Distance[b[i]-1][e[i]-1]=-1;
                        Distance[e[i]-1][b[i]-1]=-1;   
                        rx1=Xq[i];
                        ry1=Yq[i];
                        re1=e[i];
                        if(X==Xp[j]&&Y==Yp[j]){
                            Distance[b[i]-1][b[j]-1]=1;
                            Distance[b[j]-1][b[i]-1]=1;
                            Distance[b[j]-1][e[i]-1]=1;
                            Distance[e[i]-1][b[j]-1]=1;
                            //辺の更新
                            m++;
                            for(l=0;l<M+m;l++){
                                if(l==i){
                                    Xq[l]=X;
                                    Yq[l]=Y;
                                    e[l]=b[j];
                                }
                                else if(l=M){
                                    Xp[l]=X;
                                    Yp[l]=Y;
                                    Xq[l]=rx1;
                                    Yq[l]=ry1; 
                                    b[l]=b[j];
                                    e[l]=re1;
                                }
                                else continue;
                            }
                        }
                        if(X==Xq[j]&&Y==Yq[j]){
                            //cout<<" in2\n";
                            Distance[b[i]-1][e[j]-1]=1;
                            Distance[e[j]-1][b[i]-1]=1;
                            Distance[e[j]-1][e[i]-1]=1;
                            Distance[e[i]-1][e[j]-1]=1;
                            //辺の更新
                            m++;
                            for(l=0;l<M+m;l++){
                                if(l==i){
                                    Xq[l]=X;
                                    Yq[l]=Y;
                                    e[l]=e[j];
                                }
                                else if(l=M){
                                    Xp[l]=X;
                                    Yp[l]=Y;
                                    Xq[l]=rx1;
                                    Yq[l]=ry1;
                                    b[l]=e[j];
                                    e[l]=re1;  
                                }
                                else continue;
                            } 
                        }
                    }

                    if((X!=Xp[j]&&Y!=Yp[j])&&(X!=Xq[j]&&Y!=Yq[j])){
                        Distance[b[j]-1][e[j]-1]=-1;
                        Distance[e[j]-1][b[j]-1]=-1;   
                        rx1=Xq[j];
                        ry1=Yq[j];
                        re2=e[j];
                        if(X==Xp[i]&&Y==Yp[i]){
                            //cout<<" in3\n";
                            Distance[b[i]-1][b[j]-1]=1;
                            Distance[b[j]-1][b[i]-1]=1;
                            Distance[b[i]-1][e[j]-1]=1;
                            Distance[e[j]-1][b[i]-1]=1;
                            //辺の更新
                            m++;
                            for(l=0;l<M+m;l++){
                                if(l==j){
                                    Xq[l]=X;
                                    Yq[l]=Y;
                                    e[l]=b[i];
                                }
                                else if(l==M){
                                    Xp[l]=X;
                                    Yp[l]=Y;
                                    Xq[l]=rx1;
                                    Yq[l]=ry1;
                                    b[l]=b[i];
                                    e[l]=re2; 
                                }
                                else continue;
                            }
                                
                        }
                        if(X==Xq[i]&&Y==Yq[i]){
                            Distance[b[j]-1][e[i]-1]=1;
                            Distance[e[i]-1][b[j]-1]=1;
                            Distance[e[i]-1][e[j]-1]=1;
                            Distance[e[j]-1][e[i]-1]=1;
                            //辺の更新
                            m++;
                            for(l=0;l<M+m;l++){
                                if(l==j){
                                    Xq[l]=X;
                                    Yq[l]=Y;
                                    e[l]=e[i];
                                }
                                else if(l==M){
                                    Xp[l]=X;
                                    Yp[l]=Y;
                                    Xq[l]=rx1;
                                    Yq[l]=ry1;
                                    b[l]=e[i];
                                    e[l]=re2;
                                }
                                else continue;
                            }
                        }
                    }
                    continue;
                }
                /*---------------------------------*/
                    
                x[N+k]=X;  //座標行列に交点座標を追加
                y[N+k]=Y;
                    
                //交点を加えた隣接行列を随時更新
                for(l=0;l<N+k;l++){
                    if(l==b[i]-1 || l==e[i]-1 || l==b[j]-1 || l==e[j]-1) 
                        Distance[l][N+k]=1;
                    else Distance[l][N+k]=-1;
                }
                    
                for(l=0;l<N+k;l++){
                     if(l==b[i]-1 || l==e[i]-1 || l==b[j]-1 || l==e[j]-1) 
                        Distance[N+k][l]=1;
                    else Distance[N+k][l]=-1;
                }
                //cout<<" inX\n";
                Distance[b[i]-1][e[i]-1]=-1;
                Distance[e[i]-1][b[i]-1]=-1;
                Distance[b[j]-1][e[j]-1]=-1;
                Distance[e[j]-1][b[j]-1]=-1;

                k++;
                rx1=Xq[i];
                ry1=Yq[i];
                rx2=Xq[j];
                ry2=Yq[j];
                re1=e[i];
                re2=e[j];
                //辺の更新
                m=m+2;
               for(l=0;l<M+m;l++){
                    if(l==i||l==j){
                        Xq[l]=X;
                        Yq[l]=Y;
                        e[l]=N+k;
                    }
                    else if(l==M+m-2){
                        Xp[l]=X;
                        Yp[l]=Y;
                        Xq[l]=rx1;
                        Yq[l]=ry1; 
                        b[l]=N+k;
                        e[l]=re1;  
                    }
                    else if(l==M+m-1){
                        Xp[l]=X;
                        Yp[l]=Y;
                        Xq[l]=rx2;
                        Yq[l]=ry2;
                        b[l]=N+k;
                        e[l]=re2;
                    }
                    else continue;
                }              
            }
            else continue;
        }

    }
    

    for(i=0;i<N+k;i++)
    {
        for(j=0;j<N+k;j++)
        {   
            if(x[i]==x[j] && y[i]==y[j]) 
                Distance[i][j]=0;
            if(Distance[i][j]==1)
                Distance[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
        }
    }
    
    for(i=0;i<M+m;i++){
        cout<<setprecision(3)<<Xp[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M+m;i++){
        cout<<setprecision(3)<<Yp[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M+m;i++){
        cout<<setprecision(3)<<Xq[i]<<"\t";
    }
    cout<<"\n";
    for(i=0;i<M+m;i++){
        cout<<setprecision(3)<<Yq[i]<<"\t";
    }
    cout<<"\n";

    cout<<"-------------------------------------\n";

    for(i=0;i<N+k;i++){
        for(j=0;j<N+k;j++){
            cout<<setprecision(3)<<Distance[i][j]<<"\t";
        }
        cout<<"\n";
    }

   
    return 0;
}
    
   