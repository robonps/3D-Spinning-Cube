#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>

void matmul(int mat1[][10], int mat2[][10]);
int mult[10][10];

int main(void){
	dclear(C_WHITE);
	int points[][10] = {
		{1,2},
		{2,3},
	};
	int matrixthing[][10] = {
		{6, 5},
		{5, 6},
	};
	char answer[10];
	matmul(matrixthing, points);
	sprintf(answer, "%d", mult[0][0]);
	dprint(1,1,C_BLACK,answer);
	dupdate();

	getkey();
	return 1;
}

// Function to multiply both matrices
void matmul(int mat1[][10], int mat2[][10]){

	// Finding row size and column size for both mat1 and mat2
	const int row1 = sizeof(mat1) / sizeof(mat1[0]);
	const int col1 = sizeof(mat1[0]) / sizeof(mat1[0][0]);

	const int row2 = sizeof(mat2) / sizeof(mat2[0]);
	const int col2 = sizeof(mat2[0]) / sizeof(mat2[0][0]);

	if(col1 != row2){
		return;
	}

	int i,j,k;

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < row1; ++i)
	{
		for(j = 0; j < col2; ++j)
		{
			mult[i][j] = 0;
			for(k=0; k<col1; ++k)
			{
				mult[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}