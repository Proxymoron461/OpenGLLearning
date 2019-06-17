#include <GL/glut.h>
#include <cmath>

void display() {
    float func_x = -1.0f;
    int steps = 320;
    float change_x = 2.0f / float(steps);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= steps; i++, func_x += change_x)
            glVertex2f(func_x, sin(3.0f * func_x));
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
