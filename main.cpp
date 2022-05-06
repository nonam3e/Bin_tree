#include <iostream>

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

class binary_tree {
	tree_elem * m_root;
	int m_size;
	void print_tree (tree_elem * curr) {
        if (curr) {
            print_tree (curr->m_left);
            cout << curr->m_data << " ";
            print_tree (curr->m_right);
		}
    }
	void delete_tree (tree_elem * curr) {
		delete_tree (curr->m_left);
		delete_tree (curr->m_right);
		delete curr;
	}
public:
	binary_tree (int key) {
		m_root = new tree_elem(key);
		m_size = 1;
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
            else if (curr->m_data < key)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
        return false;
    }
	void insert (int key) {
		tree_elem * curr = m_root;
		while (curr && curr->m_data != key) {
			if (curr->m_data > key && curr->m_left == NULL) {
				curr->m_left = new tree_elem(key);
				++m_size;
				return;
			}
			if (curr->m_data < key && curr->m_right == NULL) {
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
    binary_tree  tree (13);
    for (int i = 0; i < 9; i++) { tree.insert(s[i]); }
    tree.print();
    return 0;
}
