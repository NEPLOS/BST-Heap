
#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Node
{
public:
    std::string name;
    int id;

    Node *parents = nullptr;
    Node *rigthChild = nullptr;
    Node *leftChild = nullptr;

    Node(std::string name, int id);
    Node();
};

class BST
{

public:
    Node *head = nullptr;

    void insertRequest(std::string name, int id);
    bool isEmptyBST();
    Node *searchRequst(int id);
    int getSize(Node *node);
    void drawBinarySearchTree(Node* node, int x = 0 , int y = 0);
    void printBst();

private:
    void print(Node *n);
};