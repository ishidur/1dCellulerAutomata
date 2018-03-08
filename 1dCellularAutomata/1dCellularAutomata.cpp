// 1dCellularAutomata.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define CELLS_NO 51 //セルの全体数
#define CELL_NEIGHBOR_NO 1 //セルの近傍数
#define RULE_NO 90 //規則
#define TIME_LIM 51 //時間
#define STATE_NO 2 //状態数
#define VIEW_SIZE 2.0 //画面の幅

class Rule
{
public:
	int rule_no;
	int rule_patterns;

	Rule(int _ruleNo = 0, int stateNo = 2, int neighborNo = 1)
	{
		rule_no = _ruleNo;
		rule_patterns = int(pow(double(STATE_NO), double(2) * CELL_NEIGHBOR_NO + 1));
	}

	int get_next_state(int decimalState)
	{
		int next_state = 0;
		int left_decimal = rule_no;
		for (int i = 0; i <= decimalState; i++)
		{
			next_state = left_decimal % STATE_NO;
			left_decimal /= STATE_NO;
		}
		return next_state;
	}
};

Rule this_rule = Rule();

//render square
void draw_square(double x, double y, double width, double height)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + width, y);
	glVertex2d(x + width, y + height);
	glVertex2d(x, y + height);
	glEnd();
}

//render single cell
void draw_cell(double x, double y, int state)
{
	double width = VIEW_SIZE / CELLS_NO;
	glColor3d((STATE_NO - 1 - state) / double(STATE_NO - 1), (STATE_NO - 1 - state) / double(STATE_NO - 1),
	          (STATE_NO - 1 - state) / double(STATE_NO - 1));
	draw_square(x, y, width, width);
}

//render cells row
void draw_cells_row(int cells[CELLS_NO], int time)
{
	double width = VIEW_SIZE / CELLS_NO;
	double x = -VIEW_SIZE / 2.0;
	double y = (TIME_LIM / 2.0 - double(time) - 1.0) * width;
	for (int i = 0; i < CELLS_NO; i++)
	{
		draw_cell(x, y, cells[i]);
		x += width;
	}
}

//cell update by Rule
int update_cell(int neighbor_cells[CELL_NEIGHBOR_NO * 2 + 1])
{
	int decimal_state = 0;
	int cell_max_no = CELL_NEIGHBOR_NO * 2 + 1;
	for (int i = 0; i < cell_max_no; i++)
	{
		decimal_state += int(pow(double(STATE_NO), double(i))) * neighbor_cells[cell_max_no - i - 1];
	}
	int n = this_rule.get_next_state(decimal_state);
	return n;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int cells[CELLS_NO] = {0}; //current cells state
	int tmp_cells[CELLS_NO] = {0}; //temporary cells array
	cells[int(CELLS_NO / 2.0)] = 1;
	for (int i = 0; i < TIME_LIM; i++)
	{
		draw_cells_row(cells, i);
		for (int j = 0; j < CELLS_NO; j++)
		{
			int neighbor_cells[CELL_NEIGHBOR_NO * 2 + 1] = {0};
			for (int l = 0; l < CELL_NEIGHBOR_NO * 2 + 1; l++)
			{
				int n = (j + l - CELL_NEIGHBOR_NO) % CELLS_NO;
				if (n < 0) { n += CELLS_NO; }
				neighbor_cells[l] = cells[n];
			}
			tmp_cells[j] = update_cell(neighbor_cells);
		}
		for (int k = 0; k < CELLS_NO; k++)
		{
			cells[k] = tmp_cells[k];
		}
	}
	glFlush();
}

void init(void) { glClearColor(0.0, 0.0, 1.0, 1.0); }

int main(int argc, char* argv[])
{
	int rule_no = RULE_NO;
	std::cout << "rule no." << rule_no << std::endl;
	//	std::cout << "rule no. up to " << pow(STATE_NO, pow(STATE_NO, CELL_NEIGHBOR_NO * 2 + 1)) << std::endl;
	//	std::cin >> ruleNo;
	//	while (ruleNo >= pow(STATE_NO, pow(STATE_NO, CELL_NEIGHBOR_NO * 2 + 1)) || ruleNo < 0)
	//	{
	//		std::cout << "out of possible rule No " << pow(STATE_NO, pow(STATE_NO, CELL_NEIGHBOR_NO * 2 + 1)) << ". type again... " << std::endl;
	//		std::cin >> ruleNo;
	//	}
	this_rule = Rule(rule_no, STATE_NO, CELL_NEIGHBOR_NO);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
