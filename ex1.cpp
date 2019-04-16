#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

int main(){
    double Ax[2],Ay[2];
    double Bx[2],By[2];
    double s,t,Z,X,Y;
    int i;

    cout<<"線分Aの端点座標を入力してください"<<endl;
    for(i=0;i<2;i++){
        cin>>Ax[i];
        cin>>Ay[i];
    }
    cout<<"線分Bの端点座標を入力してください"<<endl;
    for(i=0;i<2;i++){
        cin>>Bx[i];
        cin>>By[i];
    }
    
    Z=abs((Ax[1]-Ax[0])*(By[0]-By[1])+(Bx[1]-By[0])*(Ay[1]-Ay[0]));
    
    if(Z==0){
        cout<<"NA"<<endl;
        exit(1);
    }
    else{
        //cout<<"Zは"<<Z<<endl;
        s=(((By[0]-By[1])*(Ax[1]-Ax[0])-(Bx[1]-Bx[0])*(Ay[0]-Ay[1]))/Z)*(Bx[0]-Ax[0]);
        t=(((By[0]-By[1])*(Ax[1]-Ax[0])-(Bx[1]-Bx[0])*(Ay[0]-Ay[1]))/Z)*(By[0]-Ay[0]);
    }

    if(0<=s<=1&&0<=t<=1){
        X=Ax[0]+((Ax[1]-Ax[0])*s);
        Y=Ay[0]+((Ay[1]-Ay[0])*t);
        cout<<"交点座標は"<<"("<<X<<","<<Y<<")"<<"です\n"<<endl;
    }
    else{
        cout<<"交点なし\n"<<endl;
        exit(2);
    }


    return 0;
}