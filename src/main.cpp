#include "main.h"
#include "tree.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main(){
    BST tree;
    srand(time(nullptr));
    tree.randTree(10);
    tree.printLevelOrder();
    tree.printPreOrder();
    return 0;
}