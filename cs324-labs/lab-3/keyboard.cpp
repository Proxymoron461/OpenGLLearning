#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stddef.h>
#include <iostream>

// values controlled by fast keys
GLfloat g_angle = 0.0f;
GLfloat g_xoffset = 0.0f;
GLfloat g_yoffset = 0.0f;
GLfloat g_scale_factor = 100.0f;

// increments
const GLfloat g_angle_step = 10.0f;  // degrees
const GLfloat g_offset_step = 32.0f;  // world coord units
const GLfloat g_scale_step = 10.0f;  // Scale factor

void draw_triangle()
{
	// in model coordinates centred at (0,0)
	static float vertex[3][2] =
		{
			{ -1.0f, -1.0f },
			{  1.0f, -1.0f },
			{  0.0f,  1.0f }
		};

	glBegin(GL_LINE_LOOP);
		for (size_t i=0;i<3;i++)
			glVertex2fv(vertex[i]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(500.0f + g_xoffset, 500.0f + g_yoffset, 0.0f);
		glScalef(g_scale_factor, g_scale_factor, 1.0f);
		glRotatef(g_angle, 0.0f, 0.0f, 1.0f);
		draw_triangle();
	glPopMatrix(); // done with stack
	glutSwapBuffers();
}

// will get which key was pressed and x and y positions if required
void keyboard(unsigned char key, int x, int y)
{
	std::cerr << "\t you pressed the " << key << " key" << std::endl;
	std::cerr << "\t x position: " << x << ", y position: " << y << std::endl;

	switch (key)
	{
		case 'q': exit(1); // quit!

		// clockwise rotate
		case 'r': g_angle += g_angle_step; break;

		case '+': g_scale_factor += g_scale_step; break;
		case '-': g_scale_factor -= g_scale_step; break;
	}

	glutPostRedisplay(); // force a redraw
}

// any special key pressed like arrow keys
void special(int key, int x, int y)
{
	std::cerr << "\t x position: " << x << ", y position: " << y << std::endl;
	
	// handle special keys
	switch (key)
	{
		case GLUT_KEY_LEFT: g_xoffset -= g_offset_step; break;
		case GLUT_KEY_RIGHT: g_xoffset += g_offset_step; break;
		case GLUT_KEY_UP: g_yoffset += g_offset_step; break;
		case GLUT_KEY_DOWN: g_yoffset -= g_offset_step; break;
	}

	glutPostRedisplay(); // force a redraw on next glutMainLoop()
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);  // Turn off repeating keys
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Keyboard Test");
	glutDisplayFunc(display);

	// handlers for keyboard input
	glutKeyboardFunc(keyboard);  // Handle regular keys
	glutSpecialFunc(special);  // Handle special keys

	init();
	glutMainLoop();

	return 0;
}
