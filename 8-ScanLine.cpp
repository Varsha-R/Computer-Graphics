//Develop a menu driven program to fill the polygon using scan line algorithm

#include <Windows.h>
#include <glut.h> 
using namespace std;
#include<stdio.h>
#include<stdlib.h>

float x1, x2, x3, x4, y1, y2, y3, y4;
void myinit();
void display();
void myMenu(int id);
void disp(float r, float g, float b);
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b);
void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re);
void draw_pixel(int x, int y, float r, float g, float b);

void main() 
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Scan-Line Filling Algorithm");
	glutDisplayFunc(display);
	myinit();

	glutCreateMenu(myMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutMainLoop();
}

void myinit() 
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glFlush();
}

void myMenu(int id)
{
	switch (id)
	{
	case 1: disp(1.0, 0.0, 0.0);
		break;
	case 2: disp(0.0, 1.0, 0.0);
		break;
	case 3: disp(0.0, 0.0, 1.0);
		break;
	case 4: exit(0);
	}
}

void disp(float r, float g, float b) 
{
	x1 = 200.0; y1 = 200.0; x2 = 100.0; y2 = 300.0;
	x3 = 200.0; y3 = 400.0; x4 = 300.0; y4 = 300.0;
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	scanfill(x1, y1, x2, y2, x3, y3, x4, y4, r, g, b);
	glFlush();
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b) 
{
	int le[500], re[500];
	int i, y;
	for (i = 0; i < 500; i++) {
		le[i] = 500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);
	for (y = 0; y < 500; y++) {
		if (le[y] <= re[y])
			for (i = (int)le[y]; i < (int)re[y]; i++)
				draw_pixel(i, y, r, g, b);
	}
}

void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re) 
{
	float mx, x, temp;
	int i;
	if (y2 - y1 < 0) {
		temp = y1;
		y1 = y2;
		y2 = temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y2 - y1 != 0)
		mx = (x2 - x1) / (y2 - y1);
	else
		mx = x2 - x1;
	x = x1;
	for (i = y1; i <= y2; i++) {
		if (x < (float)le[i])
			le[i] = (int)x;
		if (x >(float) re[i])
			re[i] = (int)x;
		x += mx;
	}
}


void draw_pixel(int x, int y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}











