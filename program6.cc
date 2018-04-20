// Daniel Casper
// djc062000@utdallas.edu
// CS3377.002

#include "cdk.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <sstream>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"
#define maxRecordStringLength 25

using namespace std;

int main(int argc, char * argv[]) {
	// Create structs to populate with binary data
	struct BinaryFileHeader {
		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
	} headers;


	struct BinaryFileRecord { 
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
	};

	// Create file pointer
	FILE *file;
	
	// Create CDK window pointers
	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;
	
	// Label columns and rows; set width and length.
	const char *rowTitles[MATRIX_HEIGHT+1] = {"0", "a", "b", "c" };
	const char *columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c", "d", "e" };
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

	drawCDKMatrix(myMatrix, true);

	// Read contents of binary file for header
	file = fopen("cs3377.bin", "rb");
	fread(&headers,sizeof(headers),1,file);

	// Now that number of records known, use for loop to read data and place in CDK cells 
	for (uint32_t i = 0; i < headers.numRecords; i++) {
		BinaryFileRecord record;
		fread(&record, sizeof(record),1,file);
		string lenString = "strlen: " + to_string(record.strLength);
		setCDKMatrixCell(myMatrix, i + 2, 1, lenString.c_str());
		setCDKMatrixCell(myMatrix, i + 2, 2, record.stringBuffer);
	}
	
	// Close file when finished
	fclose(file);

	// Convert Magic Number back from base 10 into hex
	stringstream sstream;
	sstream << "0X" << uppercase << hex << headers.magicNumber;

	// Write headers to CDK Cells
	string magic = "Magic: " + sstream.str();
	string versionNumber = "Version: " + to_string(headers.versionNumber);
	string numRecords = "NumRecords: " + to_string(headers.numRecords);
	setCDKMatrixCell(myMatrix, 1, 1, magic.c_str());
	setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());

	drawCDKMatrix(myMatrix, true);

	sleep(10);

	endCDK();

	return 0;
}
