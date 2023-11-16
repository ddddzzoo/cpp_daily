#include <iostream>

class MyString {
 public:
  MyString() : _pstr(nullptr) { std::cout << "MyString()" << std::endl; }

  MyString(const char* pstr) : _pstr(new char[strlen(pstr) + 1]) {
    std::cout << "MyString(const char*)" << std::endl;
    strcpy(_pstr, pstr);
  }

  MyString(const MyString& rhs) : _pstr(new char[strlen(rhs._pstr) + 1]) {
    std::cout << "MyString(const MyString&)" << std::endl;
    strcpy(_pstr, rhs._pstr);
  }



  // (传递右值时)具有移动语义的函数优先具有复制语义的函数
  // 移动构造函数、移动赋值运算符函数称为具有移动语义函数
  // 移动构造函数（只针对右值）
  MyString(MyString&& rhs) : _pstr(rhs._pstr) {
    std::cout << "MyString(MyString&& rhs)" << std::endl;
    rhs._pstr = nullptr;
  }

  // 移动赋值运算符函数
  MyString& operator=(MyString&& rhs) {
    std::cout << "MyString &operator= (MyString&& rhs)" << std::endl;
    if (this != &rhs) {  // 考虑自移动
      delete[] _pstr;    // 释放左操作数
      _pstr = nullptr;
      _pstr = rhs._pstr;    // 转移右操作数的资源
      rhs._pstr = nullptr;  // 右操作数置为空
    }

    return *this;  // 返回*this
  }
  // ......
 private:
  char* _pstr;
};

void test() { MyString s1("Hello"); }