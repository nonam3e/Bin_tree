#include <iostream>
#include <stack>

using namespace std;

class tree_elem {
public:
	int m_data;
	tree_elem * m_left;
	tree_elem * m_right;


	tree_elem(int val) {
		m_left = nullptr;
		m_right = nullptr;
		m_data = val;
	}

};
void delete_tree (tree_elem * curr) {
    if (curr->m_left) delete_tree (curr->m_left);
    if (curr->m_right) delete_tree (curr->m_right);
    delete curr;
}

void print_tree (tree_elem * curr) {
    if (curr) {
        print_tree (curr->m_left);
        cout << curr->m_data << " ";
        print_tree (curr->m_right);
    }
}

class binary_tree {
	tree_elem * m_root;
	int m_size;
public:
	explicit binary_tree (int key) {
		m_root = new tree_elem(key);
		m_size = 1;
	}
	binary_tree& operator = (const binary_tree& other) {
		if(this == &other) return *this;
		delete_tree(m_root);
		stack <tree_elem *> node_stack;
		m_root = new tree_elem(*other.m_root);
        m_root->m_right = nullptr;
        m_root->m_left = nullptr;
		m_size = 1;
		node_stack.push(other.m_root);
		while (!node_stack.empty()) {
			tree_elem *temp = new tree_elem(*node_stack.top());
			this->insert(temp->m_data);
			node_stack.pop();
            if (temp->m_right) node_stack.push(temp->m_right);
			if (temp->m_left) node_stack.push(temp->m_left);
            delete temp;
		}
		return *this;

	}
	~binary_tree () {
		delete_tree (m_root);
	}
	void print () {
		print_tree (m_root);
		cout << endl;
	}
	bool find (int key) {
		tree_elem * curr = m_root;
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
	void insert (int key) {
		tree_elem * curr = m_root;
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
	int min() {
		tree_elem * curr = m_root;
		while (curr->m_left != nullptr) {
			curr = curr->m_left;
		}
		return curr->m_data;
	}
	int max() {
		tree_elem * curr = m_root;
		while (curr->m_right != nullptr) {
			curr = curr->m_right;
		}
		return curr->m_data;
	}
	void erase (int);
	int size() {
		return m_size;
	}
};


int main()
{
	int s[9] = {11,15,19,7,2,8,10,12,18 };
	binary_tree tree (13);
	for (int i : s) { tree.insert(i); }
    if (tree.find(2) && tree.min() == 2 && tree.max() == 19 && tree.size() == 10)
	   tree.print();
	binary_tree tree_check(3);
	tree_check = tree;
	cout<<tree_check.size()<<endl;
	tree_check.print();

	return 0;
}
