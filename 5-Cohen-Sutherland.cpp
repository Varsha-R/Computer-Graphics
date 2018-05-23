/*
Clip lines using Cohen-Sutherland algorithm.
*/
#include <Windows.h>
#include <glut.h> 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#include<iostream>

#define opcode int 

void myinit();
void display();
opcode compopcode(float x, float y);
void cohensutherland();

enum { top = 0x2, bottom = 0x1, left = 0x4, right = 0x8 };
float xmin, xmax, ymin, ymax, umin, umax, vmin, vmax;
float x1, y1, x2, y2;


void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CLIPPING ALGORITHM");
	myinit();

	printf("Enter the clipping window points xmin,xmax,ymin,ymax");
	scanf("%f%f%f%f", &xmin, &xmax, &ymin, &ymax);
	printf("Enter the display window points umin,umax,vmin,vmax");
	scanf("%f%f%f%f", &umin, &umax, &vmin, &vmax);
	printf("\nEnter the first point x1,y1\n");
	scanf("%f%f", &x1, &y1);
	printf("\nEnter the second point x2,y2\n");
	scanf("%f%f", &x2, &y2);

	glutDisplayFunc(display);
	glutMainLoop();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymax);
		glVertex2f(xmax, ymax);
		glVertex2f(xmax, ymin);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(umin, vmin);
		glVertex2f(umin, vmax);
		glVertex2f(umax, vmax);
		glVertex2f(umax, vmin);
	glEnd();
	cohensutherland();
	glFlush();
}

void cohensutherland()
{
	bool accept = false, done = false;
	int x = 0, y = 0;
	opcode p1, p2, p;
	p1 = compopcode(x1, y1);
	p2 = compopcode(x2, y2);
	float m = (y2 - y1) / (x2 - x1);
	do {
		if (!(p1 | p2))
		{
			accept = true;
			done = true;
		}
		else if (p1&p2)
			done = true;
		else
		{
			p = p1 ? p1 : p2;

			if (p&bottom)
			{
				y = ymin;
				x = x1 + (ymin - y1) / m;
			}
			if (p&top)
			{
				y = ymax;
				x = x1 + (ymax - y1) / m;
			}
			if (p&right)
			{
				x = xmax;
				y = y1 + (xmax - x1)*m;
			}
			if (p&left)
			{
				x = xmin;
				y = y1 + (xmin - x1)*m;
			}
			if (p == p2)
			{
				x2 = x;
				y2 = y;
				p2 = compopcode(x2, y2);
			}
			if (p == p1)
			{
				x1 = x;
				y1 = y;
				p1 = compopcode(x1, y1);
			}
		}
	} while (!done);
	if (accept)
	{
		float sx = (umax - umin) / (xmax - xmin);
		float sy = (vmax - vmin) / (ymax - ymin);
		x1 = sx * x1 + umin - sx * xmin;
		y1 = sy * y1 + vmin - sy * ymin;
		x2 = sx * x2 + umax - sx * xmax;
		y2 = sy * y2 + vmax - sy * ymax;
	}
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

opcode compopcode(float x, float y)
{
	int  p = 0;
	if (x<xmin)p = p | left;
	if (x>xmax)p = p | right;
	if (y<ymin)p = p | bottom;
	if (y>ymax)p = p | top;
	return p;
}






