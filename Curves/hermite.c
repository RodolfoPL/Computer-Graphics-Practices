#include <stdio.h>
#include <stdlib.h>

#include "bresenham.h"
#include "perspective.h"
#include "curve.h"

void main(){
	int H[4][4] = {
			{2,-2,1,1},
			{-3,3,-2,-1},
			{0,0,1,0},
			{1,0,0,0}
		};
	//start / end points
	float x0, y0, z0;
	float x1, y1, z1;
	//tangents
	float x_0, y_0, z_0;
	float x_1, y_1, z_1;
	float t;


	int n;

	float steep;


	scanf("%f %f %f", &x0, &y0, &z0);
	scanf("%f %f %f", &x1, &y1, &z1);
	scanf("%f %f %f", &x_0, &y_0, &z_0);
	scanf("%f %f %f", &x_1, &y_1, &z_1);
	scanf("%d", &n);

	steep = 1.0/(n-1);

	float G[4][3] = {
				{x0, y0, z0},
				{x1, y1, z1},
				{x_0, y_0, z_0},
				{x_1, y_1, z_1}
			};	

	float R[4][3];

	//calculate the M*G multiplication
	m1(H, G, R);

	Curve c[n]; 
	Curve c2[n];

	int i=0;
	for(t=0; t <= 1; t+=steep){
		calculeCurve(t, R, &c[i]);
		i++;
	}

	float f = 30;

	float w = 1/f;
	float proj[4][4] = {{1,0,0,0},		//0
						{0,1,0,0},		//1
						{0,0,1,0},		//2
						{0,0,w,0}};		//3
	
	

	//project 
	float xmin=width, xmax=0, ymin=height, ymax=0;
	for(i = 0; i<n; i++){
		float cp[4];
		float p1[4] = {c[i].q[0], c[i].q[1], c[i].q[2], 1};

		//printf("%f %f %f\n", c[i].q[0], c[i].q[1], c[i].q[2]);
		if(p1[2] == 0){		
			cp[0] = p1[0];
			cp[1] = p1[1];
		}
		else{
			multiplyP(proj, p1, cp);
		}
		
		//printf("%f %f %f %f\n", cp[0], cp[1], cp[2], cp[3]);

		if(cp[0] < xmin){
			xmin = cp[0];
		}
		if(cp[0] > xmax){
			xmax = cp[0];
		}

		if(cp[1] < ymin){
			ymin = cp[1];
		}
		if(cp[1] > ymax){
			ymax = cp[1];
		}

		c2[i].q[0] = cp[0];
		c2[i].q[1] = cp[1];
		
	}

	float sx=10, sy=10, tx=0, ty=0;

	if(xmin < 0)
		tx = (-1)*xmin;

	if(ymin < 0)
		ty = (-1)*ymin;

	sx = (width/2)/xmax;
	sy = (width/2)/ymax;


	//int project the curve
	for(i=0; i<n-1; i++){
		int x1 = (c2[i].q[0]+tx)*sx;
		int y1 = (c2[i].q[1]+ty)*sy;

		int x2 = (c2[i+1].q[0]+tx)*sx;
		int y2 = (c2[i+1].q[1]+ty)*sy;

	
		defineLine(x1, y1, x2, y2, 150, 20, 19);
	}	

	draw();

}
