//integrated

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Pictures.h"
using namespace std;
//Global defaults
int screenWidth = 500;
int screenHeight = 500;
int ruleflag = 0;
int full = 1;
int screenLength = 800, level = 0, asize = 0, solBuffer = 5, score = 0;
float rotateX = 0, rotateY = 0, goalX = 0, goalY = 0;
bool pass = false;

int picture[300][3];

void RandomizeZ(int ray[][3], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		ray[i][2] = (rand() % 400) - 200;
	}
}

void Leveler() {
	//Set random solution point
	srand(time(NULL));
	goalX = (rand() % 198) - 99;
	goalY = (rand() % 198) - 99;

	//Clear picture
	memset(picture, 0, sizeof(int) * asize * 3);

	//Level up
	level++;

	//Load level picture
	switch (level) {
	case 1:
		asize = sizeof(square) / sizeof(square[0]);
		memcpy(picture, square, sizeof(int) * asize * 3);
		break;
	case 2:
		asize = sizeof(doubleSquare) / sizeof(doubleSquare[0]);
		memcpy(picture, doubleSquare, sizeof(int) * asize * 3);
		break;
	case 3:
		asize = sizeof(starTrek) / sizeof(starTrek[0]);
		memcpy(picture, starTrek, sizeof(int) * asize * 3);
		break;
	case 4:
		asize = sizeof(patrick) / sizeof(patrick[0]);
		memcpy(picture, patrick, sizeof(int) * asize * 3);
		solBuffer--;
		break;
	case 5:
		asize = sizeof(dumbell) / sizeof(dumbell[0]);
		memcpy(picture, dumbell, sizeof(int) * asize * 3);
		break;
	default:
		cout << " Score: " << score << "\nGame Over\n";
		exit(0);
	}
	if (level > 1)
		cout << " Score: " << score;
	cout << "\nLevel " << level;

	//Randomize z coordinates
	RandomizeZ(picture, asize);
}

void DrawPixel() {
	glColor3f(1, 1, 1);
	//Draw points
	glPointSize(5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_POINTS, 0, asize);
	glDisableClientState(GL_VERTEX_ARRAY);
	//Draw lines
	glLineWidth(1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_LINE_LOOP, 0, asize);
	glDisableClientState(GL_VERTEX_ARRAY);
}




void keys(unsigned char asd, int x, int y)
{

	switch (asd)
	{
		case 'q':	exit(0);
			break;
		case 'Q':	exit(0);
			break;

		case 'N':	ruleflag = 1;
			break;
		
		case 'n':	ruleflag = 1;
			break;
		case 'B':
		{
			ruleflag = 0;
			break;
		}
		case 'S':
		{
			ruleflag = 2;
			break;
		}
		case 'b':
		{
			ruleflag = 0;
			break;
		}
		case 's':
		{
			ruleflag = 2;
			break;
		}
	}
}

void drawsc(const char *text, int x, int y, int sparkle)
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
	//glRasterPos2i(x, y);
	glTranslatef(x, y, 0);
	if(sparkle)
	{ 
		glScalef(.3, .3, .0);
	}
	else
	{
		glScalef(.15, .15, .7);
		glLineWidth(2);
	}
	//glScalef(.3, .3, .0);
	for (int i = 0; text[i] != '\0'; i++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);

		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)text[i]);
		//if (sparkle)
	}
	//	glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));


	glutPostRedisplay();
	glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixd(matrix);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

}


void display() {
	if (!ruleflag)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gluLookAt(0, 0, -10, 0, 0, 3, 0, 10, 0);
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		//glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
		glColor3f(0.5, 1.0, 0.0);
		
		drawsc("Pretty Pixel", 320, 350, 1);
		glColor3f(1.0, 0.0, 0.0);
		
		drawsc("n: Next", 20, 400, 0);
		drawsc("q: quit", 20, 300, 0);
		drawsc("s: start game", 20, 200, 0);
		drawsc(".", 700, 700, 0);
		glColor3f(0.5, 1.0, 0.0);
		
		drawsc("Shreyas N", 50, 100, 1);
		drawsc("Computer Graphics Project", 175, 530, 1);
		drawsc("1MV14CS130", 50, 50, 1);
		drawsc("Shashank S", 545, 100, 1);
		drawsc("1MV14CS130", 545, 50, 1);
		glLineWidth(5.0);
		//glRasterPos2i(GLUT_SCREEN_HEIGHT, GLUT_SCREEN_WIDTH);
		//glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(10, 10, 0);
		glVertex3f(10, 580, 0);
		glVertex3f(790,580, 0);
		glVertex3f(790,10, 0);
		glEnd();
		glFlush();
	}
	else if (ruleflag == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gluLookAt(0, 0, -10, 0, 0, 3, 0, 10, 0);
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();
		//glColor3f(((rand() % 100) / 100.0), ((rand() % 100) / 100.0), ((rand() % 100) / 100.0));
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(10, 10, 0);
		glVertex3f(10, 580, 0);
		glVertex3f(790, 580, 0);
		glVertex3f(790, 10, 0);
		glEnd();
		glColor3f(0.0, 1.0, 0.0);
		drawsc("The rules are simple",200, 500, 1);
		glColor3f(0.0, 1.0, 1.0);
		drawsc("1)Blah blah blah blah ",300,400,0);
		drawsc("2)Blah blah blah blah ",300,300, 0);
		drawsc("3)Blah blah blah blah ",300,200, 0);
		drawsc("4)Blah blah blah blah ",300,100, 0);

		
		glFlush();
	}
	else if (ruleflag == 2)
	{
		printf("The game goes here \n");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glLoadIdentity();

		//Check solution
		if (abs(goalX - rotateX) < solBuffer &&
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
}


/*void reshape(int w, int he) {
	GLfloat h = (GLfloat)he / (GLfloat)w;
	glViewport(0, 0, (GLint)w, (GLint)he);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, h, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -w / 2, w / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseMove(int x, int y) {
	x = x - (screenLength / 2),
		y = (screenLength - y) - (screenLength / 2);
	rotateX = -y / 3;
	rotateY = x / 3;
	score++;
	glutPostRedisplay();
}

void MouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			cout << "\nGame Over\n";
			exit(0);
		}
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN && pass == true) {
			pass = false;
			Leveler();
		}
		break;
	}
}

int main(int argc, char **argv) {
	cout << "Hello World!  Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Pretty Pixel");
	//glutFullScreen();
	glutKeyboardFunc(keys);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	/***********************/

	cout << "LMB advance, RMB to exit";
	Leveler();

	/***********************/

	glutReshapeFunc(reshape);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}