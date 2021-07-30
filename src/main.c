#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>
#include <math.h>

void matmul(float mat1[9][9], float mat2[9][9], int row1, int row2, int col1, int col2, float output[9][9]);
void matcp(float input[9][9], float output[9][9], int row, int col);

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

	bool renderEdges = true;
	float pix = 12;

	int i,j;
	

	float points[9][9] = {
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, -1},
		{1, -1, -1},
		{1, 1, 1},
		{-1, 1, 1},
		{-1, -1, 1},
		{1, -1, 1}
	};

	float edges[12][12] = {
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

	float point[9][9];
	float pos[9][9];
	int pointslen = 8;
	int edgeslen = 12;
	float multOutput[9][9];

	while(true) {
		float offset[9][9] = {
				{1, 0, 0, offsetX},
				{0, -1, 0, offsetY},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
		};

		float p[9][9] = {
				{(f*128)/(2*Px), skew, 0, 0},
				{0, (f*64)/(2*Py), 0, 0},
				{0, 0, -1, 0},
				{0, 0, 0, 1}
		};

		float c[9][9] = {
				{1, 0, 0, -Cx},
				{0, 1, 0, -Cy},
				{0, 0, 1, -Cz},
				{0, 0, 0, 1}
		};

		float Rx[9][9] = {
				{1, 0, 0, 0},
				{0, cos(RotX), -sin(RotX), 0},
				{0, sin(RotX), cos(RotX), 0},
				{0, 0, 0, 1}
		};

		float Ry[9][9] = {
				{cos(RotY), 0, sin(RotY), 0},
				{0, 1, 0, 0},
				{-sin(RotY), 0, cos(RotY), 0},
				{0, 0, 0, 1}
		};

		float Rz[9][9] = {
				{cos(RotZ), -sin(RotZ), 0, 0},
				{sin(RotZ), cos(RotZ), 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
		};

		float g[9][9] = {
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
			matmul(g, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(Rz, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(Ry, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(Rx, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(c, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(p, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			float n[9][9] = {
				{1/point[2][0], 0, 0, 0},
				{0, 1/point[2][0], 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			
			};
			matmul(n, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			matmul(offset, point, 4, 4, 4, 1, multOutput);
			matcp(multOutput, point, 4, 1);
			pos[i][0] = point[0][0];
			pos[i][1] = point[1][0];
			pos[i][2] = point[2][0];

		}
		dclear(C_WHITE);
		for(i = 0; i< pointslen; ++i){
			float d = pix / pos[i][2] / 2;
			if(renderEdges){
				for(j = 0; j < edgeslen; ++j){
					int x1 = edges[j][0] - 1;
					int x2 = edges[j][1] - 1;
					dline(pos[x1][0] - d, pos[x1][1] - d, pos[x2][0] - d, pos[x2][1] - d, C_BLACK);
				}
			}else{
				dpixel(pos[i][0] - d, pos[i][1] - d, C_BLACK);
			}
		}
		RotX = RotX + 0.01;
		RotY = RotY + 0.01;
		RotZ = RotZ + 0.01;
		dupdate();

		int keyPressed = get_inputs();
		if(keyPressed == 1){
			return 1;
		}else if(keyPressed == 2){
			Cz = Cz - 0.5;
		}else if(keyPressed == 3){
			Cz = Cz + 0.5;
		}

	}
}

// Function to multiply both matrices
void matmul(float mat1[9][9], float mat2[9][9], int row1, int row2, int col1, int col2, float output[9][9]){

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
			output[i][j] = sum;
		}
	}
}

void matcp(float input[9][9], float output[9][9], int row, int col){
	int i,j;
	for(i = 0; i < row; ++i){
		for(j = 0; j < col; ++j){
			output[i][j] = input[i][j];
		}
	}
}

int get_inputs(void){
	int opt = GETKEY_DEFAULT & ~GETKEY_REP_ALL & GETKEY_MENU & GETKEY_MOD_SHIFT & GETKEY_MOD_ALPHA;
	int timeout = 1;
	while(1){
		key_event_t ev = getkey_opt(opt, &timeout);
		if(ev.type == KEYEV_NONE) return -1;
		
		int key = ev.key;
		if(key == KEY_MENU) return 1;
		if(key == KEY_SHIFT) return 2;
		if(key == KEY_ALPHA) return 3;
	}
}