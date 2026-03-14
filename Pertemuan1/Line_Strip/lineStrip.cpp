#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(2.0);            

    glBegin(GL_LINE_STRIP);   
        glColor3f(1.0, 0.0, 0.0); 
        glVertex2f(-0.8, -0.5);   
        
        glColor3f(0.0, 1.0, 0.0); 
        glVertex2f(-0.4,  0.5);   
        
        glColor3f(0.0, 0.0, 1.0); 
        glVertex2f( 0.0, -0.5);   
        
        glColor3f(1.0, 1.0, 0.0); 
        glVertex2f( 0.4,  0.5);   
        
        glColor3f(1.0, 0.0, 1.0); 
        glVertex2f( 0.8, -0.5);   
    glEnd();

    glFlush(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Contoh GL_LINE_STRIP");
    glutInitWindowSize(600, 600);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

