
#ifndef BINARY_SORT_TREE
#define BINARY_SORT_TREE

#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Node
{
public:
    std::string name;
    int id;
    Vector2 coordinate;

    Node *parents = nullptr;
    Node *rightChild = nullptr;
    Node *leftChild = nullptr;

    Node(std::string name, int id);
    Node();
};

class BST
{

public:
    Node *head = nullptr;

    void insertRequest(std::string name, int id);
    void deleteRequest(int id);
    void transplant(Node* oldNode , Node* newNode);
    bool isEmptyBST();
    Node *searchRequst(int id);
    void searchRequstTrace(int id , Node* node , int x , int y);
    int getSize(Node *node);
    void drawBinarySearchTree(Node* node);
    void recalcuteCoordinates(Node* node , int x = 0, int y = 0);
    Node* getMinimumNode(Node* starter);
    int drawUpToRoot(Node* node);
    void printBst();

private:
    void print(Node *n);
};

#endif
