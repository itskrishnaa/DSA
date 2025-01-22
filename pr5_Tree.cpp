//Practical 5: Books and Sections with Tree


#include<iostream>
#include<vector>
using namespace std;

struct Node{
    string ch_name;
    struct Node* child[10];
    int ch_count;
};

class GT{
public:
    void create_tree();
    void display(Node* r1);
    int calculate_height(Node* r1);
    void menu();
    
    GT() {
        root = NULL;
    }
private:
    Node* root;
};

void GT::create_tree() {
    root = new Node;
    
    cout << "Enter name of the book: ";
    getline(cin, root->ch_name);
    cout << "Enter number of chapters: ";
    cin >> root->ch_count;
    cin.ignore();
    
    for (int i = 0; i < root->ch_count; i++) {
        root->child[i] = new Node;
        cout << "Enter the name of chapter " << i + 1 << ": ";
        getline(cin, root->child[i]->ch_name);
        cout << "Enter the number of sections in chapter " << root->child[i]->ch_name << ": ";
        cin >> root->child[i]->ch_count;
        cin.ignore();
        
        for (int j = 0; j < root->child[i]->ch_count; j++) {
            root->child[i]->child[j] = new Node;
            cout << "Enter section " << j + 1 << " name: ";
            getline(cin, root->child[i]->child[j]->ch_name);
        }
    }
}

void GT::display(Node* r1) {
    if (r1 != NULL) {
        cout << "\n--------------------BOOK HIERARCHY-----------------------";
        cout << "\nBOOK TITLE: " << r1->ch_name;
        
        int tchapters = r1->ch_count;
        
        for (int i = 0; i < tchapters; i++) {
            cout << "\n Chapter " << i + 1 << ": " << r1->child[i]->ch_name;
            cout << "\n Sections:";
            
            int tsections = r1->child[i]->ch_count;
            for (int j = 0; j < tsections; j++) {
                cout << "\n  - " << r1->child[i]->child[j]->ch_name;
            }
        }
    }
}

int GT::calculate_height(Node* r1) {
    if (r1 == NULL) {
        return 0;
    }
    
    int max_height = 0;
    
    for (int i = 0; i < r1->ch_count; i++) {
        int height_of_child = calculate_height(r1->child[i]);
        max_height = max(max_height, height_of_child);
    }
    
    return max_height + 1;
}

void GT::menu() {
    int choice;
    
    do {
        cout << "\n------------------- MENU -------------------";
        cout << "\n1. Create Tree";
        cout << "\n2. Display Book Hierarchy";
        cout << "\n3. Calculate and Display Tree Height";
        cout << "\n4. Exit";
        cout << "\n--------------------------------------------";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                create_tree();
                break;
            case 2:
                display(root);
                break;
            case 3:
                int height;
                height = calculate_height(root);
                cout << "\nHeight of the tree: " << height << endl;
                break;
            case 4:
                cout << "\nExiting program..." << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}

int main() {
    GT tree;
    tree.menu();
    
    return 0;
}

