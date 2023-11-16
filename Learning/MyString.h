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
  // ......
 private:
  char* _pstr;
};

void test() { MyString s1("Hello"); }