#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class tree_elem {
public:
  int m_data;
  tree_elem *m_left;
  tree_elem *m_right;

  tree_elem(int val) {
    m_left = nullptr;
    m_right = nullptr;
    m_data = val;
  }
  tree_elem(tree_elem &other) {
    m_data = other.m_data;
    m_left = other.m_left;
    m_right = other.m_right;
  }
  tree_elem &operator=(tree_elem &other) {
    m_data = other.m_data;
    m_left = other.m_left;
    m_right = other.m_right;
    return *this;
  }
};
void delete_tree(tree_elem *curr) {
  if (curr->m_left)
    delete_tree(curr->m_left);
  if (curr->m_right)
    delete_tree(curr->m_right);
  delete curr;
}

void print_tree(tree_elem *curr) {
  if (curr) {
    print_tree(curr->m_left);
    cout << curr->m_data << " ";
    print_tree(curr->m_right);
  }
}

class binary_tree {

public:
  tree_elem *m_root;
  int m_size;
  explicit binary_tree(int key) {
    m_root = new tree_elem(key);
    m_size = 1;
  }
  explicit binary_tree() {
    m_root = nullptr;
    m_size = 0;
  }
  binary_tree(const binary_tree &other) {
    stack<tree_elem *> node_stack;
    m_root = new tree_elem(*other.m_root);
    m_root->m_right = nullptr;
    m_root->m_left = nullptr;
    m_size = 1;
    node_stack.push(other.m_root);
    while (!node_stack.empty()) {
      tree_elem *temp = new tree_elem(*node_stack.top());
      this->insert(temp->m_data);
      node_stack.pop();
      if (temp->m_right)
        node_stack.push(temp->m_right);
      if (temp->m_left)
        node_stack.push(temp->m_left);
      delete temp;
    }
  }
  binary_tree &operator=(const binary_tree &other) {
    if (this == &other)
      return *this;
    delete_tree(m_root);
    queue<tree_elem *> node_stack;
    m_root = new tree_elem(*other.m_root);
    m_root->m_right = nullptr;
    m_root->m_left = nullptr;
    m_size = 1;
    node_stack.push(other.m_root);
    while (!node_stack.empty()) {
      tree_elem *temp = new tree_elem(*node_stack.front());
      this->insert(temp->m_data);
      node_stack.pop();
      if (temp->m_right)
        node_stack.push(temp->m_right);
      if (temp->m_left)
        node_stack.push(temp->m_left);
      delete temp;
    }
    return *this;
  }
  ~binary_tree() { delete_tree(m_root); }
  void print() {
    if (m_root != nullptr)
      print_tree(m_root);
    else
      cout << "empty";
    cout << endl;
  }
  bool find(int key) {
    tree_elem *curr = m_root;
    while (curr != nullptr) {
      if (curr->m_data == key)
        return true;
      else if (curr->m_data > key)
        curr = curr->m_left;
      else
        curr = curr->m_right;
    }
    return false;
  }
  void insert(int key) {
    if (m_root == nullptr) {
      m_root = new tree_elem(key);
      ++m_size;
    } else {
      tree_elem *curr = m_root;
      while (curr && curr->m_data != key) {
        if (curr->m_data > key && curr->m_left == nullptr) {
          curr->m_left = new tree_elem(key);
          ++m_size;
          return;
        }
        if (curr->m_data < key && curr->m_right == nullptr) {
          curr->m_right = new tree_elem(key);
          ++m_size;
          return;
        }
        if (curr->m_data > key)
          curr = curr->m_left;
        else
          curr = curr->m_right;
      }
    }
  }
  int min() {
    tree_elem *curr = m_root;
    while (curr->m_left != nullptr) {
      curr = curr->m_left;
    }
    return curr->m_data;
  }
  int max() {
    tree_elem *curr = m_root;
    while (curr->m_right != nullptr) {
      curr = curr->m_right;
    }
    return curr->m_data;
  }
  void erase(int key) {
    tree_elem *curr = m_root;
    tree_elem *prev = nullptr;
    while (curr != nullptr && curr->m_data != key) {
      prev = curr;
      if (key < curr->m_data)
        curr = curr->m_left;
      else
        curr = curr->m_right;
    }
    if (curr == nullptr) {
      return;
    }

    if (curr->m_left == nullptr || curr->m_right == nullptr) {
      tree_elem *newCurr;
      if (curr->m_left == nullptr)
        newCurr = curr->m_right;
      else
        newCurr = curr->m_left;
      if (prev == nullptr) {
        prev = m_root;
        m_root = newCurr;
        delete prev;
        m_size--;
        return;
      }
      if (curr == prev->m_left)
        prev->m_left = newCurr;
      else
        prev->m_right = newCurr;
      delete curr;
    } else {
      tree_elem *p = nullptr;
      tree_elem *temp;
      temp = curr->m_right;
      while (temp->m_left != nullptr) {
        p = temp;
        temp = temp->m_left;
      }
      if (p != nullptr)
        p->m_left = temp->m_right;
      else
        curr->m_right = temp->m_right;
      curr->m_data = temp->m_data;
      delete temp;
    }
    m_size--;
  }
  int height() {
    if (m_root == nullptr)
      return 0;
    int max = 0;
    int cur_height;
    stack<pair<tree_elem *, int>> node_stack;
    node_stack.push(make_pair(m_root, 0));
    while (!node_stack.empty()) {
      auto *temp = new tree_elem(*node_stack.top().first);
      cur_height = node_stack.top().second;
      node_stack.pop();
      if (temp->m_right)
        node_stack.push(make_pair(temp->m_right, cur_height + 1));
      if (temp->m_left)
        node_stack.push(make_pair(temp->m_left, cur_height + 1));
      delete temp;
      if (cur_height > max)
        max = cur_height;
    }
    return max;
  }

  friend ostream &operator<<(ostream &out, binary_tree &self) {
    if (self.m_root == nullptr) {
      out << "empty" << endl;
      return out;
    }
    int space = 0;
    tree_elem *cur = self.m_root;
    stack<pair<tree_elem *, int>> s;
    while (cur != nullptr || !s.empty()) {
      while (cur != nullptr) {
        s.push(make_pair(cur, space += 5));
        cur = cur->m_right;
      }
      cur = s.top().first;
      space = s.top().second;
      for (int i = 5; i < space; ++i) {
        out << " ";
      }
      out << cur->m_data << endl;
      s.pop();
      cur = cur->m_left;
    }
    return out;
  }

  int size() const { return m_size; }
};

void to_vec(tree_elem *root, vector<tree_elem *> &a) {
  if (root == nullptr)
    return;
  to_vec(root->m_left, a);
  a.push_back(root);
  to_vec(root->m_right, a);
}

class balanced_bst : public binary_tree {
public:
  balanced_bst(const binary_tree &a) {
    tree_elem *temp = a.m_root;
    vector<tree_elem *> vec;
    to_vec(a.m_root, vec);
    m_root = util(vec, 0, vec.size() - 1);
    m_size = a.m_size;
  }
  tree_elem *util(const vector<tree_elem *> &a, int start, int end) {
    if (start > end)
      return nullptr;
    int mid = (start + end) / 2;
    tree_elem *root = a[mid];
    root->m_left = util(a, start, mid - 1);
    root->m_right = util(a, mid + 1, end);
    return root;
  }
};

int main() {
  int s[9] = {11, 15, 19, 7, 2, 8, 10, 12, 18};
  binary_tree tree(13);
  for (int i : s) {
    tree.insert(i);
  }
  if (tree.find(2) && tree.min() == 2 && tree.max() == 19 && tree.size() == 10)
    cout << "------------------------\nheight: " << tree.height() << endl
         << "------------------------" << endl
         << tree;
  binary_tree tree_check(3);
  balanced_bst bal(tree);
  cout << "\n------------------------\nnaive "
          "balanced\n------------------------\n"
       << bal;
  tree_check = tree;
  cout << "------------------------\nsize: " << tree_check.size() << endl
       << "------------------------" << endl;
  cout << tree_check;
  binary_tree tree_check_second(tree_check);
  tree.print();
  for (int i : s) {
    tree.erase(i);
  }
  tree.erase(13);
  tree.print();
  cout << tree.size() << endl;
  tree.insert(9);
  tree.erase(13);
  tree.print();
  cout << tree.size() << endl;

  return 0;
}
