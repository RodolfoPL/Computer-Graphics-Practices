#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bresenham.h"

#define N 968
#define PI 3.14159265

void matrixMultiplication2(float m1[4][4], float m2[4][1], float res[4][1]);
float lower(float a, float b, float c);
float bigger(float a, float b, float c);
void clean();
void drawI(char *name);

struct triangulo
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
};

void main(int argc, char *argv[]){
	struct triangulo t[N];
	int i = 0;
	float z, ofsetx = 0, ofsety = 0, sx = 0, sy = 0, aux, maxx=0, maxy=0;
	int r = 255, g = 255, b = 255;
	int x1, y1, x2, y2, x3, y3, rx1, rx2, rx3, ry1, ry2, ry3;
	int angle;//= atof(argv[1]);
	int midx = (width)/2;
	int midy = (height)/2;
	int minx, miny;
	int cx, cy;
	int sumx = 0, sumy = 0;

	FILE *raw;
	raw = fopen("monkey.raw", "r");

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

		sumx = sumx + t[i].x1 + t[i].x2 + t[i].x3;
		sumx = sumy + t[i].y1 + t[i].y2 + t[i].y3;

		i++;
	}

	//mass center
	sumx = sumx/(N*3);
	sumy = sumy/(N*3);

	sumx = (sumx+ofsetx)*sx;
	sumy = (sumy+ofsety)*sy;

	fclose(raw);
//	printf("%f\n", ofsetx);

	minx = ofsetx;
	miny = ofsety;
	//Made positive the ofset
	ofsetx *= -1;
	ofsety *= -1;

	maxx = sx;
	maxy = sy;
	//calculate the scale
	sx = (width/2)/(sx+ofsetx);
	sy = (height/2)/(sy+ofsety);


	//Center of the image
	cx = ((int)((maxx+ofsetx)*sx)-((int)(minx+ofsetx)*sx))/2;
	cy = ((int)((maxy+ofsety)*sy)-((int)(miny+ofsety)*sy))/2;


	//diferent images
	for(angle = 0; angle<360; angle++){
		//clean raster
		clean();

		//draw all lines
		for(i=0; i<N; i++){
			//scale and translate point
			x1 = (t[i].x1 + ofsetx)*sx;
			x2 = (t[i].x2 + ofsetx)*sx;
			x3 = (t[i].x3 + ofsetx)*sx;

			y1 = (t[i].y1 + ofsety)*sy;
			y2 = (t[i].y2 + ofsety)*sy;
			y3 = (t[i].y3 + ofsety)*sy;


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

			//Rotation

			//Translate to center of rotation (center screen)
			float T_[4][4] = {
							{1, 0, 0, -midx},
							{0, 1, 0, -midy},
							{0, 0, 1, 0},
							{0, 0, 0, 1}
					 	   };

			float T[4][4] = {
							{1, 0, 0, midx},
							{0, 1, 0, midy},
							{0, 0, 1, 0},
							{0, 0, 0, 1}
		 	   			  };

		 	float R[4][4] = {
		 					{cos((float)angle*PI/180), sin((float)angle*PI/180), 0, 0},
		 					{(-1)*sin((float)angle*PI/180), cos((float)angle*PI/180), 0, 0},
		 					{0, 0, 1, 0},
							{0, 0, 0, 1}
		 				  };

		 	float r1[4][1];
		 	float r2[4][1];

			float final1[4][1];
		 	float final2[4][1];
		 	float final3[4][1];


		 	float p1[4][1] = {
		 						{x1}, {y1}, {0}, {1}
		 				   };

			float p2[4][1] = {
		 						{x2}, {y2}, {0}, {1}
		 				   };

		 	float p3[4][1] = {
		 						{x3}, {y3}, {0}, {1}
		 				   };


			matrixMultiplication2(T_, p1, r1);
			matrixMultiplication2(R, r1, r2);
			matrixMultiplication2(T, r2, final1);

			matrixMultiplication2(T_, p2, r1);
			matrixMultiplication2(R, r1, r2);
			matrixMultiplication2(T, r2, final2);

			matrixMultiplication2(T_, p3, r1);
			matrixMultiplication2(R, r1, r2);
			matrixMultiplication2(T, r2, final3);

			defineLine(final1[0][0], final1[0][1], final2[0][0], final2[0][1]);
			defineLine(final2[0][0], final2[0][1], final3[0][0], final3[0][1]);
			defineLine(final1[0][0], final1[0][1], final3[0][0], final3[0][1]);
		}
		char name[8] = "";
		char number[5] = "";
		//memset(name, '\0', sizeof(name));
		sprintf(number, "%d", angle);
		char ext[5];
		strcpy(ext, ".ppm");
		strcpy(name, number);
		strcat(name, ext);
		int len = strlen(name);
		name[len+1] = '\0';
		drawI(name);
	}
	return;
}


//Verify the type of line that needs to be draw

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

void drawI(char *name){
	int x, y;
	FILE *ppm;
	
	ppm = fopen(name, "w");
	fprintf(ppm, "P3\n %d %d\n 255\n", width, height);

	for(y=height-1; y>=0; y--){
		for(x=0; x<width; x++){
			fprintf(ppm, "%d  %d  %d ", raster[x][y][0], raster[x][y][1], raster[x][y][2]);
		}
		fprintf(ppm, "\n");
	}
	fclose(ppm);
	return;
}

void clean(){
	int x, y;
	for (x = 0; x < width; x++){
		for(y = 0; y < height; y++){
			raster[x][y][0] = 0;
			raster[x][y][1] = 0;
			raster[x][y][2] = 0;
		}
	}
}

void matrixMultiplication2(float m1[4][4], float m2[4][1], float res[4][1]){
	int i,j,k;
	float sum = 0;
	for(i=0; i<4; i++){
		for(j=0; j<1; j++){
			sum = 0;
			for(k=0; k<4; k++){
				sum += m1[i][k] * m2[k][j];
			}
			res[i][j] = sum;
		}
	}
}