#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>

void matmul(int mat1[10][10], int mat2[10][10], int row1, int row2, int col1, int col2);
int mult[10][10];

int main(void){
	dclear(C_WHITE);
	int points[10][10] = {
		{1,2},
		{2,3},
	};
	int matrixthing[10][10] = {
		{6, 5},
		{5, 6},
	};
	char answer[10];
	matmul(matrixthing, points,2,2,2,2);
	sprintf(answer, "%d", mult[0][0]);
	dprint(1,1,C_BLACK,answer);
	dupdate();

	getkey();
	return 1;
}

// Function to multiply both matrices
void matmul(int mat1[10][10], int mat2[10][10], int row1, int row2, int col1, int col2){

	if(col1 != row2){
		return;
	}

	int i,j,k,sum;

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