// Daniel Casper
// djc062000@utdallas.edu
// CS3377.002

#include "cdk.h"
#include <sys/stat.h>
#include <iostream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Text Matrix"

using namespace std;

int main(int argc, char * argv[]) {
	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;
	const char *rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3" };
	const char *columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3" };
	int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

	window = initscr();
	cdkscreen = initCDKScreen(window);

	initCDKColor();

	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

	if (myMatrix == NULL) {
		printf("Error in creating matrix");
		_exit(1);
	}
	
	struct stat results;

	if(stat("cs3377.bin", &results) == 0) {
		cout << results.st_size;
	}
	else {
		return 1;
	}

	drawCDKMatrix(myMatrix, true);
	setCDKMatrixCell(myMatrix, 2, 2, "message");
	drawCDKMatrix(myMatrix, true);

	sleep(10);

	endCDK();

	return 0;
}
