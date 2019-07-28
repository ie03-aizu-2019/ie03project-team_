#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void printVector( vector<int> &vec ){
    cout << "size = " << vec.size() << endl;
    for(int i = 0; i < (int)vec.size(); ++i){
        cout << vec[i] << ", ";
    }
    cout << endl << endl;
}

int main(void){
    // 8つの要素を持つvector<int>型の変数vecを作成
    int _vec[] = {5, 3, 5, 2, 7, 5, 5, 3};
    vector<int> vec(&_vec[0], &_vec[ sizeof(_vec) / sizeof(_vec[0]) ]);
    
    // unique()を使う準備としてソートが必要
    sort(vec.begin(), vec.end());
    // unique()をしただけでは後ろにゴミが残るので、eraseで削除する
    vec.erase( unique(vec.begin(), vec.end()), vec.end() );

    printVector(vec); // 2, 3, 5, 7, 
    
    return 0;
}