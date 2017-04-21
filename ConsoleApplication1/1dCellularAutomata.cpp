// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>

#define CELLS_NO 51 //セルの全体数
#define CELL_NEIGHBOR_NO 1 //セルの近傍数
#define RULE_NO 25 //規則
#define TIME_LIM 50 //時間
#define STATE_NO 2 //状態数
#define VIEW_SIZE 2.0 //画面の幅

class Rule {
public:
	int ruleNo;
	int rulePatterns;
	Rule(int _ruleNo, int stateNo, int neighborNo) {
		ruleNo = _ruleNo;
		rulePatterns = (int)pow((double)STATE_NO, (double)2 * CELL_NEIGHBOR_NO + 1);
	}
	int getNextState(int decimalState) {
		int nextState = 0;
		int leftDecimal = ruleNo;
		for (int i = 0; i <= decimalState; i++)
		{
			nextState = leftDecimal % STATE_NO;
			leftDecimal /= STATE_NO;
		}
		return nextState;
	}
};

Rule thisRule = Rule(RULE_NO, STATE_NO, CELL_NEIGHBOR_NO);

//render square
void drawSquare(double x, double y, double width, double height)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + width, y);
	glVertex2d(x + width, y + height);
	glVertex2d(x, y + height);
	glEnd();
}
//render single cell
void drawCell(double x, double y, int state)
{
	double width = VIEW_SIZE / CELLS_NO;
	glColor3d((STATE_NO - 1 - state) / (double)(STATE_NO - 1), (STATE_NO - 1 - state) / (double)(STATE_NO - 1), (STATE_NO - 1 - state) / (double)(STATE_NO - 1));
	drawSquare(x, y, width, width);
}
//render cells row
void drawCellsRow(int cells[CELLS_NO], int time)
{
	int i;
	double width = VIEW_SIZE / CELLS_NO;
	double x = -VIEW_SIZE / 2.0;
	double y = (TIME_LIM / 2.0 - time) * width;
	for (i = 0; i < CELLS_NO; i++) {
		drawCell(x, y, cells[i]);
		x += width;
	}
}
//cell update by Rule
int updateCell(int neighborCells[CELL_NEIGHBOR_NO * 2 + 1])
{
	int decimalState = 0;
	int cellMaxNo = CELL_NEIGHBOR_NO * 2 + 1;
	for (int i = 0; i < cellMaxNo; i++)
	{
		decimalState += (int)pow((double)STATE_NO, (double)(i)) * neighborCells[cellMaxNo - i - 1];
	}
	int n = thisRule.getNextState(decimalState);
	return n;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int cells[CELLS_NO] = { 0 }; //current cells state
	int tmpCells[CELLS_NO] = { 0 }; //temporary cells array
	cells[(int)(CELLS_NO / 2.0)] = 1;
	for (int i = 0; i < TIME_LIM; i++) {
		drawCellsRow(cells, i);
		for (int j = 0; j < CELLS_NO; j++)
		{
			int neighborCells[CELL_NEIGHBOR_NO * 2 + 1] = { 0 };
			for (int l = 0; l < CELL_NEIGHBOR_NO * 2 + 1; l++)
			{
				int n = (j + l - CELL_NEIGHBOR_NO) % CELLS_NO;
				if (n < 0)
				{
					n += CELLS_NO;
				}
				neighborCells[l] = cells[n];
			}
			tmpCells[j] = updateCell(neighborCells);
		}
		for (int k = 0; k < CELLS_NO; k++)
		{
			cells[k] = tmpCells[k];
		}
	}
	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}