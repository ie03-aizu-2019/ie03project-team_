#include <iostream>
#include <string>
using namespace std;

#define Nmax 1000
#define Nmin 2
#define Mmax 500
#define Mmin 1
#define Qmax 100
#define Qmin 0
#define XYmax 1000
#define XYmin 0

#define INF 1e10
#define EPS 1e-8

//地点数、道数、最短ルート数
extern int N,M,P,Q; 

struct Point{
    double x,y; 

    bool operator<(const Point& right)const{
        return x==right.x?y<right.y:x<right.x;
  }
};

struct Line{
    Point P,Q;
};

Point searchIntersection(Line L1, Line L2);
int to_int(string s);
int dijkstra(int start, int goal);
