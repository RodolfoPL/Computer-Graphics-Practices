void multiplyP(float proj[][4], float *p, float *pp);
float lower(float a, float b, float c);
float bigger(float a, float b, float c);


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

void multiplyP(float proj[][4], float *p, float *pp){
	int i, j;
	float sum=0;
	for(i=0; i<4; i++){		//rows of proj
		sum=0;
		for(j=0; j<4; j++){	//cols of point
			sum = sum + (proj[i][j]*p[j]);
		}
		pp[i] = sum;
	}
	for(i=0; i<4; i++){
		pp[i] = pp[i]/pp[3];
	}
}