#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

int main(){
    int n = 10;
    std::vector< std::vector<int> > x(n);
    std::cout << x.size() << std::endl;
    for(int idx = 0; idx < n; idx++){
        x[idx].push_back(idx);
        std::cout << x[idx].size() << std::endl;
    }
}