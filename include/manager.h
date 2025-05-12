
#ifndef DATA_MANAGER
#define DATA_MANAGER

#include "./binarySortTree.h"
#include "./maxHeap.h"

class manager
{

public :
    BST binaryTree;
    maxHeap heap;
    
    manager()
    {

    }
    void insertProcess(std::string name , int id , int priority)
    {
        binaryTree.insertRequest(name,id);
        heap.insertHeap(id,priority);
    }
};

#endif 
