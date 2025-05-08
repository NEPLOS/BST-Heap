
#include "./binarySortTree.h"

extern Camera2D camera;
extern bool nodeCollisionHelper;
extern Node* collisionNode;
extern int lvl;

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

        if(temp->id == id)
            return;
        else if (temp->id < data->id)
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

Node *BST::searchRequst(int id)
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

void BST::searchRequstTrace(int id , Node* node , int x , int y)
{
    if (node == nullptr)
    {
        return;
    }

    std::cout << node->id << "\n";

    if (id == node->id)
    {
        std::cerr << "found it\n";
        DrawCircleLines(x,y,20,BLACK);
    }
    else if (id < node->id)
    {

        int leftChildSize = getSize(node->leftChild);
        
        int rightChildDistance = 70 * (leftChildSize + 1);
        
        if (node->rigthChild == nullptr)
        {
            rightChildDistance = 0;
        }
        DrawLineEx((Vector2){x, y}, (Vector2){x - rightChildDistance, y + rightChildDistance},6, GREEN);
        searchRequstTrace(id,node->rigthChild,x - rightChildDistance, y + rightChildDistance);
    }
    else if(id > node->id)
    {
        int rightChildSize = getSize(node->rigthChild);
        int leftChildDistance = 70 * (rightChildSize + 1);
    
        if (node->leftChild == nullptr)
        {
            leftChildDistance = 0;
        }
        DrawLineEx((Vector2){x, y}, (Vector2){x + leftChildDistance, y + leftChildDistance}, 6, GREEN);
        searchRequstTrace(id,node->leftChild,x + leftChildDistance, y + leftChildDistance);
    }
    

}

int BST::getSize(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getSize(node->rigthChild) + getSize(node->leftChild) + 1;
}

int BST::drawUpToRoot(Node *node, int x, int y)
{
    if (node == nullptr || node->parents == nullptr)
    {
        return 0;
    }

    Node *temp = node->parents;
    int distance = 0;
    int distance_y = 0;
    if (temp->leftChild == node)
    {
        distance = 70 * (getSize(temp->rigthChild) + 1);
        distance_y = distance;
        distance *= -1;
    }
    else
    {
        distance = 70 * (getSize(temp->leftChild) + 1);
        distance_y = distance;
    }

    DrawLineEx((Vector2){x, y}, (Vector2){x + distance, y - distance_y}, 10, RED);
    return 1 + drawUpToRoot(temp, x + distance, y - distance_y);
}

void BST::drawBinarySearchTree(Node *node, int x, int y)
{
 

    if (node == nullptr)
    {
        return;
    }

    int leftChildSize = getSize(node->leftChild);
    int rightChildSize = getSize(node->rigthChild);

    int rightChildDistance = 70 * (leftChildSize + 1);
    int leftChildDistance = 70 * (rightChildSize + 1);

    if (node->leftChild == nullptr)
    {
        leftChildDistance = 0;
    }

    if (node->rigthChild == nullptr)
    {
        rightChildDistance = 0;
    }

    DrawLineEx((Vector2){x, y}, (Vector2){x + leftChildDistance, y + leftChildDistance}, 5, BLACK);
    DrawLineEx((Vector2){x, y}, (Vector2){x - rightChildDistance, y + rightChildDistance}, 5, BLACK);

    if (CheckCollisionPointCircle(GetScreenToWorld2D(GetMousePosition(), camera), (Vector2){x, y}, 40))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            deleteRequest(node->id);
            return;
        }
        
        
        lvl = drawUpToRoot(node, x, y);
        nodeCollisionHelper = true;
        collisionNode = node;

    }

    DrawCircle(x, y, 43, BLACK);
    if (node->parents == nullptr)
    {
        DrawCircle(x, y, 40, GOLD);
    }
    else
    {
        DrawCircle(x, y, 40, ORANGE);
    }
    
    std::string label = std::to_string(node->id);
    std::string nameLabel = node->name;
    DrawText(label.c_str(), x - MeasureText(label.c_str(), 15) / 2, y - 13, 15, BLACK);
    DrawText(nameLabel.c_str(), x - MeasureText(nameLabel.c_str(), 15) / 2, y + 3, 15, DARKGRAY);
    drawBinarySearchTree(node->rigthChild, x - rightChildDistance, y + rightChildDistance);
    drawBinarySearchTree(node->leftChild, x + leftChildDistance, y + leftChildDistance);


}

void BST::transplant(Node *oldNode, Node *newNode)
{
    if (oldNode->parents == nullptr)
    {
        head = newNode;
    }
    else if (oldNode == oldNode->parents->leftChild)
    {
        oldNode->parents->leftChild = newNode;
    }
    else
    {
        oldNode->parents->rigthChild = newNode;
    }

    if (newNode != nullptr)
    {
        newNode->parents = oldNode->parents;
    }
}

Node* BST::getMinimumNode(Node *starter)
{
    Node *temp = starter;
    while (temp->leftChild != nullptr)
    {
        temp = temp->leftChild;
    }
    return temp;
}

void BST::deleteRequest(int id)
{
    Node *target = searchRequst(id);

    if (target == nullptr)
        return;

    if (target->leftChild == nullptr)
    {
        transplant(target, target->rigthChild);
    }
    else if (target->rigthChild == nullptr)
    {
        transplant(target, target->leftChild);
    }
    else
    {
        Node* minNode = getMinimumNode(target->rigthChild);

        if (minNode->parents != target)
        {
            transplant(minNode, minNode->rigthChild);
            minNode->rigthChild = target->rigthChild;
            if (minNode->rigthChild)
            {
                minNode->rigthChild->parents = minNode;
            }
        }

        transplant(target, minNode);
        minNode->leftChild = target->leftChild;
        if (minNode->leftChild)
        {
            minNode->leftChild->parents = minNode;
        }
    }

    target->leftChild = target->rigthChild = nullptr;
    target->parents = nullptr;
    delete target;
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