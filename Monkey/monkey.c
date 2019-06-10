
#include <stdio.h>
#include <stdlib.h>
#include "bresenham.h"

#define N 1152

float lower(float a, float b, float c);
float bigger(float a, float b, float c);

struct triangulo{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
};

void main(){
	struct triangulo t[N];
	int i = 0;
	float z, ofsetx = 0, ofsety = 0, sx = 0, sy = 0, aux;
	int r = 255, g = 255, b = 255;
	int x1, y1, x2, y2, x3, y3;
	int noLines = 0;

	FILE *raw;
	raw = fopen("dona.raw", "r");

	//READ FILE
	while(!feof(raw) && i<N){
		fscanf(raw,"%f %f %f %f %f %f %f %f %f", &t[i].x1, &z, &t[i].y1, &t[i].x2, &z, &t[i].y2, &t[i].x3, &z, &t[i].y3);
		//find lower x
		aux = lower(t[i].x1, t[i].x2, t[i].x3);
		if(aux < ofsetx)
			ofsetx = aux;
		//find bigger x
		aux = bigger(t[i].x1, t[i].x2, t[i].x3);
		if(aux > sx)
			sx = aux;
		//find lower y
		aux = lower(t[i].y1, t[i].y2, t[i].y3);
		if(aux < ofsety)
			ofsety = aux;
		//find bigger y
		aux = bigger(t[i].y1, t[i].y2, t[i].y3);
		if(aux > sy)
			sy = aux;
		//printf("%f %f %f : %f\n", t[i].x1, t[i].x2, t[i].x3, aux);
		i++;
	}

	//Made positive the ofset
	ofsetx *= -1;
	ofsety *= -1;
	//calculate the sxcale
	sx = (width-1)/(sx+ofsetx);
	sy = (height-1)/(sy+ofsety);
	//sx = sy;

//	int midx = (sx-ofsetx)/2;

	//draw all lines
	for(i=0; i<N; i++){
		x1 = (t[i].x1 + ofsetx)*sx;
		x2 = (t[i].x2 + ofsetx)*sx;
		x3 = (t[i].x3 + ofsetx)*sx;

		y1 = (t[i].y1 + ofsety)*sy;
		y2 = (t[i].y2 + ofsety)*sy;
		y3 = (t[i].y3 + ofsety)*sy;

		defineLine(x2, y2, x1, y1);
		defineLine(x2, y2, x3, y3);
		defineLine(x1, y1, x3, y3);
	}

	draw();
	return;
}

float lower(float a, float b, float c){
	if(a < b && a < c)
		return a;
	
	else if(b < a && b < c)
		return b;

	else
		return c;
}

float bigger(float a, float b, float c){
	if(a > b && a > c)
		return a;
	
	else if(b > a && b > c)
		return b;

	else
		return c;
}