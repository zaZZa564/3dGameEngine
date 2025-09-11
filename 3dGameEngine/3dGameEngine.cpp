#include "olcConsoleGameEngine.h"
#include <iostream>
#include <vector>

using namespace std;

//coordinates in 3d space (vertices)
struct vec3d {
	float x, y, z;
};

//for triangle (3 points)
struct triangle {
	vec3d p[3];
};

//for 3d meshes composed from triangles
struct mesh {
	vector<triangle> tris;
};

class olcEngine3D : public olcConsoleGameEngine{
private:
	mesh meshCube;

public:
	olcEngine3D() { //constructor
		//uses 'L' prefix for wchar data type => extended char set
		m_sAppName = L"3D engine";
	}

	bool OnUserCreate() override {
		meshCube.tris = {
			//south
			{0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f},

			//east
			{1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f},

			//north
			{1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f},

			//west
			{0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f},

			//top
			{0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f},
			{0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f},

			//bottom
			{1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f},

		};
		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		//draw triangles
		for (auto tri : meshCube.tris) {

		}

		return true;
	}
};

int main() {
	//console setup
	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 4, 4)) {
		demo.Start();
	}

	return 0;
}