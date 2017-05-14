#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//Global defaults
int screenLength = 800;
float rotateX = 0, rotateY = 0, goalX = 0, goalY = 0;

using namespace std;

void DisplayPixels() {
	glutWireCube(400);
	glutWireTeapot(200);
}

void DrawPixel() {
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex3f(-200, -200, 0);
	glVertex3f(-200, 200, 0);
	glVertex3f(200, 200, 0);
	glVertex3f(200, -200, 0);
	glEnd();
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
	glLoadIdentity();

	//Rotate playing field
	glRotatef(goalX - rotateX, 1, 0, 0);
	glRotatef(goalY - rotateY, 0, 1, 0);

	//Display Image
	DisplayPixels();
	//DrawPixel();

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/2, w/2, -h/2, h/2, -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseMove(int x, int y) {
	x = x - (screenLength / 2), 
	y = (screenLength - y) - (screenLength / 2);
	rotateX = -y/4;
	rotateY = x/4;
	cout << "rx: " << rotateX << " ry: " << rotateY << endl;
	glutPostRedisplay();
}

void MouseClick(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_RIGHT_BUTTON :
			if(state == GLUT_DOWN) {
				exit(0);
			}
			break;
	}
}

int main (int argc, char **argv) {
	cout << "Hello World! Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenLength)/2, 
						   (glutGet(GLUT_SCREEN_HEIGHT)-screenLength)/2);
	glutInitWindowSize(screenLength, screenLength);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glEnable(GL_DEPTH_TEST); 

	//Set random solution point
	srand (time(NULL));
	goalX = (rand()%198) - 99;
	goalY = (rand()%198) - 99;

	glutDisplayFunc(Pretty);		
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	glutMainLoop();

	return 0;
}