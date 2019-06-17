#include <GL/glut.h>
#include <cmath>
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);

    glLineWidth(1.0f);

    // CIRCLE CODE
    const float radius = 0.7f; // a given radius
	const float pi = atan(1) * 4; // define pi

	const size_t steps = 32; // how many steps once round the circle
	const float theta_step = 2 * pi / float(steps); // angle step in radians

	float theta = 0.0f;

    glBegin(GL_POLYGON);

        // however many times once round the circle
        for (size_t i = 0; i < steps; i++, theta += theta_step) 
        {
            float x = radius * cos(theta);
            float y = radius * sin(theta);

            glVertex2f(x, y);

            // debug to standard out
            std::cout << "x = " << x << ", y = " << y << std::endl;
        }

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Circle");

    glutDisplayFunc(display);

    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}