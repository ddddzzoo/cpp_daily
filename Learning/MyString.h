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
    if (this != &rhs) {  // ��ֹ���Ҹ���
      delete[] _pstr;
      _pstr = nullptr;
      _pstr = new char[strlen(rhs._pstr) + 1]();  // ���
      strcpy(_pstr, rhs._pstr);
    }
    return *this;
  }

  // (������ֵʱ)�����ƶ�����ĺ������Ⱦ��и�������ĺ���
  // �ƶ����캯�����ƶ���ֵ�����������Ϊ�����ƶ����庯��
  // �ƶ����캯����ֻ�����ֵ��
  MyString(MyString&& rhs) : _pstr(rhs._pstr) {
    std::cout << "MyString(MyString&& rhs)" << std::endl;
    rhs._pstr = nullptr;
  }

  // �ƶ���ֵ���������
  MyString& operator=(MyString&& rhs) {
    std::cout << "MyString &operator= (MyString&& rhs)" << std::endl;
    if (this != &rhs) {  // �������ƶ�
      delete[] _pstr;    // �ͷ��������
      _pstr = nullptr;
      _pstr = rhs._pstr;    // ת���Ҳ���������Դ
      rhs._pstr = nullptr;  // �Ҳ�������Ϊ��
    }

    return *this;  // ����*this
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
  // MyString("world") ��ֵ����ʱ�������ݴ���ջ��
  std::cout << "s2 = " << s2 << std::endl;

  std::cout << std::endl;
  MyString s4 = "****";
  // std::move����ֵת��Ϊ��ֵ
  // ʵ���Ϸ�����ǿ��ת��static_cast<T &&>(lvalue)
  s2 = std::move(s4);  // MyString &operator= (MyString&& rhs)
  std::cout << "s2 = " << s2 << std::endl;
}