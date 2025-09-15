#include "olcConsoleGameEngine.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const float PI = 3.14159f;

//coordinates in 3d space (vertices)
struct vec3d {
	float x, y, z;
};

//triangle (3 points)
struct triangle {
	vec3d p[3];
};

//3d meshes composed from triangles
struct mesh {
	vector<triangle> tris;
};

//4 x 4 matrix
struct mat4x4 {
	float m[4][4] = { 0 };
};

class olcEngine3D : public olcConsoleGameEngine{
private:
	mesh meshCube;
	mat4x4 matProj;

	//myltiply matrix by vector
	void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &mat) {
		o.x = i.x * mat.m[0][0] + i.y * mat.m[1][0] + i.z * mat.m[2][0] + mat.m[3][0];
		o.y = i.x * mat.m[0][1] + i.y * mat.m[1][1] + i.z * mat.m[2][1] + mat.m[3][1];
		o.z = i.x * mat.m[0][2] + i.y * mat.m[1][2] + i.z * mat.m[2][2] + mat.m[3][2];
		float w = i.x * mat.m[0][3] + i.y * mat.m[1][3] + i.z * mat.m[2][3] + mat.m[3][3];

		if (w != 0.0f) {
			o.x /= w;
			o.y /= w;
			o.z /= w;
		}
	}

public:
	//constructor
	olcEngine3D() {
		//uses 'L' prefix for wchar data type => extended char set
		m_sAppName = L"3D engine";
	}

	bool OnUserCreate() override {
		//coordinates with 'f' suffix to define float nums
		meshCube.tris = {
			// SOUTH
			{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

			// EAST                                                      
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

			// NORTH                                                     
			{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

			// WEST                                                      
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

			// TOP                                                       
			{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

			// BOTTOM                                                    
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
		};

		//projection matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;

		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		//draw triangles
		for (auto tri : meshCube.tris) {
			triangle triProjected, triTranslated;

			/*
			triTranslated = tri;
			triTranslated.p[0].z = tri.p[0].z + 3.0f;
			triTranslated.p[1].z = tri.p[1].z + 3.0f;
			triTranslated.p[2].z = tri.p[2].z + 3.0f;
			*/

			MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(tri.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(tri.p[2], triProjected.p[2], matProj);

			//scale into view
			
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

			//draw triangles
			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_WHITE);
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