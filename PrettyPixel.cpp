#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//Global defaults
int screenWidth = 800;
int screenHeight = 800;
float mouseX = 0.0, mouseY = 0.0;
float 
	cx = 0.0, cy = 0.0, cz = 5.0,
	lx = 0.0, ly = 0.0, lz = 0.0;
int timerDuration = 50;
float fraction = 0.0;

using namespace std;

void DrawPixels() {
	//glutWireCube(700);
	//glutWireTeapot(1);
	glLineStipple(1, 0x00FF);
	glBegin(GL_LINE_LOOP);
	glVertex3f( -50*2,  -50*2, -20*2);
		glVertex3f( -50*2,  -40*2, -50*2);
		glVertex3f( -50*2,  -20*2, -30*2);
		glVertex3f( -50*2,  30*2, 30*2);
	glVertex3f( -50*2,  50*2, 10*2);
		glVertex3f( -20*2,  50*2, -10*2);
		glVertex3f( 30*2,  50*2, 20*2);
		glVertex3f( 40*2,  50*2, -20*2);
	glVertex3f( 50*2,  50*2, 0*2);
		glVertex3f( 50*2,  20*2, 10*2);
		glVertex3f( 50*2,  -30*2, 20*2);
		glVertex3f( 50*2,  -40*2, 30*2);
	glVertex3f( 50*2,  -50*2, 10*2);
		glVertex3f( 30*2,  -50*2, -20*2);
		glVertex3f( 10*2,  -50*2, 30*2);
		glVertex3f( -35*2,  -50*2, -40*2);
	glEnd();
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
	glLoadIdentity();
	gluLookAt (cx, cy, cz, lx, ly, lz, 0.0, 1.0, 0.0);
	DrawPixels();
	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);
	glOrtho(-w/2, w/2, -h/2, h/2, -400, 400);
	glMatrixMode(GL_MODELVIEW);
}

void MouseMove(int x, int y) {
	cout << "Mouse at (" << x << "," << y - screenHeight << ")\n";
	if(abs(x - mouseX/100.0) > 0) {
		mouseX = x/100.0;
		mouseY = (y - screenHeight)/100.0;
		cx = sin(mouseX)*10;
		cz = cos(mouseX)*10;
		glutPostRedisplay();
	}
	if(abs((y - screenHeight) - mouseY/100.0) > 0) {
		mouseX = x/100.0;
		mouseY = (y - screenHeight)/100.0;
		cy = sin(mouseY)*10;
		cz = cos(mouseY)*10;
		glutPostRedisplay();
	}
}

void KeyArrow(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT :
			mouseX += 0.1;
			cx = sin(mouseX)*10;
			cz = cos(mouseX)*10;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT :
			mouseX -= 0.1;
			cx = sin(mouseX)*10;
			cz = cos(mouseX)*10;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			mouseY += 0.1;
			cy = sin(mouseY)*10;
			cz = cos(mouseY)*10;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN :
			mouseY -= 0.1;
			cy = sin(mouseY)*10;
			cz = cos(mouseY)*10;
			glutPostRedisplay();
		case GLUT_KEY_PAGE_UP:
			cz += 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_DOWN :
			cz -= 0.1;
			glutPostRedisplay();
			break;
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
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
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
	//glutPassiveMotionFunc(MouseMove);
	//glutSpecialFunc(KeyArrow);
	glutMainLoop();

	return 0;
}