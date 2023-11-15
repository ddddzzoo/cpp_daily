#include <iostream>

class Date {
  using Month = int;

 public:
  Month m;

  int month() const { return m; }
};

void func(const Date& date) { std::cout << date.month() << '\n'; }

int main() {
  Date d{10};
  func(d);
}