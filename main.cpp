#include <iostream>
#include <vector>
#include "MinMatch.h"

using namespace std;

int main() {
    vector<int> A = {0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,0,1,0};
    vector<int> B = {0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0};
    auto minMatch = new MinMatch(A, B);

    minMatch->recursivo();
    minMatch->memoizado();

    delete(minMatch);
    return 0;
}