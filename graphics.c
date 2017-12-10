/* Graphics for mancala
11/8/17

Commented out functions are things that I don't know if we need.
I lowkey don't know how any of this works
*/

#include "MancalaModel.h"
#include "obj2d.h"
#include <gl.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 750
#define NUM_PIECES 24

float obj2d * objlist[24];

float house00[] = {-0.65, -0.3};
float house01[] = {0.475, -0.3};
float house02[] = {-0.425, -0.3};
float house03[] = {0.25, -0.3};
float house04[] = {-0.2, -0.3};
float house05[] = {0.025, -0.3};
float house10[] = {-0.65, 0.3};
float house11[] = {0.475, 0.3};
float house12[] = {-0.425, 0.3};
float house13[] = {0.25, 0.3};
float house14[] = {-0.2, 0.3};
float house15[] = {0.025, 0.3};
float store0[] = {-0.85, -0.3};
float store1[] = {0.7, -0.3};

/*
CALLABLE METHODS
sendTo(obj2d piece, int row, int col, int store):
	Send a piece to the house at the row and column specified.
	Enter a store value of 1 if piece is sent to a store (in which case, put row as 0, and column as 0 or 1)
	For houses, do not exceed row 1 or column 5.
	There is no error handling for indexes so make sure the program handles this well.
*/

public void sendTo(obj2d piece, int row, int col, int store) {
	float x, y;
	if (store == 1) {
		if (col == 0) {
			x = store0[0] + ((float)rand()/(float)(RAND_MAX))*0.15f;
			y = store0[1] + ((float)rand()/(float)(RAND_MAX))*0.25f;
		}
		else if (col == 1) {
			x = store0[0] + ((float)rand()/(float)(RAND_MAX))*0.15f;
			y = store0[1] + ((float)rand()/(float)(RAND_MAX))*0.25f;
		}
	}
	else {
		// TODO: find an elegant way to handle this
	}
	piece->x = x;
	piece->y = y;
}

/*
END CALLABLE METHODS
Below are OpenGL methods
*/

private void update() {

}

private void render() {
	glClearColor(0.25,0.25,0.25,1);
	glClear(GL_COLOR_BUFFER_BIT);
	// Creating the board:
	glColor3f(0.75f, 0.65f, 0.75f); // Board color
	glBegin(GL_POLYGON);
		glVertex3f(-0.9f, -0.35f, 1);
		glVertex3f(0.9f, -0.35f, 1);
		glVertex3f(0.9f, 0.35f, 1);
		glVertex3f(-0.9f, 0.35f, 1);
	glEnd();
	// Creating the houses and stores:
	glColor3f(0.5f, 0.5f, 0.5f); // House/store color
	for (int i = -1; i < 2; i += 2) {
		glBegin(GL_POLYGON);
			glVertex3f(-0.85f*i, -0.3f*i, 1);
			glVertex3f(-0.7f*i, -0.3f*i, 1);
			glVertex3f(-0.7f*i, 0.3f*i, 1);
			glVertex3f(-0.85f*i, 0.3f*i, 1);
		glEnd();
		for (int j = -1; j < 2; j += 2) {
			glBegin(GL_POLYGON);
				glVertex3f(-0.65f*i, -0.3f*i*j, 1);
				glVertex3f(-0.475f*i, -0.3f*i*j, 1);
				glVertex3f(-0.475f*i, -0.05f*i*j, 1);
				glVertex3f(-0.65f*i, -0.05f*i*j, 1);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(-0.425f*i, -0.3f*i*j, 1);
				glVertex3f(-0.25f*i, -0.3f*i*j, 1);
				glVertex3f(-0.25f*i, -0.05f*i*j, 1);
				glVertex3f(-0.425f*i, -0.05f*i*j, 1);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(-0.20f*i, -0.3f*i*j, 1);
				glVertex3f(-0.025f*i, -0.3f*i*j, 1);
				glVertex3f(-0.025f*i, -0.05f*i*j, 1);
				glVertex3f(-0.20f*i, -0.05f*i*j, 1);
			glEnd();
		}
	}
	// Drawing the pieces:
	for (int i = 0; i < NUM_PIECES; i++) {
		float x = objlist[i]->x;
		float y = objlist[i]->y;
		glColor3f(objlist[i]->r, objlist[i]->g, objlist[i]->b);
		glBegin(GL_POLYGON);
			glVertex3f(x+0.05, y+0.05, 1);
			glVertex3f(x+0.05, y-0.05, 1);
			glVertex3f(x-0.05, y-0.05, 1);
			glVertex3f(x-0.05, y+0.05, 1);
		glEnd();
	}
	glFlush();
}

public void display() {
	update();
	render();
}

private void initializePieces() {
	for (int i = 0; i < NUM_PIECES; i++) {
		r =
		objlist[i] = create(0, 0, r, g, b);
	}
	// TODO: Use sendTo to send pieces to correct starting places
}

int main(int argc, char *argv[]) {
	// TODO: initialize openGL shit

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1,0,1);
	glClearColor(0.25,0.25,0.25,1);
}

/*
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
// a

*/
