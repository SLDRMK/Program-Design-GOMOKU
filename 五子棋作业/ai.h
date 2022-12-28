/* Computer putting chess functions. */
#ifndef AI_H_
#define AI_H_

#define MIN 5
#define MAX 20
#define SIZE 25
long double A;
long double B;

void initialize(struct point p[SIZE][SIZE], int color);
void aiPutB();	// AI Put Black Chess
void aiPutW();	// AI Put White Chess
void test();
void assess_easy(struct point p[SIZE][SIZE]);
void swap(int* a, int* b);
int partsort(struct point p[SIZE][SIZE], int* a, int left, int right);
void fastsort(struct point p[SIZE][SIZE], int* a, int begin, int end);
int end(struct point p[SIZE][SIZE]);
void p_assess(struct point p[SIZE][SIZE]);     //某点价值分评定
double assess(struct point p[SIZE][SIZE]);     //局面优势评估
double deduction(struct point p[SIZE][SIZE], int sex, int depth, long double a, long double b);//递归推演 

#endif 