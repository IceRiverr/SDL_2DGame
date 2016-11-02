
#pragma once
#include "Header.h"
#include <math.h>
class Camera
{
public:
	Camera(): x(0), y(0), w(640), h(480) {}
	Camera(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}
	~Camera() {}

	SDL_Rect GetCameraRect() 
	{
		SDL_Rect rect;
		rect.x = static_cast<int>(round(x));
		rect.y = static_cast<int>(round(y));
		rect.w = static_cast<int>(round(w));
		rect.h = static_cast<int>(round(h));
		return rect;
	}

	float x, y;
	float w, h;


};