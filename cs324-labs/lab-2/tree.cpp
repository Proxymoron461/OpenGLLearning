#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stddef.h>
#include <cmath>

void draw_triangle(GLfloat scale_factor, GLfloat x, GLfloat y)
{
    // in model coordinates centred at (0,0)
    static GLfloat vertex[3][2] =
    {
        { -1.0f, -1.0f },
        {  1.0f, -1.0f },
        {  0.0f,  1.0f }
    };

    glPushMatrix();  // get new matrix to play with

        glTranslatef(x, y, 0.0f);  // Centre the triangle at (x,y)
        glScalef(scale_factor, scale_factor, 1.0f);
        glRotatef(float(drand48() * 360), 0.0f, 0.0f, 1.0f);

    	glBegin(GL_LINE_LOOP);
            // Draw triangle
    		for (size_t i = 0; i < 3; i++)
    			glVertex2fv(vertex[i]);
    	glEnd();
    glPopMatrix();
}

void draw_line_pair(GLfloat scale_factor, GLfloat x, GLfloat y) {
    // in model coordinates centred at (0, 0)
    static GLfloat lines[3][2] =
    {
        { -1.0f, 0.3f },
        {  0.0f, 0.0f },
        {  1.0f, 0.3f }
    };

    glPushMatrix();  // get new matrix to play with
        glTranslatef(x, y, 0.0f);
        glScalef(scale_factor, scale_factor, 1.0f);
        glRotatef(float(asin(x / y)), 0.0f, 0.0f, 1.0f);
        //glRotatef(360.0f - float(asin(x / y)), 0.0f, 0.0f, 1.0f);

        glBegin(GL_LINE_STRIP);
            for (int i = 0; i < 3; i++)
                glVertex2fv(lines[i]);
        glEnd();

    glPopMatrix();

}

void draw_triangles_along_line(GLfloat start_x, GLfloat start_y, GLfloat end_x, GLfloat end_y) {
    // TODO
}

void draw_line_pair_along_line(GLfloat start_x, GLfloat start_y, GLfloat end_x, GLfloat end_y) {
    // TODO
}

float getLengthOfLine(GLfloat start_x, GLfloat start_y, GLfloat end_x, GLfloat end_y) {
    // TODO ??
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	glLineWidth(2.0f);

	// work on MODELVIEW matrix stack
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

		// translate it to where we want it
		glTranslatef(500.0f, 500.0f, 0.0f);

        int depth = 5;

		for (size_t i = 0; i < 5; i++) {
            // TODO
        }

	glPopMatrix(); // done with stack

	glutSwapBuffers();
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
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Fractal tree");
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
