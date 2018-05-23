/*
Draw a color cube and allow the user to move the camera suitably to experiment with perspective viewing.
*/
#include <Windows.h>
#include <glut.h> 
using namespace std;
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void myinit();
void display();
void mousefunc(int button, int status, int x, int y);
void mykey(unsigned char key, int x, int y);
void reshape(int w, int h);
void colorcube();
void drawpoly(int a, int b, int c1, int d);

float v[8][3] = { { -1,-1,1 },{ -1,1,1 },{ 1,1,1 },{ 1,-1,1 },
{ -1,-1,-1 },{ -1,1,-1 },{ 1,1,-1 },{ 1,-1,-1 } };
float c[8][3] = { { 0,0,1 },{ 0,1,1 },{ 1,1,1 },{ 1,0,1 },
{ 0,0,0 },{ 0,1,0 },{ 1,1,0 },{ 1,0,0 } };
float theta[3] = { 0,0,0 };
int viewer[3] = { 0,0,2 };
int flag = 2;

void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube Rotation");
	myinit();

	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);
	glutKeyboardFunc(mykey);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, 2, 20);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
	glRotatef(theta[0], 1, 0, 0);//x
	glRotatef(theta[1], 0, 1, 0);//y
	glRotatef(theta[2], 0, 0, 1);//z
	colorcube();
	glFlush();
	glutSwapBuffers();
}

void mousefunc(int button, int status, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
		flag = 2;
	if (button == GLUT_MIDDLE_BUTTON && status == GLUT_DOWN)
		flag = 1;
	if (button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
		flag = 0;

	theta[flag]++;
	if (theta[flag]>360)theta[flag] = 0;
	glutPostRedisplay();

}

void mykey(unsigned char key, int x, int y)
{
	if (key == 'x')viewer[0]--;
	if (key == 'X')viewer[0]++;
	if (key == 'y')viewer[1]--;
	if (key == 'Y')viewer[1]++;
	if (key == 'z')viewer[2]--;
	if (key == 'Z')viewer[2]++;
	glutPostRedisplay();

}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, 2, 20);

	else
		glFrustum(-2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2, 2, 20);

	glMatrixMode(GL_MODELVIEW);
}

void colorcube()
{
	drawpoly(0, 1, 2, 3);
	drawpoly(0, 1, 5, 4);
	drawpoly(1, 5, 6, 2);
	drawpoly(4, 5, 6, 7);
	drawpoly(3, 2, 6, 7);
	drawpoly(0, 4, 7, 3);
}

void drawpoly(int a, int b, int c1, int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(c[a]);
		glVertex3fv(v[a]);

		glColor3fv(c[b]);
		glVertex3fv(v[b]);

		glColor3fv(c[c1]);
		glVertex3fv(v[c1]);

		glColor3fv(c[d]);
		glVertex3fv(v[d]);
	glEnd();
}



