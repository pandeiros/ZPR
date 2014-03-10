#include "PerlinNoise.h"
#include <cmath>
#include <ctime>

PerlinNoise::PerlinNoise() {
	srand((int)time(NULL));
	offsetX = rand() % 100000 / 100.0;
	offsetY = rand() % 100000 / 100.0;
}

PerlinNoise::~PerlinNoise() {
}

//Pseudorandom number generator, return number between -1 and 1
inline double PerlinNoise::CalculateNoise(double x, double y) {

	int n = (int)x + (offsetX + (int)y) * 57;
	n = (n << 13) ^ n;
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

inline double PerlinNoise::Interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft))* 0.5;
	return a*(1.0 - f) + b*f;
}

double PerlinNoise::Noise(double x, double y) {
	double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
	double floory = (double)((int)y);
	double s, t, u, v;//Integer declaration
	s = CalculateNoise(floorx, floory);
	t = CalculateNoise(floorx + 1, floory);
	u = CalculateNoise(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
	v = CalculateNoise(floorx + 1, floory + 1);
	double int1 = Interpolate(s, t, x - floorx);//Interpolate between the values.
	double int2 = Interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	return Interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
}

sf::Image PerlinNoise::RenderMap(int w, int h, double zoom, double p, int r, int g, int b) {//                                        use 75. P stands for persistence, this controls the roughness of the picture, i use 1/2
	int octaves = 5;
	sf::Image image;
	image.create(w, h, sf::Color::Black);//Create an empty image.


	for (int y = 0; y < h; y++)	{//Loops to loop trough all the pixels
		for (int x = 0; x < w; x++) {

			double distanceFromCenter = 1; // -2 * sqrt(pow((double)((double)h / 2 - y), 2) + pow((double)((double)w / 2 - x), 2)) / w;//255 - sqrt((pow((h / 2 - x) , 2) / pow(h/2, 2) + pow((w / 2 - y) / w, 2)) / pow(w/2, 2));
			
			if (x > 0.6*w) {
				distanceFromCenter -= (25.0 / 4.0) * pow((x - w*0.6),2) / pow(w,2);
			}
			if (y > 0.6*h) {
				distanceFromCenter -= (25.0 / 4.0) * pow((y - h*0.6), 2) / pow(h, 2);
			}
			if (x < 0.4*w) {
				distanceFromCenter -= (25.0 / 4.0) * pow((w*0.4 - x), 2) / pow(w, 2);
			}
			if (y < 0.4*h) {
				distanceFromCenter -= (25.0 / 4.0) * pow((h*0.4 - y), 2) / pow(h, 2);
			}

			if (distanceFromCenter < 0) {
				distanceFromCenter = 0;
			}

			double getnoise = 0;

			for (int a = 0; a < octaves - 1; a++) {
				double frequency = pow(2, a);//This increases the frequency with every loop of the octave.
				double amplitude = pow(p, a);//This decreases the amplitude with every loop of the octave.
				getnoise += Noise(((double)x)*frequency / zoom, ((double)y) / zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
			}//                                         It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

			int color = (int)((getnoise*128.0) + 128.0);//Convert to 0-256 values.
			color = (int)(color * distanceFromCenter);
			if (color > 255){
				color = 255;
			}

			if (color < 0) {
				color = 0;
			}
			if (color <= 10) {
				image.setPixel(x, y, sf::Color(0,0,50)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (color <= 40) {
				image.setPixel(x, y, sf::Color(0, 30, 90)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (color <= 60) {
				image.setPixel(x, y, sf::Color(250, 250, 20)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (color <= 180) {
				image.setPixel(x, y, sf::Color(20, 130, 20)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (color <= 255) {
				image.setPixel(x, y, sf::Color(0, 30, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
		}//                                                          given at the beginning in the function.

	}
	return image;
}