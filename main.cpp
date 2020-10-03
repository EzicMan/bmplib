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
		for (int j = 0; j < x; j++) {
			myImage.setPixel(j, i, Color(rand() % 256, rand() % 256, rand() % 256));
		}
	}
	myImage.saveToFile("test.bmp");
	return 0;
}