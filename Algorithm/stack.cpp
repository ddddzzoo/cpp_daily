// 栈 后进先出 LIFO
// 通过链表实现

#include <iostream>

// 链表节点
template <typename T>
struct Node {
  T data;
  Node *next;

  Node(T value) : data(value), next(nullptr) {}
};

// 链表栈
template <typename T>
class LinkedListStack {
 private:
  Node<T> *top;  // 栈顶指针
 public:
  LinkedListStack() : top(nullptr) {}

  ~LinkedListStack() {}

  // 入栈
  void push(T value) {
    Node<T> *new_node = new Node(value);
    new_node->next = top;
    top = new_node;
  }

  // 出栈
  T pop() {
    if (isEmpty()) {
      std::cerr << "Error: Stack is empty." << std::endl;
      return T();  // 返回默认值
    }

    Node<T> *tmp = top;
    T pop_value = top->data;
    top = top->next;
    delete tmp;
    return pop_value;
  }

  // 查看栈顶元素
  T peek() const {
    if (isEmpty()) {
      std::cerr << "Error: Stack is empty." << std::endl;
      return T();  // 返回默认值
    }
    return top->data;
  }

  // 是否为空栈
  bool isEmpty() const { return top == nullptr; }

  // 获取栈大小
  int size() const {
    int count = 0;
    Node<T> *current = top;
    while (current) {
      count++;
      current = current->next;
    }
    return count;
  }
};

int main() {
  LinkedListStack<int> stack;

  // 入栈
  stack.push(1);
  stack.push(2);
  stack.push(3);

  // 出栈
  std::cout << "Popped: " << stack.pop() << std::endl;

  // 查看栈顶元素
  std::cout << "Top: " << stack.peek() << std::endl;

  // 输出栈的大小
  std::cout << "Size: " << stack.size() << std::endl;

  return 0;
}