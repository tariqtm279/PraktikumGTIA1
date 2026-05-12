/*
 * ============================================================
 *  MOBIL 3D - OpenGL dengan Depth & Lighting
 * ============================================================
 *  Kontrol:
 *    Panah Kiri/Kanan  : Putar kamera
 *    Panah Atas/Bawah  : Maju / Mundur
 *    W / S             : Naik / Turun kamera
 *    R                 : Putar objek mobil (auto-rotate toggle)
 *    ESC               : Keluar
 *
 *  Struktur mobil terdiri dari panel-panel (GL_QUADS) yang
 *  dirotasi & ditranslasi untuk membentuk rangka badan mobil,
 *  kap, atap, spoiler, dan 4 roda silinder agar Depth & Lighting
 *  bekerja dengan baik.
 * ============================================================
 */

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979f

/* -- Kamera ------------------------------------------------- */
float angle    = 0.0f, deltaAngle = 0.0f;
float camX     = 0.0f, camY = 3.5f, camZ = 18.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int   deltaMove = 0, deltaY = 0;
int   winW = 800, winH = 600;
float ratio;

/* -- Rotasi mobil ------------------------------------------- */
float carRot    = 0.0f;
int   autoRotate = 0;

/* =============================================================
 *  KAMERA
 * ============================================================= */
void updateCamera(void) {
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              camX + lx, camY + ly, camZ + lz,
              0.0f, 1.0f, 0.0f);
}

void orientMe(float ang) {
    lx =  sinf(ang);
    lz = -cosf(ang);
    updateCamera();
}

void moveMeFlat(int i) {
    camX += i * lx * 0.15f;
    camZ += i * lz * 0.15f;
    updateCamera();
}

void moveMeUp(int i) {
    camY += i * 0.15f;
    updateCamera();
}

/* =============================================================
 *  GRID LANTAI
 * ============================================================= */
void Grid(void) {
    int i;
    const float RANGE = 50.0f, GAP = 2.0f;
    glDisable(GL_LIGHTING);
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_LINES);
    for (i = (int)(-RANGE); i <= (int)RANGE; i += (int)GAP) {
        glVertex3f((float)i, 0.0f, -RANGE);
        glVertex3f((float)i, 0.0f,  RANGE);
        glVertex3f(-RANGE, 0.0f, (float)i);
        glVertex3f( RANGE, 0.0f, (float)i);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

/* =============================================================
 *  HELPER – PANEL QUAD (satu sisi kotak)
 *  Menggambar 1 panel berukuran (w x h) di bidang XY,
 *  terpusat di origin. Normal menghadap +Z.
 * ============================================================= */
static void drawPanel(float w, float h) {
    float hw = w * 0.5f, hh = h * 0.5f;
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-hw, -hh, 0.0f);
        glVertex3f( hw, -hh, 0.0f);
        glVertex3f( hw,  hh, 0.0f);
        glVertex3f(-hw,  hh, 0.0f);
    glEnd();
}

/* =============================================================
 *  HELPER – KOTAK (box) dari 6 panel
 *  sx, sy, sz = ukuran setengah sisi (half-extents)
 * ============================================================= */
static void drawBox(float sx, float sy, float sz) {
    /* Depan */
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, sz);
        drawPanel(sx*2, sy*2);
    glPopMatrix();
    /* Belakang */
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -sz);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        drawPanel(sx*2, sy*2);
    glPopMatrix();
    /* Kiri */
    glPushMatrix();
        glTranslatef(-sx, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawPanel(sz*2, sy*2);
    glPopMatrix();
    /* Kanan */
    glPushMatrix();
        glTranslatef(sx, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        drawPanel(sz*2, sy*2);
    glPopMatrix();
    /* Atas */
    glPushMatrix();
        glTranslatef(0.0f, sy, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        drawPanel(sx*2, sz*2);
    glPopMatrix();
    /* Bawah */
    glPushMatrix();
        glTranslatef(0.0f, -sy, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        drawPanel(sx*2, sz*2);
    glPopMatrix();
}

/* =============================================================
 *  HELPER – SILINDER (untuk roda)
 *  radius, tinggi (half-height), potongan
 * ============================================================= */
static void drawCylinder(float r, float halfH, int slices) {
    int i;
    float step = 2.0f * PI / slices;

    /* Tutup depan */
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, halfH);
        for (i = 0; i <= slices; i++) {
            float a = i * step;
            glVertex3f(r * cosf(a), r * sinf(a), halfH);
        }
    glEnd();
    /* Tutup belakang */
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, -halfH);
        for (i = slices; i >= 0; i--) {
            float a = i * step;
            glVertex3f(r * cosf(a), r * sinf(a), -halfH);
        }
    glEnd();
    /* Selimut */
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i <= slices; i++) {
            float a = i * step;
            float cx = cosf(a), cy = sinf(a);
            glNormal3f(cx, cy, 0.0f);
            glVertex3f(r*cx, r*cy,  halfH);
            glVertex3f(r*cx, r*cy, -halfH);
        }
    glEnd();
}

/* =============================================================
 *  RODA  (4 buah)
 * ============================================================= */
static void setColorRoda(void) {
    GLfloat amb[]  = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat diff[] = {0.20f, 0.20f, 0.20f, 1.0f};
    GLfloat spec[] = {0.6f,  0.6f,  0.6f,  1.0f};
    GLfloat shi[]  = {60.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shi);
    glColor3f(0.15f, 0.15f, 0.15f);
}

static void drawRoda(void) {
    setColorRoda();
    /* Roda = silinder, sumbu sejajar Z, lalu dirotasi agar tegak lurus sumbu X */
    glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.65f, 0.35f, 24);
    glPopMatrix();
}

/* =============================================================
 *  MATERIAL WARNA MOBIL
 * ============================================================= */
static void matBodyRed(void) {
    GLfloat amb[]  = {0.25f, 0.03f, 0.03f, 1.0f};
    GLfloat diff[] = {0.80f, 0.10f, 0.10f, 1.0f};
    GLfloat spec[] = {1.00f, 0.80f, 0.80f, 1.0f};
    GLfloat shi[]  = {96.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shi);
    glColor3f(0.85f, 0.10f, 0.10f);
}

static void matCabin(void) {
    GLfloat amb[]  = {0.05f, 0.05f, 0.15f, 1.0f};
    GLfloat diff[] = {0.15f, 0.20f, 0.50f, 1.0f};
    GLfloat spec[] = {0.90f, 0.90f, 1.00f, 1.0f};
    GLfloat shi[]  = {110.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shi);
    glColor3f(0.20f, 0.25f, 0.60f);
}

static void matGlass(void) {
    GLfloat amb[]  = {0.05f, 0.10f, 0.10f, 1.0f};
    GLfloat diff[] = {0.20f, 0.45f, 0.50f, 1.0f};
    GLfloat spec[] = {1.00f, 1.00f, 1.00f, 1.0f};
    GLfloat shi[]  = {128.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shi);
    glColor3f(0.40f, 0.80f, 0.85f);
}

static void matSpoiler(void) {
    GLfloat amb[]  = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat diff[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat spec[] = {0.80f, 0.80f, 0.80f, 1.0f};
    GLfloat shi[]  = {80.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shi);
    glColor3f(0.12f, 0.12f, 0.12f);
}

/* =============================================================
 *  MOBIL UTAMA
 *  Sistem koordinat: Y ke atas, Z ke depan mobil
 *  Origin mobil di tengah bawah badan (di atas lantai).
 *
 *  Bagian-bagian:
 *  1. Badan bawah (chassis) – kotak lebar, rendah
 *  2. Kap depan (hood) – kotak miring ke depan
 *  3. Kabin      – kotak lebih kecil di atas badan
 *  4. Kaca depan – panel miring
 *  5. Kaca belakang – panel miring
 *  6. Spoiler belakang
 *  7. Empat roda
 * ============================================================= */
void drawMobil(void) {

    /* -- 1. BADAN / CHASSIS ----------------------------------- */
    matBodyRed();
    glPushMatrix();
        /* Badan utama tengah  (lebar 4.4, tinggi 1.0, panjang 8.0) */
        glTranslatef(0.0f, 0.70f, 0.0f);
        drawBox(2.2f, 0.50f, 4.0f);
    glPopMatrix();

    /* -- 2. KAP DEPAN (hood) ---------------------------------- */
    matBodyRed();
    glPushMatrix();
        /* Pindah ke depan badan, sedikit naik, lalu miring ke bawah */
        glTranslatef(0.0f, 1.05f, 3.2f);
        glRotatef(-12.0f, 1.0f, 0.0f, 0.0f);
        drawBox(2.2f, 0.12f, 1.30f);
    glPopMatrix();

    /* -- 3. KABIN --------------------------------------------- */
    matCabin();
    glPushMatrix();
        /* Di atas badan, agak ke belakang */
        glTranslatef(0.0f, 1.75f, -0.4f);
        drawBox(1.90f, 0.55f, 2.30f);
    glPopMatrix();

    /* -- 4. KACA DEPAN ---------------------------------------- */
    matGlass();
    glPushMatrix();
        /* Posisi di antara kap dan kabin, miring ~55° */
        glTranslatef(0.0f, 1.45f, 1.95f);
        glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
        drawPanel(3.70f, 0.85f);
    glPopMatrix();

    /* -- 5. KACA BELAKANG ------------------------------------- */
    matGlass();
    glPushMatrix();
        glTranslatef(0.0f, 1.45f, -2.75f);
        glRotatef(55.0f, 1.0f, 0.0f, 0.0f);
        drawPanel(3.70f, 0.80f);
    glPopMatrix();

    /* -- 6. KACA SAMPING KIRI --------------------------------- */
    matGlass();
    glPushMatrix();
        glTranslatef(-1.91f, 1.75f, -0.4f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawPanel(4.50f, 0.90f);
    glPopMatrix();

    /* -- 6b. KACA SAMPING KANAN ------------------------------- */
    matGlass();
    glPushMatrix();
        glTranslatef(1.91f, 1.75f, -0.4f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        drawPanel(4.50f, 0.90f);
    glPopMatrix();

    /* -- 7. BAGASI BELAKANG (trunk) --------------------------- */
    matBodyRed();
    glPushMatrix();
        glTranslatef(0.0f, 1.10f, -3.7f);
        drawBox(2.2f, 0.35f, 0.50f);
    glPopMatrix();

    /* -- 8. SPOILER ------------------------------------------- */
    matSpoiler();
    glPushMatrix();
        glTranslatef(0.0f, 1.65f, -4.10f);
        drawBox(2.0f, 0.10f, 0.20f);
    glPopMatrix();
    /* tiang kiri spoiler */
    glPushMatrix();
        glTranslatef(-0.80f, 1.45f, -4.10f);
        drawBox(0.08f, 0.25f, 0.08f);
    glPopMatrix();
    /* tiang kanan spoiler */
    glPushMatrix();
        glTranslatef(0.80f, 1.45f, -4.10f);
        drawBox(0.08f, 0.25f, 0.08f);
    glPopMatrix();

    /* -- 9. BEMPER DEPAN -------------------------------------- */
    matSpoiler();
    glPushMatrix();
        glTranslatef(0.0f, 0.35f, 4.30f);
        drawBox(2.0f, 0.22f, 0.20f);
    glPopMatrix();

    /* -- 10. BEMPER BELAKANG ---------------------------------- */
    matSpoiler();
    glPushMatrix();
        glTranslatef(0.0f, 0.35f, -4.30f);
        drawBox(2.0f, 0.22f, 0.20f);
    glPopMatrix();

    /* -- 11. RODA --------------------------------------------- */
    /* Kiri Depan */
    glPushMatrix();
        glTranslatef(-2.35f, 0.65f, 2.60f);
        drawRoda();
    glPopMatrix();
    /* Kanan Depan */
    glPushMatrix();
        glTranslatef(2.35f, 0.65f, 2.60f);
        drawRoda();
    glPopMatrix();
    /* Kiri Belakang */
    glPushMatrix();
        glTranslatef(-2.35f, 0.65f, -2.60f);
        drawRoda();
    glPopMatrix();
    /* Kanan Belakang */
    glPushMatrix();
        glTranslatef(2.35f, 0.65f, -2.60f);
        drawRoda();
    glPopMatrix();
}

/* =============================================================
 *  DISPLAY
 * ============================================================= */
void display(void) {
    if (deltaMove)  moveMeFlat(deltaMove);
    if (deltaY)     moveMeUp(deltaY);
    if (deltaAngle) { angle += deltaAngle; orientMe(angle); }
    if (autoRotate) carRot += 0.4f;

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Grid();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(carRot, 0.0f, 1.0f, 0.0f);
        drawMobil();
    glPopMatrix();

    /* HUD teks */
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.5f);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, winW, 0, winH);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glRasterPos2i(10, winH - 20);
            const char *msg = "Panah: gerak kamera | R: rotasi mobil | W/S: naik/turun";
            for (const char *c = msg; *c; c++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

/* =============================================================
 *  INPUT
 * ============================================================= */
void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  deltaAngle = -0.015f; break;
        case GLUT_KEY_RIGHT: deltaAngle =  0.015f; break;
        case GLUT_KEY_UP:    deltaMove  =  1;      break;
        case GLUT_KEY_DOWN:  deltaMove  = -1;      break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  if (deltaAngle < 0) deltaAngle = 0; break;
        case GLUT_KEY_RIGHT: if (deltaAngle > 0) deltaAngle = 0; break;
        case GLUT_KEY_UP:    if (deltaMove  > 0) deltaMove  = 0; break;
        case GLUT_KEY_DOWN:  if (deltaMove  < 0) deltaMove  = 0; break;
    }
}

void normalKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'W': deltaY =  1; break;
        case 's': case 'S': deltaY = -1; break;
        case 'r': case 'R': autoRotate = !autoRotate; break;
        case 27: exit(0);
    }
}

void normalKeyUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'W': if (deltaY > 0) deltaY = 0; break;
        case 's': case 'S': if (deltaY < 0) deltaY = 0; break;
    }
}

/* =============================================================
 *  RESHAPE
 * ============================================================= */
void reshape(int w, int h) {
    if (h == 0) h = 1;
    winW = w; winH = h;
    ratio = (float)w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              camX + lx, camY + ly, camZ + lz,
              0.0f, 1.0f, 0.0f);
}

/* =============================================================
 *  LIGHTING SETUP
 * ============================================================= */
void initLighting(void) {
    /* Cahaya utama – dari atas kanan depan */
    const GLfloat amb0[]  = {0.30f, 0.30f, 0.35f, 1.0f};
    const GLfloat diff0[] = {1.00f, 0.95f, 0.90f, 1.0f};
    const GLfloat spec0[] = {1.00f, 1.00f, 1.00f, 1.0f};
    const GLfloat pos0[]  = {8.0f, 20.0f, 12.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);

    /* Cahaya pengisi – dari bawah kiri belakang (fill light) */
    const GLfloat amb1[]  = {0.05f, 0.05f, 0.10f, 1.0f};
    const GLfloat diff1[] = {0.25f, 0.28f, 0.40f, 1.0f};
    const GLfloat spec1[] = {0.10f, 0.10f, 0.20f, 1.0f};
    const GLfloat pos1[]  = {-10.0f, 5.0f, -8.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT,  amb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diff1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
}

/* =============================================================
 *  MAIN
 * ============================================================= */
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil 3D - Depth & Lighting");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    initLighting();

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutKeyboardFunc(normalKey);
    glutKeyboardUpFunc(normalKeyUp);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
