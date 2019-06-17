#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stddef.h>

void draw_square()
{
	// in model coordinates centred at (0,0)
	static GLfloat vertex[4][2] =
		{
			{ -0.5f, -0.5f },
			{ -0.5f,  0.5f },
			{  0.5f,  0.5f },
            {  0.5f, -0.5f }
		};

	glBegin(GL_LINE_LOOP);
		for (size_t i = 0; i < 4; i++)
			glVertex2fv(vertex[i]);  // Takes pointer to array of size 2
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	glLineWidth(2.0f);

	// work on MODELVIEW matrix stack, for translating models about the world coordinates
	glMatrixMode(GL_MODELVIEW);

    for (int i = 0; i < 5; i++) {
        glPushMatrix();  // Make new matrix to play with

            static GLfloat scale_factor = 200.0f;
            GLfloat rand_angle = float(drand48() * 360.0f);
            GLfloat rand_x = scale_factor + float(drand48() * (1000.0f - (2.0f * scale_factor)));
            GLfloat rand_y = scale_factor + float(drand48() * (1000.0f - (2.0f * scale_factor)));

            glTranslatef(rand_x, rand_y, 0.0f);
            glScalef(scale_factor, scale_factor, 1.0f);
            glRotatef(rand_angle, 0.0f, 0.0f, 1.0f);

            draw_square();

        glPopMatrix();  // Get rid of it

    }

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
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Rotate");
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
