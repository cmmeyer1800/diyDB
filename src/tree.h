#pragma once

class BST{
    private:

        struct BSTNode{
            int val;
            BSTNode * left;
            BSTNode * right;
            BSTNode(int val): val(val), left(nullptr), right(nullptr){}
        };

        BSTNode * root_;

        void insertHelper(BSTNode * & root, BSTNode * ins);

        void printPreOrder(BSTNode * root);

        void del(BSTNode * root);
        
    public:

        void insert(int val);
        
        void printLevelOrder();

        void printPreOrder();

        BST();

        ~BST();

        void randTree(int count);
};