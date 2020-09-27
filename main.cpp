#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <string>
#include "bmplib.hpp"
using namespace std;

int main()
{
	int x, y;
	x = 1024;
	y = 768;
	bitMapImage myImage(x,y);
	srand(time(NULL));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x * 4; j+=4) {
			myImage.setPixel(j, i, Color(rand() % 256, rand() % 256, rand() % 256));
		}
	}
	ofstream out("test.bmp");
	byteArray sourceFile = myImage.fullFile();
	for (int i = 0; i < sourceFile.size; i++) {
		out << sourceFile.bytes[i];
	}
	out.close();
	return 0;
}