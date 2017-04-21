// ConsoleApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <GL/glut.h>

void drawSquare(double x, double y, double width, double height)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x+width, y);
	glVertex2d(x+width, y+height);
	glVertex2d(x, y+height);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	drawSquare(-1.0, -1.0, 1.0, 1.0);
	glColor3d(0.0, 1.0, 0.0);
	drawSquare(0.0, -1.0, 1.0, 1.0);
	glColor3d(0.0, 0.0, 1.0);
	drawSquare(-1.0, 0.0, 1.0, 1.0);
	glColor3d(1.0, 1.0, 0.0);
	drawSquare(0.0, 0.0, 1.0, 1.0);
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

