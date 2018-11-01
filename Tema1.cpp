#include "Tema1.h"
#include "DrawRect.h"
#include "DrawCircle.h"
#include "Transform2D.h"
#include "Collision2D.h"
#include "Brick.h"
#include <vector>
#include <iostream>
#include <string>
#include <Core/Engine.h>

const float PI = 3.1415926535;

using namespace std;

Tema1::Tema1(){}

Tema1::~Tema1(){}

std::string str = "";
float walls[3]; //contains the inner margins of the outer walls

std::vector<Brick> blocks;

glm::ivec2 resolution;
void Tema1::Init()
{
	resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);

	//Brick act_block();

	Mesh* LeftWall = DrawRect::CreateRectangle("LeftWall", glm::vec3(0, 30, 0), resolution.y - 30, 30.0f, glm::vec3(1, 0, 0), true);
	AddMeshToList(LeftWall);
	walls[0] = 30.0f;

	Mesh* Ceiling = DrawRect::CreateRectangle("Ceiling", glm::vec3(30, resolution.y - 30, 0), 50.0f, resolution.x - 60, glm::vec3(1, 0, 0), true);
	AddMeshToList(Ceiling);
	walls[1] = resolution.y - 50;

	Mesh* RightWall= DrawRect::CreateRectangle("RightWall", glm::vec3(resolution.x - 30, 30, 0), resolution.y-30, 30.0f, glm::vec3(1, 0, 0), true);
	AddMeshToList(RightWall);
	walls[2] = resolution.x - 30;
	
	int coordBx, coordBy = 350;

	for (int i = 1; i <= 5; i++) {
		coordBx = 150;
		for (int j = 1; j <= 10; j++) {
			str = "block";
			str += i;
			str += j;
			Mesh* block1 = DrawRect::CreateRectangle(str, glm::vec3(coordBx, coordBy , 0), 30, 80, glm::vec3(1, 0, 0), true);
			AddMeshToList(block1);
			Brick act_block(str, coordBx, (coordBx + 80), coordBy, (coordBy + 30), 1);
			blocks.push_back(act_block);
			coordBx += 100;
		}
		coordBy += 60;
	}

	Mesh* platform = DrawRect::CreateRectangle("Platform", glm::vec3(540, 0, 0), 20, 200, glm::vec3(0, 1, 0), true);
	AddMeshToList(platform);

	Mesh* ball = DrawCircle::CreateCircle("Ball", glm::vec3(640, 30, 0), 10, glm::vec3(0, 1, 1));
	AddMeshToList(ball);
	

	Mesh* life1 = DrawCircle::CreateCircle("life1", glm::vec3(7, 7, 0), 7, glm::vec3(0.2f, 0.6f, 0.4f));
	AddMeshToList(life1);

	Mesh* life2 = DrawCircle::CreateCircle("life2", glm::vec3(27, 7, 0), 7, glm::vec3(0.2f, 0.6f, 0.4f));
	AddMeshToList(life2);

	Mesh* life3 = DrawCircle::CreateCircle("life3", glm::vec3(47, 7, 0), 7, glm::vec3(0.2f, 0.6f, 0.4f));
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

float ty = 0, tx = 0, platfx = 0, platflength = 200, sx = 0, sy = 0;
short ok_space = 0; //becomes 1 when SPACE key is pressed
double constx = 0.01f, consty = 200; //translation step for x-axis and y-axis; initially, the ball will go straight up

void Tema1::Update(float deltaTimeSeconds) {
	
	modelMatrix = glm::mat3(1);
	
	
	RenderMesh2D(meshes["LeftWall"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["Ceiling"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["RightWall"], shaders["VertexColor"], modelMatrix);

	short k = 0;
	
	for (int i = 1; i <= 5; i++) {
		
		for (int j = 1; j <= 10; j++) {
			modelMatrix = glm::mat3(1);
			str = "block";
			str += i;
			str += j;
			if(blocks.at(k).level > 0)
				RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
			/*else
				{
				
				while (sx > -1000)
				{
					sx -= deltaTimeSeconds * 100;
					sy -= deltaTimeSeconds * 100;
					cout << sx << ' ' << sy << '\n';
					modelMatrix *= Transform2D::Scale(sx, sy);
					RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
				}
					
				}*/
			k++;
		}
	}

	modelMatrix *= Transform2D::Translate(platfx, 0);

	RenderMesh2D(meshes["Platform"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	if (ok_space == 1)
	{
		tx += (deltaTimeSeconds) * constx;
		ty += (deltaTimeSeconds ) * consty;
	}
	modelMatrix *= Transform2D::Translate(tx, ty);
	RenderMesh2D(meshes["Ball"], shaders["VertexColor"], modelMatrix);

	/***************************************************************************************************************************************/
	/***************************************************************************************************************************************/
	float degToRad;
	switch (Collision2D::WallCollision(glm::vec3((tx + resolution.x / 2), ty, 0), walls, false))
	{
		case 1: 
			constx = -constx;
			break;

		case 2:
			consty = -consty;
			break;
		case 3:
			
			if (Collision2D::PlatformCollision(glm::vec3(tx, ty, 0), platfx, platflength) == 1)
			{
				
				degToRad = 0.9*abs(platfx - tx)*PI/180;
				//std::cout << degToRad << '\n' << cos(degToRad) << ' ' << sin(degToRad) << '\n';
				
				if (tx > platfx)
				{
					constx = (1 - cos(degToRad)) * 200;
					if (cos(degToRad) < 0.5f)
						constx *= 1.5f;
					consty = (1 - sin(degToRad)) * 200;
				}
				else
				{
					constx = (cos(PI - degToRad)) * 200;
					consty = (1 - sin(degToRad)) * 200;
				}
			}
			break;

		case 4:
			consty = -consty;
			break;
	}
	/***************************************************************************************************************************/
	/***************************************************************************************************************************************/
	//cout << Collision2D::BlockCollision(glm::vec3(tx + 640, ty, 0), blocks) << '\n';
	short scale_position = -1;

	for (int i = 0; i < 50; i++)
	{
		switch (Collision2D::BlockCollision(glm::vec3(tx + 640, ty + 30, 0), blocks.at(i)))
		{
			case 1:
				blocks.at(i).level = 0;
				constx *= -1;
				break;

			case 2:
				blocks.at(i).level = 0;
				constx *= -1;
				break;

			case 3:
				//Tema1::DestroyBrick(blocks.at(i));
				blocks.at(i).level = 0;
				consty *= -1;
				scale_position = i;
				break;

			case 4:
				blocks.at(i).level = 0;
				consty *= -1;
				break;
		}
	}
	sx += deltaTimeSeconds*10;
	sy += deltaTimeSeconds*10;
	if (scale_position >= 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(sx, sy);
		RenderMesh2D(meshes[blocks.at(scale_position).name], shaders["VertexColor"], modelMatrix);
	}

	//cout << sx << ' ' << sy << '\n';

	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["life3"], shaders["VertexColor"], modelMatrix);

}

//void Tema1::DestroyBrick(Brick brick, float deltaTimeSeconds)
//{
//	modelMatrix = glm::mat3(1);
//	modelMatrix *= 
	/*float sx = brick.x_right_coord - brick.x_left_coord, sy = brick.y_upper_coord - brick.y_lower_coord;
	modelMatrix = glm::mat3(1);
	while (sx > 0 && sy > 0)
	{
		modelMatrix *= Transform2D::Scale(-0.05f, -0.133f);
		RenderMesh2D(meshes[brick.name], shaders["VertexColor"], modelMatrix);
		sx -= 0.05f;
		sy -= 0.133f;
	}*/
//}

void Tema1::OnInputUpdate(float deltaTime, int mods){};

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		ok_space = 1;
	}
		

};

void Tema1::OnKeyRelease(int key, int mods){};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	modelMatrix = glm::mat3(1);
	if (ok_space == 0)
		tx += deltaX;	//the ball will move with the platform until SPACE key is pressed
	platfx += deltaX;
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods){};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods){}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY){}

void Tema1::OnWindowResize(int width, int height){}