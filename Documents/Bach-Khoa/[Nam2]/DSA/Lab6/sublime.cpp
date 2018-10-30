#include <iostream>
#include <fstream>
using namespace std;

struct *Node{
    string phoneName;
    string phoneNumber;
    Node *left;
    Node *right;
    int balance = 0;
}

int findBalance(Node *root){
    if (root == NULL){
        return -1;
    }
    else
        return root->balance;
}

Node *AVLInsert(Node *root, Node *newNode){

    bool taller;

    if(root == NULL){
        root = newNode;
        taller = true;
        return root;
    }

    else if(newNode->phoneName == root->phoneName){
        taller = false;
        throw "Duplicate_error";
    } 

    if(newNode->phoneName < root->phoneName){
        root->left = AVLInsert(root->left, newNode);
        if(taller){
            if(root->balance == 1)
            {
                root = leftBalance(root, taller);
            }
            else if (root->balance == 0){
                root->balance = 1;
            }
            else { root->balance = 0; taller = false;}
        }
    }
    
    else{
        
        root->right = AVLInsert(root->right, newNode)
        if(taller){
            if(root->balance == 1){
                root->balance = 0;
                taller = false;
            }
            else if (root->balance = 0){
                root->balance = -1
            }
            else{
                root = rightBalance(root, taller)
            }
        }
    }

    return root;
    
}

Node *rotateLeft(Node *root){
    Node *tempPtr = root->right;
    root->right = tempPtr->left;
    tempPtr->left = root;

    return tempPtr;
}

Node *rotateRight(Node *root){
    Node *tempPtr = root->left;
    root->left = tempPtr->right;
    tempPtr->right = root;

    return tempPtr;
}



Node *leftBalance(Node *root, bool taller){

    leftTree = root->left;
    if(leftTree == 1){
        rotateRight(root);
        root->balance = 0;
        leftTree->balance = 0;
        taller = false;
    }
    else{
        rightTree = leftTree->right;
        if(rightTree->balance == 1){
            root->balance = -1;
            leftTree->balance = 0;
        }
        else if (rightTree->balance = 0){
            leftTree->balance = 0;
        }
        else{
            root->balance = 0;
            leftTree->balance = 1;
        }

        rightTree->balance = 0;
        root->left = rotateLeft(leftTree);
        root = rotateRight(root);
        taller = false;
    }

    return root;
}

Node *rightBalance(Node *root,bool taller){
    rightTree = root->right;

    if(rightTree == -1){
        rotateLeft(root);
        root->balance = 0;
        rightTree->balance = 0;
        taller = false;
    }

    else{
        leftTree = rightTree->left;
        if(leftTree->balance = -1){
            root->balance = 1;
            rightTree->balance = 0;
        }
        else if(leftTree->balance = 0){
            rightTree->balance = 0;
        }
        else{
            root->balance = 0;
            rightTree->balance = -1;
        }

        leftTree->balance = 0;
        root->right = rotateRight(rightTree);
        root = rotateLeft(root);
        taller = false;
    }

    return root;
}

Node *InputData(ifstream &file){
    Node *root = NULL;
    Node *leaf;
    while(!file.eof()){
        leaf = new Node;
        getline(file, leaf->phoneName);
        getline(file, leaf->phoneNumber);
        leaf->balance = 0;
        leaf->right = leaf->left = NULL;
        if(root == NULL){
            root = leaf;
        }

        root = insertData(root, leaf);
    }
    return root;
}

void printAVLTree(Node *root){
    Node *pTemp;
    if(root != NULL){
        printAVLTree(root->left);
        cout << root->phoneName << setw(10) << root->phoneNumber << "\n";

        if(root->left == NULL){cout << "NULL \n";}
        else{
            pTemp = root->left;
            cout << pTemp->phoneName << setw(10) << pTemp->phoneNumber << "\n";
        }
        if(root->right == NULL){cout << "NULL \n";}
        else{
            pTemp = root->right;
            cout << pTemp->phoneName << setw(10) << pTemp->phoneNumber << "\n";
        }

        printAVLTree(root->right);
    }
    return;
}
int main()
{
    ifstream CheckFile;
    char inputFileName[] = "input.txt";
    CheckFile.open(inputFileName);
    if(!CheckFile){cout << "Input file does not exist. \n\n";}
    else{
        cout  << "File opened. \n";
    }
    Node *head = InputData(CheckFile);
    cout << "Print AVL Tree: \n\n";
    printAVLTree(head);
    
    return 0;
}
