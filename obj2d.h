/* Object struct for use with OpenGL commands
11/28/17
*/

#ifndef FILE_OBJ2D_SEEN
#define FILE_OBJ2D_SEEN

typedef struct obj2d obj2d_t;

struct obj2d {
	int x, y;
	int diam;
	int r, g, b;
};

obj2d * create(int x, int y, int diam, int r, int g, int b);

#endif
