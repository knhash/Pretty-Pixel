#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//Global defaults
int screenLength = 800;
float mouseX = 0.0, mouseY = 0.0, curX = 0.0, curY = 0.0;
float 
	cx = 0.0, cy = 0.0, cz = 5.0,
	lx = 0.0, ly = 0.0, lz = 0.0;
bool LMB = false;

using namespace std;

void DisplayPixels() {
	glutWireCube(400);
	
}

void DrawPixel(int x, int y) {
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex3f(x, y, 0);
	glEnd();
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
	glLoadIdentity();
	gluLookAt (cx, cy, cz, lx, ly, lz, 0.0, 1.0, 0.0);
	glRotatef(-3, 1, 0, 0);
	DisplayPixels();
	cout << endl;
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
	curX = x - (screenLength / 2), 
	curY = (screenLength - y) - (screenLength / 2);
	if(LMB == true) {
		DrawPixel(curX, curY);
		glFlush();
	}	
}

void MouseMove(int x, int y) {
	curX = x - (screenLength / 2), 
	curY = (screenLength - y) - (screenLength / 2);
	cout 
		<< " cx: " << cx*180/M_PI
		<< " cy: " << cy*180/M_PI
		<< " cz: " << cz*180/M_PI;
	if(abs(curX - mouseX) > 0) {
		mouseX = curX/(screenLength/2);
		mouseY = curY/(screenLength/2);
		cx = sin(mouseX);
		cz = cos(mouseX);
		glutPostRedisplay();
	}
	if(abs(curY - mouseY) > 0) {
		mouseX = curX/(screenLength/2);
		mouseY = curY/(screenLength/2);
		cy = sin(mouseY);
		cz = cos(mouseY);
		glutPostRedisplay();
	}
}

void MouseClick(int button, int state, int x, int y) {
	curX = x - (screenLength / 2), 
	curY = (screenLength - y) - (screenLength / 2);
	switch(button) {
		case GLUT_LEFT_BUTTON :
			if(state == GLUT_DOWN) {
				LMB = true;
			}
			else if(state == GLUT_UP) {
				LMB = false;
			}
		case GLUT_RIGHT_BUTTON :
			if(state == GLUT_DOWN) {
				exit(0);
			}
	}
}

int main (int argc, char **argv) {
	cout << "Hello World! Pretty Pixel\n\nNerd Stats:\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenLength)/2, 
						   (glutGet(GLUT_SCREEN_HEIGHT)-screenLength)/2);
	glutInitWindowSize(screenLength, screenLength);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glEnable(GL_DEPTH_TEST); 

	glutDisplayFunc(Pretty);		
	glutReshapeFunc(Reshape);
	glutMotionFunc(MouseClickMove);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	//glutSpecialFunc(KeyArrow);
	glutMainLoop();

	return 0;
}