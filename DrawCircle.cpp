#include "DrawCircle.h"
#include <iostream>

#include <Core/Engine.h>

const float PI = 3.1415926535;

Mesh* DrawCircle::CreateCircle(std::string name, float radius, float coordx, float coordy, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	int triangleAmount = 20;
	

	float rad = PI / triangleAmount, x, y;
	//glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
	{
		float angle = i * 2 * rad;
		x = cos(angle) * radius + coordx;
		y = sin(angle) * radius + coordy;

		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		indices.push_back(i);
	}

	Mesh* circle = new Mesh(name);

	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);


	return circle;

	//glEnd();
}