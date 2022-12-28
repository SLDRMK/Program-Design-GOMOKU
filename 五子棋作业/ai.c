/* Computer putting chess functions. */
#include "ai.h"
#include "board.h"
#include "endGame.h"
#include "meta.h"
#include <stdio.h>

void aiPutB() 
{
	if (board[8][8] == 0)
		board[8][8] = 3;
	else
	{
		struct point p[SIZE][SIZE];
		initialize(p, 1);
		int i, j, x = 12, y = 12, m, n, t = 0;
		long double v = -999999999999999999;    //10^18
		for (i = MIN; i < MAX; i++)        //寻找最佳落子点
		{
			for (j = MIN; j < MAX; j++)
			{
				calProcess = (i - MIN) * BOARDSIZE + j - MIN + 1;
				drawBoard(1);
				if (p[i][j].state == 0)      //为空
				{
					t = 0;
					for (m = -1; m < 2; m++) {
						for (n = -1; n < 2; n++) {
							if (p[i + m][j + n].state != 0) {
								t++;
							}
						}
					}
					if (t != 0)
					{
						p[i][j].state = 1;
						if (end(p) == 2)
						{
							board[i][j] = 4;
							return;
						}
						p[i][j].n_value = deduction(p, 1, SCORELAYERS, A, B);
						p[i][j].state = 0;
						if (p[i][j].n_value > v && p[i][j].state == 0)
						{
							v = p[i][j].n_value;
							x = i;
							y = j;
						}
					}
				}
			}
		}
		board[x - MIN + 1][y - MIN + 1] = 3;
		lastPos[0] = x - MIN + 'A';
		lastPos[1] = BOARDSIZE - (y - MIN);
		return;
	}
}/*
{
	if (board[8][8] == 0)
	{
		board[8][8] = 3;
		lastPos[0] = lastPos[1] = 8;
		return;
	}
	int i, j, x = 8, y = 8, r, l, t = 0;
	long double v = MAXSCORE0;
	copyBoard();
	for (r = 1; r < BOARDSIZE; r++)
	{
		for (l = 1; l < BOARDSIZE; l++)
			if (board[r][l] == 0)
			{
				t = 0;
				for (i = -1; i < 2; i++)
					for (j = -1; j < 2; j++)
						if (board[r + i][l + j] != 0)
							t++;
				if (t != 0)
				{
					boardForCalculating[r][l] = 1;
					if (allScore(1) >= 500000)
					{
						board[r][l] = 3;
						return 0;
					}
					allScores[r][l] = calculateScore(1, 1, SCORELAYERS, MAXSCORE0, MINSCORE0);
					boardForCalculating[r][l] = 0;
					if (allScores[r][l] > v)
					{
						v = allScores[r][l];
						maxPos[0] = r;
						maxPos[1] = l;
					}
				}
			}
	}
	board[maxPos[0]][maxPos[1]] = 3;
	lastPos[0] = maxPos[0] + 'A' - 1;
	lastPos[1] = BOARDSIZE - maxPos[1] + 1;
}*/

void aiPutW()
{
	if (board[7][9] == 0)
		board[7][9] = 4;
	else
	{
		struct point p[SIZE][SIZE];
		initialize(p, 2);
		int i, j, x = 12, y = 12, m, n, t = 0;
		long double v = -999999999999999999;    //10^18
		for (i = MIN; i < MAX; i++)        //寻找最佳落子点
		{
			for (j = MIN; j < MAX; j++)
			{
				calProcess = (i - MIN) * BOARDSIZE + j - MIN + 1;
				drawBoard(1);
				if (p[i][j].state == 0)      //为空
				{
					t = 0;
					for (m = -1; m < 2; m++) {
						for (n = -1; n < 2; n++) {
							if (p[i + m][j + n].state != 0) {
								t++;
							}
						}
					}
					if (t != 0)
					{
						p[i][j].state = 1;
						if (end(p) == 2)
						{
							board[i][j] = 4;
							return;
						}
						p[i][j].n_value = deduction(p, 1, SCORELAYERS, A, B);
						p[i][j].state = 0;
						if (p[i][j].n_value > v && p[i][j].state == 0)
						{
							v = p[i][j].n_value;
							x = i;
							y = j;
						}
					}
				}
			}
		}
		board[x - MIN + 1][y - MIN + 1] = 4;
		lastPos[0] = x - MIN + 'A';
		lastPos[1] = BOARDSIZE - (y - MIN);
		return;
	}
}

void initialize(struct point p[SIZE][SIZE], int color)
{
	A = -999999999999999999;
	B = 999999999999999999;
	trim = 0;
	int i, j;
	num = 0;
	int color1 = 1 + !(color - 1);
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j <= MAX; j++)
		{
			if (board[i - MIN + 1][j - MIN + 1] == color || board[i - MIN + 1][j - MIN + 1] == color + 2)
				p[i][j].state = 1;
			else if (board[i - MIN + 1][j - MIN + 1] == color1 || board[i - MIN + 1][j - MIN + 1] == color1 + 2)
				p[i][j].state = -1;
			else
				p[i][j].state = 0;
			p[i][j].value = 0;
			p[i][j].n_value = 0;
			p[i][j].p_value = 0;
			p[i][j].x = i;
			p[i][j].y = j;
		}
	}
}

int end(struct point p[SIZE][SIZE])
{
	int i, j, k = 0, x = 0, y = 0, b = 0, q = 0, e = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				k++;
				if (k == 0)
				{
					e = 1;
				}
			}
			if (p[i][j].state)
			{
				for (x = -2; p[i][j].state == p[i][j + x].state && x < 4; x++)     //横
				{
				}
				for (y = -2; p[i][j].state == p[i + y][j].state && y < 4; y++)      //纵
				{
				}
				for (b = -2; p[i][j].state == p[i + b][j + b].state && b < 4; b++)    //斜下
				{
				}
				for (q = -2; p[i][j].state == p[i - q][j + q].state && q < 4; q++)    //斜上
				{
				}
				if (x == 3 || y == 3 || b == 3 || q == 3)
				{
					if (p[i][j].state == 1)
					{
						e = 2;
					}
					if (p[i][j].state == -1)
					{
						e = 3;
					}
				}
			}
		}
	}
	return e;
}

double assess(struct point p[SIZE][SIZE])
{
	int i, j;
	p_assess(p);     //某点价值评定
	long double s_value = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			s_value += p[i][j].value;//棋盘总优势分为所有点分数的和
		}
	}
	return s_value;
}

void p_assess(struct point p[SIZE][SIZE])
{
	int i, j, k, m, n, x, y;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				p[i][j].value = 0;
			}
			else
			{
				long double v1 = V, v2 = V, v3 = V, v4 = V, v5 = V, v6 = V, v7 = V, v8 = V;
				for (x = 0, n = j; p[i][j].state != -p[i][n + 1].state && n + 1 < 20 && x < 4; x++, n++)       //右
				{
				}
				if (x < 4)
				{
					v1 = 0;
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n + 1].state && k < 5; k++, n++)       //右
					{
						v1 *= V;
					}
				}
				for (y = 0, n = j; p[i][j].state != -p[i][n - 1].state && n - 1 > 4 && y < 4; y++, n--)      //左
				{
				}
				if (y < 4)
				{
					v2 = 0;
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n - 1].state && k < 5; k++, n--)      //左
					{
						v2 *= V;
					}
				}
				for (x = 0, n = i; p[i][j].state != -p[n + 1][j].state && n + 1 < 20 && x < 5; x++, n++)       //上
				{
				}
				if (x < 4)
				{
					v3 = 0;
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n + 1][j].state && k < 5; k++, n++)       //上
					{
						v3 *= V;
					}
				}
				for (y = 0, n = i; p[i][j].state != -p[n - 1][j].state && n - 1 > 4 && y < 5; y++, n--)       //下
				{
				}
				if (y < 4)
				{
					v4 = 0;
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n - 1][j].state && k < 5; k++, n--)       //下
					{
						v4 *= V;
					}
				}
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n + 1].state && n + 1 < 20 && m - 1 > 4 && x < 5; x++, m--, n++) //右上
				{
				}
				if (x < 4)
				{
					v5 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n + 1].state && k < 5; k++, m--, n++)       //右上
					{
						v5 *= V;
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n - 1].state && m + 1 < 20 && n - 1 > 4 && y < 5; y++, m++, n--) //左下
				{
				}
				if (y < 4)
				{
					v6 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n - 1].state && k < 5; k++, m++, n--)       //左下
					{
						v6 *= V;
					}
				}
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n - 1].state && n - 1 > 4 && m - 1 > 4 && x < 5; x++, m--, n--)  //左上
				{
				}
				if (x < 4)
				{
					v7 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n - 1].state && k < 5; k++, m--, n--)       //左上
					{
						v7 *= V;
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n + 1].state && n + 1 < 20 && m + 1 < 20 && y < 5; y++, m++, n++) //右下
				{
				}
				if (y < 4)
				{
					v8 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n + 1].state && k < 5; k++, m++, n++)       //右下
					{
						v8 *= V;
					}
				}
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //加上距离中心优势分
				if (p[i][j].state == -1)
				{
					p[i][j].value = -p[i][j].value * E;
				}
			}
		}
	}
}

void assess_easy(struct point p[SIZE][SIZE])
{
	int i, j, k, m, n, x, y;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].state == 0)
			{
				p[i][j].state = 1;
				long double v1 = V, v2 = V, v3 = V, v4 = V, v5 = V, v6 = V, v7 = V, v8 = V;
				for (x = 0, n = j; p[i][j].state != -p[i][n + 1].state && n + 1 < 20 && x < 4; x++, n++)       //右
				{
				}
				if (x < 4)
				{
					v1 = 0;
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n + 1].state && k < 5; k++, n++)       //右
					{
						v1 *= V;
					}
				}
				for (y = 0, n = j; p[i][j].state != -p[i][n - 1].state && n - 1 > 4 && y < 4; y++, n--)      //左
				{
				}
				if (y < 4)
				{
					v2 = 0;
				}
				else {
					for (k = 0, n = j; p[i][j].state == p[i][n - 1].state && k < 5; k++, n--)      //左
					{
						v2 *= V;
					}
				}
				for (x = 0, n = i; p[i][j].state != -p[n + 1][j].state && n + 1 < 20 && x < 5; x++, n++)       //上
				{
				}
				if (x < 4)
				{
					v3 = 0;
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n + 1][j].state && k < 5; k++, n++)       //上
					{
						v3 *= V;
					}
				}
				for (y = 0, n = i; p[i][j].state != -p[n - 1][j].state && n - 1 > 4 && y < 5; y++, n--)       //下
				{
				}
				if (y < 4)
				{
					v4 = 0;
				}
				else {
					for (k = 0, n = i; p[i][j].state == p[n - 1][j].state && k < 5; k++, n--)       //下
					{
						v4 *= V;
					}
				}
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n + 1].state && n + 1 < 20 && m - 1 > 4 && x < 5; x++, m--, n++) //右上
				{
				}
				if (x < 4)
				{
					v5 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n + 1].state && k < 5; k++, m--, n++)       //右上
					{
						v5 *= V;
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n - 1].state && m + 1 < 20 && n - 1 > 4 && y < 5; y++, m++, n--) //左下
				{
				}
				if (y < 4)
				{
					v6 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n - 1].state && k < 5; k++, m++, n--)       //左下
					{
						v6 *= V;
					}
				}
				for (x = 0, m = i, n = j; p[i][j].state != -p[m - 1][n - 1].state && n - 1 > 4 && m - 1 > 4 && x < 5; x++, m--, n--)  //左上
				{
				}
				if (x < 4)
				{
					v7 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m - 1][n - 1].state && k < 5; k++, m--, n--)       //左上
					{
						v7 *= V;
					}
				}
				for (y = 0, m = i, n = j; p[i][j].state != -p[m + 1][n + 1].state && n + 1 < 20 && m + 1 < 20 && y < 5; y++, m++, n++) //右下
				{
				}
				if (y < 4)
				{
					v8 = 0;
				}
				else {
					for (k = 0, m = i, n = j; p[i][j].state == p[m + 1][n + 1].state && k < 5; k++, m++, n++)       //右下
					{
						v8 *= V;
					}
				}
				p[i][j].p_value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));    //加上距离中心优势分
				p[i][j].state = 0;
			}
		}
	}
	for (i = 0; i < BOARDSIZE * BOARDSIZE; i++)
		sort[i] = i;
	fastsort(p, sort, 0, BOARDSIZE * BOARDSIZE - 1);
}

void swap(int* a, int* b)
{
	long double temp = *a;
	*a = *b;
	*b = temp;
}

int partsort(struct point p[SIZE][SIZE], int* a, int left, int right)
{
	int key = left;
	while (left < right)
	{
		while (left < right &&
			p[a[right] / BOARDSIZE + MIN][a[right] % BOARDSIZE + MIN].p_value
		>= p[a[key] / BOARDSIZE + MIN][a[key] % BOARDSIZE + MIN].p_value)
			--right;
		while (left < right &&
			p[a[left] / BOARDSIZE + MIN][a[left] % BOARDSIZE + MIN].p_value
		<= p[a[key] / BOARDSIZE + MIN][a[key] % BOARDSIZE + MIN].p_value)
			++left;
		swap(&a[left], &a[right]);
	}
	swap(&a[key], &a[left]);
	return left;
}

void fastsort(struct point p[SIZE][SIZE], int* a, int begin, int end)
{
	if (begin > end)
		return;

	int key = partsort(p, a, begin, end);
	fastsort(p, a, begin, key - 1);
	fastsort(p, a, key + 1, end);
}

double deduction(struct point p[SIZE][SIZE], int sex, int depth, long double a, long double b)
{
	int x, y, m, n, i, j, t, k = 0, br = 0;
	long double va = 0;
	if (depth == 0 || end(p) != 0)
	{
		return assess(p);
	}
	else if (sex % 2 == 1)
	{
		assess_easy(p);
		for (x = MIN; x < MAX; x++)
		{
			if (br == 1) {
				break;
			}
			for (y = MIN; y < MAX; y++)
			{
				k = BOARDSIZE * BOARDSIZE - ((x - MIN) * BOARDSIZE + y - MIN) - 1;
				m = sort[k] / BOARDSIZE + MIN;
				n = sort[k] % BOARDSIZE + MIN;
				if (p[m][n].state == 0)
				{
					if (num < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (p[i + m][j + n].state != 0) {
									t++;
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)
					{
						va = B;
					}
					else {
						p[m][n].state = -1;
						va = deduction(p, sex + 1, depth - 1, a, b);
						p[m][n].state = 0;
					}
					if (va < b)
					{
						b = va;
					}
					if (b < a)
					{
						br = 1;
						trim++;
						break;
					}
				}
			}
		}
		return b;
	}
	else if (sex % 2 == 0)
	{
		for (x = MIN; x < MAX; x++)
		{
			if (br == 1) {
				break;
			}
			for (y = MIN; y < MAX; y++)
			{
				k = BOARDSIZE * BOARDSIZE - ((x - MIN) * BOARDSIZE + y - MIN) - 1;
				m = sort[k] / BOARDSIZE + MIN;
				n = sort[k] % BOARDSIZE + MIN;
				if (p[m][n].state == 0)
				{
					if (num < 80) {
						t = 0;
						for (i = -1; i < 2; i++) {
							for (j = -1; j < 2; j++) {
								if (p[i + m][j + n].state != 0) {
									t++;
								}
							}
						}
					}
					else {
						t = 1;
					}
					if (t == 0)
					{
						va = A;
					}
					else {
						p[m][n].state = 1;
						va = deduction(p, sex + 1, depth - 1, a, b);
						p[m][n].state = 0;
					}
					if (va > a)
					{
						a = va;
					}
					if (b < a)
					{
						br = 1;
						trim++;
						break;
					}
				}
			}
		}
		return a;
	}
	return 0;
}

void test()
{
	struct point p[SIZE][SIZE];
	initialize(p, 2);
	p[12][12].state = 1;
	assess_easy(p);
	int k = BOARDSIZE * BOARDSIZE - 1;
	int m = sort[k] / BOARDSIZE + MIN;
	int n = sort[k] % BOARDSIZE + MIN;
	for (int i = MIN; i < MAX; i++)
	{
		for (int j = MIN; j < MAX; j++)
			printf("%.1f ", p[i][j].p_value);
		printf("\n");
	}
	printf("%.1f\n", p[m][n].p_value);
}