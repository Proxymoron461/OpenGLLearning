#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stddef.h>
#include <iostream>

class Square {
public:
    GLfloat x;
    GLfloat y;
    GLfloat x_velocity;
    GLfloat y_velocity;
    GLfloat scale_factor;

    Square() {
        x = 500.0f;
        y = 500.0f;
        x_velocity = 5.0f;
        y_velocity = 5.0f;
        width = 10.0f;
        half_width = width / 2.0f;
        scale_factor = 250.0f;
    }

    // Needs to be with GL_LINE_LOOP
    static GLfloat vertices[4][2] = {
        { -0.5f, -0.5f },
        { -0.5f,  0.5f },
        {  0.5f,  0.5f },
        {  0.5f, -0.5f }
    };

    GLfloat getLeft() { return x - half_width; }
    GLfloat getRight() { return x + half_width; }
    GLfloat getBottom() { return y - half_width; }
    GLfloat getTop() { return y + half_width; }

    void move() {
        x += x_velocity;
        y += y_velocity;
    }

    void draw() {
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 4; i++)
                glVertex2fv(vertices[i]);
        glEnd();
    }

private:
    GLfloat width;
    GLfloat half_width;
};

struct World {
    GLfloat x_min;
    GLfloat x_max;
    GLfloat y_min;
    GLfloat y_max;
};

// Create a square object
Square square();

// Create a world struct
struct World world;
world.x_min = 0.0f;
world.x_max = 1000.0f;
world.y_min = 0.0f;
world.y_max = 1000.0f;

void visibility(int vis) {
    if (vis == GLUT_VISIBLE) {
        std::cerr << "visible" << std::endl;
    } else {
        std::cerr << "not visible" << std::endl;
    }
}

void idle() {
    // Check collisions
    if (square.getRight() + square.x_velocity >= world.x_max
        || square.getLeft() square.x_velocity <= world.x_min) {
            square.x_velocity *= -1.0f;
    }

    if (square.getTop() + square.y_velocity >= world.y_max
        || square.getBottom() + square.y_velocity <= world.y_min) {
            square.y_velocity *= -1.0f;
    }

    // Update positions + draw when next possible
    square.move();
    glutPostRedisplay();
}

void display() {

    // Clear the display
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glTranslatef(square.x_position, square.y_position, 0.0f);
        glScalef(square.scale_factor, square.scale_factor, 1.0f);

        // Draw the square
        square.draw();

    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    // Setup glut, OpenGL, etc.

    // Set up world co-ordinates
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(world.x_min, world.x_max, world.y_min, world.y_max);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char* argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bouncing square");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutVisibilityFunc(visibility);

    init();
}
