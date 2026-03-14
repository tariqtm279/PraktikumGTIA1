#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f,  0.4f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.6f, -0.4f); 
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f( 0.0f,  0.4f);
        glColor3f(1.0f, 1.0f, 0.0f); glVertex2f( 0.0f, -0.4f);
        glColor3f(1.0f, 0.0f, 1.0f); glVertex2f( 0.6f,  0.4f);
        glColor3f(0.0f, 1.0f, 1.0f); glVertex2f( 0.6f, -0.4f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GL_TRIANGLE_STRIP - Warna");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

