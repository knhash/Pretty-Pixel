#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//Global defaults
int screenWidth = 800;
int screenHeight = 800;
float mouseX = 0.0, mouseY = 0.0, curX = 0.0, curY = 0.0;
float 
	cx = 0.0, cy = 0.0, cz = 5.0,
	lx = 0.0, ly = 0.0, lz = 0.0;
int timerDuration = 50;
float fraction = 0.0;
bool LMB = false;

using namespace std;

void DisplayPixels() {
	glutWireCube(400);
	//glutWireTeapot(300);
	
}

void DrawPixel(int x, int y) {
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
	glVertex3f(x, y, 0);
	glEnd();
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
	glLoadIdentity();
	gluLookAt (cx, cy, cz, lx, ly, lz, 0.0, 1.0, 0.0);
	DisplayPixels();
	//DrawPixel(0,0);
	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);
	glOrtho(-w/2, w/2, -h/2, h/2, -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseClickMove(int x, int y) {
	curX = x - (screenWidth / 2), curY = (screenHeight - y) - (screenHeight / 2);
	if(LMB == true) {
		cout << "Click at (" << curX << "," <<  curY << ")\n";
		DrawPixel(curX, curY);
		glFlush();
	}	
}

void MouseMove(int x, int y) {
	curX = x - (screenWidth / 2), curY = (screenHeight - y) - (screenHeight / 2);
	cout << "Mouse at (" << curX << "," <<  curY << ")\n";
	if(abs(curX - mouseX) > 0) {
		mouseX = curX/(200);
		mouseY = curY/(200);
		cx = sin(mouseX)*10;
		cz = cos(mouseX)*10;
		glutPostRedisplay();
	}
	if(abs(curY - mouseY) > 0) {
		mouseX = curX/(screenWidth/2);
		mouseY = curY/(screenHeight/2);
		cy = sin(mouseY)*10;
		cz = cos(mouseY)*10;
		glutPostRedisplay();
	}
}

void MouseClick(int button, int state, int x, int y) {
	curX = x - (screenWidth / 2), curY = (screenHeight - y) - (screenHeight / 2);
	switch(button) {
		case GLUT_LEFT_BUTTON :
			if(state == GLUT_DOWN) {
				LMB = true;
			}
			else if(state == GLUT_UP) {
				LMB = false;
			}
	}
}

void Timer(int v) {
	fraction += 0.1;
	cx = sin(fraction)*10;
	cz = -cos(fraction)*10;
	cy = sin(fraction)*10;
	glutPostRedisplay();
	glutTimerFunc(timerDuration, Timer, 0);
}

int main (int argc, char **argv) {
	cout << "Hello World! Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenWidth)/2, 
							(glutGet(GLUT_SCREEN_HEIGHT)-screenHeight)/2);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 0.0, 0.0, 0.0);		
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); 

	glutDisplayFunc(Pretty);		
	glutReshapeFunc(Reshape);
	//glutTimerFunc(timerDuration, Timer, 0);
	glutMotionFunc(MouseClickMove);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	//glutSpecialFunc(KeyArrow);
	glutMainLoop();

	return 0;
}