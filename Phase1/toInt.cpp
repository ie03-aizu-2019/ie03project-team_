#include <iostream>
#include <string>
#include "team.h"
using namespace std;


int to_int(string s)
{
    int S;
    int i;

    if(s[0]=='C')
    {
        s.erase(s.begin() + 0); 
        S=atoi(s.c_str());
        return S;
        
    } 
    
    else 
    {
        S=atoi(s.c_str());
        return S;
    }
}
