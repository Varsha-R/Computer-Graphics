/*
Design, develop and implement recursively subdivide a tetrahedron to form 3D
sierpinski gasket. The number of recursive steps is to be specified by the user.
*/

#include<stdio.h>
#include<gl/glut.h>

int c;
float v[4][3] = {{0,0,1},{-1,-0.5,0},{0,1,0},{1,-0.5,0}};

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600); 
	glutInitWindowPosition(300,150);
	printf("Enter the number of subdivisions:\n");
	scanf("%d",&c); 
	glutCreateWindow("3D Recursive Sierpinski Gasket");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}

void myinit()	
{
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity(); 
	glOrtho(-2,2,-2,2,-2,2); 
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,1);
	div_tri(v[1],v[2],v[3],c);

	glColor3f(1,0,0);
	div_tri(v[0],v[1],v[2],c);

	glColor3f(0,1,0);
	div_tri(v[0],v[2],v[3],c);

	glColor3f(0,0,1);
	div_tri(v[0],v[1],v[3],c);

	glFlush();
}

void div_tri(float *a,float *b,float *c,int n)
{ 
	float v1[3],v2[3],v3[3];
	int i;
	 
	if(n>0)
	{
		for(i=0;i<3;i++)
		{ 
			v1[i] = (a[i] + b[i])/2; 
			v2[i] = (a[i] + c[i])/2;
			v3[i] = (b[i] + c[i])/2;
		} 
		div_tri(a,v1,v2,n-1); 
		div_tri(v1,b,v3,n-1);
		div_tri(v2,v3,c,n-1);

	}
	else
		disp_tri(a,b,c); 
}

void disp_tri(float a[3],float b[3],float c[3])
{
	glBegin(GL_POLYGON); 
		glVertex3fv(a);
		glVertex3fv(b); 
		glVertex3fv(c);
	glEnd();
}




