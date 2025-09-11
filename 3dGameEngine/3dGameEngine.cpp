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

		};
		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override {
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