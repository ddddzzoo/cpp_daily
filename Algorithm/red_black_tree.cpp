// 红黑树
// 1.节点只有黑和红
// 2.根节点是黑
// 3.所有叶子节点都是黑
// 4.如果一个节点是红色的，则它的两个孩子节点都是黑色的
// 5.任意节点到其每个叶子节点的黑节点相同

#include <iostream>

enum Color { RED, BLACK };

template <typename T>
struct TreeNode {
  T data;
  TreeNode<T>* parent;
  TreeNode<T>* left;
  TreeNode<T>* right;
  Color color;

  TreeNode(const T& value)
      : data(value),
        parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(RED) {}
};

template <typename T>
class RedBlackTree {
 private:
  TreeNode<T>* root;
  // 左旋
  void leftRotate(TreeNode<T>*&);
  // 右旋
  void rightRotate(TreeNode<T>*&);
  // 插入修复
  void insertFixup(TreeNode<T>*&);
  // 插入节点
  void insertNode(TreeNode<T>*&, TreeNode<T>*&);
  // 删除节点
  void transplant(TreeNode<T>*, TreeNode<T>*);
  // 删除修正
  void deleteFixup(TreeNode<T>*);
  // 查找节点
  TreeNode<T>* findNode(const T&);
  // 插入最小值
  TreeNode<T>* minimum(TreeNode<T>*);
  // 中序遍历
  void inOrderTraversal(TreeNode<T>*);

 public:
  RedBlackTree() : root(nullptr) {}
  ~RedBlackTree() = default;

  // 插入
  void insert(const T&);
  // 删除
  void remove(const T&);
  // 中序遍历输出
  void printInOrder();

 private:
};

//   x                    y
//  / \     左旋转        / \
// lx  y   --------->   x   ry
//    / \              / \
//   ly  ry          lx  ly
template <typename T>
void RedBlackTree<T>::leftRotate(TreeNode<T>*& x) {
  // 处理x的右子节点
  TreeNode<T>* y = x->right;  // 右节点变成x的父节点，保存右节点
  x->right = y->left;         // ly变成x的右节点
  if (y->left != nullptr) {
    y->left->parent = x;
  }

  // 处理y与父节点的关系
  y->parent = x->parent;  // 原来x的父节点变为y的父节点

  if (x->parent == nullptr) {  // 当x为root节点时需要将y设置为root节点
    root = y;
  }
  else if (x == x->parent->left) {
    x->parent->left = y;  // 原x的父节点的左子节点连接新节点y
  }
  else {
    x->parent->right = y;  // 原x的父节点的右子节点连接新节点y
  }

  // 处理x与y的关系
  y->left = x;
  x->parent = y;
}

//     x                    y
//    / \     右旋转        / \
//   y   rx   ---------> ly   x
//  / \                      / \
// ly  ry                  ry   rx
template <typename T>
void RedBlackTree<T>::rightRotate(TreeNode<T>*& x) {
  // 处理x的左子节点
  TreeNode<T>* y = x->left;  // 左节点变成x的父节点，保存左节点
  y->right = x->left;        // ry变成x的左节点
  if (y->right != nullptr) {
    y->right->parent = x;
  }

  // 处理y与父节点的关系
  y->parent = x->parent;  // 原来x的父节点变为y的父节点

  if (x->parent == nullptr) {
    root = y;
  }
  else if (x == x->parent->right) {
    x->parent->right = y;  // 原x的父节点的右子节点连接新节点y
  }
  else {
    x->parent->left = y;  // 原x的父节点的左子节点连接新节点y
  }

  // 处理x与y的关系
  y->right = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::insertFixup(TreeNode<T>*& z) {
  while (z->parent != nullptr &&
         z->parent->color == RED) {  // 当前节点的父节点为红色，需要进行调整
    // 当前节点的父节点是祖父节点的左子节点
    if (z->parent == z->parent->parent->left) {
      TreeNode<T>* y = z->parent->parent->right;  // 获取叔叔节点

      if (y != nullptr && y->color == RED) {  // 叔叔节点存在且为红色
        // 颜色翻转，父亲和叔叔节点都变为黑色，祖父节点变为红色，当前节点设置为祖父节点，依次往上判断是否破坏了红黑树的性质
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else {  // 无叔叔节点或叔叔节点不是黑色
        if (z == z->parent->right) {  // 当前节点为父节点的右节点
          z = z->parent;
          leftRotate(z);  // 以父节点进行左旋,旋转后当前节点为父节点的左节点
        }

        // 改变颜色，以祖父节点右旋
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(z->parent->parent);
      }
    }
    else {  // 当前节点的父节点是祖父节点的右子节点
      TreeNode<T>* y = z->parent->parent->right;  // 获取叔叔节点

      if (y != nullptr && y->color == RED) {  // 叔叔节点存在且为红色
        // 颜色翻转，父亲和叔叔节点都变为黑色，祖父节点变为红色，当前节点设置为祖父节点，依次往上判断是否破坏了红黑树的性质
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(z);  // 以父节点进行右旋,旋转后当前节点为父节点的右节点
        }

        // 改变颜色，以祖父节点左旋
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotate(z->parent->parent);
      }
    }
  }

  // 若插入节点为根节点 重新赋值为黑色
  root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::insertNode(TreeNode<T>*& root, TreeNode<T>*& z) {
  // 按照二叉树的性质插入节点
  Node<T>* y = nullptr;
  Node<T>* x = root;

  // 找到插入节点的父节点
  while (x != nullptr) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    }
    else {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == nullptr) {
    root = z;
  }
  else if (z->data < y->data) {
    y->left = z;
  }
  else {
    y->right = z;
  }
}

// 用节点v代替节点u
template <typename T>
void RedBlackTree<T>::transplant(TreeNode<T>* u, TreeNode<T>* v) {
  if (u->parent == nullptr) {  // U为根节点
    root = v;
  }
  else if (u == u->parent->left) {  // u为其父节点的左子节点
    u->parent->left = v;
  }
  else {  // u为其父节点的右子节点
    u->parent->right = v;
  }

  // 如果v不为空，更新v的父节点为u的父节点
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

template <typename T>
void RedBlackTree<T>::deleteFixup(TreeNode<T>* x) {
  while (x != root && (x == nullptr || x->color == BLACK)) {
    // 如果 x 是其父节点的左子节点
    if (x == x->parent->left) {
      Node<T>* w = x->parent->right;

      // 情况 1: 兄弟节点 w 为红色
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }

      // 情况 2: 兄弟节点 w 的两个子节点都为黑色
      if ((w->left == nullptr || w->left->color == BLACK) &&
          (w->right == nullptr || w->right->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      }
      else {
        // 情况 3: 兄弟节点 w 的右子节点为黑色
        if (w->right == nullptr || w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(w);
          w = x->parent->right;
        }

        // 情况 4: 兄弟节点 w 为黑色，且 w 的右子节点为红色
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(x->parent);
        x = root;
      }
    }
    else {
      // 如果 x 是其父节点的右子节点，与上面对称的情况
      Node<T>* w = x->parent->left;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }

      if ((w->right == nullptr || w->right->color == BLACK) &&
          (w->left == nullptr || w->left->color == BLACK)) {
        w->color = RED;
        x = x->parent;
      }
      else {
        if (w->left == nullptr || w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
      }
    }
  }

  // 将根节点的颜色设置为黑色，保持红黑树性质
  if (x != nullptr)
    x->color = BLACK;
}

template <typename T>
TreeNode<T>* RedBlackTree<T>::findNode(const T&) {
  return nullptr;
}

template <typename T>
TreeNode<T>* RedBlackTree<T>::minimum(TreeNode<T>*) {
  return nullptr;
}

template <typename T>
void RedBlackTree<T>::inOrderTraversal(TreeNode<T>*) {}

template <typename T>
void RedBlackTree<T>::insert(const T& value) {
  TreeNode<T>* z = new TreeNode<T>(value);
  insertNode(root, z);
  insertFixup(z);
}

template <typename T>
void RedBlackTree<T>::remove(const T&) {}

template <typename T>
void RedBlackTree<T>::printInOrder() {}

int main() {
  RedBlackTree<int> rbTree;

  rbTree.insert(10);
  rbTree.insert(20);
  rbTree.insert(30);
  rbTree.insert(15);
  rbTree.insert(25);

  std::cout << "In-Order Traversal of Red-Black Tree: ";
  rbTree.printInOrder();

  rbTree.remove(20);

  std::cout << "In-Order Traversal after removing 20: ";
  rbTree.printInOrder();

  return 0;
}