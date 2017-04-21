// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <GL/glut.h>

#define CELLS_NO 51 //セルの全体数
#define CELL_NEIGHBOR_NO 1 //セルの近傍数
#define RULE_NO 90 //規則
#define TIME_LIM 50 //時間
#define STATE_NO 2 //状態数
#define VIEW_SIZE 2.0 //画面の幅

void drawSquare(double x, double y, double width, double height) //render square
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + width, y);
	glVertex2d(x + width, y + height);
	glVertex2d(x, y + height);
	glEnd();
}

void drawCell(double x, double y, int state) //render single cell
{
	double width = VIEW_SIZE / CELLS_NO;
	switch (state) {
	case 1:
		glColor3d(1.0, 0.0, 0.0);
		break;
	default:
		glColor3d(0.0, 0.0, 1.0);
		break;
	}
	drawSquare(x, y, width, width);
}

void drawCellsRow(int cells[CELLS_NO], int time) //render cells row
{
	int i;
	double width = VIEW_SIZE / CELLS_NO;
	double x = -VIEW_SIZE / 2.0;
	double y = (time - TIME_LIM / 2.0) * width;
	for (i = 0; i < CELLS_NO; i++) {
		drawCell(x, y, cells[i]);
		x += width;
	}
}
//TODO
//cell update by rule
int updateCell(int neighborCells[CELL_NEIGHBOR_NO * 2 + 1])
{
	return neighborCells[1];
	/*
	int nextCell=0;
	for (int i = 0; i < CELL_NEIGHBOR_NO * 2 + 1; i++)
	{
		nextCell += neighborCells[i];
	}
	return nextCell% STATE_NO;*/
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
				neighborCells[l] = cells[(j + l - CELL_NEIGHBOR_NO) % CELLS_NO];
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

