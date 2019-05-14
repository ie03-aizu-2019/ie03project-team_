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
    double Z=0;
    double s,t;

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

    
    Z = abs(((Xq[0] - Xp[0]) * (Yp[1] - Yq[1])) + ((Xq[1] - Xp[1]) * (Yq[0] - Yp[0])));

    cout<<Z<<"\n";
    
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