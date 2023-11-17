// 队列 先进先出 FIFO
// 通过链表实现队列和循环队列

#include <iostream>

template <typename T>
struct Node {
  T data;
  Node* next;

  explicit Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedListQueue {
 private:
  Node<T>* front;
  Node<T>* rear;

 public:
  LinkedListQueue() : front(nullptr), rear(nullptr) {}

  ~LinkedListQueue() {
    while (!isEmpty()) {
      dequeue();
    }
  }

  // 是否为空队列
  [[nodiscard]] bool isEmpty() const { return front == nullptr; }

  // 入队
  void enqueue(const T& value) {
    auto* new_node = new Node(value);
    if (isEmpty()) {
      front = rear = new_node;
      rear->next = front;  // 构成循环
    }
    else {
      rear->next = new_node;
      rear = new_node;
      rear->next = front;  // 构成循环
    }
  }

  // 出队
  void dequeue() {
    if (isEmpty()) {
      std::cerr << "Error: Queue is empty." << std::endl;
      return;
    }

    Node<T>* temp = front;
    if (front == rear) {
      front = rear = nullptr;
    }
    else {
      front = front->next;
      rear->next = front;  // 更新循环队列尾部指向头部
    }

    delete temp;
  }

  // 查看队首元素
  [[nodiscard]] T getFront() const {
    if (isEmpty()) {
      std::cout << "Error: Queue is empty." << std::endl;
      return T();
    }

    return front->data;
  }
};

int main() {
  LinkedListQueue<int> queue;

  // 入队
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  // 查看队首元素
  std::cout << "Front element: " << queue.getFront() << std::endl;

  // 出队
  queue.dequeue();
  std::cout << "Front element after dequeue: " << queue.getFront() << std::endl;

  return 0;
}