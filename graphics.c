/* Graphics for mancala
 11/8/17
 Commented out functions are things that I don't know if we need.
 I lowkey don't know how any of this works
*/

#include "MancalaModel.h"
#include "obj2d.h"
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 750
#define NUM_PIECES 24
struct obj2d *objlist[NUM_PIECES];
//float obj2d = objlist[24];

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

float * houses[] = {house00, house01, house02, house03, house04, house05,0,0,0,0, house10, house11, house12, house13, house14, house15};

/*
 CALLABLE METHODS
 sendTo(obj2d piece, int rowcol, int store):
 Send a piece to the house at the row and column specified (concatenate the row and column into 1 integer, for example row 1 column 2 is rowcol 12).
 Enter a store value of 1 if piece is sent to a store (in which case, put row as 0, and column as 0 or 1)
 For houses, do not exceed row 1 or column 5.
 There is no error handling for indexes so make sure the program handles this well.
 
 winMessage() and loseMessage():
 Order the program to show a win message or lose message. Text can be changed within this program by editing the message string below.
*/

void sendTo(struct obj2d piece, int rowcol, int store) {
  float x, y;
  if (store == 1) {
    if (rowcol == 0) {
      x = store0[0] + ((float)rand()/(float)(RAND_MAX))*0.15f;
      y = store0[1] + ((float)rand()/(float)(RAND_MAX))*0.25f;
    }
    else if (rowcol==1){
      x = store1[0] + ((float)rand()/(float)(RAND_MAX))*0.15f;
      y = store1[1] + ((float)rand()/(float)(RAND_MAX))*0.25f;
    }

  }
  else {
    x = houses[rowcol][0] + ((float)rand()/(float)(RAND_MAX))*0.15f;
    y = houses[rowcol][1] + ((float)rand()/(float)(RAND_MAX))*0.15f;
  }
  piece.x = x;
  piece.y = y;
}
//The output function would be here to show whether or not the player wins.
void output(float x, float y, char *message) {
  glRasterPos2f(x,y);
  int len = (int) strlen(message);
  for (int i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
  }
}
void winMessage() {
  char message[] = "You are winner!";
  glColor3f(0,0.75,0);
  output(-10, -10, message);
}

void loseMessage() {
  char message[] = "You lose!";
  glColor3f(0.75,0,0);
  output(-10, -10, message);
}


/*
 END CALLABLE METHODS
 Below are OpenGL methods
*/
void update() {
  /*here we would connect it up to the game
     we would see what the gamestate was and update
     the gameboard accordingly*/

}


void initializePieces() {
  int j = 0;
  float r =0.0f;
  float g=0.0f;
  float b=0.0f;

  for (int i = 0; i < NUM_PIECES; i++) {
    objlist[i]=malloc(sizeof(struct obj2d));
  }
  // TODO: Use sendTo to send pieces to correct starting places
  while (j!=NUM_PIECES){
    for (int i = 0; i < 4; i++) {
      for (int k = 0; k < NUM_PIECES/4; k++) {
	objlist[j]=create(houses[k][0],houses[k][1], r, g, b);
      }
      for (int k = 10; k < 16; k++) {
	objlist[j]=create(houses[k][0],houses[k][1], r, g, b);
      }
      j++;

    }
  }
}
void freepieces(){
  for(int i=0;i<NUM_PIECES;i++){
    free(objlist[i]);
  }

}


void render() {
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
  //glutSwapBuffers();
  // Drawing the pieces:
  initializePieces();
  for (int i = 0; i < NUM_PIECES; i++) {
    //initializePieces();
    float x = objlist[i]->x+((float)rand()/(float)(RAND_MAX))*-0.85f;//These move the pieces
    float y = objlist[i]->y+((float)rand()/(float)(RAND_MAX))*0.35f;
    glColor3f(objlist[i]->r, objlist[i]->g, objlist[i]->b);
    glBegin(GL_POLYGON);
    glVertex3f(x+0.05, y+0.05, 1);
    glVertex3f(x+0.05, y-0.05, 1);
    glVertex3f(x-0.05, y-0.05, 1);
    glVertex3f(x-0.05, y+0.05, 1);
    glEnd();
  }
  glutSwapBuffers();
  glFlush();
}


void display() {
  update();
  render();
}

void renderScene(void) {
  //this is here as a test

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5,-0.5,0.0);
  glVertex3f(0.5,0.0,0.0);
  glVertex3f(0.0,0.4,0.0);
  glEnd();

  glutSwapBuffers();
}


int main(int argc, char *argv[]) {
  // TODO: initialize openGL shit

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WINDOW_SIZE,WINDOW_SIZE/1.5);
  glutCreateWindow("Mancala");

  glutDisplayFunc(render);
  freepieces();
  glutMainLoop();

  return EXIT_SUCCESS;
  /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);
    glClearColor(0.25,0.25,0.25,1);
  */
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
