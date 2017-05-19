#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <fstream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <time.h>

//Level picture storage
#include "Pictures.h"

using namespace std;

/**************************************************************************/
//Global defaults

int
	screenLength = 800, screenWidth, screenHeight, level = 0, siz = 0,
	solBuffer = 5, score = 1000, picture[300][3], custPicture[300][3],
	ind = 0;
float
	rotateX = 0, rotateY = 0, goalX = 0, goalY = 0, cx, cy;
bool
	pass = false, drawSC = false, custGame = false, firstG = true;
char
	scoreText[7], levelText[3];

/**************************************************************************/
//Background operations

//Randomize z-coordinates
void RandomizeZ(int ray[][3], int siz) {
	srand(time(NULL));
	for (int i = 0; i < siz; ++i) {
		ray[i][2] = (rand() % 600) - 300;
	}
}

//Draw and store picture for custom game
void DrawCustomPixel(int x, int y) {
	glPushMatrix();
	cout << endl << ind;
	glColor3f(1, 1, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
	glutSwapBuffers();
	glPopMatrix();

	//Store points
	custPicture[ind][0] = x,
		custPicture[ind][1] = y,
		custPicture[ind][2] = 0;
	ind++;
}

//Custom Drawboard display
void CustomDraw() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.3, 0.69, 0.31);
	glLineWidth(1);
	glutWireCube(700);
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

//Text render 
void DrawText(const char *text, int x, int y, int sparkle) {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0);
	if (sparkle == 1) {
		glScalef(.5, .5, 0);
		glLineWidth(5);
	}
	else if (sparkle == 2) {
		glScalef(.15, .15, 0);
		glLineWidth(2);
	}
	else if (sparkle == 3) {
		glScalef(.3, .3, 0);
		glLineWidth(3);
	}

	for (int i = 0; text[i] != '\0'; i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, (int)text[i]);
	glutPostRedisplay();
	glPopMatrix();
}

//Draw playground 
void DrawPixel() {
	glPushMatrix();
	//Draw points
	glColor3f(.33, .44, .98);
	glPointSize(7);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_POINTS, 0, siz);
	glDisableClientState(GL_VERTEX_ARRAY);
	//Draw lines
	glColor3f(1, 1, 1);
	glLineWidth(1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, picture);
	glDrawArrays(GL_LINES, 0, siz);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

/**************************************************************************/
//Display functions

//Main game display
void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1);

	//Round details
	sprintf(levelText, "%d", level);
	DrawText("Level: ",
		-70, (screenHeight / 2.2), 2);
	DrawText(levelText,
		30, (screenHeight / 2.2), 2);
	sprintf(scoreText, "%d", score);
	DrawText("Score: ",
		-70, (screenHeight / 2.4), 2);
	DrawText(scoreText,
		30, (screenHeight / 2.4), 2);

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
	glutSwapBuffers();
}

//Gameover display
void GameOver() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(1);
	glColor3f(1.0, 0.54, 0.5);
	DrawText("GameOver",
		-(screenLength / 3.4), (screenHeight / 4), 1);

	glColor3f(0.3, 0.69, 0.31);
	DrawText("(m/M): MAIN MENU",
		-(screenLength / 5.5), (screenHeight / 16), 2);
	DrawText("(q/Q): EXIT",
		-(screenLength / 5.5), 0, 2);

	glColor3f(1.0, 0.54, 0.5);
	DrawText("Your High Score:  ",
		-(screenLength / 2.3), -(screenHeight / 5), 3);
	DrawText(scoreText,
		(screenLength / 5), -(screenHeight / 5), 3);

	glColor3f(1.0, 0.44, 0.26);
	glBegin(GL_LINES);
	glVertex3f(-(screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glVertex3f(-(screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glEnd();
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

//Splash screen display
void Splash() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0, 0.54, 0.5);
	DrawText("PRETTY PIXEL",
		-(screenLength / 2.7), (screenHeight / 4), 1);

	glColor3f(0.3, 0.69, 0.31);
	DrawText("(g/G): START GAME",
		-(screenLength / 5), (screenHeight / 16), 2);
	DrawText("(h/H): HELP",
		-(screenLength / 5), 0, 2);
	DrawText("(c/C): CUSTOM GAME",
		-(screenLength / 5), -(screenHeight / 16), 2);

	glColor3f(1.0, 0.54, 0.5);
	DrawText("Computer Graphics Project",
		-(screenLength / 2.05), -(screenHeight / 5), 3);

	glColor3f(0.3, 0.69, 0.31);
	DrawText("Shreyas N",
		-(screenWidth / 2.5), -(screenHeight / 3.5), 2);
	DrawText("1MV14CS130",
		-(screenWidth / 2.5), -(screenHeight / 3), 2);
	DrawText("Shashank S",
		(screenWidth / 2.5) - 157, -(screenHeight / 3.5), 2);
	DrawText("1MV14CS131",
		(screenWidth / 2.5) - 157, -(screenHeight / 3), 2);
	glLineWidth(10);

	glColor3f(1.0, 0.44, 0.26);
	glBegin(GL_LINES);
	glVertex3f(-(screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glVertex3f(-(screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glEnd();
	glFlush();
	glPopMatrix();
	score = 1000;
	glutSwapBuffers();
}

//Help screen display
void Help() {
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glLineWidth(10);
	glColor3f(1.0, 0.44, 0.26);
	glBegin(GL_LINES);
	glVertex3f(-(screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), (screenHeight / 2 - 40), 0);
	glVertex3f((screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glVertex3f(-(screenWidth / 2), -(screenHeight / 2 - 40), 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	DrawText("The rules are simple",
		-(screenLength / 4), (screenHeight / 3), 2);
	glColor3f(0.0, 1.0, 1.0);
	DrawText("Move mouse to rotate the playing field",
		-(screenLength / 2.1), (screenHeight / 16), 2);
	DrawText("Left Mouse Button to advance to next level",
		-(screenLength / 2.1), 0, 2);
	DrawText("Right Mouse Button to exit the game",
		-(screenLength / 2.1), -(screenHeight / 16), 2);
	DrawText("(m/M) to go to menu, (g/G) to start game",
		-(screenLength / 2.1), -(screenHeight / 8), 2);
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

/**************************************************************************/

//Level initialization
void Leveler() {
	//Set random solution point
	srand(time(NULL));
	cx = (rand() % screenLength) - (screenLength / 2);
	cy = (rand() % screenLength) - (screenLength / 2);
	goalX = cy / (screenLength / 200);
	goalY = cx / (screenLength / 200);

	//Clear picture
	memset(picture, 0, sizeof(int) * siz * 3);

	//Level up
	level++;

	//Play Custom Game
	if (custGame) {
		siz = ind;
		memcpy(picture, custPicture, sizeof(int) * siz * 3);
		score = 1000;
		level = 999;
		custGame = false;
	}

	//Play default game
	else {
		//Load level picture
		switch (level) {
		case 1:
			siz = sizeof(one) / sizeof(one[0]);
			memcpy(picture, one, sizeof(int) * siz * 3);
			break;

		case 2:
			siz = sizeof(two) / sizeof(two[0]);
			memcpy(picture, two, sizeof(int) * siz * 3);
			score += 1000;
			break;

		case 3:
			siz = sizeof(three) / sizeof(three[0]);
			memcpy(picture, three, sizeof(int) * siz * 3);
			score += 1000;
			break;

		case 4:
			siz = sizeof(four) / sizeof(four[0]);
			memcpy(picture, four, sizeof(int) * siz * 3);
			score += 1000;
			break;

		case 5:
			siz = sizeof(five) / sizeof(five[0]);
			memcpy(picture, five, sizeof(int) * siz * 3);
			score += 1000;
			break;

		default://Gameover
			cout << " Score: " << score << "\nGame Over\n";
			siz = sizeof(one) / sizeof(one[0]);
			memcpy(picture, one, sizeof(int) * siz * 3);
			level = 1;
			score = 1000;
			glutDisplayFunc(GameOver);
			break;
		}
	}

	if (level > 1)
		cout << " Score: " << score;
	cout << "\nLevel " << level;

	//Randomize z coordinates
	RandomizeZ(picture, siz);
}

//Window reshape callback
void Reshape(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -w / 2, w / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**************************************************************************/
//Input callbacks

//Passive motion callback
void MouseMove(int x, int y) {
	//Normalization
	x = x - (screenLength / 2),
	y = (screenLength - y) - (screenLength / 2);
	if (!drawSC) {
		rotateX = -y / (screenLength / 200);
		rotateY = x / (screenLength / 200);
		if (--score < 0)
		{
			score = 1000;
			glutDisplayFunc(GameOver);
		}
		glutPostRedisplay();
	}
}

//Active motion callback
void MouseClickMove(int x, int y) {
	//Normalization
	x = x - (screenLength / 2),
	y = (screenLength - y) - (screenLength / 2);
}

//Mouse click call back
void MouseClick(int button, int state, int x, int y) {
	//Normalization
	x = x - (screenLength / 2),
	y = (screenLength - y) - (screenLength / 2);

	switch (button) {
	case GLUT_RIGHT_BUTTON://Right mouse button
		if (state == GLUT_DOWN) {
			if (!drawSC) {
				cout << "\nGame Over\n";
				exit(0);
			}
			else {
				//WriteCoord();
				drawSC = false;
				custGame = true;
				glutSetWindowTitle("Pretty Pixel");
				glutFullScreen();
				glPointSize(1);
				Leveler();
				glutDisplayFunc(Pretty);
			}
		}
		break;
	case GLUT_LEFT_BUTTON://left mouse button
		if (state == GLUT_DOWN && pass == true && !drawSC) {
			//Level up
			pass = false;
			Leveler();
		}
		else if (state == GLUT_DOWN && drawSC &&
			x > -350 && x < 350 && y > -350 && y < 350) {
			//User drawing board
			DrawCustomPixel(x, y);
			glFlush();
		}
		break;
	}
}

//Keyboard callback
void Keys(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'm':
	case 'M':
		//Splash screen
		drawSC = false;
		glutDisplayFunc(Splash);
		break;

	case 'h':
	case 'H':
		//Help screen
		drawSC = false;
		glutDisplayFunc(Help);
		break;

	case 'g':
	case 'G':
		//Game screen
		drawSC = false;
		if (firstG) {
			Leveler();
			firstG = false;
		}
		glutSetWindowTitle("Pretty Pixel");
		glutDisplayFunc(Pretty);
		break;

	case 'f':
	case 'F':
		//Full screen toggle
		glutFullScreenToggle();
		break;

	case 'c':
	case 'C':
		//Custom game screen
		drawSC = true;
		ind = 0;
		glutReshapeWindow(800, 800);
		glutSetWindowTitle("Pretty Draw");
		glutDisplayFunc(CustomDraw);
		break;

	case 'q':
	case 'Q':
		//Quit game
		exit(0);
		break;
	}
}

/**************************************************************************/

//Main
int main(int argc, char **argv) {
	cout << "Hello World!  Pretty Pixel\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenLength) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - screenLength) / 2);
	glutInitWindowSize(screenLength, screenLength);
	
	glutCreateWindow("Pretty Pixel");
	glutFullScreen();
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseClickMove);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keys);
	glutDisplayFunc(Splash);

	glutMainLoop();

	return 0;
}