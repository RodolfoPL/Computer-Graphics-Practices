//(x1, y1, z1) (x2, y2, z2) (x3, y3, z3)
//x y ofset
//x y scale

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bresenham.h"
#include "perspective.h"

#define N 1152	//monkey

int raster[width][height][3];


struct triangulo
{
	float x1;
	float y1;
	float z1;
	float x2;
	float y2;
	float z2;
	float x3;
	float y3;
	float z3;
};

void main(int argc, char *argv[]){
	struct triangulo t[N];
	struct triangulo td[N];
	struct triangulo ti[N];
	float d=0.5;
	int i = 0;
	float z, ofsetx = 0, ofsety = 0, ofsetz = 0, sx = 0, sy = 0, sz = 0, aux, maxx=0, maxy=0, maxz = 0;
	int r, g, b;
	int x1, y1, x2, y2, x3, y3;
	int midx = (width-1)/2;
	int midy = (height-1)/2;
	int midz = (width-1)/2;
	int minx, miny, minz;
	int cx, cy, cz;
	//float f = 30; //=> monkey1
	//float f = 60;// => monkey2
	//float f = 150; //=> monkey
	//float f = 300; //=> monkey3
	float f = 30;

	float w = 1/f;
	float projd[4][4] = {{1,0,0,d},		//0
						{0,1,0,0},		//1
						{0,0,1,0},		//2
						{0,0,w,0}};		//3

	float proji[4][4] = {{1,0,0,-d},	//0
						{0,1,0,0},		//1
						{0,0,1,0},		//2
						{0,0,w,0}};		//3

	FILE *raw;
	raw = fopen("dona.raw", "r");

	//READ FILE
	while(!feof(raw) && i<N){
		fscanf(raw,"%f %f %f %f %f %f %f %f %f", &t[i].x1, &t[i].z1, &t[i].y1, &t[i].x2, &t[i].z2, &t[i].y2, &t[i].x3, &t[i].z3, &t[i].y3);
		i++;
	}
	fclose(raw);


	for(i=0; i<N; i++){
		//make the points vectors
		float p1[4] = {t[i].x1, t[i].y1, t[i].z1, 1};
		float pp1[4];

		float p2[4] = {t[i].x2, t[i].y2, t[i].z2, 1};
		float pp2[4];

		float p3[4] = {t[i].x3, t[i].y3, t[i].z3, 1};
		float pp3[4];
		//multiply matrix
		multiply(projd, p1, pp1);
		multiply(projd, p2, pp2);
		multiply(projd, p3, pp3);

		td[i].x1 = pp1[0];
		td[i].y1 = pp1[1];

		td[i].x2 = pp2[0];
		td[i].y2 = pp2[1];

		td[i].x3 = pp3[0];
		td[i].y3 = pp3[1];


		multiply(proji, p1, pp1);
		multiply(proji, p2, pp2);
		multiply(proji, p3, pp3);

		ti[i].x1 = pp1[0];
		ti[i].y1 = pp1[1];

		ti[i].x2 = pp2[0];
		ti[i].y2 = pp2[1];

		ti[i].x3 = pp3[0];
		ti[i].y3 = pp3[1];


		//find lower x
		aux = lower(td[i].x1, td[i].x2, td[i].x3);
		if(aux < ofsetx)
			ofsetx = aux;
		//find bigger x
		aux = bigger(td[i].x1, td[i].x2, td[i].x3);
		if(aux > sx)
			sx = aux;
		//find lower y
		aux = lower(td[i].y1, td[i].y2, td[i].y3);
		if(aux < ofsety)
			ofsety = aux;
		//find bigger y
		aux = bigger(td[i].y1, td[i].y2, td[i].y3);
		if(aux > sy)
			sy = aux;	

		aux = lower(ti[i].x1, td[i].x2, td[i].x3);
		if(aux < ofsetx)
			ofsetx = aux;
		aux = lower(ti[i].x1, td[i].x2, td[i].x3);
		if(aux < ofsetx)
			ofsetx = aux;
	}


//	printf("%f\n", ofsetx);

	minx = ofsetx;
	miny = ofsety;
	minz = ofsetz;
	//Made positive the ofset
	ofsetx *= -1;
	ofsety *= -1;
	ofsetz *= -1;

	maxx = sx;
	maxy = sy;
	maxz = sz;
	//calculate the scale is disable to see the f parameter
	//sx = .5*(width-1)/(sx+ofsetx);
	//sy = .5*(height-1)/(sy+ofsety);

	sy = 10;
	sx = sy;

	//Center of the image
	cx = ((int)((maxx+ofsetx)*sx)-((int)(minx+ofsetx)*sx))/2;
	cy = ((int)((maxy+ofsety)*sy)-((int)(miny+ofsety)*sy))/2;

		//draw all lines
		for(i=0; i<N; i++){

			//right

			//scale and translate point
			x1 = round((td[i].x1 + ofsetx)*sx);
			x2 = round((td[i].x2 + ofsetx)*sx);
			x3 = round((td[i].x3 + ofsetx)*sx);

			y1 = round((td[i].y1 + ofsety)*sy);
			y2 = round((td[i].y2 + ofsety)*sy);
			y3 = round((td[i].y3 + ofsety)*sy);


			//center image

			x1 += midx;
			x2 += midx;
			x3 += midx;

			y1 += midy;
			y2 += midy;
			y3 += midy;

			x1 -= cx;
			x2 -= cx;
			x3 -= cx;

			y1 -= cy;
			y2 -= cy;
			y3 -= cy;


			r = 255, g = 0, b = 0;
			defineLine(x2, y2, x1, y1, r, g, b);
			defineLine(x2, y2, x3, y3, r, g, b);
			defineLine(x1, y1, x3, y3, r, g, b);
		

			//left
			
			//scale and translate point
			x1 = round((ti[i].x1 + ofsetx)*sx);
			x2 = round((ti[i].x2 + ofsetx)*sx);
			x3 = round((ti[i].x3 + ofsetx)*sx);

			y1 = round((ti[i].y1 + ofsety)*sy);
			y2 = round((ti[i].y2 + ofsety)*sy);
			y3 = round((ti[i].y3 + ofsety)*sy);


			//center image

			x1 += midx;
			x2 += midx;
			x3 += midx;

			y1 += midy;
			y2 += midy;
			y3 += midy;

			x1 -= cx;
			x2 -= cx;
			x3 -= cx;

			y1 -= cy;
			y2 -= cy;
			y3 -= cy;


			r = 0, g = 0, b = 255;
			defineLine(x2, y2, x1, y1, r, g, b);
			defineLine(x2, y2, x3, y3, r, g, b);
			defineLine(x1, y1, x3, y3, r, g, b);	
		}
		
	draw();
	
	return;
}
