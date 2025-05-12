
#include "./maxHeap.h"

// struct maxHeapData
// {
//     int id;
//     int priority;
// };



maxHeap::maxHeap()
{
    array.clear();
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

void maxHeap::drawMaxHeap(int index , int x , int y, int distance)
{
    if (index >= array.size())
    {
        return ;
    }

    // int distance = 100;// = array.size() * 70;
    // //int distance = getDepth(index);
    // //distance = (250 * (maxchild(index) + 1 )) / (distance + 1);

    // distance = ((int)(log2(array.size())) + 1)  / (getDepth(index) + 1);// / log2(array.size() + 1);

    // distance = distance * 2;

    if (getRightChild(index) < array.size())
    {
        DrawLineEx((Vector2){x, y}, (Vector2){(x + distance), (y + distance)}, 5, BLACK);
    }

    if (getLeftChild(index) < array.size())
    {
        DrawLineEx((Vector2){x, y}, (Vector2){(x - distance), (y + distance)}, 5, BLACK);
    }
    
    

    DrawCircle(x,y,43,BLACK);
    DrawCircle(x,y,40,ORANGE);
    DrawText(std::to_string(array[index].priority).c_str(), x - MeasureText(std::to_string(array[index].priority).c_str(), 15) / 2, y - 13, 15, BLACK);
    DrawText(std::to_string(array[index].id).c_str(), x - MeasureText(std::to_string(array[index].id).c_str(), 15) / 2, y + 3, 15, DARKGRAY);
  //  std::cerr << "[" << array[index].id << ',' << array[index].priority << "]" << '\n';

    drawMaxHeap(getLeftChild(index) ,  (x - distance) , (y + distance) , distance/2 );
    drawMaxHeap(getRightChild(index) , (x + distance) , (y + distance) , distance/2 );
}

int maxHeap::maxchild(int index)
{
    if (index > array.size())
    {
        return 0;
    }
    
    return maxchild(getLeftChild(index)) + 1;
}

int maxHeap::getDepth(int index)
 {
    int depth = 0;
    
    while (index > 0) 
    {
        index = getParent(index);
        depth++;
    
    }
    return depth;
}
    

void maxHeap::print()
{
    for (int i = 0; i < sizeMaxHeap(); i++)
    {
        std::cout << "[id: " << array[i].id << ",priority: " << array[i].priority << "] "; 
    }
    std::cout << '\n';
}
