#ifndef KURSACH_TREE_H
#define KURSACH_TREE_H

#include "Node.h"

class Tree {
public:
    Node * root;

    ~Tree(){}
    Tree(){}

    void Log()
    {
        cout << endl << "Дерево в прямом порядке КЛП:" << endl;
        root->Log();
        cout << endl;
    }

};


#endif //KURSACH_TREE_H
