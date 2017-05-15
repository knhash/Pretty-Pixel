#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <GL/glut.h>

#include "Pictures.h"

using namespace std;

//Global defaults
int screenLength = 800, level = 0, size = 0, solBuffer = 5, score = 0;
float rotateX = 0, rotateY = 0, goalX = 0, goalY = 0;
bool pass = false;

int picture[100][3];

void RandomizeZ(int ray[][3], int size) {
	srand (time(NULL));
	for(int i = 0; i < size; ++i) {
		ray[i][2] = (rand()%400) - 200;
	}
}

void Leveler() {
	//Set random solution point
	srand (time(NULL));
	goalX = (rand()%198) - 99;
	goalY = (rand()%198) - 99;

	//Clear picture
	memset(picture, 0, sizeof(int) * size * 3);

	//Level up
	level++;

	//Load level picture
	switch(level) {
		case 1:
			size = sizeof(square) / sizeof (square[0]);
			memcpy(picture, square, sizeof(int) * size * 3);
			break;
		case 2:
			size = sizeof(doubleSquare) / sizeof (doubleSquare[0]);
			memcpy(picture, doubleSquare, sizeof(int) * size * 3);
			break;
		case 3:
			size = sizeof(starTrek) / sizeof (starTrek[0]);
			memcpy(picture, starTrek, sizeof(int) * size * 3);
			break;
		case 4:
			size = sizeof(patrick) / sizeof (patrick[0]);
			memcpy(picture, patrick, sizeof(int) * size * 3);
			solBuffer--;
			break;
		case 5:
			size = sizeof(dumbell) / sizeof (dumbell[0]);
			memcpy(picture, dumbell, sizeof(int) * size * 3);
			break;
		default:
			cout << " Score: " << score << "\nGame Over\n";
			exit(0);
	}
	if(level > 1)
		cout << " Score: " << score;
	cout << "\nLevel " << level ;

	//Randomize z coordinates
	RandomizeZ(picture, size);
}

void DrawPixel() {
	glColor3f(1, 1, 1);
	//Draw points
	glPointSize(5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_POINTS, 0, size);
	glDisableClientState(GL_VERTEX_ARRAY);
	//Draw lines
	glLineWidth(1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_LINE_LOOP, 0, size);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
	glLoadIdentity();

	//Check solution
	if(abs(goalX - rotateX) < solBuffer && 
		abs(goalY - rotateY) < solBuffer) {
		rotateX = goalX;
		rotateY = goalY;
		pass = true;
	}

	//Rotate playing field
	glRotatef(goalX - rotateX, 1, 0, 0);
	glRotatef(goalY - rotateY, 0, 1, 0);

	//Display Image
	DrawPixel();

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/2, w/2, -h/2, h/2, -w/2, w/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseMove(int x, int y) {
	x = x - (screenLength / 2), 
	y = (screenLength - y) - (screenLength / 2);
	rotateX = -y/4;
	rotateY = x/4;
	score++;
	glutPostRedisplay();
}

void MouseClick(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_RIGHT_BUTTON :
			if(state == GLUT_DOWN) {
				cout << "\nGame Over\n";
				exit(0);
			}
			break;
		case GLUT_LEFT_BUTTON :
			if(state == GLUT_DOWN && pass == true) {
				pass = false;
				Leveler();
			}
			break;
	}
}

int main (int argc, char **argv) {
	cout << "Hello World!  Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenLength)/2, 
						   (glutGet(GLUT_SCREEN_HEIGHT)-screenLength)/2);
	glutInitWindowSize(screenLength, screenLength);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glEnable(GL_DEPTH_TEST); 

	/*******************************************************************/

	cout << "LMB advance, RMB to exit" ;
	Leveler();

	/*******************************************************************/

	glutDisplayFunc(Pretty);		
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	glutMainLoop();

	return 0;
}