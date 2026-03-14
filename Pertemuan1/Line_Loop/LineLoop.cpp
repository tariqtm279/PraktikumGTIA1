#include <GL/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 8; i++) {
            float angle = i * (2 * 3.14159f / 8);
            glVertex2f(cos(angle) * 0.5f, sin(angle) * 0.5f);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Contoh GL_LINE_LOOP");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

