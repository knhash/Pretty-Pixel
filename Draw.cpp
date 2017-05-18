#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#include <GL/glut.h>

using namespace std;

//Global defaults
int screenLength = 800;
int picture[300][3];
int ind = 0, i;
char picName[25];

void WriteCoord() {
	if(ind == 0)
		return;
	cout << "Writing " << picName;
	ofstream fout;
	fout.open("Pictures.h", ios::app);
	fout << "\n\nint " << picName << "[][3] = {" ;
	for(i = 0; i < ind - 1; ++i) {
		cout << ".";
		fout << "\n{" << picture[i][0] << ", " 
			<< picture[i][1] << ", 0}," ; 
	}
	fout << "\n{" << picture[i][0] << ", " << picture[i][1] << ", 0}};" ; 
	fout.close();
	cout << ". Done\n";
}

void DrawPixel(int x, int y) {
	glColor3f(1, 1, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();

	//Store points
	picture[ind][0] = x, picture[ind][1] = y, picture[ind][2] = 0;
	cout << ind << endl;
	ind++;
}

void Pretty() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);	
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
}

void MouseClick(int button, int state, int x, int y) {
	x = x - (screenLength / 2), 
	y = (screenLength - y) - (screenLength / 2);
	switch(button) {
		case GLUT_RIGHT_BUTTON :
			if(state == GLUT_DOWN) {
				WriteCoord();
				exit(0);
			}
			break;
		case GLUT_LEFT_BUTTON :
			if(state == GLUT_DOWN) {
				DrawPixel(x, y);
				glFlush();
			}
			break;
	}
}

int main (int argc, char **argv) {
	cout << "Pretty Drawer\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-screenLength)/2, 
						   (glutGet(GLUT_SCREEN_HEIGHT)-screenLength)/2);
	glutInitWindowSize(screenLength, screenLength);
	glutCreateWindow("Pretty Pixel");
	glClearColor(0.0, 1.0, 0.0, 0.0);	
	glEnable(GL_DEPTH_TEST); 

	if(argc != 2) {
		cout << "Pass picture name as argument\nExiting\n";
		exit(0);
	}
	strcpy(picName, argv[1]);

	//Clear picture
	memset(picture, 0, sizeof(int) * 100 * 3);

	glutDisplayFunc(Pretty);		
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutMainLoop();

	return 0;
}