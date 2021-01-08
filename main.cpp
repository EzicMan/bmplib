#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <string>
#include "bmplib.hpp"
using namespace std;

int main()
{
	srand(time(NULL));
	int x, y;
	x = 315;
	y = 315;
	/*Color colors[16];
	for (int i = 0; i < 8; i++) {
		colors[0 + i] = Color(i & 1 ? 128 : 0, i & 2 ? 128 : 0, i & 4 ? 128 : 0);
		colors[8 + i] = Color(i & 1 ? 255 : 0, i & 2 ? 255 : 0, i & 4 ? 255 : 0);
	}*/
	bitMapImage<4294967295> myImage(x,y);
	/*srand(time(NULL));
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
	}*/
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			myImage.setPixel(j, i, rand()%16);
		}
	}
	myImage.saveToFile("test.bmp");
	return 0;
}