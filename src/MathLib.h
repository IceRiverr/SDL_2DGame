
#include <math.h>

//double round(double x)
//{
//	return x > 0 ? floor(x + 0.5) : ceil(x - 0.5);
//}

struct Vector2
{
	float x;
	float y;
	Vector2(float _x, float _y) :x(_x), y(_y) {}
	Vector2 operator / (const float& value)
	{
		return Vector2(x / value, y / value);
	}

	Vector2 operator * (const float& value)
	{
		return Vector2(x * value, y * value);
	}

	Vector2 operator- (const Vector2& value)
	{
		return Vector2(x - value.x, y - value.y);
	}

	Vector2 operator+ (const Vector2& value)
	{
		return Vector2(x + value.x, y + value.y);
	}
};
