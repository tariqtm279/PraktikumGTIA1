#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.9f, 0.75f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.09f, 0.90f);
        glVertex2f( 0.09f, 0.90f);
        glVertex2f( 0.09f, 0.72f);
        glVertex2f(-0.09f, 0.72f);
    glEnd();

    glColor3f(0.3f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.09f, 0.70f);
        glVertex2f( 0.09f, 0.70f);
        glVertex2f( 0.09f, 0.52f);
        glVertex2f(-0.09f, 0.52f);
    glEnd();

    glColor3f(0.3f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.09f, 0.50f);
        glVertex2f( 0.09f, 0.50f);
        glVertex2f( 0.09f, 0.32f);
        glVertex2f(-0.09f, 0.32f);
    glEnd();

    glColor3f(0.3f, 0.8f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.29f, 0.70f);
        glVertex2f(-0.11f, 0.70f);
        glVertex2f(-0.11f, 0.52f);
        glVertex2f(-0.29f, 0.52f);
    glEnd();

    glColor3f(0.3f, 0.8f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.29f, 0.50f);
        glVertex2f(-0.11f, 0.50f);
        glVertex2f(-0.11f, 0.32f);
        glVertex2f(-0.29f, 0.32f);
    glEnd();

    glColor3f(0.3f, 0.8f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f( 0.11f, 0.70f);
        glVertex2f( 0.29f, 0.70f);
        glVertex2f( 0.29f, 0.52f);
        glVertex2f( 0.11f, 0.52f);
    glEnd();

    glColor3f(0.3f, 0.8f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f( 0.11f, 0.50f);
        glVertex2f( 0.29f, 0.50f);
        glVertex2f( 0.29f, 0.32f);
        glVertex2f( 0.11f, 0.32f);
    glEnd();

    glColor3f(0.9f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.19f, 0.30f);
        glVertex2f(-0.01f, 0.30f);
        glVertex2f(-0.01f, 0.12f);
        glVertex2f(-0.19f, 0.12f);
    glEnd();

    glColor3f(0.9f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.19f, 0.10f);
        glVertex2f(-0.01f, 0.10f);
        glVertex2f(-0.01f, -0.08f);
        glVertex2f(-0.19f, -0.08f);
    glEnd();

    glColor3f(0.9f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f( 0.01f, 0.30f);
        glVertex2f( 0.19f, 0.30f);
        glVertex2f( 0.19f, 0.12f);
        glVertex2f( 0.01f, 0.12f);
    glEnd();

    glColor3f(0.9f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f( 0.01f, 0.10f);
        glVertex2f( 0.19f, 0.10f);
        glVertex2f( 0.19f, -0.08f);
        glVertex2f( 0.01f, -0.08f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 700);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Kerangka Manusia");
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

