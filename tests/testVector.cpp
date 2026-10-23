#include <iostream>
#include <vector>

int main(){
    std::vector<int> nums(5, 1);
    for(auto i : nums){
        std::cout<<i<<std::endl;
    }
    nums.resize(0);
    std::cout<<std::endl;
    for(auto i : nums){
        std::cout<<i<<std::endl;
    }
    return 0;
}