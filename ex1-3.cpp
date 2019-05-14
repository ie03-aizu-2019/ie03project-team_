#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(){
    int x[200],y[200];
    int Xp[100],Yp[100];
    int Xq[100],Yq[100];
    int b[100],e[100];
    int N,M,P,Q,i,j,k=0;
    double Cx[100],Cy[100];
    double X,Y;
    double Z=0;
    double s,t;

    cin>>N>>M>>P>>Q;
    cout<<"------\n";

    for(i=0;i<N;i++){
        cin>>x[i];
        cin>>y[i];
    }
    cout<<"------\n";

    for(i=0;i<M;i++){
        cin>>b[i];
        cin>>e[i];
    }
    cout<<"------\n";

    for(i=0;i<M;i++){
        Xp[i]=x[b[i]-1];
        Yp[i]=y[b[i]-1];
        Xq[i]=x[e[i]-1];
        Yq[i]=y[e[i]-1];
    }
    
    for(i=0;i<M;i++){
        for(j=i+1;j<M;j++){
            Z = 0;
            s = 0;
            t = 0;

            Z = abs(((Xq[i] - Xp[i]) * (Yp[j] - Yq[j])) + ((Xq[j] - Xp[j]) * (Yq[i] - Yp[i])));
    
            if(Z==0) continue;
            else{
                s = ((Yp[j] - Yq[j]) * (Xp[j] - Xp[i]) + (Xq[j] - Xp[j]) * (Yp[j] - Yp[i])) / Z;
                t = ((Yp[i] - Yq[i]) * (Xp[j] - Xp[i]) + (Xq[i] - Xp[i]) * (Yp[j] - Yp[i])) / Z;
            }

            if (0 <= s && s <= 1){
                if (0 <= t && t <= 1){
                    X = Xp[i] + (Xq[i] - Xp[i]) * s;
                    Y = Yp[i] + (Yq[i] - Yp[i]) * s;
                    if(X==Xp[i] || X==Xq[i] || X==Xp[j] || X==Xq[j]) continue;
                    cout << "交点座標は"<< "(" << X << "," << Y << ")"<< "です\n";
                    Cx[k]=X;
                    Cy[k]=Y;
                    k++;
                }
            }
            else continue;
        }
    }

    for(i=0;i<3;i++){
        cout<<Cx[i]<<" "<<Cy[i]<<"\n";
    }


return 0;
}