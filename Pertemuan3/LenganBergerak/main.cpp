#include <GL/glut.h>


static int angShoulder = 0, angElbow = 0;
static int angWristUD = 0, angWristSide = 0;  

/* Ibu jari (jempol): 3 sendi */
static int angThumbBase = 0, angThumbMid = 0, angThumbTip = 0;

/* Telunjuk: 3 sendi */
static int angIndexBase = 0, angIndexMid = 0, angIndexTip = 0;

/* Tengah: 3 sendi */
static int angMidBase = 0, angMidMid = 0, angMidTip = 0;

/* Manis: 3 sendi */
static int angRingBase = 0, angRingMid = 0, angRingTip = 0;

/* Kelingking: 3 sendi */
static int angPinkyBase = 0, angPinkyMid = 0, angPinkyTip = 0;


/* Clamp angle agar selalu [0, maxVal) */
static int clampAngle(int val, int maxVal) {
    val = val % maxVal;
    if (val < 0) val += maxVal;
    return val;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void drawFinger(float segLen, float segW,
                int bAngle, int mAngle, int tAngle,
                int isThumb) {
    float ax = isThumb ? 0.0f : 0.0f;
    float ay = isThumb ? 0.0f : 1.0f;
    float az = isThumb ? 1.0f : 0.0f;

    // Ruas Pangkal
    glRotatef((GLfloat)bAngle, ax, ay, az);
    glPushMatrix();
        glTranslatef(segLen / 6.0f, 0.0f, 0.0f);
        glScalef(segLen / 3.0f, segW, segW);
        glutWireCube(1.0);
    glPopMatrix();

    // Ruas Tengah 
    glTranslatef(segLen / 3.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)mAngle, ax, ay, az);
    glPushMatrix();
        glTranslatef(segLen / 6.0f, 0.0f, 0.0f);
        glScalef(segLen / 3.0f, segW * 0.9f, segW * 0.9f);
        glutWireCube(1.0);
    glPopMatrix();

    // Ruas Ujung
    glTranslatef(segLen / 3.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)tAngle, ax, ay, az);
    glPushMatrix();
        glTranslatef(segLen / 6.0f, 0.0f, 0.0f);
        glScalef(segLen / 3.0f, segW * 0.8f, segW * 0.8f);
        glutWireCube(1.0);
    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Bahu
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)angShoulder, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);

    // Lengan Atas
    glPushMatrix();
        glScalef(2.0f, 0.4f, 1.0f);
        glutWireCube(1.0);
    glPopMatrix();

    // Siku
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)angElbow, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);

    // Lengan Bawah 
    glPushMatrix();
        glScalef(2.0f, 0.4f, 1.0f);
        glutWireCube(1.0);
    glPopMatrix();

    // Pergelangan Tangan
    glTranslatef(1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)angWristUD,   0.0f, 0.0f, 1.0f); // atas-bawah
    glRotatef((GLfloat)angWristSide, 0.0f, 1.0f, 0.0f); // ke samping
    glTranslatef(0.2f, 0.0f, 0.0f);

    // Balok Pergelangan
    glPushMatrix();
        glScalef(0.3f, 0.3f, 0.3f);
        glutWireCube(1.0);
    glPopMatrix();

    // Telapak Tangan
    glTranslatef(0.5f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(0.7f, 0.7f, 0.3f);
        glutWireCube(1.0);
    glPopMatrix();

    // Ibu Jari
    glPushMatrix();
        glTranslatef(-0.05f, -0.3f, 0.2f);
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-60.0f, 0.0f, 0.0f, 1.0f);
        drawFinger(0.5f, 0.18f,
                   angThumbBase, angThumbMid, angThumbTip, 1);
    glPopMatrix();

    // Kelingking
    glPushMatrix();
        glTranslatef(0.35f, 0.27f, 0.0f);
        drawFinger(0.45f, 0.12f,
                   angPinkyBase, angPinkyMid, angPinkyTip, 0);
    glPopMatrix();

    // Manis
    glPushMatrix();
        glTranslatef(0.35f, 0.10f, 0.0f);
        drawFinger(0.60f, 0.14f,
                   angRingBase, angRingMid, angRingTip, 0);
    glPopMatrix();

    // Tengah
    glPushMatrix();
        glTranslatef(0.35f, -0.10f, 0.0f);
        drawFinger(0.65f, 0.15f,
                   angMidBase, angMidMid, angMidTip, 0);
    glPopMatrix();

    // Telunjuk
    glPushMatrix();
        glTranslatef(0.35f, -0.30f, 0.0f);
        drawFinger(0.60f, 0.14f,
                   angIndexBase, angIndexMid, angIndexTip, 0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -5.0f);
}


void keyboard(unsigned char key, int x, int y) {
    int step = 5;
    switch (key) {

        // Bahu 
        case 's': angShoulder = clampAngle(angShoulder + step, 360); break;
        case 'S': angShoulder = clampAngle(angShoulder - step, 360); break;

        // Siku
        case 'e': angElbow = clampAngle(angElbow + step, 360); break;
        case 'E': angElbow = clampAngle(angElbow - step, 360); break;

        // Pergelangan - atas/bawah 
        case 'w': angWristUD = clampAngle(angWristUD + step, 360); break;
        case 'W': angWristUD = clampAngle(angWristUD - step, 360); break;

        // Pergelangan - samping 
        case 'a': angWristSide = clampAngle(angWristSide + step, 360); break;
        case 'A': angWristSide = clampAngle(angWristSide - step, 360); break;

        // Ibu Jari 
        case '1': angThumbBase = clampAngle(angThumbBase + step, 90); break;
        case '!': angThumbBase = clampAngle(angThumbBase - step, 90); break;
        case 'q': angThumbMid  = clampAngle(angThumbMid  + step, 90); break;
        case 'Q': angThumbMid  = clampAngle(angThumbMid  - step, 90); break;
        case 'z': angThumbTip  = clampAngle(angThumbTip  + step, 90); break;
        case 'Z': angThumbTip  = clampAngle(angThumbTip  - step, 90); break;

        // Telunjuk 
        case '2': angIndexBase = clampAngle(angIndexBase + step, 90); break;
        case '@': angIndexBase = clampAngle(angIndexBase - step, 90); break;
        case 'i': angIndexMid  = clampAngle(angIndexMid  + step, 90); break;
        case 'I': angIndexMid  = clampAngle(angIndexMid  - step, 90); break;
        case 'x': angIndexTip  = clampAngle(angIndexTip  + step, 90); break;
        case 'X': angIndexTip  = clampAngle(angIndexTip  - step, 90); break;

        // Tengah
        case '3': angMidBase = clampAngle(angMidBase + step, 90); break;
        case '#': angMidBase = clampAngle(angMidBase - step, 90); break;
        case 'm': angMidMid  = clampAngle(angMidMid  + step, 90); break;
        case 'M': angMidMid  = clampAngle(angMidMid  - step, 90); break;
        case 'c': angMidTip  = clampAngle(angMidTip  + step, 90); break;
        case 'C': angMidTip  = clampAngle(angMidTip  - step, 90); break;

        // Manis 
        case '4': angRingBase = clampAngle(angRingBase + step, 90); break;
        case '$': angRingBase = clampAngle(angRingBase - step, 90); break;
        case 'r': angRingMid  = clampAngle(angRingMid  + step, 90); break;
        case 'R': angRingMid  = clampAngle(angRingMid  - step, 90); break;
        case 'v': angRingTip  = clampAngle(angRingTip  + step, 90); break;
        case 'V': angRingTip  = clampAngle(angRingTip  - step, 90); break;

        // Kelingking
        case '5': angPinkyBase = clampAngle(angPinkyBase + step, 90); break;
        case '%': angPinkyBase = clampAngle(angPinkyBase - step, 90); break;
        case 't': angPinkyMid  = clampAngle(angPinkyMid  + step, 90); break;
        case 'T': angPinkyMid  = clampAngle(angPinkyMid  - step, 90); break;
        case 'b': angPinkyTip  = clampAngle(angPinkyTip  + step, 90); break;
        case 'B': angPinkyTip  = clampAngle(angPinkyTip  - step, 90); break;

        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 650);
    glutInitWindowPosition(150, 80);
    glutCreateWindow("Lengan Bergeruy");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
