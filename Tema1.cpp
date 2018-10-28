#include "Tema1.h"
#include "DrawRect.h"
#include "DrawCircle.h"
#include "Transform2D.h"
#include <vector>
#include <iostream>
#include <string>
#include <Core/Engine.h>

using namespace std;

Tema1::Tema1(){}

Tema1::~Tema1(){}

std::string str = "";
//Mesh* meshList[10];


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	Mesh* LeftWall = DrawRect::CreateRectangle("LeftWall", glm::vec3(0, 30, 0), resolution.x - 30, 30, glm::vec3(1, 0, 0), true);
	AddMeshToList(LeftWall);

	Mesh* Ceiling = DrawRect::CreateRectangle("Ceiling", glm::vec3(30, resolution.y - 30, 0), 50, resolution.x - 60, glm::vec3(1, 0, 0), true);
	AddMeshToList(Ceiling);

	Mesh* RightWall= DrawRect::CreateRectangle("RightWall", glm::vec3(resolution.x - 30, 30, 0), resolution.x-30, 50, glm::vec3(1, 0, 0), true);
	AddMeshToList(RightWall);
	
	int coordBx, coordBy = 350;

	for (int i = 1; i <= 5; i++) {
		coordBx = 150;
		for (int j = 1; j <= 10; j++) {
			str = "block";
			str += i;
			str += j;
			Mesh* block1 = DrawRect::CreateRectangle(str, glm::vec3(coordBx, coordBy , 0), 30, 80, glm::vec3(1, 0, 0), true);
			AddMeshToList(block1);
			coordBx += 100;
		}
		coordBy += 60;
	}

	Mesh* platform = DrawRect::CreateRectangle("Platform", glm::vec3(540, 0, 0), 20, 200, glm::vec3(0, 1, 0), true);
	AddMeshToList(platform);

	Mesh* ball = DrawCircle::CreateCircle("Ball", 10, 640, 30, glm::vec3(0, 1, 1));
	AddMeshToList(ball);

	Mesh* life1 = DrawCircle::CreateCircle("life1", 7, 7, 7, glm::vec3(0.2f, 0.6f, 0.4f));
	AddMeshToList(life1);

	Mesh* life2 = DrawCircle::CreateCircle("life2", 7, 27, 7, glm::vec3(0.2f, 0.6f, 0.4f));
	AddMeshToList(life2);

	Mesh* life3 = DrawCircle::CreateCircle("life3", 7, 47, 7, glm::vec3(0.2f, 0.6f, 0.4f));
	AddMeshToList(life3);
	
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::FrameEnd()
{

}
float ty = 0, tx = 0, platfx = 0, platfy = 0;
short ok_space = 1;

void Tema1::Update(float deltaTimeSeconds) {
	modelMatrix = glm::mat3(1);
	std::cout << ok_space;
	
	
	RenderMesh2D(meshes["LeftWall"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["Ceiling"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["RightWall"], shaders["VertexColor"], modelMatrix);
	
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 10; j++) {
			str = "block";
			str += i;
			str += j;
			RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
		}
	}

	modelMatrix *= Transform2D::Translate(platfx, 0);

	RenderMesh2D(meshes["Platform"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	if (ok_space == 0)
	{
		tx += deltaTimeSeconds * 100;
		ty += deltaTimeSeconds * 100;
	}
	modelMatrix *= Transform2D::Translate(tx, ty);

	RenderMesh2D(meshes["Ball"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["life3"], shaders["VertexColor"], modelMatrix);

}

void Tema1::OnInputUpdate(float deltaTime, int mods){};

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		ok_space = 0;
	}
		

};

void Tema1::OnKeyRelease(int key, int mods){};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	modelMatrix = glm::mat3(1);
	if (ok_space == 1)
		tx += deltaX;
	platfx += deltaX;
	//cout << mouseX << ' ' << mouseY << ' ' << deltaX << ' ' << deltaY;
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods){};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods){}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY){}

void Tema1::OnWindowResize(int width, int height){}