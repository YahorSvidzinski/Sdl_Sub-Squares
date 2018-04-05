#include "draw.h"
#include "stdafx.h"
#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)

void putpixel(SDL_Surface *surface, int x,int y, Uint32 pixel)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[(y * surface->w) + x] = pixel;
}
void line(SDL_Surface *surface,int x1, int y1, int x2, int y2,Uint32 color) {

	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	putpixel(surface,x2, y2,color);
	while (x1 != x2 || y1 != y2){
		putpixel(surface,x1, y1,color);
		const int error2 = error * 2;
		//
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
		
	}
}
void os(SDL_Surface *s)
{
	float xA, yA, xB, yB, xC, yC, xD, yD,
		xxA, yyA, xxB, yyB, xxC, yyC, xxD, yyD, p = 0.8, q;
	int i;
   
	q = 1.0 - p;
	xA = 10.0; xB = 470.0; xC = 470.0; xD = 10.0;
	yA = 10.0; yB = 10.0; yC = 470.0; yD = 470.0;
	for (i = 0; i < 10; i++)
	{


		line(s, xA, yA, xB, yB, 0xFFFFFFFF);
		line(s, xB, yB, xC, yC, 0xFFFFFFFF);
		line(s, xC, yC, xD, yD, 0xFFFFFFFF);
		line(s, xD, yD, xA, yA, 0xFFFFFFFF);
		xxA = p*xA + q*xB; yyA = p*yA + q*yB; xxB = p*xB + q*xC;
		yyB = p*yB + q*yC; xxC = p*xC + q*xD; yyC = p*yC + q*yD; xxD = p*xD + q*xA;
		yyD = p*yD + q*yA;


		xA = round(xxA); xB = round(xxB); xC = round(xxC); xD = round(xxD);
		yA = round(yyA); yB = round(yyB); yC = round(yyC); yD = round(yyD);

	}
	}
float sw = 0;
void draw(SDL_Surface *s, double a) {
	
	sw += a;
	float xA, yA, xB, yB, xC, yC, xD, yD,
		xxA, yyA, xxB, yyB, xxC, yyC, xxD, yyD, p = 0.8 + sw, q;
	int i;

	q = 1.0 - p;
	xA = 10.0; xB = 470.0; xC = 470.0; xD = 10.0;
	yA = 10.0; yB = 10.0; yC = 470.0; yD = 470.0;
	for (i = 0; i < 10; i++)
	{


		line(s, xA, yA, xB, yB, 0xFFFFFFFF);
		line(s, xB, yB, xC, yC, 0xFFFFFFFF);
		line(s, xC, yC, xD, yD, 0xFFFFFFFF);
		line(s, xD, yD, xA, yA, 0xFFFFFFFF);
		xxA = p*xA + q*xB; yyA = p*yA + q*yB; xxB = p*xB + q*xC;
		yyB = p*yB + q*yC; xxC = p*xC + q*xD; yyC = p*yC + q*yD; xxD = p*xD + q*xA;
		yyD = p*yD + q*yA;


		xA = round(xxA); xB = round(xxB); xC = round(xxC); xD = round(xxD);
		yA = round(yyA); yB = round(yyB); yC = round(yyC); yD = round(yyD);

	}
}
