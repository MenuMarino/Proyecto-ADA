#include <iostream>
#include <vector>
#include "MinMatch.h"

using namespace std;

int main() {
    ///Vectores
    vector<int> A = {0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,1};
    vector<int> B = {0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,1};
    auto minMatch = new MinMatch(A, B);

    ///Algoritmos
    minMatch->recursivo();
    minMatch->memoizado();
    minMatch->dinamico();

    delete(minMatch);
    return 0;
}