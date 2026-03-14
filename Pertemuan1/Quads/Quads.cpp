#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.2f, 0.2f);
        glVertex2f(-0.9f,  0.9f);
        glVertex2f(-0.1f,  0.9f);
        glVertex2f(-0.1f,  0.1f);
        glVertex2f(-0.9f,  0.1f);

        glColor3f(0.2f, 0.9f, 0.3f);
        glVertex2f( 0.1f,  0.9f);
        glVertex2f( 0.9f,  0.9f);
        glVertex2f( 0.9f,  0.1f);
        glVertex2f( 0.1f,  0.1f);

        glColor3f(1.0f, 0.9f, 0.0f);
        glVertex2f(-0.9f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
        glVertex2f(-0.1f, -0.9f);
        glVertex2f(-0.9f, -0.9f);

        glColor3f(0.7f, 0.2f, 1.0f);
        glVertex2f( 0.1f, -0.1f);
        glVertex2f( 0.9f, -0.1f);
        glVertex2f( 0.9f, -0.9f);
        glVertex2f( 0.1f, -0.9f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GL_QUADS - Banyak Kotak");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

