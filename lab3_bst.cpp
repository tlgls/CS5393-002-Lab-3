#include <iostream>
#include <vector>

using namespace std;

// structure for each node in the binary search tree (BST)
struct Node {
    int key; // data value for node
    Node* left; // pointer to left child
    Node* right; // pointer to right child

    // constructor to initialize new node
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// function to insert a key in the BST
Node* insert(Node* node, int key) {
    if (node == nullptr) { // the base case: if the tree is empty, then we create a new node
        cout << "Inserting node with key: " << key << endl;
        return new Node(key);
    }
    if (key < node->key) { // recursive case: insert in the left or right subtree based on the key
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }
    return node;
}

// function to find the minimum value node in the given BST
Node* findMin(Node* node) {
    // loop created to find the leftmost leaf on the tree
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// function to search for a key in the BST
bool search(Node* node, int key) {
    if (node == nullptr) {
        return false; // key not found
    }

    if (key < node->key) {
        return search(node->left, key); // search in the left subtree
    } else if (key > node->key) {
        return search(node->right, key); // search in the right subtree
    } else {
        return true; // key found
    }
}

// function to delete a node from the bst
Node* deleteNode(Node* node, int key, bool root = true, bool printMessage = true) {
    // base case: if the tree is empty
    if (node == nullptr) {
        if (printMessage) {
            cout << "Node with key " << key << " not found, so not deleted." << endl;
        }
        return node;
    }

    // recursive case: we traverse the tree to find the node to delete
    if (key < node->key) {
        node->left = deleteNode(node->left, key, false, printMessage);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key, false, printMessage);
    } else {
        if (printMessage) {
            cout << "Deleting node with key: " << key << endl;
        }

        // case 1: node with only one or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp; // returns the right child
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp; // returns the left child
        }

        // case 2: node with two children
        // finds the in-order successor (smallest in the right subtree)
        Node* temp = findMin(node->right);
        node->key = temp->key; // replaces node's key with the in-order successor's key
        node->right = deleteNode(node->right, temp->key, false, false);  // deletes the in-order successor without printing its key (used to prevent it from printing: Deleting node with key: 60)
    }
    return node;
}

// function to perform in-order traversal of the BST
void inOrder(Node* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}

int main() {
    Node* root = nullptr;

    // initialize the vector with keys
    int keys[] = {50, 30, 10, 40, 20, 100, 70, 90, 60, 80};
    vector<int> vec(keys, keys + sizeof(keys) / sizeof(int));

    // insert values into the BST
    for (int key : vec) {
        root = insert(root, key);
    }

    // In-order traversal before deletion
    cout << "In-order traversal before deletion: ";
    inOrder(root);
    cout << endl;

    // Search for nodes 60, 100
    int searchKeys1[] = {60, 100};
    cout << "Searching for nodes 60 and 100:" << endl;
    for (int key : searchKeys1) {
        bool found = search(root, key);
        if (found) {
            cout << "Node with key " << key << " is found in the BST." << endl;
        } else {
            cout << "Node with key " << key << " is not found in the BST." << endl;
        }
    }

    // Search for nodes 25, 96.3 (we'll use 96 since BST typically handles integers)
    float searchKeys2[] = {25, 96.3};
    cout << "Searching for nodes 25 and 96.3:" << endl;
    for (float key : searchKeys2) {
        int intKey = static_cast<int>(key);
        bool found = search(root, intKey);
        cout << "Node with key " << intKey << " (from " << key << ") is ";
        if (found) {
            cout << "found in the BST." << endl;
        } else {
            cout << "not found in the BST." << endl;
        }
    }

    // Delete nodes 50 and 100
    root = deleteNode(root, 50);
    root = deleteNode(root, 100);

    // In-order traversal after deletion
    cout << "In-order traversal after deletion: ";
    inOrder(root);
    cout << endl;

    return 0;
}
