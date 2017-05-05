#include <iostream>
#include <GL/glut.h>

//Global defaults
int screenWidth = 661;
int screenHeight = 661;

using namespace std;

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//Select clear color as black

	//Initialize viewing aspects
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT);		//Clear all pixels

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);		//Draw square
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();

    glFlush();		//Render immediately
}

int main (int argc, char **argv) {
	cout << "Hello World!" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)-screenHeight)/2);		//Display window at screen centre
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pretty Pixel");

	Initialize();

	glutDisplayFunc(Pretty);		//Display event callback
	glutMainLoop();

	return 0;
}