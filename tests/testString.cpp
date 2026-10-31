#include <iostream>
#include <string>

int main(){
    std::string str = "hello world";
    auto first = str.find_first_not_of("\t");
    std::cout<<first<<std::endl;
    // stoll可以解析带+、-号的数据 stoi检查int范围，stoll检查long long范围
    auto num = std::stoll(std::string("-100"));
    std::cout<<num<<std::endl;
    return 0;
}