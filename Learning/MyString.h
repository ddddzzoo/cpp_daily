#include <iostream>

class MyString {
 public:
  MyString() : _pstr(nullptr) { std::cout << "MyString()" << std::endl; }

  MyString(const char* pstr) : _pstr(new char[strlen(pstr) + 1]) {
    std::cout << "MyString(const char*)" << std::endl;
    strcpy(_pstr, pstr);
  }

  // MyString s2 = s1
  MyString(const MyString& rhs) : _pstr(new char[strlen(rhs._pstr) + 1]) {
    std::cout << "MyString(const MyString&)" << std::endl;
    strcpy(_pstr, rhs._pstr);
  }

  MyString& operator=(const MyString& rhs) {
    std::cout << "MyString& operator=(const MyString &)" << std::endl;
    if (this != &rhs) {  // 防止自我复制
      delete[] _pstr;
      _pstr = nullptr;
      _pstr = new char[strlen(rhs._pstr) + 1]();  // 深拷贝
      strcpy(_pstr, rhs._pstr);
    }
    return *this;
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

  ~MyString() {
    std::cout << "~MyString()" << std::endl;
    if (_pstr) {
      delete[] _pstr;
      _pstr = nullptr;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const MyString& rhs);

 private:
  char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const MyString& rhs) {
  if (rhs._pstr) {
    os << rhs._pstr;
  }
  return os;
}

void test() {
  MyString s1("Hello");  // MyString(const char*)
  std::cout << "s1 = " << s1 << std::endl;

  std::cout << std::endl;
  MyString s2 = s1;  // MyString(const MyString&)
  std::cout << "s1 = " << s1 << std::endl;
  std::cout << "s2 = " << s2 << std::endl;

  std::cout << std::endl;
  MyString s3 = "world";  // MyString(const char*)
  std::cout << "s3 = " << s3 << std::endl;

  std::cout << std::endl;
  s2 = MyString("world");  // MyString &operator= (MyString&& rhs)
  // MyString("world") 右值，临时对象会短暂存在栈上
  std::cout << "s2 = " << s2 << std::endl;

  std::cout << std::endl;
  MyString s4 = "****";
  // std::move将左值转换为右值
  // 实际上发生了强制转换static_cast<T &&>(lvalue)
  s2 = std::move(s4);  // MyString &operator= (MyString&& rhs)
  std::cout << "s2 = " << s2 << std::endl;
}