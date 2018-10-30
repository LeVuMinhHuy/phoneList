#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

struct Node{
    string phoneName;
    string phoneNumber;
    Node *left;
    Node *right;
    int balance = 0;
};


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
};



Node *leftBalance(Node *root, bool taller){

    Node *leftTree = root->left;
    if(leftTree->balance == 1){
        rotateRight(root);
        root->balance = 0;
        leftTree->balance = 0;
        taller = false;
    }
    else{
        Node *rightTree = leftTree->right;
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
    Node *rightTree = root->right;

    if(rightTree->balance == -1){
        rotateLeft(root);
        root->balance = 0;
        rightTree->balance = 0;
        taller = false;
    }

    else{
        Node *leftTree = rightTree->left;
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

Node *AVLInsert(Node *root, Node *newNode){

    bool taller;
    //cout << "\n\n" << newNode->phoneName.compare(root->phoneName) << "\n\n";
    if(root == NULL){

        return newNode;
    }

    else if(newNode->phoneName.compare(root->phoneName) == 0 ){

        taller = false;
        return newNode;
    }

    if(newNode->phoneName.compare(root->phoneName) < 0){
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

        root->right = AVLInsert(root->right, newNode);
        if(taller){
            if(root->balance == 1){
                root->balance = 0;
                taller = false;
            }
            else if (root->balance = 0){
                root->balance = -1;
            }
            else{
                root = rightBalance(root, taller);
            }
        }
    }

    return root;

};

Node *InputData(ifstream &file){
    Node *root = new Node();
    root = NULL;
    Node *leaf;

    while(!file.eof()){
        leaf = new Node();
        getline(file, leaf->phoneName);
        getline(file, leaf->phoneNumber);
        leaf->balance = 0;
        leaf->right = leaf->left = NULL;
        if(root == NULL){
            root = leaf;
        }

        root = AVLInsert(root, leaf);
    }
    return root;
}

void printPhoneList(Node *root)
{


    if(root != NULL)
    {
        printPhoneList(root->left);
        cout << root->phoneNumber << setw(40) << root->phoneName << "\n";
        printPhoneList(root->right);
    }
    return;
}

Node *searchFromUser(Node *root, string nameInput){
    if(root == NULL){
    cout << "Not Found!" << endl;
    return NULL;}


    if(root->phoneName.compare(nameInput) < 0){
        return searchFromUser(root->right, nameInput);
    }
    else if(root->phoneName.compare(nameInput) > 0){
        return searchFromUser(root->left, nameInput);
    }
    else{return root;}

}

void insertFromUser(){
    cout << "Input a name without any space: ";
    string newNameInput;
    cin >> newNameInput;
    cout << "Input a number phone: ";
    string newPhoneInput;
    cin >> newPhoneInput;
    cout << "\n";
    ofstream myfile;
    myfile.open("input.txt",std::ios::app);
    myfile << newNameInput << "\n";
    myfile << newPhoneInput << "\n";
    myfile.close();
}

int menuForUser(){
    cout << setw(30); cout <<"====================================\n";
    cout << setw(30) <<"====            MENU            ====\n";
    cout << setw(30) <<"====================================\n\n";
    cout << setw(30) <<"| 1. Print all the phone number    |\n";
    cout << setw(30) <<"| 2. Search for name               |\n";
    cout << setw(30) <<"| 3. Insert new contact            |\n";
    cout << setw(30) <<"| 4. Delete a contact              |\n";
    cout << setw(30) <<"| 5. Exit                          |\n";
    cout << setw(30) <<"====================================\n\n";
}

int main()
{

    int chooseFromUser;


    while(chooseFromUser != 5){
    menuForUser();
    cin >> chooseFromUser;
    cout <<"\n";
    switch(chooseFromUser){
        case 1:{
            ifstream CheckFile;
            char inputFileName[] = "input.txt";
            CheckFile.open(inputFileName);
            if(!CheckFile){cout << "Input file does not exist. \n\n";}
            Node *head = InputData(CheckFile);
            cout << "Phone list: \n\n";
            printPhoneList(head);
            cout << "\n\n";
            break;}
        case 2:{
            ifstream CheckFile;
            char inputFileName[] = "input.txt";
            CheckFile.open(inputFileName);
            if(!CheckFile){cout << "Input file does not exist. \n\n";}
            Node *head = InputData(CheckFile);
            string nameFromUser;
            cout << "Input the name which you want to find: ";
            cin >> nameFromUser;
            cout << "\n\n";
            Node *resultSearch = searchFromUser(head, nameFromUser);
            if(resultSearch != NULL){
            cout << resultSearch->phoneName << "\n";
            cout << resultSearch->phoneNumber << "\n";
            }
            cout << "\n\n";
            break;}
        case 3:{
            insertFromUser();
            ifstream CheckFile;
            char inputFileName[] = "input.txt";
            CheckFile.open(inputFileName);
            if(!CheckFile){cout << "Input file does not exist. \n\n";}
            Node *head = InputData(CheckFile);
            printPhoneList(head);}
        }

    }


    return 0;
}
