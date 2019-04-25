#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

int main(){
    int x[4],y[4];
    int Xp[2],Yp[2];
    int Xq[2],Yq[2];
    int b[2],e[2];
    int N,M,P,Q,i;
    double X,Y;
    int Z=0,s,t;

    cin>>N>>M>>P>>Q;

    for(i=0;i<N;i++){
        cin>>x[i];
        cin>>y[i];
    }
    for(i=0;i<M;i++){
        cin>>b[i];
        cin>>e[i];
    }
    for(i=0;i<M;i++){
        Xp[i]=x[b[i]-1];
        Yp[i]=y[b[i]-1];
        Xq[i]=x[e[i]-1];
        Yq[i]=y[e[i]-1];
    }

    cout<<Xp[0];
    cout<<Yp[0];
    cout<<Xq[0];
    cout<<Yq[0];
    cout<<Xp[1];
    cout<<Yp[1];
    cout<<Xq[1];
    cout<<Yq[1]<<"\n";

    cout<<Xq[1]-Xp[1]<<"\n";
    cout<<Yp[0]-Yq[0]<<"\n";
    cout<<Xq[0]-Xp[0]<<"\n";
    cout<<Yq[1]-Yp[1]<<"\n";

    Z=abs(((Xq[1]-Xp[1])*(Yp[0]-Yq[0]))+((Xq[0]-Xp[0])*(Yq[1]-Yp[1])));
    
    cout<<Z<<"\n";
    
    if(Z==0){
        cout<<"NA"<<endl;
        exit(1);
    }
    else{
        s=((Yp[0]-Yq[0])*(Xq[1]-Xp[1])-(Xq[0]-Xp[0])*(Yp[1]-Yq[1]))/Z*(Xp[0]-Xp[1]);
        t=((Yp[0]-Yq[0])*(Xq[1]-Xp[1])-(Xq[0]-Xp[0])*(Yp[1]-Yq[1]))/Z*(Yp[0]-Yp[1]);
    }

    cout<<s<<"\n";
    cout<<t<<"\n";

    if(0<=s<=1&&0<=t<=1){
        X=Xp[1]+(Xq[1]-Xp[1])*s;
        Y=Yp[1]+(Yq[1]-Yp[1])*s;
        cout<<"交点座標は"<<"("<<X<<","<<Y<<")"<<"です\n"<<endl;
    }
    else{
        cout<<"NA\n"<<endl;
        exit(2);
    }


    return 0;
}