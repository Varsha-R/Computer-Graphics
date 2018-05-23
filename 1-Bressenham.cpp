Implement Bresenham’s line drawing algorithm for all types of slope.
#include<gl/glut.h>
#include<stdio.h>
#include<math.h>

void main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Line using Bresenham algorithm");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
}	

void resize(int w, int h)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,w,0.0,h);
	glViewport(0,0,w,h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLint x0,y0,xe,ye;
	GLfloat m;
	printf("Enter the starting point\n");
	scanf("%d%d",&x0,&y0);
	printf("Enter the end point\n");
	scanf("%d%d",&xe,&ye);
	m=(float)(ye-y0)/(xe-x0);
	if(fabs(m)<1)
		lineBres_lt1(x0,y0,xe,ye,m);
	else
		lineBres_ge1(x0,y0,xe,ye,m);
}

void lineBres_lt1(GLint x1,GLint y1, GLint x2, GLint y2,GLfloat m)
{
	GLint x,y,xend,p,dy,dx,tdy,tdx;
	dy=abs(y2-y1);
	dx=abs(x2-x1);

	if(x1>x2)
	{
		x=x2;
		y=y2;
		xend=x1;
	}
	else
	{
		x=x1;
		y=y1;
		xend=x2;
	}
	p = 2*dy-dx;
	setPixel(x,y);
	while(x<xend)
	{
		x++;
		if(p<0)
			p+=2*dy;
		else
		{
			if(m<0)
				y--;
			else
				y++;
			p+=2*dy-2*dx;
		}
		setPixel(x,y);
	}
}

void lineBres_ge1(GLint x1,GLint y1, GLint x2, GLint y2,GLfloat m)
{
	GLint x,y,yend,p,dy,dx,tdy,tdx;
	dy=abs(y2-y1);
	dx=abs(x2-x1);
	
	if(y1>y2)
	{
		x=x2;
		y=y2;
		yend=y1;
	}
	else
	{
		x=x1;
		y=y1;
		yend=y2;
	}
	p=2*dx-dy;
	setPixel(x,y);
	while(y<yend)
	{
		y++;
		if(p<0)
			p+=2*dx;
		else
		{
			if(m<0)
				x--;
			else
				x++;
			p+=2*dx-2*dy;
		}
		setPixel(x,y);
	}
}


void setPixel(GLint x,GLint y)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}



