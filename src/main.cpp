#include <iostream>
#include "./binarySortTree.h"
#include "raylib.h"
#include "raymath.h"

int main(int argc, char *argv[])
{
    BST binaryTree;


    binaryTree.insertRequest("test 1" , 22);
    binaryTree.insertRequest("test 2" , 2);
    binaryTree.insertRequest("test 3" , 5);
    binaryTree.insertRequest("test 4" , 1);
    binaryTree.insertRequest("test 5" , 8);
    binaryTree.insertRequest("test 6" , 6);
    binaryTree.insertRequest("test 7" , 25);
    binaryTree.insertRequest("test 8" , 1811);
    binaryTree.insertRequest("test 9" , 14);
    binaryTree.insertRequest("test 10" , 23);
    binaryTree.insertRequest("test 11" , 12);
    binaryTree.insertRequest("test 12" , 121);
    binaryTree.insertRequest("test 13" , 31);
    binaryTree.insertRequest("test 14" , -3);
    binaryTree.insertRequest("test 15" , 0);
    binaryTree.insertRequest("test 16" , 18);
    binaryTree.insertRequest("test 18" , 28);
    binaryTree.insertRequest("test 17" , 29);
    binaryTree.insertRequest("test 19" , 27);
    binaryTree.insertRequest("test 20" , 122);
    binaryTree.insertRequest("test 21" , 19);
    binaryTree.insertRequest("test 22" , 26);
    binaryTree.insertRequest("test 23" , 1822);
    binaryTree.insertRequest("test 24" , -80);
    binaryTree.insertRequest("test 25" , -42);
    

    binaryTree.printBst();

    std::cout << "\nbst size : " << binaryTree.getSize(binaryTree.head) << '\n';

   // std::cout << binaryTree.searchRequst(13)->name << '\n';

    InitWindow(800,800,"project");
    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0 , 100 };
    camera.offset = (Vector2){ 400,400 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (WindowShouldClose() == false)
    {
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            Vector2 delta = GetMouseDelta();
            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;
        }

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);

        

        binaryTree.drawBinarySearchTree(binaryTree.head);

        EndMode2D();
        EndDrawing();
    }
    

    return 0;

   // std::cout << "Hello world!" << std::endl;
}
