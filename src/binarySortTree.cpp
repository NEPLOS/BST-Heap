
#include "./binarySortTree.h"

extern Camera2D camera;
extern bool nodeCollisionHelper;
extern Node* collisionNode;
extern int lvl;

Node* holdingNode = nullptr;
bool holdingSomething = false;

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

void BST::recalcuteCoordinates(Node* node , int x , int y)
{
    if (node == nullptr)
    {
        return;
    }
    
    node->coordinate.x = x;
    node->coordinate.y = y;
    int leftChildSize = getSize(node->leftChild);
    int rightChildSize = getSize(node->rightChild);

    int rightChildDistance = 70 * (leftChildSize + 1);
    int leftChildDistance = 70 * (rightChildSize + 1);

    recalcuteCoordinates(node->leftChild  , x - leftChildDistance, y + leftChildDistance);
    recalcuteCoordinates(node->rightChild , x + rightChildDistance, y + rightChildDistance);

}

void BST::insertRequest(std::string name, int id)
{
    Node* data = new Node(name, id);
    if (head == nullptr)
    {
        head = data;
        head->coordinate.x = 0;
        head->coordinate.y = 0;
        return;
    }

    Node *before = nullptr;
    Node *temp = head;

    int sizeX = 0;
    int sizeY = 0;

    while (temp != nullptr)
    {
        before = temp;

        if (temp->id == id)
            return;
        else if (data->id < temp->id)
            temp = temp->leftChild;
        else
            temp = temp->rightChild;
        
    }

    if (data->id < before->id)
        before->leftChild = data;

    else
        before->rightChild = data;

    
    data->parents = before;

    recalcuteCoordinates(head,0,0);
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

    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
            return temp;
        else if (temp->id > id)
            temp = temp->leftChild;
        else
            temp = temp->rightChild;
    }

    return temp;
}

void BST::searchRequstTrace(int id , Node* node , int x , int y)
{
    if (node == nullptr)
    {
        return;
    }

    if (id == node->id)
    {
        DrawCircleLines(x,y,20,BLACK);
    }
    else if (id > node->id)
    {

        if (node->rightChild)
        {
            DrawLineEx((Vector2){node->coordinate.x, node->coordinate.y}, (Vector2){node->rightChild->coordinate.x, node->rightChild->coordinate.y},6, GREEN);
        }
        
        searchRequstTrace(id,node->rightChild,node->rightChild->coordinate.x, node->rightChild->coordinate.y);
    }
    else if(id < node->id)
    {

        if (node->leftChild)
        {
            DrawLineEx((Vector2){node->coordinate.x, node->coordinate.y}, (Vector2){node->leftChild->coordinate.x, node->leftChild->coordinate.y},6, GREEN);
        }
        
        searchRequstTrace(id,node->leftChild,node->leftChild->coordinate.x, node->leftChild->coordinate.y);
    }
    

}

int BST::getSize(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getSize(node->rightChild) + getSize(node->leftChild) + 1;
}

int BST::drawUpToRoot(Node *node)
{
    if (node == nullptr || node->parents == nullptr)
    {
        return 0;
    }

    // Node *temp = node->parents;
    // int distance = 0;
    // int distance_y = 0;
    // if (temp->leftChild == node)
    // {
    //     distance = 70 * (getSize(temp->rightChild) + 1);
    //     distance_y = distance;
    // }
    // else
    // {
    //     distance = 70 * (getSize(temp->leftChild) + 1);
    //     distance_y = distance;
    //     distance *= -1;
    // }

    DrawLineEx((Vector2){node->coordinate.x, node->coordinate.y}, (Vector2){node->parents->coordinate.x , node->parents->coordinate.y}, 10, RED);
    return 1 + drawUpToRoot(node->parents);
}

void BST::drawBinarySearchTree(Node *node)
{
 
    if (node == nullptr)
    {
        return;
    }

    if (node->leftChild != nullptr)
    {
        DrawLineEx((Vector2){node->coordinate.x, node->coordinate.y}, (Vector2){node->leftChild->coordinate.x, node->leftChild->coordinate.y}, 5, BLACK);
    }

    if (node->rightChild != nullptr)
    {
        DrawLineEx((Vector2){node->coordinate.x, node->coordinate.y}, (Vector2){node->rightChild->coordinate.x, node->rightChild->coordinate.y}, 5, BLACK);
    }

    if (CheckCollisionPointCircle(GetScreenToWorld2D(GetMousePosition(), camera) , Vector2{node->coordinate.x,node->coordinate.y} , 40))
    {
        collisionNode = node;
        nodeCollisionHelper = true;
        drawUpToRoot(node);
    }
    
    
    if ( CheckCollisionPointCircle(GetScreenToWorld2D(GetMousePosition(), camera) , Vector2{node->coordinate.x,node->coordinate.y} , 40) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (holdingNode == node || holdingNode == nullptr))
    {
        holdingNode = node;
        node->coordinate = GetScreenToWorld2D(GetMousePosition(), camera);

        if (holdingSomething == false)
        {
            holdingNode = node;
        }
        
        holdingSomething = true;
    }
    else
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) == true)
        {
            if (holdingSomething == true && node == holdingNode)
            {
                holdingNode = node;
                node->coordinate = GetScreenToWorld2D(GetMousePosition(), camera);
            }
        }
        else
        {
            holdingSomething = false;
            holdingNode = nullptr;
        }
    }
    
    
    
    DrawCircle(node->coordinate.x, node->coordinate.y, 43, BLACK);
    
    if (node->parents == nullptr)
    {
        DrawCircle(node->coordinate.x, node->coordinate.y, 40, GOLD);
    }
    else
    {
        DrawCircle(node->coordinate.x, node->coordinate.y, 40, ORANGE);
    }
    
    
    std::string label = std::to_string(node->id);
    std::string nameLabel = node->name;
    DrawText(label.c_str(), node->coordinate.x - MeasureText(label.c_str(), 15) / 2,  node->coordinate.y - 13, 15, BLACK);
    DrawText(nameLabel.c_str(), node->coordinate.x - MeasureText(nameLabel.c_str(), 15) / 2,  node->coordinate.y + 3, 15, DARKGRAY);
    drawBinarySearchTree(node->rightChild);
    drawBinarySearchTree(node->leftChild);


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
        oldNode->parents->rightChild = newNode;
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
        transplant(target, target->rightChild);
    }
    else if (target->rightChild == nullptr)
    {
        transplant(target, target->leftChild);
    }
    else
    {
        Node* minNode = getMinimumNode(target->rightChild);

        if (minNode->parents != target)
        {
            transplant(minNode, minNode->rightChild);
            minNode->rightChild = target->rightChild;
            if (minNode->rightChild)
            {
                minNode->rightChild->parents = minNode;
            }
        }

        transplant(target, minNode);
        minNode->leftChild = target->leftChild;
        if (minNode->leftChild)
        {
            minNode->leftChild->parents = minNode;
        }
    }

    target->leftChild = target->rightChild = nullptr;
    target->parents = nullptr;

    delete target;
    recalcuteCoordinates(head,0,0);
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

    std::cout << "[" << n->id << ',' << n->name << "] ";
    print(n->leftChild);
    print(n->rightChild);
}