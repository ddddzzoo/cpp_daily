#include <iostream>
/*
有三根柱子（通常称为 A、B
和C），以及一些圆盘，圆盘的大小不同，初始时按照从大到小的顺序依次放在柱子 A 上。
问题的目标是将所有的圆盘从柱子 A 移动到柱子 C，同时遵守以下规则：
一次只能移动一个圆盘。
大的圆盘不能放在小的圆盘上面。
*/

static void move(char x, char y) { printf("%c --> %c\n", x, y); }

static void hanoi(int n, char one, char two, char three) {
  if (n == 1) {
    move(one, three);
  }
  else {
    hanoi(n - 1, one, three, two);
    move(one, three);
    hanoi(n - 1, two, one, three);
  }
}

int main() {
  int n = 5;
  hanoi(n, 'A', 'B', 'C');

  return 0;
}