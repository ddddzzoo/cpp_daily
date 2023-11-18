// 二叉树

#include <iostream>

template <typename T>
struct TreeNode {
  T data;
  TreeNode<T>* left;
  TreeNode<T>* right;

  explicit TreeNode(const T& value)
      : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
 private:
  TreeNode<T>* root;

  void destoryTree(TreeNode<T>* node) {
    if (node) {
      destoryTree(node->left);
      destoryTree(node->right);
      delete node;
    }
  }

 public:
  BinaryTree() : root(nullptr) {}

  ~BinaryTree() { destoryTree(root); }

  // 插入树
  void insert(const T& value) { root = insertRec(root, value); }

  // 中序遍历
  void printInOrder() { printInOrderRec(root); }

 private:
  TreeNode<T>* insertRec(TreeNode<T>* node, const T& value) {
    if (node == nullptr) {
      return new TreeNode<T>(value);
    }

    if (value < node->data) {
      node->left = insertRec(node->left, value);
    }
    else if (value > node->data) {
      node->right = insertRec(node->right, value);
    }

    return node;
  }

  void printInOrderRec(TreeNode<T>* node) {
    if (node) {
      printInOrderRec(node->left);
      std::cout << node->data << " ";
      printInOrderRec(node->right);
    }
  }
};

int main() {
  BinaryTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);

  std::cout << "In-order traversal: ";
  tree.printInOrder();
  std::cout << std::endl;

  return 0;
}