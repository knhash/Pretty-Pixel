#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

//Global defaults
int screenWidth = 661;
int screenHeight = 661;
float xAngle=0, yAngle=0, zAngle=0;
int timerDuration = 10;
float randNum;

using namespace std;

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT);		//Clear all pixels
	glColor3f((rand() % 100)/100.0, (rand() % 100)/100.0, (rand() % 100)/100.0);		//Random colors
	glLoadIdentity();
	gluLookAt (3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);		//eyex, eyey, eyez, centrex, centrey, centrez, upx, upy, upz
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
	glLineWidth(3);
	glutWireCube (3.0); 
	glFlush();

    glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.5);		//3D projection
	glMatrixMode(GL_MODELVIEW);
}

void Timer(int v) {
	xAngle=yAngle=zAngle+=1;
	if(xAngle>360)
		xAngle=yAngle=zAngle-=360;
	glutPostRedisplay();
	glutTimerFunc(timerDuration, Timer, 0);
}

int main (int argc, char **argv) {
	cout << "Hello World! Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)-screenHeight)/2);		//Display window at screen centre
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 0.0, 0.0, 0.0);		//Select clear color as black
	glShadeModel(GL_FLAT);

	glutDisplayFunc(Pretty);		//Display event callback
	glutReshapeFunc(Reshape);		//Display window reshape event callback
	glutTimerFunc(timerDuration, Timer, 0);		//Timer for infinite update and display
	glutMainLoop();

	return 0;
}