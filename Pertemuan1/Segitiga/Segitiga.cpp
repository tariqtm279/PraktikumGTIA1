#include <GL/gl.h>
#include <GL/glut.h>

void Segitiga(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.1, -0.1, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1, -0.1, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0.1, 0);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0, -0.1, 0);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1920, 1080);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Membuat Segitiga");
    glutDisplayFunc(Segitiga);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
	
