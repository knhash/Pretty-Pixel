#include <iostream>
#include <GL/glut.h>


using namespace std;

//Global defaults
int screenWidth = 500;
int screenHeight = 500;


void DrawChar(const char *text, int x, int y,int sparkle)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	//glColor3f(0.3, 1.0, 0.0);
	for (int i = 0; text[i] != '\0'; i++)
	{	
		glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
		if(sparkle)
		{
			glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
			glBegin(GL_LINE_LOOP);
			glVertex2f(25, 25);
			glVertex2f(775, 25);
			glVertex2f(775, 575);
			glVertex2f(25, 575);
			glEnd();
			glLineWidth(5.0);

		}
		if(sparkle)
		glutPostRedisplay();
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glutWireTeapot(200);
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0,0,-10,0,0,3,0,10,0);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
	//glBegin(GL_LINES);
	//glVertex2i(50, 50);
	//glVertex2i(300, 300);
	//glEnd();
	//glLineWidth(1.0f);
	DrawChar("Pretty Pixel", 320,350,1);
	DrawChar("Computer Graphics Project", 175, 530, 0);
	DrawChar("Shreyas N", 50, 100,0);
	DrawChar("1MV14CS130", 50, 50, 0);
	DrawChar("Shashank S", 545, 100,0);
	DrawChar("1MV14CS131", 545, 50, 0);
	glFlush();
}

void Reshape(int w, int h) {
	GLfloat hbyw = (GLfloat)h / (GLfloat)w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, hbyw, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv) {
	cout << "Hello World! \n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pretty Pixel");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}