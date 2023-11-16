#include <iostream>
/*
���������ӣ�ͨ����Ϊ A��B
��C�����Լ�һЩԲ�̣�Բ�̵Ĵ�С��ͬ����ʼʱ���մӴ�С��˳�����η������� A �ϡ�
�����Ŀ���ǽ����е�Բ�̴����� A �ƶ������� C��ͬʱ�������¹���
һ��ֻ���ƶ�һ��Բ�̡�
���Բ�̲��ܷ���С��Բ�����档
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