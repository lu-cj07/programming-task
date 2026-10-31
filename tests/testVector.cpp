#include <iostream>
#include <vector>

int main(){
    std::vector<int> nums(5, 1);
    
    for(auto i : nums){
        std::cout<<i;
    }
    // 调整数组存储元素数量为0
    // 容量不改变
    nums.resize(0);
    std::cout<<'\r\r'<<"capacity:"<<std::endl<<nums.capacity()<<std::endl;
    std::cout<<sizeof(int)<<"、"<<sizeof(int64_t)<<std::endl;
    for(auto i : nums){
        std::cout<<i<<std::endl;
    }

    return 0;
}