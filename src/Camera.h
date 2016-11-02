
#pragma once
#include "Header.h"
#include <math.h>
class Camera
{
public:
	Camera(): x(0), y(0), w(640), h(480) {}
	Camera(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}
	~Camera() {}

	SDL_Rect GetCameraRect() 
	{
		SDL_Rect rect;
		rect.x = round(x);
		rect.y = round(y);
		rect.w = round(w);
		rect.h = round(h);
		return rect;
	}

	float x, y;
	float w, h;


};