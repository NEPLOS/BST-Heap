
#include "./binarySortTree.h"

Node::Node(std::string name, int id)
{
    this->name = name;
    this->id = id;
}

Node::Node()
{
    name = "Unknown";
    id = -1;
}

void BST::insertRequest(std::string name, int id)
{
    Node *data = new Node(name, id);
    if (head == nullptr)
    {
        head = data;
        return;
    }

    Node *before = nullptr;
    Node *temp = head;
    while (temp != nullptr)
    {
        before = temp;
        if (temp->id < data->id)
            temp = temp->leftChild;
        else
            temp = temp->rigthChild;
    }

    if (before->id < data->id)
        before->leftChild = data;
    else
        before->rigthChild = data;
    data->parents = before;
}

bool BST::isEmptyBST()
{
    if (head == nullptr)
        return true;
    else
        return false;
}

Node* BST::searchRequst(int id)
{

    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
            return temp;
        else if (id > temp->id)
            temp = temp->leftChild;
        else
            temp = temp->rigthChild;
    }

    return temp;
}

int BST::getSize(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getSize(node->rigthChild) + getSize(node->leftChild) + 1;
}

void BST::drawBinarySearchTree(Node* node, int x , int y)
{

    if (node == nullptr)
    {
        return;
    }

    int leftChildSize = getSize(node->leftChild);
    int rightChildSize = getSize(node->rigthChild);

    int rightChildDistance =  70 * (leftChildSize + 1);
    int leftChildDistance = 70 * (rightChildSize + 1);

    if (node->leftChild == nullptr)
    {
        leftChildDistance = 0;
    }
    
    if (node->rigthChild == nullptr)
    {
        rightChildDistance = 0;
    }
    
    
    if (!(node->leftChild == nullptr && node->rigthChild == nullptr))
    {
        DrawLineEx((Vector2){x,y} , (Vector2){x+leftChildDistance,y+leftChildDistance} , 2 , BLACK);
        DrawLineEx((Vector2){x,y} , (Vector2){x-rightChildDistance,y+rightChildDistance} , 2 , BLACK);
    }
    
    DrawCircle(x,y,40,ORANGE);
    DrawCircleLines(x,y,40,BLACK);
    std::string label = std::to_string(node->id);
    std::string nameLabel = node->name;
    DrawText(label.c_str(), x - MeasureText(label.c_str(), 15)/2, y - 13, 15, BLACK);
    DrawText(nameLabel.c_str(), x - MeasureText(nameLabel.c_str(), 15)/2, y + 3, 15, DARKGRAY);
    drawBinarySearchTree(node->rigthChild,x-rightChildDistance,y+rightChildDistance);
    drawBinarySearchTree(node->leftChild,x+leftChildDistance,y+leftChildDistance);

}


void BST::printBst()
{
    print(head);
    std::cout << "\n";
}


void BST::print(Node *n)
{
    if (n == nullptr)
        return;

    print(n->rigthChild);
    std::cout << "[" << n->id << ',' << n->name << "] ";
    print(n->leftChild);
}