#include "Node.h"

Node::Node()
{

}

Node::~Node()
{
    for(int it = 0; it < childs.size(); it++)
        delete childs[it];
}

void Node::Log()
{
    cout << data.getType() << "|" << data.getValue() << endl;

    for(int it = 0; it < childs.size(); it++)
        if(childs[it] != NULL)
            childs[it]->Log();
}