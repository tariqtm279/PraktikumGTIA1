#include <gl/glut.h>


//Primitf Drawing
void Jendela(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//fungsi titk
void point(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    	glBegin(GL_POINTS);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glVertex3f(0.25, 0.25, 0.0);
    glEnd();
    glFlush();
}

//Membuat Garis
void Garis(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    	glColor3f(1.0f, 1.0f, 1.0f);
    	glVertex3f(0.00, 0.20, 0.0);
    	glVertex3f(0.00, -0.20, 0.0);
    glEnd();
    glFlush();
}

//Membuat Segitiga
void Segitiga(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.10, -0.10, 0.00);
    	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.10, -0.10, 0.00);
    	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.00, 0.10, 0.00);
    glEnd();
    glFlush();
}

void SegiEmpat(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-0.18, 0.18, 0.18, -0.18);
    glFlush();
}


int main(int argc, char*argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	
	//layar kosong
	//glutCreateWindow("biru"); glutDisplayFunc(Jendela);
	
	//Membuat Titik
	//glutCreateWindow("Titik"); glutDisplayFunc(point);
	
	//Membuat Garis
	//glutCreateWindow("Membuat Garis"); glutDisplayFunc(Garis);
    
    //Membuat Segitiga
	//glutCreateWindow("Membuat Segitiga"); glutDisplayFunc(Segitiga);
    
    //Membuat SegiEmpat
    glutCreateWindow("Segi Empat"); glutDisplayFunc(SegiEmpat);
    
    
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
