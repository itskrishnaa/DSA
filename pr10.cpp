#include<iostream>
using namespace std;

class node
{
public:
    string key;
    string meaning;
    node *left;
    node *right;
};

struct AVL
{
    node *root;
};


void init(AVL &a);
void create(AVL &a);
node* insert(node* cur, node* temp);
node* balance(node* temp);
int dif(node* temp);
int height(node* temp);
int maximum(int a, int b);

node* LL(node* par);
node* RR(node* par);
node* LR(node* par);
node* RL(node* par);

void ascending(node* temp);
void descending(node* temp);
void display(AVL &a);
bool search(node* cur, string key1);
void search_value(AVL &a);

node* delete_n(node* cur, string key1);
void deleten(AVL &a);

node* extractmin(node* t);


void init(AVL &a)
{
    a.root = NULL;
}

void create(AVL &a)
{
    char answer;
    node *temp;
    do
    {
        temp = new node();
        cout << "\n Enter the keyword:";
        cin >> temp->key;
        cout << "\n Enter the meaning:";
        cin >> temp->meaning;
        temp->left = temp->right = NULL;

        a.root = insert(a.root, temp);

        cout << "\n Do you want to add another word?(y/n)";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}

node* insert(node* cur, node* temp)
{
    if (cur == NULL)
        return temp;
    if (temp->key < cur->key)
    {
        cur->left = insert(cur->left, temp);
        cur = balance(cur);
    }
    else if (temp->key > cur->key)
    {
        cur->right = insert(cur->right, temp);
        cur = balance(cur);
    }
    return cur;
}

node* balance(node* temp)
{
    int bal = dif(temp);

    if (bal >= 2)
    {
        if (dif(temp->left) < 0)
            temp = LR(temp);
        else
            temp = LL(temp);
    }
    else if (bal <= -2)
    {
        if (dif(temp->right) < 0)
            temp = RR(temp);
        else
            temp = RL(temp);
    }
    return temp;
}

int dif(node* temp)
{
    int l = height(temp->left);
    int r = height(temp->right);
    return (l - r);
}

int height(node* temp)
{
    if (temp == NULL)
        return (-1);
    return (maximum(height(temp->left), height(temp->right)) + 1);
}

int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

node* LL(node* par)
{
    node* temp = par->left;
    node* temp1 = temp->right;
    temp->right = par;
    par->left = temp1;
    return temp;
}

node* RR(node* par)
{
    node* temp = par->right;
    node* temp1 = temp->left;
    temp->left = par;
    par->right = temp1;
    return temp;
}

node* LR(node* par)
{
    par->left = RR(par->left);
    return LL(par);
}

node* RL(node* par)
{
    par->right = LL(par->right);
    return RR(par);
}

void ascending(node* temp)
{
    if (temp != NULL)
    {
        ascending(temp->left);
        cout << "\n\t" << temp->key << " : " << temp->meaning;
        ascending(temp->right);
    }
}

void descending(node* temp)
{
    if (temp != NULL)
    {
        descending(temp->right);
        cout << "\n\t" << temp->key << " : " << temp->meaning;
        descending(temp->left);
    }
}

void display(AVL &a)
{
    cout << "\n The keywords in ascending order are : \n";
    ascending(a.root);
    cout << "\n The keywords in descending order are : \n";
    descending(a.root);
}

bool search(node* cur, string key1)
{
    if (cur)
    {
        if (cur->key == key1)
            return true;
        if (cur->key > key1)
            return search(cur->left, key1);
        else
            return search(cur->right, key1);
    }
    return false;
}

void search_value(AVL &a)
{
    string key2;
    cout << "\n Enter the keyword you wish to search : ";
    cin >> key2;
    if (search(a.root, key2))
        cout << "\n The entered keyword is present in the AVL tree";
    else
        cout << "\n The entered keyword is not present in the AVL tree";
}

node* delete_n(node* cur, string key1)
{
    if (!cur)
        return cur;

    if (key1 < cur->key)
        cur->left = delete_n(cur->left, key1);
    else if (key1 > cur->key)
        cur->right = delete_n(cur->right, key1);
    else
    {
        node* l = cur->left;
        node* r = cur->right;
        delete cur;
        if (!r)
            return l;
        node* m = r;
        while (m->left)
            m = m->left;
        m->right = extractmin(r);
        m->left = l;
        return balance(m);
    }
    return balance(cur);
}

node* extractmin(node* t)
{
    if (!t->left)
        return t->right;
    t->left = extractmin(t->left);
    return balance(t);
}

void deleten(AVL &a)
{
    string key;
    cout << "\n Enter the keyword to be deleted : ";
    cin >> key;
    a.root = delete_n(a.root, key);
}


int main()
{
    char c;
    int ch;
    AVL a;
    init(a);

    do
    {
        cout << "*********************************";
        cout << "\n 1.Insert a keyword in AVL tree.";
        cout << "\n 2.Display the AVL tree.";
        cout << "\n 3.Search a keyword";
        cout << "\n 4.Delete a keyword.";
        cout << "\n Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            create(a);
            break;
        case 2:
            display(a);
            break;
        case 3:
            search_value(a);
            break;
        case 4:
            deleten(a);
            break;
        default:
            cout << "\n Wrong choice ! ";
        }

        cout << "\n Do you want to continue? (y/n): ";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    return 0;
}

