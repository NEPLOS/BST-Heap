#include <iostream>
#include "./binarySortTree.h"
#include "./textField.h"
#include "./button.h"
#include "raylib.h"
#include "raymath.h"
#include "./maxHeap.h"
#include "./manager.h"

Camera2D camera = {0};

Node *collisionNode = nullptr;
bool nodeCollisionHelper = false;
int lvl = 0;
textField idField((Rectangle){620, 30, 160, 40});
textField nameField((Rectangle){620, 80, 160, 40});
textField priorityField((Rectangle){620, 130, 160, 40});
button submitButton((Rectangle){675, 180, 105, 25}, "submit", 18);
button changeMode((Rectangle){675, 210, 105, 25}, "change mode", 15);

button phpr((Rectangle){675,750,100,25} , "phpr" , 20);

std::string title = "binary search tree";
int pendingDeleteID = -1;



// textField 

Font font1; // = LoadFontEx("./font/2.ttf",35,0,0);

enum Tab
{
	TAB_BINARY_SEARCH_TREE,
	TAB_MAX_HEAP
};

enum Mode
{
	INSERT_MODE,
	INCREASE_PRIORITY_MODE,
	SEARCH_MODE,
};

Mode currentMode = INSERT_MODE;
Tab currentTab = TAB_BINARY_SEARCH_TREE;
bool IdExists = false;
int IdSearch;

void drawFieldMaxHeap()
{
	// submitButtononclick()
	// {

	// }
}

void drawTextField(BST &binaryTree , maxHeap& heap)
{

	if (changeMode.onclick())
	{
		int curr = currentMode;
		curr = ++curr % 3;
		currentMode = (Mode)curr;

		if (currentMode == INSERT_MODE)
		{
			nameField.setVisible(true);
			priorityField.setVisible(true);

		}
		else if(currentMode == INCREASE_PRIORITY_MODE)
		{
			nameField.setVisible(false);
			priorityField.setVisible(true);
			//idField.setVisible(true);
		}
		else
		{
			nameField.setVisible(false);
			priorityField.setVisible(false);
		}
	}

	if (idField.handleInput() && currentMode == SEARCH_MODE)
	{
		if (idField.input.empty() || idField.input == "-")
		{
			IdExists = false;
			return;
		}

		if (binaryTree.searchRequst(idField.inputToNumber()) != nullptr)
		{
			IdExists = true;
			IdSearch = idField.inputToNumber();
		}
		else
		{
			IdExists = false;
		}
	}
	idField.drawTextField();

	nameField.drawTextField();
	nameField.handleInput();

	priorityField.drawTextField();
	priorityField.handleInput();
	
	submitButton.drawButton();

	changeMode.drawButton();

	if (submitButton.onclick())
	{
		int targetID = idField.inputToNumber();
		switch (currentMode)
		{
		case INSERT_MODE:
			// std::cout << targetID << '\n';
			binaryTree.insertRequest(nameField.input, targetID);
			heap.insertHeap(targetID,priorityField.inputToNumber());
			break;
		case INCREASE_PRIORITY_MODE:
			// std::cerr << "target : " << targetID << '\n';
			//pendingDeleteID = targetID;
			heap.increasePriority(targetID,priorityField.inputToNumber());
			break;
		default:
			break;
		}
	}

	std::string title;

	switch (currentMode)
	{
	case INSERT_MODE:
		// binaryTree.insertRequest(nameField.input, targetID);
		// DrawText("insert mode" , 5 , 5 , 35 , BLACK);
		title = "insert mode";
		break;
	case INCREASE_PRIORITY_MODE:
		// DrawText("delete mode" , 5 , 5 , 35 , BLACK);
		title = "increase priority mode";
		break;
	default:
		title = "search mode";
		// DrawText("search mode" , 5 , 5 , 35 , BLACK);
		break;
	}

	DrawTextEx(font1, title.c_str(), {5, 5}, 40, 2, BLACK);

	phpr.drawButton();

	if(phpr.onclick())
	{
		heap.processHighestPriorityRequest(&binaryTree);
	}
	// title;
}

void panel()
{
	if (nodeCollisionHelper == true && collisionNode != nullptr)
	{
		int rectangleX = GetScreenToWorld2D(GetMousePosition(), camera).x;
		int rectangleY = GetScreenToWorld2D(GetMousePosition(), camera).y;

		// int rectangleX = GetMousePosition().x;
		// int rectangleY = GetMousePosition().y;

		std::string label = "id : " + std::to_string(collisionNode->id);
		std::string nameLabel = "name : " + collisionNode->name;
		std::string nodeLevel = "lvl : " + std::to_string(lvl);
		DrawRectangleV((Vector2){rectangleX, rectangleY}, (Vector2){130, 100}, GRAY);
		DrawRectangleLinesEx((Rectangle){rectangleX, rectangleY, 130, 100}, 4, BLACK);
		// DrawTextPro(font1,label.c_str(),(Vector2){7 + rectangleX, rectangleY + 15},{0,0},0,15,0,BLACK);
		DrawText(label.c_str(), 7 + rectangleX, rectangleY + 15, 15, BLACK);
		DrawText(nameLabel.c_str(), 7 + rectangleX, rectangleY + 31, 15, BLACK);
		DrawText(nodeLevel.c_str(), 7 + rectangleX, rectangleY + 47, 15, BLACK);
	}
}

void updateCamera()
{
	camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

	if (camera.zoom > 3.0f)
		camera.zoom = 3.0f;
	else if (camera.zoom < 0.02f)
		camera.zoom = 0.02f;

	if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
	{
		Vector2 delta = GetMouseDelta();
		camera.target.x -= delta.x / camera.zoom;
		camera.target.y -= delta.y / camera.zoom;
	}
}

int main(int argc, char *argv[])
{

	manager man;

	srand(time(NULL));

	man.insertProcess("test 1", 22, 30);
	man.insertProcess("test 2", 2, 50);
	man.insertProcess("test 3", 5, 10);
	man.insertProcess("test 4", 1, 60);
	man.insertProcess("test 5", 25, 230);
	man.insertProcess("test 6", 10, 130);
	man.insertProcess("test 7", 15, 30);
	man.insertProcess("test 8", 13, 41);
	man.insertProcess("test 9", 154, 42);
	man.insertProcess("test 10", 152, 433);
	man.insertProcess("test 11", 153, 12);
	man.insertProcess("test 11", 133, 20);

	// for (int i = 0; i < 10; i++)
	// {
	// 	man.insertProcess("test 11", rand() % 200 , rand() % 200);
	// }

	man.heap.print();

	InitWindow(800, 800, "project");

	font1 = LoadFontEx("./fonts/DMSerifText.ttf", 35, 0, 0);

	SetTargetFPS(60);

	camera.target = (Vector2){0, 100};
	camera.offset = (Vector2){400, 400};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	//man.binaryTree.printBst();

	//man.heap.print();

	while (WindowShouldClose() == false)
	{

		updateCamera();

		BeginDrawing();
		ClearBackground(WHITE);
		// DrawText(title.c_str() , 10 , 755 , 35 , BLACK);
		
		BeginMode2D(camera);
		
		if (currentTab == TAB_MAX_HEAP)
		{
			//	std::cerr << "\n\n";
			man.heap.drawMaxHeap(0, 0, 0, pow(2, ((int)(log2(man.heap.array.size())) + 1)) * 20);
			// std::cerr << "\n\n";
			EndMode2D();
		}
		else
		{
			nodeCollisionHelper = false;
			man.binaryTree.drawBinarySearchTree(man.binaryTree.head);
			
			if (currentMode == SEARCH_MODE && IdExists)
			man.binaryTree.searchRequstTrace(IdSearch, man.binaryTree.head, 0, 0);
			panel();
			EndMode2D();
		}
		drawTextField(man.binaryTree,man.heap);
		
		DrawTextEx(font1, title.c_str(), (Vector2){10, 755}, 35, 2, BLACK);

		EndDrawing();

		if (pendingDeleteID != -1)
		{
			man.binaryTree.deleteRequest(pendingDeleteID);
			pendingDeleteID = -1;
		}

		// if (IsKeyDown(KEY_A))
		// {
		// 	man.heap.increasePriority(22,50);
		// }
		

		if (IsKeyPressed(KEY_M))
		{
			if (currentTab == TAB_BINARY_SEARCH_TREE)
			{
				currentTab = TAB_MAX_HEAP;
				title = "max Heap";
			}
			else
			{
				currentTab = TAB_BINARY_SEARCH_TREE;
				title = "binary search tree";
			}
		}
	}

	return 0;

	// std::cout << "Hello world!" << std::endl;
}
