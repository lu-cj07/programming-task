#include <iostream>
class Book{
    private:
        int id;
    public:
        Book(int id){this->id = id;}
        /*
            const成员函数
            此处的const用于隐式修改this指针的类型，由于默认情况下this的类型是
            T *const(常量指针)所以无法直接把this绑定到一个常量对象上，c++允许
            在参数列表时候紧跟一个const关键字，使得this的类型修饰为const T *const(指向常量的常量指针)
        */
        int getId() const {return id;}
};

int main(){
    const Book book = Book(1);
    std::cout<<book.Book::getId()<<std::endl;
    return 0;
}