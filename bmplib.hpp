#pragma once
#include <cstring>

class byteArray {
public:
	char* bytes;
	int size;
	inline byteArray()
	{
		size = 1;
		bytes = new char[1];
	}
	inline byteArray(int size, int num)
	{
		this->size = size;
		bytes = new char[this->size];
		int temp = num;
		for (int i = 0; i < size; i++) {
			bytes[i] = temp % 256;
			temp >>= 8;
		}
	}
	inline ~byteArray() {
		delete[] bytes;
		size = 0;
	}
	inline byteArray& operator+=(const byteArray& right)
	{
		int newSize = right.size + size;
		char* newBuf = new char[newSize];
		for (int i = 0; i < size; i++) {
			newBuf[i] = bytes[i];
		}
		for (int i = 0; i < right.size; i++) {
			newBuf[size + i] = right.bytes[i];
		}
		size = newSize;
		delete[] bytes;
		bytes = newBuf;
		return *this;
	}
	inline byteArray(byteArray&& r) noexcept {
		bytes = r.bytes;
		size = r.size;
		r.bytes = nullptr;
		r.size = 0;
	}
	inline byteArray(const byteArray& r) {
		size = r.size;
		bytes = new char[size];
		memcpy(bytes, r.bytes, size);
	}
	inline byteArray& operator=(byteArray&& r) noexcept {
		delete[] bytes;
		bytes = r.bytes;
		size = r.size;
		r.bytes = nullptr;
		r.size = 0;
		return *this;
	}
	inline byteArray& operator=(const byteArray& r) {
		size = r.size;
		delete[] bytes;
		bytes = new char[size];
		memcpy(bytes, r.bytes, size);
	}
};

struct Color {
	int red;
	int green;
	int blue;
	inline Color(int r = 0, int g = 0, int b = 0) {
		red = r;
		green = g;
		blue = b;
	}
};

class bitMapImage {
	//file header
	byteArray bfType;
	byteArray bfSize;
	byteArray bfReserved;
	byteArray bfOffBits;
	//image header(windows style)
	byteArray biSize;
	byteArray biWidth;
	byteArray biHeight;
	byteArray biPlanes;
	byteArray biBitCount;
	byteArray biCompression;
	byteArray biSizeImage;
	byteArray biXPelsPerMeter;
	byteArray biYPelsPerMeter;
	byteArray biClrUsed;
	byteArray biClrImportant;
	//color table
	byteArray colorTbl1;
	byteArray colorTbl2;
	byteArray colorTbl3;
	//Pixel data(each 4 bytes for 1 pixel)
	byteArray pixelBuf;
	int w;
	int h;
public:
	inline bitMapImage(int x, int y) {
		this->bfType.size = 2;
		w = x;
		h = y;
		delete[] this->bfType.bytes;
		this->bfType.bytes = new char[2];
		this->bfType.bytes[0] = 'B';
		this->bfType.bytes[1] = 'M';
		this->bfSize = byteArray(4, 66 + x * y * 4);
		this->bfReserved = byteArray(4, 0);
		this->bfOffBits = byteArray(4, 66);
		this->biSize = byteArray(4, 40);
		this->biWidth = byteArray(4, x);
		this->biHeight = byteArray(4, y);
		this->biPlanes = byteArray(2, 1);
		this->biBitCount = byteArray(2, 32);
		this->biCompression = byteArray(4, 0);
		this->biSizeImage = byteArray(4, 0);
		this->biXPelsPerMeter = byteArray(4, 0);
		this->biYPelsPerMeter = byteArray(4, 0);
		this->biClrUsed = byteArray(4, 0);
		this->biClrImportant = byteArray(4, 0);
		this->colorTbl1 = byteArray(4, 0x00000000);
		this->colorTbl2 = byteArray(4, 0x00000000);
		this->colorTbl3 = byteArray(4, 0x00000000);
		this->pixelBuf.size = x * y * 4;
		delete[] this->pixelBuf.bytes;
		this->pixelBuf.bytes = new char[this->pixelBuf.size];
	}
	inline byteArray* getBytes() {
		return &pixelBuf;
	}
	inline byteArray fullFile()
	{
		byteArray ans = bfType;
		ans += bfSize;
		ans += bfReserved;
		ans += bfOffBits;
		ans += biSize;
		ans += biWidth;
		ans += biHeight;
		ans += biPlanes;
		ans += biBitCount;
		ans += biCompression;
		ans += biSizeImage;
		ans += biXPelsPerMeter;
		ans += biYPelsPerMeter;
		ans += biClrUsed;
		ans += biClrImportant;
		ans += colorTbl1;
		ans += colorTbl2;
		ans += colorTbl3;
		ans += pixelBuf;
		return ans;
	}
	inline void setPixel(int x, int y, Color c) {
		pixelBuf.bytes[y * w * 4 + x + 2] = c.red;
		pixelBuf.bytes[y * w * 4 + x + 1] = c.green;
		pixelBuf.bytes[y * w * 4 + x] = c.blue;
		pixelBuf.bytes[y * w * 4 + x + 3] = 0;
	}
};