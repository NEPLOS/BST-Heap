
#include "./maxHeap.h"

// struct maxHeapData
// {
//     int id;
//     int priority;
// };



maxHeap::maxHeap()
{

}
void maxHeap::insertHeap(int id , int priority)
{
    maxHeapData data = {id , priority};
    array.push_back(data);
    heapifyUp(array.size() - 1);
}

void maxHeap::deleteMaxHeap() 
{
    if (isEmptyHeap()) return;

    array[0] = array.back();
    array.pop_back();

    if (!isEmptyHeap())
        maxHeapify(0);
}


void maxHeap::heapifyUp(int index)
 {
    while (index > 0 && array[getParent(index)].priority < array[index].priority) 
    {
        std::swap(array[index], array[getParent(index)]);
        index = getParent(index);
    }
}

int maxHeap::sizeMaxHeap()
{
    return array.size(); 
}
bool maxHeap::isEmptyHeap()
{
    return sizeMaxHeap() == 0;
}
void maxHeap::maxHeapify(int index) 
{
    int largest = index;
    int left = getLeftChild(index);
    int right = getRightChild(index);

    if (left < array.size() && array[left].priority > array[largest].priority)
        largest = left;
    if (right < array.size() && array[right].priority > array[largest].priority)
        largest = right;

    if (largest != index) 
    {
        std::swap(array[index], array[largest]);
        maxHeapify(largest);
    }
}

void maxHeap::processHighestPriorityRequest(BST* binaryTree) 
{
    if (isEmptyHeap()) return;

    int idToRemove = array[0].id;
    deleteMaxHeap();
    binaryTree->deleteRequest(idToRemove);
}

int maxHeap::getRightChild(int index)
{
    return 2*index + 2;
}
int maxHeap::getLeftChild(int index)
{
    return 2*index + 1;
}
int maxHeap::getParent(int index)
{
    return (index-1)/2;
}

void maxHeap::print()
{
    for (int i = 0; i < sizeMaxHeap(); i++)
    {
        std::cout << "[id: " << array[i].id << ",priority: " << array[i].priority << "] "; 
    }
    std::cout << '\n';
}
