#include "tree.h"
#include <queue>
#include <iostream>
#include <stdlib.h>

BST::BST(){
    root_ = nullptr;
}

void BST::insert(int val){
    BSTNode * newNode = new BSTNode(val);
    insertHelper(root_, newNode);
}

void BST::insertHelper(BSTNode * &root, BSTNode * ins){
    if(root == nullptr){
        root = ins;
        return;
    }
    else{
        if(ins->val < root->val){
            insertHelper(root->left, ins);
        }
        else{
            insertHelper(root->right, ins);
        }
    }
}

void BST::printLevelOrder(){
    std::queue<BSTNode *> q;

    if(root_ == NULL) return;

    q.push(root_);

    while(q.empty() == false){
        BSTNode * node = q.front();
        std::cout << node->val << " ";
        q.pop();

        if (node->left != nullptr)
            q.push(node->left);
 
        if (node->right != nullptr)
            q.push(node->right);
    }

    std::cout << std::endl;
}

void BST::printPreOrder(){
    if(root_ == NULL) return;
    printPreOrder(root_);
    std::cout << std::endl;
}

void BST::printPreOrder(BSTNode * root){
    if(root == nullptr) return;
    std::cout << root->val << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void BST::del(BSTNode * root){
    if(root == NULL){
        return;
    }
    del(root->left);
    del(root->right);
    delete root;
}

void BST::randTree(int count){
    for(int i = 0; i < count; i++){
        insert(rand() % 100);
    }
}

BST::~BST(){
    if(root_ != NULL){
        del(root_);
    }
}