/* Object struct for use with OpenGL commands
11/28/17
*/

#ifndef FILE_OBJ2D_SEEN
#define FILE_OBJ2D_SEEN

typedef struct obj2d obj2d_t;

struct obj2d {
	int x, y;
	int r, g, b;
};

struct obj2d * create(int x, int y, int r, int g, int b) {
	struct obj2d obj;
	obj.x = x;
	obj.y = y;
	obj.r = r;
    obj.g = g;
    obj.b = b;
	return obj;
}

#endif
