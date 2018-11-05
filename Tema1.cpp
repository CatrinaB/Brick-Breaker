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

const float PI = 3.14159265;

using namespace std;

Tema1::Tema1(){}

Tema1::~Tema1(){}

std::string str = "";
float walls[3]; //contains the inner margins of the outer walls

std::vector<Brick> blocks;

std::vector<short> powerups;

glm::ivec2 resolution;
short platflength = 200;	//platform length

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

	Mesh* LeftWall = DrawRect::CreateRectangle("LeftWall", glm::vec3(0, 30, 0), resolution.y - 30.0f, 30.0f, glm::vec3(1, 0, 0), true);
	AddMeshToList(LeftWall);
	walls[0] = 30.0f;

	Mesh* Ceiling = DrawRect::CreateRectangle("Ceiling", glm::vec3(30.0f, resolution.y - 30.0f, 0.0f), 50.0f, resolution.x - 60.0f, glm::vec3(1, 0, 0), true);
	AddMeshToList(Ceiling);
	walls[1] = resolution.y - 50.0f;

	Mesh* RightWall = DrawRect::CreateRectangle("RightWall", glm::vec3(resolution.x - 30.0f, 30.0f, 0.0f), resolution.y - 30.0f, 30.0f, glm::vec3(1, 0, 0), true);
	AddMeshToList(RightWall);
	walls[2] = resolution.x - 30.0f;
	
	int coordBx, coordBy = 350;

	for (int i = 1; i <= 5; i++) {	//makes the meshes for the bricks
		coordBx = 150;
		for (int j = 1; j <= 10; j++) {
			str = "block";
			str += i;
			str += j;
			Mesh* block1 = DrawRect::CreateRectangle(str, glm::vec3(coordBx, coordBy , 0), 30, 80, glm::vec3(1, 0, 0), true);
			AddMeshToList(block1);
			Brick act_block(str, coordBx, (coordBx + 80), coordBy, (coordBy + 30), 1, 0);
			if (i + j == 7)
				act_block.powerup = 1;	//creates blocks with power-ups
			blocks.push_back(act_block);
			coordBx += 100;
		}
		coordBy += 60;
	}

	Mesh* platform = DrawRect::CreateRectangle("Platform", glm::vec3(540, 0, 0), 20, platflength, glm::vec3(0, 1, 0), true);
	AddMeshToList(platform);

	Mesh* ball = DrawCircle::CreateCircle("Ball", glm::vec3(640, 30, 0), 10, glm::vec3(0, 1, 1));
	AddMeshToList(ball);
	
	float x_life = 7;
	for (int i = 1; i <= 3; i++)
	{
		str = "life";
		str += (i + 48);
		Mesh* life = DrawCircle::CreateCircle(str, glm::vec3(x_life, 7, 0), 7, glm::vec3(0.2f, 0.6f, 0.4f));
		AddMeshToList(life);
		x_life += 20;
	}
	
	Mesh* powerup_length = DrawRect::CreateRectangle("PowerupL", glm::vec3(690, 375, 0), 10, 10, glm::vec3(1, 0, 1), true);
	AddMeshToList(powerup_length);
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

void Tema1::FrameEnd(){}

float translateY = 0.0f, translateX = 0.0f;	//ball translation step for x-axis and y-axis
float platfx = 0.0f;	//platform x-axis translation step
// float scaleX = 0.0f, scaleY = 0.0f;
char ok_space = 0; //becomes 1 when SPACE key is pressed
float constx = 0.0f, consty = 200.0f; //ball translation speed for x-axis and y-axis; initially, the ball will go straight up
char nr_life = 3;	//number of lifes left
char scale_position = -1;
float rotation = 0.0f, pwy = 0.0f;	//power-up rotation and y-axis translation step
//fmm, fmmm;
char ok_pwup = 0;	//becomes 1 while a power-up is active
short nr_sec_pw_up = 0;	//counts the number of frames since the power-up is active

void Tema1::LengthPowerUp(float deltaTimeSeconds, char &scale_position)
{
	if (scale_position == 5)
	{
		rotation += deltaTimeSeconds * 2;
		pwy -= deltaTimeSeconds * 50;
		if (pwy > -550)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(0, pwy);
			modelMatrix *= Transform2D::Translate(695, 360);
			modelMatrix *= Transform2D::Rotate(rotation);
			modelMatrix *= Transform2D::Translate(-695, -380);
			RenderMesh2D(meshes["PowerupL"], shaders["VertexColor"], modelMatrix);
		}

		if (platfx + 640 <= 695 && platfx + 840 >= 695 && pwy <= -350 && nr_sec_pw_up < 2000)
		{
			ok_pwup = 1;
			pwy = -551;
			platflength = 400;

		}
		if (ok_pwup == 1)
			nr_sec_pw_up++;
		
		if (nr_sec_pw_up == 2000)
		{
			platflength = 200;
			ok_pwup = 0;
			nr_sec_pw_up = 0;
			scale_position = -1;
		}
	}
}

void Tema1::Update(float deltaTimeSeconds) {

	modelMatrix = glm::mat3(1);
	cout << (int)scale_position << '\n';

	RenderMesh2D(meshes["LeftWall"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["Ceiling"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["RightWall"], shaders["VertexColor"], modelMatrix);

	char k = 0;

	for (int i = 1; i <= 5; i++) {	//renders the bricks

		for (int j = 1; j <= 10; j++) {
			modelMatrix = glm::mat3(1);
			str = "block";
			str += i;
			str += j;
			if (blocks.at(k).level > 0)
				RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
			/*else
				{

				while (scaleX > -1000)
				{
					scaleX -= deltaTimeSeconds * 100;
					scaleY -= deltaTimeSeconds * 100;
					cout << scaleX << ' ' << scaleY << '\n';
					modelMatrix *= Transform2D::Scale(scaleX, scaleY);
					RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
				}

				}*/
			k++;
		}
	}
	
	if (ok_pwup == 0)
	{
		modelMatrix *= Transform2D::Translate(platfx, 0);
		RenderMesh2D(meshes["Platform"], shaders["VertexColor"], modelMatrix);
	}
	else
	{
		modelMatrix = glm::mat3(1);
		
		modelMatrix *= Transform2D::Translate(platfx, 0); 
		modelMatrix *= Transform2D::Translate(540, 0);
		modelMatrix *= Transform2D::Scale(2, 1);
		modelMatrix *= Transform2D::Translate(-590, 0);
		
		RenderMesh2D(meshes["Platform"], shaders["VertexColor"], modelMatrix);
	}

	modelMatrix = glm::mat3(1);
	if (ok_space == 1)
	{
		translateX += (deltaTimeSeconds)* constx;
		translateY += (deltaTimeSeconds)* consty;
	}
	//float vec = constx / consty;
	modelMatrix *= Transform2D::Translate(translateX, translateY);
	RenderMesh2D(meshes["Ball"], shaders["VertexColor"], modelMatrix);

	/***************************************************************************************************************************************/
	/***************************************************************************************************************************************/
	float degToRad;
	switch (Collision2D::WallCollision(glm::vec3((translateX + resolution.x / 2), translateY, 0), walls, false)) //checks if the ball hits a wall
	{																							//or drops below 30 px height
	case 1:
		constx = -constx;
		break;

	case 2:
		consty = -consty;
		break;
	case 3:
		if (Collision2D::PlatformCollision(glm::vec3(translateX, translateY, 0), platfx, platflength) == 1)	//checks if the ball hits the platform
		{
			if (platflength == 200)
				degToRad = 0.9f*abs(platfx + 100 - translateX)*PI / 180;
			else
				degToRad = 0.45f*abs(platfx + 200 - translateX)*PI / 180;
			
			constx = (cos(degToRad)) * 200;
			consty = sqrt(40000 - constx * constx);
		}
		else
		{
			nr_life--;
			ok_space = 0;
			translateX = 0;
			translateY = 0;
			platfx = 0;
			ok_pwup = 0;
			nr_sec_pw_up = 0;

		}
		break;

	case 4:
		consty = -consty;
		break;
	}
	/***************************************************************************************************************************/
	/***************************************************************************************************************************************/

	for (int i = 0; i < 50; i++)
	{
		switch (Collision2D::BlockCollision(glm::vec3(translateX + 640, translateY + 30, 0), blocks.at(i)))
		{
		case 1:
			blocks.at(i).level = 0;
			constx *= -1;
			scale_position = i;
			break;

		case 2:
			blocks.at(i).level = 0;
			constx *= -1;
			scale_position = i;
			break;

		case 3:
			//Tema1::DestroyBrick(blocks.at(i));
			blocks.at(i).level = 0;
			consty *= -1;
			if(blocks.at(i).powerup == 1)
			{
				scale_position = i;
			}

			break;

		case 4:
			blocks.at(i).level = 0;
			consty *= -1;
			scale_position = i;
			break;
		}
	}
	if (scale_position != -1)
	{
		Tema1::LengthPowerUp(deltaTimeSeconds, scale_position);
	}
	
	
	


	/*scaleX += deltaTimeSeconds*10;
	scaleY += deltaTimeSeconds*10;
	if (scale_position >= 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY);
		RenderMesh2D(meshes[blocks.at(scale_position).name], shaders["VertexColor"], modelMatrix);
	}*/

	//cout << scaleX << ' ' << scaleY << '\n';

	modelMatrix = glm::mat3(1);
	for (int i = 1; i <= nr_life; i++)
	{
		str = "life";
		str += (i + 48);
		RenderMesh2D(meshes[str], shaders["VertexColor"], modelMatrix);
	}

}

//void Tema1::DestroyBrick(Brick brick, float deltaTimeSeconds)
//{
//	modelMatrix = glm::mat3(1);
//	modelMatrix *= 
	/*float scaleX = brick.x_right_coord - brick.x_left_coord, scaleY = brick.y_upper_coord - brick.y_lower_coord;
	modelMatrix = glm::mat3(1);
	while (scaleX > 0 && scaleY > 0)
	{
		modelMatrix *= Transform2D::Scale(-0.05f, -0.133f);
		RenderMesh2D(meshes[brick.name], shaders["VertexColor"], modelMatrix);
		scaleX -= 0.05f;
		scaleY -= 0.133f;
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
		translateX += deltaX;	//the ball will move with the platform until SPACE key is pressed
	platfx += deltaX;
};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods){};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods){}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY){}

void Tema1::OnWindowResize(int width, int height){}