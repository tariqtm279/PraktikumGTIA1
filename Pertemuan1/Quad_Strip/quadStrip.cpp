#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.8f, 0.3f, 0.9f); 

    glBegin(GL_QUAD_STRIP);
        glVertex2f(-0.2f,  0.7f); 
        glVertex2f(-0.6f,  0.2f);
        glVertex2f( 0.2f,  0.7f); 
        glVertex2f( 0.6f,  0.2f);
        glVertex2f(-0.9f, -0.3f); 
        glVertex2f( 0.9f, -0.3f);  
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GL_QUAD_STRIP - Trapesium");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

