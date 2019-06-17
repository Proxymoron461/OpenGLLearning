//
// Here are the required include files
// note that glut.h itself includes glu.h and gl.h
#ifdef __APPLE__
#include <GLUT/glut.h> // if we are on a Mac
#else
#include <GL/glut.h> // on linux
#endif

#include <iostream>

// ...define what OpenGL must do when asked to redraw the window
// 	note we can call this function anything we want but remember to
//  set your chosen name in the glutDisplayCallbackFunc() in main()
//
void display()
{
	std::cout << "Display being called!" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT); // clear the window to default background colour

	glColor3f(0.0f, 1.0f, 1.0f); // set RGB values of colour to draw

	glLineWidth(20.0f);

	/* DRAWING CODE BEGINS HERE, with glBegin(<primitive_type>); */
	// Bottom, y = -1, top, y = 1, left, x = -1, right, x = 1
	// Only specific commands can be used between glBegin() and glEnd()
	glBegin(GL_LINES); // draw lines between pairs of points

		glLineWidth(2.0f);
		glColor3f(1.0f, 0.0f, 0.0f); // set RGB values of colour to draw
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);

		glLineWidth(1.0f);

		glColor3f(0.0f, 1.0f, 1.0f); // set RGB values of colour to draw
		glVertex2f(0.0f, 0.7f); // 2nd startpoint
		glVertex2f(-0.7f, 0.0f); // 2nd endpoint

		glColor3f(0.0f, 0.0f, 0.5f);
		glVertex2f(-0.75f, 0.75f);
		glVertex2f(0.75f, -0.75f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.25f);
	glEnd();
	/* DRAWING CODE ENDS HERE */

	glFlush(); // force the output of any draw operations 
}


//
// ...every C/C++ program needs a main()
// 	argc is the number of command line arguments
//  argv[] is an array of null terminated strings of command line arguments
//      note that argv[0] is the program name
//
int main(int argc, char* argv[])
{
	/* OPENGL INITIALISATION BEGINS HERE */
		glutInit(&argc, argv); // we can pass certain X windows attributes to GLUT
	
		glutCreateWindow("Simple"); // a window of default size and position, with a given title
		glutDisplayFunc(display); // set a "display" or "redraw" callback
	/* OPENGL INITIALISATION ENDS HERE */

	// Do not expect to return from this function
	glutMainLoop(); // go into the main loop and wait for window events...

	return 0; // safe to return 0 to shell unless error
}
