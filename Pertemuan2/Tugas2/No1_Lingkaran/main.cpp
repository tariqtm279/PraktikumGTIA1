#include <gl/glut.h>
#include <math.h>

#define PI 3.1415926535898

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); 
    
    glBegin(GL_LINE_LOOP);
    int circle_points = 200;
    float angle;

    for(int i = 0; i < circle_points; i++)
    {
        angle = 2 * PI * i / circle_points;
        glVertex2f(cos(angle), sin(angle));
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Lingkaran Arsy Thariq Munawar 24060124120009");
    
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
