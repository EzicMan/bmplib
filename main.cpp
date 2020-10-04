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
	x = 1600;
	y = 1600;
	bitMapImage myImage(x,y);
	srand(time(NULL));
	int t = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int x = 0; x < 100; x++) {
				for (int y = 0; y < 100; y++) {
					myImage.setPixel(100 * j + x, 100 * i + y, Color(t, 0, 0));
				}
			}
			t++;
		}
	}
	myImage.saveToFile("test.bmp");
	return 0;
}