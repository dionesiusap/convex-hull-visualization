#include <GL/glut.h>

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	// gluOrtho2D (-100.0, 100.0, -75.0, 75.0);
	gluOrtho2D (-25.0, 25.0, -25.0, 25.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//draw two points
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for(int i = 0; i < 10; i++)
	{
		glVertex2i(-10+5*i,10);
	}
	glEnd();

	//draw a line
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(0,0);
		glVertex2i(50,50);
	glEnd();

	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("points and lines");
	init2D(255.,255.0,255.0);
	glutDisplayFunc(display);
	glutMainLoop();

    return 0;
}