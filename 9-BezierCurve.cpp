#include<iostream>
#include<Windows.h>
#include<glut.h>
//#include<stdio.h>
#include<gl\GL.h>

using namespace std;

void reshape(GLint w, GLint h);
void myMenu(int op);
void display();
void bezier();
void bino(GLint n, GLint *C);
void computeBezPt(GLfloat u, GLfloat *bezCurvePt, GLint *C);

#define PI 3.1416

float ctrlPts[4][2];
float ctrlPtsmain[4][2] = {
	{ 20, 100 },{ 30, 110 },{ 50, 90 },{ 60, 100 } };

GLint nCtrlPts = 4, nBezCurvePts = 20;

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Bezier Curve");

	glutCreateMenu(myMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 130, 0, 130);
	glClear(GL_COLOR_BUFFER_BIT);
}

void myMenu(int op)
{
	if (op == 1)
		glColor3f(1.0, 0.0, 0.0);
	else if (op == 2)
		glColor3f(0.0, 1.0, 0.0);
	else if (op == 3)
		glColor3f(0.0, 0.0, 1.0);
	else if (op == 4)
		exit(0);
	glutPostRedisplay();
}

void display()
{
	static float theta = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			ctrlPts[i][j] = ctrlPtsmain[i][j];

	ctrlPts[1][0] += 10 * sin(theta * PI / 180.0);
	ctrlPts[1][1] += 5 * sin(theta * PI / 180.0);
	ctrlPts[2][0] -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[2][1] -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[3][0] -= 4 * sin((theta)* PI / 180.0);
	ctrlPts[3][1] += sin((theta - 30) * PI / 180.0);
	theta += 0.1;


	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glLineWidth(5);

	glPushMatrix();
	for (int i = 0; i<24; i++)
	{
		glTranslatef(0, -0.8, 0);
		bezier();
	}

	glPopMatrix();

	glLineWidth(5);

	glBegin(GL_LINES);
		glVertex2f(20, 100);
		glVertex2f(20, 40);
	glEnd();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void bezier()
{
	GLfloat u, *bezCurvePt;
	GLint *C, k;
	bezCurvePt = new GLfloat[2];
	C = new GLint[nCtrlPts];
	bino(nCtrlPts - 1, C);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k <= nBezCurvePts; k++)
	{
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u, bezCurvePt, C);
		glVertex2f(bezCurvePt[0], bezCurvePt[1]);
	}
	glEnd();
}

void bino(GLint n, GLint *C)
{
	GLint k, j;
	for (k = 0; k <= n; k++)
	{
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void computeBezPt(GLfloat u, GLfloat *bezCurvePt, GLint *C)
{
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;
	bezCurvePt[0] = bezCurvePt[1] = 0.0;
	for (k = 0; k< nCtrlPts; k++)
	{
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezCurvePt[0] += ctrlPts[k][0] * bezBlendFcn;
		bezCurvePt[1] += ctrlPts[k][1] * bezBlendFcn;
	}
}


