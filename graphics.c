/* Graphics for mancala
11/8/17

Commented out functions are things that I don't know if we need.
I lowkey don't know how any of this works
*/

#include "MancalaModel.h"
#include <gl.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 500

void drawBoard() {
	glColor3f(0.7, 0.5, 0.5);
	glBegin(GL_POLYGON); // These are random coordinates, need to be calibrated
		glVertex3f(0.25, 0.25, 0); // Last coordinate needs to be 0
		glVertex3f(0.25, 0.5, 0);
		glVertex3f(0.5, 0.5, 0);
		glVertex3f(0.5, 0.25, 0);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	//glutReshapeWindow(w, h);
}

int main() {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutDisplayFunc(display);
	//glutVisibilityFunc();
	glutReshapeFunc(reshape);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();
	return 0;
}
