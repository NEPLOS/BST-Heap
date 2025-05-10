
#ifndef MAX_HEAP
#define MAX_HEAP

#include <iostream>
#include <vector>
#include "binarySortTree.h"

struct maxHeapData
{
    int id;
    int priority;
   // maxHeapData(int id , int priority);
};

class maxHeap
{
    public:

    std::vector<maxHeapData> array;

    maxHeap();
    void insertHeap(int id , int priority);
    int sizeMaxHeap();
    bool isEmptyHeap();
    void maxHeapify(int index);
    void processHighestPriorityRequest(BST* binartTree);
    int getRightChild(int index);
    int getLeftChild(int index);
    int getParent(int index);
    void deleteMaxHeap();
    void heapifyUp(int index);
    void print();
    

};

#endif
