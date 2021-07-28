#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>

int main(void)
{
	dclear(C_WHITE);
	int mat[4][1] = {
		{1},
		{2},
		{3},
		{4}
	};
	int num_rows = sizeof(mat) / sizeof(mat[0]);
	dprint(1,1,C_BLACK,"%s"int);
	dupdate();

	getkey();
	return 1;
}
