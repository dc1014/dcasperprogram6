// Daniel Casper
// djc062000@utdallas.edu
// CS3377.002

#include "cdk.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#define MATRIX_WIDTH 2
#define MATRIX_HEIGHT 4
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Text Matrix"

using namespace std;

int main(int argc, char * argv[]) {
	struct BinaryFileHeader {
		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
	} headers;

	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;
	const char *rowTitles[MATRIX_HEIGHT+1] = { "a", "b", "c", "d", "e" };
	const char *columnTitles[MATRIX_WIDTH+1] = { "a", "b", "c" };
	int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED};

	window = initscr();
	cdkscreen = initCDKScreen(window);

	initCDKColor();

	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

	if (myMatrix == NULL) {
		printf("Error in creating matrix");
		_exit(1);
	}

	FILE *file;
	file = fopen("cs3377.bin", "rb");

//hile(1) {
	
	fread(&headers,sizeof(headers),1,file);

	fclose(file);


//if(feof(file) != 0)
//			break;
//		printf
//	}
//	fstream file;
//	file.open("cs337.bin", fstream::in | fstream::binary);
//	file.read((char*)&headers.magicNumber, sizeof(headers.magicNumber));
//	file.read((char*)&headers.versionNumber, sizeof(headers.versionNumber));
//	file.read((char*)&headers.numRecords, sizeof(headers.numRecords));
//	file.read(&headers, sizeof(headers));
//	file.close();

//	struct stat results;
//	cout << headers.magicNumber;
//cout << headers.versionNumber << "\n";
//cout << headers.numRecords;
//
//	if(stat("cs3377.bin", &results) == 0) {
//		cout << results.st_size;
//	}
//	else {
//		return 1;
//	}
	string versionNumber = "Version: " + to_string(headers.versionNumber);
	string numRecords = "NumRecords: " + to_string(headers.numRecords);
	drawCDKMatrix(myMatrix, true);
	setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());

	sleep(10);

	endCDK();

	return 0;
}
