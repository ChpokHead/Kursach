#ifndef KURSACH_NODE_H
#define KURSACH_NODE_H

#include "Token.h"
#include <vector>

class Node {
public:
    ~Node();
    Node();

    Token data;         // Метка узла (по метке вызываем нужную функцию)
    vector<Node *> childs;   // Список указателй на другие узлы
    void Log();
};


#endif //KURSACH_NODE_H
