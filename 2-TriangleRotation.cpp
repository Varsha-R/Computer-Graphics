#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

float p[9][2]={{20,20},{40,40},{60,20}};
float xp,yp,theta,rtheta;

void main()
{
		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
		glutInitWindowPosition(100,100);
		glutInitWindowSize(500,500);
		glutCreateWindow("Traingle rotation");
		myinit();
		printf("Enter the point of rotation\n");
		scanf("%f%f",&xp,&yp);
		printf("Enter the angle of rotation\n");
		scanf("%f",&theta);
		glutDisplayFunc(display);
		glutMainLoop();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	float x,y;
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawtraiangle();
	rtheta=(theta*3.142)/180;
	for(int i=0;i<3;i++)
	{
		x=p[i][0];
		y=p[i][1];
		p[i][0]=x*cos(rtheta)-y*sin(rtheta)+xp*(1-cos(rtheta))+yp*sin(rtheta);
		p[i][1]=x*sin(rtheta)+y*cos(rtheta)+yp*(1-cos(rtheta))-xp*sin(rtheta);

	}
	glColor3f(0,1,0);
	drawtraiangle();
	glFlush();
}


void drawtraiangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2fv(p[0]);
		glVertex2fv(p[1]);
		glVertex2fv(p[2]);		
	glEnd();
}

