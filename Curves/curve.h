
typedef struct curve{
	float q[3];
}Curve;

void m1(int M[][4], float G[][3], float R[][3]);
void calculeCurve(float t, float R[][3], Curve *c);

void m1(int M[][4], float G[][3], float R[][3]){
	int i, j, k;
	float sum;
	for(i = 0; i<4; i++){
		for(j=0; j<3; j++){
			sum = 0;
			for(k=0; k<4; k++){
				sum += M[i][k] * G[k][j]; 
			}
			R[i][j] = sum;
		}
	}
}

void calculeCurve(float t, float R[][3], Curve *c){
	float T[4] = {(t*t*t), (t*t), t, 1};
	int i, j;
	float sum;
	for(i=0; i<3; i++){
		sum = 0;
		for(j=0; j<4; j++){
			sum += T[j] * R[j][i];
		}
		c->q[i] = sum;
	}
}