#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>
#include <math.h>

void matmul(float mat1[16][16], float mat2[16][16], int row1, int row2, int col1, int col2);
float mult[16][16];

int main(void){

	// Camera variables
	float Gx = 0;
	float Gy = 0;
	float Gz = 0;

	float RotX = 0;
	float RotY = 0;
	float RotZ = 0;

	float Cx = 0;
	float Cy = 0;
	float Cz = 5;

	float f = 0.1;
	float Px = .096;
	float Py = .055;
	float offsetX = 64;
	float offsetY = 32;
	float skew = 0;

	bool exit = true;
	bool renderEdges = false;
	float pix = 12;

	int i,j;
	

	float points[16][16] = {
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, -1},
		{1, -1, -1},
		{1, 1, 1},
		{-1, 1, 1},
		{-1, -1, 1},
		{1, -1, 1}
	};

	float edges[16][16] = {
		{1, 2},
		{2, 3},
		{3, 4},
		{4, 1},
		{5, 6},
		{6, 7},
		{7, 8},
		{8, 5},
		{5, 1},
		{8, 4},
		{3, 7},
		{6, 2}
	};

	float point[16][16];
	float pos[16][16];
	int pointslen = 8;
	int edgeslen = 12;

	while(exit) {
		float offset[16][16] = {
				{1, 0, 0, offsetX},
				{0, -1, 0, offsetY},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
		};

		float p[16][16] = {
				{(f*128)/(2*Px), skew, 0, 0},
				{0, (f*64)/(2*Py), 0, 0},
				{0, 0, -1, 0},
				{0, 0, 0, 1}
		};

		float c[16][16] = {
				{1, 0, 0, -Cx},
				{0, 1, 0, -Cy},
				{0, 0, 1, -Cz},
				{0, 0, 0, 1}
		};

		float Rx[16][16] = {
				{1, 0, 0, 0},
				{0, cos(RotX), -sin(RotX), 0},
				{0, sin(RotX), cos(RotX), 0},
				{0, 0, 0, 1}
		};

		float Ry[16][16] = {
				{cos(RotY), 0, sin(RotY), 0},
				{0, 1, 0, 0},
				{-sin(RotY), 0, cos(RotY), 0},
				{0, 0, 0, 1}
		};

		float Rz[16][16] = {
				{cos(RotZ), -sin(RotZ), 0, 0},
				{sin(RotZ), cos(RotZ), 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
		};

		float g[16][16] = {
				{1, 0, 0, -Gx},
				{0, 1, 0, -Gy},
				{0, 0, 1, -Gz},
				{0, 0, 0, 1}
		};
		for(i = 0; i <= pointslen; ++i){
			for(j = 0; j < 3; ++j){
				point[j][0] = points[i][j];
			}
			point[3][0] = 1;
			matmul(g, point, 4, 4, 4, 1);
			float point1[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(Rz, point1, 4, 4, 4, 1);
			float point2[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(Ry, point2, 4, 4, 4, 1);
			float point3[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(Rx, point3, 4, 4, 4, 1);
			float point4[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(c, point4, 4, 4, 4, 1);
			float point5[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(p, point5, 4, 4, 4, 1);
			float point6[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			float n[16][16] = {
				{1/point6[2][0], 0, 0, 0},
				{0, 1/point6[2][0], 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			
			};
			matmul(n, point6, 4, 4, 4, 1);
			float point7[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			matmul(offset, point7, 4, 4, 4, 1);
			float point8[16][16] = {{mult[0][0]},{mult[1][0]},{mult[2][0]},{mult[3][0]}};
			pos[i][0] = point8[0][0];
			pos[i][1] = point8[1][0];
			pos[i][2] = point8[2][0];

		}
		dclear(C_WHITE);
		for(i = 0; i< pointslen; ++i){
			float d = pix / pos[i][2] / 2;
			if(renderEdges){
				for(j = 0; j < edgeslen; ++j){
					int x1 = edges[j][0];
					int x2 = edges[j][1];
					//dline(pos[x1][0] - d, pos[x1][1] - d, pos[x2][0] - d, pos[x2][1] - d, C_BLACK);
				}
			}
			dpixel(pos[i][0] - d, pos[i][1] - d, C_BLACK);
		}
		RotX = RotX + 0.01;
		RotY = RotY + 0.01;
		RotZ = RotZ + 0.01;
		dupdate();
	}

	getkey();
	return 1;
}

// Function to multiply both matrices
void matmul(float mat1[16][16], float mat2[16][16], int row1, int row2, int col1, int col2){

	if(col1 != row2){
		return;
	}

	int i,j,k;
	float sum;

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < row1; ++i)
	{
		for(j = 0; j < col2; ++j)
		{
			sum = 0;
			for(k=0; k<col1; ++k)
			{
				sum += mat1[i][k] * mat2[k][j];
			}
			mult[i][j] = sum;
		}
	}
}