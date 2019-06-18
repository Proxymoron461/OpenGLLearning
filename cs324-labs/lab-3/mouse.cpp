#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stddef.h>
#include <iostream>
#include <cmath>

// values controlled by fast keys
GLfloat g_angle = 0.0f;
GLfloat g_xoffset = 0.0f;
GLfloat g_yoffset = 0.0f;

// increments
const GLfloat g_angle_step = 32.0f; // degrees
const GLfloat g_offset_step = 32.0f; // world coord units

// last cursor click
int g_cursor_x = 0;
int g_cursor_y = 0;

GLfloat triangle_x = 500.0f;
GLfloat triangle_y = 500.0f;

int world_width = 1000;
int world_height = 1000;

int mouse_x = 0;
int mouse_y = 0;

// float* normalise_2d_mouse_window_coords(int window_coords[]) {
// 	float window_width = float(glutGet(GLUT_WINDOW_WIDTH));
// 	float window_height = float(glutGet(GLUT_WINDOW_HEIGHT));
// 	static float coords [2] = { float(window_coords[0]) / window_width, (window_height - float(window_coords[1])) / window_height };
// 	return coords;
// }
//
// int* world_coords_from_normalised_coords(float norm_coords[]) {
// 	static int coords [2] = { int(norm_coords[0] * float(world_width)), int(norm_coords[1] * float(world_height)) };
// 	return coords;
// }
//
// int* fix_mouse_coordinates(int x, int y) {
// 	static int mouse_coords [2] = { x, y };
// 	return world_coords_from_normalised_coords(normalise_2d_mouse_window_coords(mouse_coords));
// }

int fix_mouse_x(int x) {
	float window_width = float(glutGet(GLUT_WINDOW_WIDTH));

	return int((float(x) / window_width) * float(world_width));
}

int fix_mouse_y(int y) {
	float window_height = float(glutGet(GLUT_WINDOW_HEIGHT));

	return int(((window_height - float(y)) / window_height) * float(world_height));
}

void draw_triangle()
{
	// in model coordinates centred at (0,0)
	static GLfloat vertex[3][2] =
		{
			{ -1.0f, -1.0f },  // Bottom left
			{  1.0f, -1.0f },  // Bottom right
			{  0.0f,  1.0f }   // Top
		};

	glBegin(GL_LINE_LOOP);
		for (size_t i = 0; i < 3; i++)
			glVertex2fv(vertex[i]);
	glEnd();
}

void draw_mouse_cursor() {
	static int cursor_size = 20;
	static int cursor_width = cursor_size / 2;
	static int cursor_height = cursor_width;

	// int x = fix_mouse_x(mouse_x);
	// int y = fix_mouse_y(mouse_y);
	int x = mouse_x;
	int y = mouse_y;

	// Draw mouse position, using a crossed pair of lines
	glBegin(GL_LINES);
		glVertex2i(x - cursor_width, y + cursor_height);
		glVertex2i(x + cursor_width, y - cursor_height);

		glVertex2i(x - cursor_width, y - cursor_height);
		glVertex2i(x + cursor_width, y + cursor_height);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslatef(triangle_x, triangle_y, 0.0f);
		glScalef(100.0f, 100.0f, 1.0f);

		// Rotate triangle towards mouse
		static const float RAD_TO_DEG = 180.0f/(4 * atan(1));
		g_angle = RAD_TO_DEG * atan2((triangle_y - mouse_y), (triangle_x - mouse_x));
		glRotatef(g_angle + 90.0f, 0.0f, 0.0f, 1.0f);
		std::cerr << "g_angle: "<< g_angle << std::endl;

		draw_triangle();
	glPopMatrix(); // done with stack

	draw_mouse_cursor();

	glutSwapBuffers();
}

// handles mouse click events
// button will say which button is presed, e.g. GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
// state will say if the button is GLUT_UP or GLUT_DOWN
// x and y are the poitner position
void mouse_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		std::cerr << "\t left mouse button pressed!" << std::endl;

		if (state == GLUT_UP)
		{
			std::cerr << "\t button released...click finished" << std::endl;

			// Cursor position, in WINDOW co-ordinates, relative to TOP-LEFT CORNER
			g_cursor_x = x;
			g_cursor_y = y;

			// Move triangle to cursor position

			// Get height and width of window
			// float window_width = float(glutGet(GLUT_WINDOW_WIDTH));
			// float window_height = float(glutGet(GLUT_WINDOW_HEIGHT));
			// std::cerr << "\t window - width: " << window_width << ", height: " << window_height << ")" << std::endl;
			//
			// float norm_window_x = float(g_cursor_x) / window_width;
			// float norm_window_y = (window_height - float(g_cursor_y)) / window_height;
			// std::cerr << "\t normalised - (" << norm_window_x << ", " << norm_window_y << ")" << std::endl;

			triangle_x = fix_mouse_x(g_cursor_x);
			triangle_y = fix_mouse_y(g_cursor_y);
			std::cerr << "\t final - (" << triangle_x << ", " << triangle_y << ")" << std::endl;

			std::cerr << "\t cursor at (" << g_cursor_x << ", " <<
                                             g_cursor_y << ")" << std::endl;
		}

	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		std::cerr << "\t right mouse button pressed!" << std::endl;
	}
	glutPostRedisplay();
}

void mouse_motion(int x, int y)
{
	//glutPostRedisplay();

	// Set global variables mouse_x and mouse_y to track mouse
	// mouse_x = x;
	// mouse_y = y;
	mouse_x = fix_mouse_x(x);
	mouse_y = fix_mouse_y(y);
	std::cerr << "\t mouse (in world co-ordinates) is at (" << mouse_x << ", " << mouse_y << ")" << std::endl;

	// Get glut to draw them next loop of glutMainLoop()
	glutPostRedisplay();
}


// will get which key was pressed and x and y positions if required
void keyboard(unsigned char key, int, int)
{
	std::cerr << "\t you pressed the " << key << " key" << std::endl;

	switch (key)
	{
		case 'q': exit(1); // quit!

		// clockwise rotate
		case 'r': g_angle += g_angle_step; break;
	}

	glutPostRedisplay(); // force a redraw
}

// any special key pressed like arrow keys
void special(int key, int, int)
{
	// handle special keys
	switch (key)
	{
		case GLUT_KEY_LEFT: triangle_x -= g_offset_step; break;
		case GLUT_KEY_RIGHT: triangle_x += g_offset_step; break;
		case GLUT_KEY_UP: triangle_y += g_offset_step; break;
		case GLUT_KEY_DOWN: triangle_y -= g_offset_step; break;
	}

	glutPostRedisplay(); // force a redraw
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, world_width, 0, world_height);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	g_cursor_x = g_cursor_y = 500; // middle of window
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Mouse Test");
	glutDisplayFunc(display);

	// handlers for keyboard input
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	// mouse event handlers
	glutMouseFunc(mouse_click);
	glutPassiveMotionFunc(mouse_motion);

	init();
	glutMainLoop();

	return 0;
}
