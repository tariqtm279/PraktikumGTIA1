#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265f

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.8f, 0.3f); 
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= 6; i++) {
            float angle = i * (2 * PI / 6);
            glVertex2f(cos(angle) * 0.5f, sin(angle) * 0.5f);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hexagon - GL_TRIANGLE_FAN");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

