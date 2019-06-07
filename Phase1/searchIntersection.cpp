#include <iostream>
#include <cstdlib>
#include "team.h"
using namespace std;

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