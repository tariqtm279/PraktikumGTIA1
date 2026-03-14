#include <GL/gl.h>
#include <GL/glut.h>

void Garis(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.00, 0.20, 0.0);
    glVertex3f(0.00, -0.20, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1920, 1080);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Membuat Garis");
    glutDisplayFunc(Garis);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}

