#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int key) {
        value = key;
        left = right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() {
        root = nullptr;
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }

        if (key < root->value) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }

        return root;
    }

    void insertValue(int key) {
        root = insert(root, key);
    }

    int height(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int findMin(Node* root) {
        if (root == nullptr) {
            return -1;
        }
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->value;
    }

    Node* swapChildren(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        swap(root->left, root->right);
        swapChildren(root->left);
        swapChildren(root->right);
        return root;
    }

    Node* search(Node* root, int key) {
        if (root == nullptr || root->value == key) {
            return root;
        }

        if (key < root->value) {
            return search(root->left, key);
        }

        return search(root->right, key);
    }

    Node* searchValue(int key) {
        return search(root, key);
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
        }
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;
    int choice, value;
    Node* node = nullptr;

    do {
        cout << "\n-------------------------------Binary Search Tree Operations Menu-------------------------\n";
        cout << "1. Insert a node\n";
        cout << "2. Find height (Longest path from root)\n";
        cout << "3. Find minimum value\n";
        cout << "4. Swap left and right children\n";
        cout << "5. Search for a value\n";
        cout << "6. Inorder Traversal of the tree\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insertValue(value);
                cout << "Node inserted successfully.\n";
                break;

            case 2:
                cout << "Height of the tree (Longest path from root): " 
                     << bst.height(bst.root) << endl;
                break;

            case 3:
                cout << "Minimum value in the tree: " 
                     << bst.findMin(bst.root) << endl;
                break;

            case 4:
                bst.swapChildren(bst.root);
                cout << "Swapped left and right children at every node.\n";
                break;

            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                node = bst.searchValue(value);
                if (node) {
                    cout << "Node with value " << value << " found.\n";
                } else {
                    cout << "Node with value " << value << " not found.\n";
                }
                break;

            case 6:
                cout << "Inorder Traversal of the tree: ";
                bst.inorderTraversal();
                break;

            case 7:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}

