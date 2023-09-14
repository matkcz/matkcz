#pragma once

#include <queue>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

class tree
{
    struct node
    {
        int data; //klíè èíslo, podle kterého bude strom seøazený
        string letter; //hodnota stringu vrcholu
        node* left; //levý potomek
        node* right; //pravý potomek
        int height; //výška jednotlivého vrcholu (od spoda)
    };
   
public:
    tree(); 
    ~tree();
    void insert(int x, string y);
    void remove(int x);
    void remove(string y);
    void display();
    void wide_print();
    string find(int x);
    int find(string y);
    //int maxCount(); //nakonec jsem nepoužil

private:
    node* root;
    struct node;

    bool empty();
    void makeEmpty(node* t);
    int height(node* t);
    //int getBalance(node* t);
    node* singleRightRotate(node*& t);
    node* singleLeftRotate(node*& t);
    node* doubleRightLeftRotate(node*& t);
    node* doubleLeftRightRotate(node*& t);
    node* insert(int x, node* t, string y);
    node* findMin(node* t);
    node* findMax(node* t);
    node* findNode(int x);
    node* findNode(string y);
    node* remove(int x, node* t);
    node* remove(string y, node* t);
    void inorder(node* t);
    unsigned int depth();
    
};

#pragma once