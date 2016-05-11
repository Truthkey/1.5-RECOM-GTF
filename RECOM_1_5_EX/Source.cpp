#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "rb");

	unsigned int checker = 0;
	char filename[20];
	char filepath[128];
	unsigned int pos = 0;
	unsigned int size = 0;
	int counter = 0;
	char* DATABUFFER;
	unsigned char vars[8];

	while (true)
	{
		fseek(file, 0x20 * counter, SEEK_SET);
		fread(&checker, 4, 1, file);

		if (checker == 0)
			break;

		fseek(file, 0x20 * counter, SEEK_SET);
		//for (int i = 0; i < 4; i++)
		//	fread(&vars[i], 1, 1, file);

		//pos = vars[3] * 0x1000000 + vars[2] * 0x10000 + vars[1] * 0x100 + vars[0];

		//cout << vars[3] * 0x1000000 + vars[2] * 0x10000 + vars[1] * 0x100 + vars[0] << endl;

		fread(&pos, 4, 1, file);
		pos = _byteswap_ulong(pos);
		
		fread(&filename, 20, 1, file);

		fseek(file, (0x20 * counter) + 0x1C, SEEK_SET);

		//fread(&size, 4, 1, file);
		//size = _byteswap_ulong(size);

		for (int i = 0; i < 4; i++)
			fread(&vars[i+4], 1, 1, file);
		
		size = vars[7] * 0x1000000 + vars[6] * 0x10000 + vars[5] * 0x100 + vars[4];

		system("mkdir @GTF");
		sprintf(filepath, "@GTF/%s", filename);

		cout << "Filename: " << filepath << endl
			<< "Position: " << hex << pos << endl
			<< "Size:     " << hex << size << endl;

		FILE* o = fopen(filepath, "wb");

		fseek(file, pos, SEEK_SET);
		DATABUFFER = (char*)malloc(size);
		fread(DATABUFFER, size, 1, file);
		fwrite(DATABUFFER, size, 1, o);

		fclose(o);

		counter++;
	}

	fclose(file);
	system("pause");
}