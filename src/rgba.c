#include "maze.h"

ColorRGBA::ColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	}
ColorRGBA::ColorRGBA()
	{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

	//Add two colors
ColorRGBA operator+(const ColorRGBA& color, const ColorRGBA& color2)
{
	ColorRGBA c;
	c.r = color.r + color2.r;
	c.g = color.g + color2.g;
	c.b = color.b + color2.b;
	c.a = color.a + color2.a;
	return c;
}

//Subtract two colors
ColorRGBA operator-(const ColorRGBA& color, const ColorRGBA& color2)
{
	ColorRGBA c;
	c.r = color.r - color2.r;
	c.g = color.g - color2.g;
	c.b = color.b - color2.b;
	c.a = color.a - color2.a;
	return c;
}

//Multiplies a color with an integer
ColorRGBA operator*(const ColorRGBA& color, int a)
{
	ColorRGBA c;
	c.r = color.r * a;
	c.g = color.g * a;
	c.b = color.b * a;
	c.a = color.a * a;
	return c;
}

//Multiplies a color with an integer
ColorRGBA operator*(int a, const ColorRGBA& color)
{
	ColorRGBA c;
	c.r = color.r * a;
	c.g = color.g * a;
	c.b = color.b * a;
	c.a = color.a * a;
	return c;
}

//Divides a color through an integer
ColorRGBA operator/(const ColorRGBA& color, int a)
{
	if (a == 0) return color;
	ColorRGBA c;
	c.r = color.r / a;
	c.g = color.g / a;
	c.b = color.b / a;
	c.a = color.a / a;
	return c;
}

ColorRGBA overlay(const ColorRGBA& color, const ColorRGBA& color2)
{
	ColorRGBA c;
	c.r = (color.r * color.a / 255) + (color2.r * color2.a * (255 - color.a) / (255 * 255));
	c.g = (color.g * color.a / 255) + (color2.g * color2.a * (255 - color.a) / (255 * 255));
	c.b = (color.b * color.a / 255) + (color2.b * color2.a * (255 - color.a) / (255 * 255));
	c.a = color.a + (color2.a * (255 - color.a) / 255);
	return c;
}