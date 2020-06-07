#include <iostream>
#include <vector>
#include <utility>
#include "MinMatch.h"

using namespace std;

int main() {
    vector<int> A = {1,0,1,1,0,1,1,0,0,0,0,1,0,1};
    vector<int> B = {0,1,1,0,0,1,1,1,0,1,0,0,1,1};
    auto minMatch = new MinMatch(A, B);



    delete(minMatch);
    return 0;
}