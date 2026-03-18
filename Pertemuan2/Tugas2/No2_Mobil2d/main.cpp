#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265f

void col(float r,float g,float b){glColor3f(r,g,b);}
void col4(float r,float g,float b,float a){glColor4f(r,g,b,a);}

void circle(float cx,float cy,float r,int n){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for(int i=0;i<=n;i++){float a=2*PI*i/n;glVertex2f(cx+cosf(a)*r,cy+sinf(a)*r);}
    glEnd();
}
void ellipse(float cx,float cy,float rx,float ry,int n){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for(int i=0;i<=n;i++){float a=2*PI*i/n;glVertex2f(cx+cosf(a)*rx,cy+sinf(a)*ry);}
    glEnd();
}
void circleOut(float cx,float cy,float r,int n){
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++){float a=2*PI*i/n;glVertex2f(cx+cosf(a)*r,cy+sinf(a)*r);}
    glEnd();
}


// BACKGROUND 
void drawBackground(){
    // Langit atas gelap
    glBegin(GL_QUADS);
        col(0.03f,0.05f,0.12f); glVertex2f(0,600); glVertex2f(800,600);
        col(0.05f,0.12f,0.22f); glVertex2f(800,360); glVertex2f(0,360);
    glEnd();
    // Horizon strip
    glBegin(GL_QUADS);
        col(0.05f,0.12f,0.22f); glVertex2f(0,360); glVertex2f(800,360);
        col(0.07f,0.18f,0.28f); glVertex2f(800,320); glVertex2f(0,320);
    glEnd();

    // Bintang
    float stars[][2]={{55,555},{140,510},{235,570},{345,530},{460,558},
                      {540,518},{630,545},{720,510},{780,540},{80,470},
                      {180,445},{320,460},{480,440},{640,430},{750,460},{30,500}};
    for(int i=0;i<16;i++){
        float b=0.55f+(i%3)*0.15f;
        col(b,b*0.95f,1.0f);
        circle(stars[i][0],stars[i][1],1.0f+(i%2)*0.8f,6);
    }

    // Bulan — putih keabu, kawah
    // Halo
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.80f,0.85f,0.92f,0.07f); circle(680,530,58,50);
    col4(0.82f,0.87f,0.94f,0.13f); circle(680,530,48,50);
    glDisable(GL_BLEND);
    col(0.80f,0.84f,0.89f); circle(680,530,40,60);
    // Iluminasi kanan
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.94f,0.96f,1.00f,0.28f);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(690,530);
    for(int m=0;m<=30;m++){float a=-1.57f+3.14f*m/30.0f;glVertex2f(690+cosf(a)*40,530+sinf(a)*40);}
    glEnd();
    // Bayangan kiri
    col4(0.38f,0.42f,0.50f,0.22f);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(670,530);
    for(int m=0;m<=30;m++){float a=1.57f+3.14f*m/30.0f;glVertex2f(670+cosf(a)*40,530+sinf(a)*40);}
    glEnd();
    glDisable(GL_BLEND);
    // Kawah
    col(0.68f,0.72f,0.77f); circle(668,538,8,16); col(0.76f,0.80f,0.85f); circle(668,538,6,16);
    col(0.66f,0.70f,0.75f); circle(688,520,5,14); col(0.74f,0.78f,0.83f); circle(688,520,4,14);
    col(0.68f,0.72f,0.77f); circle(674,518,3,12); col(0.70f,0.74f,0.79f); circle(690,534,4,12);

    // Awan kiri
    col(0.48f,0.54f,0.62f);
    circle(62,490,38,28); circle(104,504,48,28); circle(150,492,35,28);
    col(0.60f,0.67f,0.76f);
    circle(85,505,30,24); circle(128,515,38,24); circle(154,500,26,24);
    col(0.74f,0.80f,0.86f); circle(108,510,20,20); circle(138,518,24,20);

    // Awan tengah
    col(0.70f,0.76f,0.82f);
    circle(340,502,52,28); circle(405,488,65,28); circle(470,500,48,28);
    col(0.82f,0.87f,0.91f);
    circle(368,508,40,24); circle(420,494,52,24); circle(478,506,36,24);
    col(0.91f,0.94f,0.96f); circle(400,512,30,20); circle(440,498,36,20);

    // JALAN — seluruh area bawah adalah aspal 
    // Layer aspal dasar
    col(0.14f,0.14f,0.16f);
    glBegin(GL_QUADS);
        glVertex2f(0,320); glVertex2f(800,320);
        glVertex2f(800,0);  glVertex2f(0,0);
    glEnd();
    // Permukaan sedikit lebih terang (zona tengah jalan)
    col(0.19f,0.19f,0.21f);
    glBegin(GL_QUADS);
        glVertex2f(0,320); glVertex2f(800,320);
        glVertex2f(800,0);  glVertex2f(0,0);
    glEnd();
    // Gradient gelap di tepi bawah layar
    glBegin(GL_QUADS);
        col(0.19f,0.19f,0.21f); glVertex2f(0,320); glVertex2f(800,320);
        col(0.12f,0.12f,0.14f); glVertex2f(800,0); glVertex2f(0,0);
    glEnd();

    // Garis tepi jalan atas (horizon)
    glLineWidth(2.5f);
    col(0.52f,0.52f,0.50f);
    glBegin(GL_LINES); glVertex2f(0,318); glVertex2f(800,318); glEnd();
    glLineWidth(1.0f);

    // MARKA TENGAH — benar-benar di tengah area aspal 
    // Area aspal: Y=0..320, tengah = Y=160
    col(0.68f,0.68f,0.64f);
    for(int i=0;i<10;i++){
        float x=i*90.0f+20;
        glBegin(GL_QUADS);
            glVertex2f(x,   163); glVertex2f(x+58,163);
            glVertex2f(x+58,156); glVertex2f(x,   156);
        glEnd();
    }

    // Garis tepi kiri dan kanan jalan
    glLineWidth(2.0f);
    col(0.55f,0.55f,0.52f);
    glBegin(GL_LINES); glVertex2f(0,60);   glVertex2f(800,60);   glEnd(); // tepi bawah
    glLineWidth(1.0f);

    // Pantulan basah di aspal
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.14f,0.26f,0.52f,0.16f);
    ellipse(380,220,140,8,40);
    ellipse(580,190,75,6,30);
    glDisable(GL_BLEND);
}

// RODA 
void drawWheel(float R){
    // Ban
    col(0.09f,0.09f,0.10f); circle(0,0,R,44);
    // Ring putih ban
    glLineWidth(2.5f); col(0.82f,0.82f,0.82f);
    circleOut(0,0,R*0.95f,44); circleOut(0,0,R*0.90f,44);
    glLineWidth(1.0f);
    // Teks ban
    glPushMatrix();
        glRotatef(-25,0,0,1);
        col(0.75f,0.75f,0.75f);
        glRasterPos2f(-R*0.72f,-R*0.04f);
        const char* t="TOYO";
        for(int i=0;t[i];i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,t[i]);
    glPopMatrix();
    // Velg
    col(0.68f,0.71f,0.75f); circle(0,0,R*0.72f,40);
    // 5 spoke — sisi gelap/terang
    for(int i=0;i<5;i++){
        float a=2*PI*i/5, a2=a+PI/5.0f, am=(a+a2)*0.5f;
        col(0.34f,0.36f,0.40f);
        glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(cosf(a)*R*0.11f,   sinf(a)*R*0.11f);
            glVertex2f(cosf(am)*R*0.10f,  sinf(am)*R*0.10f);
            glVertex2f(cosf(a)*R*0.70f,   sinf(a)*R*0.70f);
            glVertex2f(cosf(am)*R*0.69f,  sinf(am)*R*0.69f);
        glEnd();
        col(0.70f,0.74f,0.80f);
        glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(cosf(am)*R*0.10f,  sinf(am)*R*0.10f);
            glVertex2f(cosf(a2)*R*0.11f,  sinf(a2)*R*0.11f);
            glVertex2f(cosf(am)*R*0.69f,  sinf(am)*R*0.69f);
            glVertex2f(cosf(a2)*R*0.70f,  sinf(a2)*R*0.70f);
        glEnd();
        col(0.86f,0.88f,0.92f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(cosf(am)*R*0.14f,sinf(am)*R*0.14f);
            glVertex2f(cosf(am)*R*0.65f,sinf(am)*R*0.65f);
        glEnd();
        glLineWidth(1.0f);
        col(0.18f,0.19f,0.21f); circle(cosf(a)*R*0.52f,sinf(a)*R*0.52f,R*0.052f,12);
        col(0.34f,0.35f,0.38f); circle(cosf(a)*R*0.52f,sinf(a)*R*0.52f,R*0.030f,10);
    }
    // Hub
    col(0.26f,0.28f,0.32f); circle(0,0,R*0.13f,20);
    col(0.55f,0.57f,0.62f); circle(0,0,R*0.07f,20);
}

void drawCaliper(float R){
    col(0.40f,0.40f,0.44f); circle(0,0,R*0.48f,40);
    col(0.30f,0.30f,0.34f); circle(0,0,R*0.32f,40);
    glPushMatrix();
        glRotatef(20,0,0,1);
        col(0.75f,0.08f,0.08f);
        glBegin(GL_QUADS);
            glVertex2f(-R*0.50f,-R*0.16f); glVertex2f(-R*0.28f,-R*0.16f);
            glVertex2f(-R*0.28f, R*0.16f); glVertex2f(-R*0.50f, R*0.16f);
        glEnd();
    glPopMatrix();
}

// LAMPU DEPAN 
void drawHeadBeam(float cx,float cy){
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    for(int i=5;i>=1;i--){
        float sp=14.0f+i*11.0f, rc=25.0f+i*18.0f;
        col4(1.0f,0.85f,0.35f,0.04f*i);
        glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
        for(int s=0;s<=12;s++){float dy=((float)s/12.0f*2-1)*sp;glVertex2f(cx-rc,cy+dy);}
        glEnd();
    }
    for(int i=3;i>=1;i--){col4(1.0f,0.82f,0.30f,0.08f*i);circle(cx,cy,6.0f+i*4.5f,28);}
    glDisable(GL_BLEND);
}
void drawHeadlight(){

    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // Beam utama — kerucut menyamping ke kiri
    float cx=138.0f, cy=358.0f;
    for(int i=6;i>=1;i--){
        float sp = 10.0f + i*14.0f;   // spread vertikal
        float rc = 20.0f + i*22.0f;   // jangkauan horizontal
        col4(0.92f, 0.82f, 0.30f, 0.038f*i);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for(int s=0;s<=16;s++){
                float dy = ((float)s/16.0f*2.0f-1.0f)*sp;
                glVertex2f(cx - rc, cy + dy);
            }
        glEnd();
    }

    // Halo kecil di sekitar lampu fog
    for(int i=4;i>=1;i--){
        col4(1.0f, 0.88f, 0.40f, 0.07f*i);
        circle(cx, cy, 5.0f+i*3.5f, 24);
    }

    glDisable(GL_BLEND);
}

// BODI MOBIL 
void drawCarBody(){
    // Bayangan — tipis langsung di bawah bodi, tepat di garis jalan
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    // Shadow utama: memanjang di bawah bodi, sangat tipis
    col4(0.01f,0.02f,0.04f,0.70f);
    ellipse(400,316,210,5,50);
    // Pendar gelap kedua lebih lebar tapi lebih transparan
    col4(0.01f,0.02f,0.04f,0.35f);
    ellipse(400,314,240,8,50);
    glDisable(GL_BLEND);

    // -- UNDERTRAY / FLOOR --
    col(0.04f,0.05f,0.07f);
    glBegin(GL_QUADS);
        glVertex2f(130,318); glVertex2f(660,318);
        glVertex2f(664,330); glVertex2f(126,330);
    glEnd();

    // -- SIDE SKIRT --
    col(0.05f,0.06f,0.09f);
    glBegin(GL_QUADS);
        glVertex2f(136,330); glVertex2f(658,330);
        glVertex2f(660,346); glVertex2f(134,346);
    glEnd();

    // -- BODI UTAMA — navy, Y=318 (tanah) ke atas --
    glBegin(GL_POLYGON);
        // bawah-kiri (gelap)
        col(0.06f,0.08f,0.16f); glVertex2f(136,346);
        col(0.06f,0.08f,0.15f); glVertex2f(118,343);
        col(0.07f,0.10f,0.18f); glVertex2f(110,356);
        col(0.08f,0.11f,0.20f); glVertex2f(108,372);
        col(0.09f,0.13f,0.23f); glVertex2f(112,388);
        col(0.11f,0.16f,0.27f); glVertex2f(124,400);
        col(0.12f,0.18f,0.30f); glVertex2f(150,408);
        col(0.13f,0.20f,0.33f); glVertex2f(205,414);
        col(0.14f,0.21f,0.35f); glVertex2f(278,418);
        // A-pillar curve smooth
        col(0.14f,0.22f,0.36f); glVertex2f(302,419);
        col(0.14f,0.21f,0.36f); glVertex2f(312,424);
        col(0.13f,0.21f,0.35f); glVertex2f(318,432);
        col(0.13f,0.20f,0.34f); glVertex2f(318,440);
        // roofline bawah lurus
        col(0.13f,0.20f,0.34f); glVertex2f(535,440);
        // C-pillar & fastback smooth
        col(0.13f,0.20f,0.34f); glVertex2f(562,438);
        col(0.12f,0.19f,0.32f); glVertex2f(585,430);
        col(0.12f,0.18f,0.31f); glVertex2f(604,420);
        col(0.11f,0.16f,0.28f); glVertex2f(622,408);
        col(0.10f,0.15f,0.26f); glVertex2f(638,394);
        col(0.09f,0.14f,0.24f); glVertex2f(650,378);
        col(0.08f,0.12f,0.21f); glVertex2f(658,362);
        col(0.07f,0.10f,0.19f); glVertex2f(660,346);
        col(0.06f,0.09f,0.17f); glVertex2f(658,330);
    glEnd();

    // -- ATAP — puncak terang metalik --
    glBegin(GL_POLYGON);
        col(0.13f,0.20f,0.34f); glVertex2f(316,432);
        col(0.13f,0.20f,0.34f); glVertex2f(318,440);
        col(0.13f,0.20f,0.34f); glVertex2f(535,440);
        col(0.13f,0.20f,0.34f); glVertex2f(562,438);
        col(0.12f,0.19f,0.32f); glVertex2f(585,430);
        col(0.12f,0.18f,0.31f); glVertex2f(604,420);
        // puncak atap
        col(0.16f,0.24f,0.40f); glVertex2f(594,452);
        col(0.18f,0.27f,0.45f); glVertex2f(555,464);
        col(0.20f,0.30f,0.48f); glVertex2f(435,470);
        col(0.20f,0.30f,0.48f); glVertex2f(355,470);
        col(0.18f,0.27f,0.45f); glVertex2f(335,464);
        col(0.16f,0.25f,0.42f); glVertex2f(320,454);
        col(0.14f,0.22f,0.38f); glVertex2f(316,444);
    glEnd();

    // -- HIGHLIGHT SPEKULER — sangat subtle, clean --
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    // Specular strip horizontal utama
    col4(0.50f,0.62f,0.82f,0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(138,374); glVertex2f(652,374);
        glVertex2f(650,382); glVertex2f(136,382);
    glEnd();
    // Chrome edge di puncak bodi
    col4(0.60f,0.70f,0.88f,0.14f);
    glBegin(GL_POLYGON);
        glVertex2f(138,384); glVertex2f(652,384);
        glVertex2f(650,388); glVertex2f(136,388);
    glEnd();
    // Highlight hood diagonal
    col4(0.45f,0.58f,0.78f,0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(158,400); glVertex2f(290,407);
        glVertex2f(287,414); glVertex2f(155,407);
    glEnd();
    // Shadow bawah bodi
    col4(0.01f,0.02f,0.05f,0.55f);
    glBegin(GL_QUADS);
        glVertex2f(134,330); glVertex2f(660,330);
        glVertex2f(662,342); glVertex2f(132,342);
    glEnd();
    glDisable(GL_BLEND);

    // -- GARIS KARAKTER --
    glLineWidth(2.0f);
    col(0.05f,0.08f,0.18f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(128,362); glVertex2f(200,366);
        glVertex2f(320,372); glVertex2f(450,374);
        glVertex2f(560,372); glVertex2f(622,366);
        glVertex2f(652,360);
    glEnd();
    // Shadow crease
    glLineWidth(1.0f);
    col(0.03f,0.05f,0.12f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(128,360); glVertex2f(320,370);
        glVertex2f(560,370); glVertex2f(652,358);
    glEnd();

    // -- FENDER ARCH — arc tepat mengikuti roda --

    // ARCH DEPAN — outer dark
    glLineWidth(4.0f);
    col(0.04f,0.06f,0.14f);
    glBegin(GL_LINE_STRIP);
        for(int f=0;f<=24;f++){
            float a = PI - (float)f/24.0f * PI; // PI?0 (kiri ke kanan)
            glVertex2f(235.0f + cosf(a)*68.0f, 318.0f + sinf(a)*68.0f);
        }
    glEnd();
    // ARCH DEPAN — inner highlight
    glLineWidth(1.8f);
    col(0.12f,0.18f,0.34f);
    glBegin(GL_LINE_STRIP);
        for(int f=1;f<=23;f++){
            float a = PI - (float)f/24.0f * PI;
            glVertex2f(235.0f + cosf(a)*64.0f, 318.0f + sinf(a)*64.0f);
        }
    glEnd();

    // ARCH BELAKANG — outer dark
    glLineWidth(4.0f);
    col(0.04f,0.06f,0.14f);
    glBegin(GL_LINE_STRIP);
        for(int f=0;f<=24;f++){
            float a = PI - (float)f/24.0f * PI;
            glVertex2f(575.0f + cosf(a)*71.0f, 318.0f + sinf(a)*71.0f);
        }
    glEnd();
    // ARCH BELAKANG — inner highlight
    glLineWidth(1.8f);
    col(0.12f,0.18f,0.34f);
    glBegin(GL_LINE_STRIP);
        for(int f=1;f<=23;f++){
            float a = PI - (float)f/24.0f * PI;
            glVertex2f(575.0f + cosf(a)*67.0f, 318.0f + sinf(a)*67.0f);
        }
    glEnd();
    glLineWidth(1.0f);

    // PINTU SAMPING (1 pintu)
    // Panel pintu sedikit lebih terang dari bodi
    col(0.09f,0.14f,0.26f);
    glBegin(GL_POLYGON);
        glVertex2f(338,346);   // kiri-bawah
        glVertex2f(528,346);   // kanan-bawah
        glVertex2f(530,440);   // kanan-atas (roofline bawah)
        glVertex2f(320,440);   // kiri-atas
        glVertex2f(318,432);   // kiri transisi A-pillar
        glVertex2f(335,348);   // kiri sedikit miring
    glEnd();

    // Celah pintu — garis tipis gelap di semua sisi
    glLineWidth(1.8f);
    col(0.02f,0.03f,0.06f);
    // Sisi kiri pintu (A-pillar ke bawah)
    glBegin(GL_LINES);
        glVertex2f(337,346); glVertex2f(319,440);
    glEnd();
    // Sisi kanan pintu (B-pillar)
    glBegin(GL_LINES);
        glVertex2f(530,346); glVertex2f(530,440);
    glEnd();
    // Sisi bawah pintu
    glBegin(GL_LINES);
        glVertex2f(337,346); glVertex2f(530,346);
    glEnd();
    glLineWidth(1.0f);

    // Highlight panel pintu — subtle
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.40f,0.55f,0.80f,0.09f);
    glBegin(GL_POLYGON);
        glVertex2f(342,370); glVertex2f(525,370);
        glVertex2f(524,380); glVertex2f(341,380);
    glEnd();
    glDisable(GL_BLEND);

    // Handle pintu — chrome kecil
    col(0.48f,0.52f,0.58f);
    glBegin(GL_QUADS);
        glVertex2f(430,386); glVertex2f(462,386);
        glVertex2f(462,391); glVertex2f(430,391);
    glEnd();
    // Handle shadow
    col(0.25f,0.27f,0.32f);
    glBegin(GL_QUADS);
        glVertex2f(430,391); glVertex2f(462,391);
        glVertex2f(462,394); glVertex2f(430,394);
    glEnd();
    // Handle highlight
    col(0.70f,0.74f,0.80f);
    glBegin(GL_QUADS);
        glVertex2f(432,387); glVertex2f(460,387);
        glVertex2f(460,389); glVertex2f(432,389);
    glEnd();

    // HOOD VENTS
    col(0.03f,0.04f,0.06f);
    glBegin(GL_POLYGON);
        glVertex2f(218,408); glVertex2f(290,412);
        glVertex2f(288,418); glVertex2f(216,414);
    glEnd();
    col(0.02f,0.02f,0.03f);
    glBegin(GL_POLYGON);
        glVertex2f(219,409); glVertex2f(289,413);
        glVertex2f(288,417); glVertex2f(218,413);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(218,399); glVertex2f(290,403);
        glVertex2f(288,409); glVertex2f(216,405);
    glEnd();
    col(0.03f,0.04f,0.06f);
    glBegin(GL_POLYGON);
        glVertex2f(218,399); glVertex2f(290,403);
        glVertex2f(288,410); glVertex2f(216,406);
    glEnd();
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.50f,0.62f,0.80f,0.22f);
    glBegin(GL_LINES); glVertex2f(219,409); glVertex2f(289,413); glEnd();
    glBegin(GL_LINES); glVertex2f(219,399); glVertex2f(289,403); glEnd();
    glDisable(GL_BLEND);
}

// BUMPER DEPAN 
void drawFrontEnd(){
    // Bumper — menyambung ke bodi
    col(0.06f,0.08f,0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(136,346);  // kanan-bawah — sama dgn bodi kiri-bawah
        glVertex2f(120,346);  // sedikit ke kiri
        glVertex2f(108,354);  // sudut kiri atas
        glVertex2f(106,368);  // kiri tengah
        glVertex2f(108,382);  // kiri bawah tengah
        glVertex2f(116,394);  // sudut kiri bawah
        glVertex2f(132,404);  // bawah kiri
        glVertex2f(205,410);  // bawah kanan (menyambung ke bodi)
        glVertex2f(205,346);  // kanan atas
    glEnd();
    // Panel concave tengah
    col(0.04f,0.05f,0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(106,368); glVertex2f(107,382);
        glVertex2f(205,382); glVertex2f(205,368);
    glEnd();
    // Grill hitam
    // Grill hitam
    col(0.03f,0.03f,0.04f);
    glBegin(GL_POLYGON);
        glVertex2f(110,366); glVertex2f(108,380);
        glVertex2f(110,392); glVertex2f(118,400);
        glVertex2f(202,402); glVertex2f(202,366);
        glVertex2f(148,364);
    glEnd();
    // Slats horizontal
    col(0.16f,0.16f,0.20f); glLineWidth(1.5f);
    for(int i=0;i<6;i++){
        float y=368+i*5;
        glBegin(GL_LINES); glVertex2f(112,y); glVertex2f(200,y-1); glEnd();
    }
    glLineWidth(1.0f);
    // Mesh vertikal
    col(0.12f,0.12f,0.16f);
    for(int i=0;i<8;i++){
        float x=116+i*10;
        glBegin(GL_LINES); glVertex2f(x,367); glVertex2f(x-2,396); glEnd();
    }
    // Air intake slot
    col(0.02f,0.02f,0.03f);
    glBegin(GL_QUADS);
        glVertex2f(106,368); glVertex2f(205,368);
        glVertex2f(205,376); glVertex2f(106,376);
    glEnd();
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.35f,0.50f,0.78f,0.38f);
    glBegin(GL_LINES); glVertex2f(107,368); glVertex2f(204,368); glEnd();
    glDisable(GL_BLEND);
    // Lampu utama — fog light diperbesar jadi headlight
    // Bezel luar gelap
    col(0.04f,0.05f,0.10f); circle(138,358,12,30);
    // Ring chrome
    col(0.48f,0.52f,0.58f); circle(138,358,10,30);
    // Reflektor
    col(0.36f,0.38f,0.42f); circle(138,358,8,30);
    // Bulb kuning
    col(0.95f,0.84f,0.35f); circle(138,358,6,24);
    col(1.00f,0.96f,0.65f); circle(138,358,4,20);
    col(1.00f,1.00f,0.92f); circle(138,358,2,14);
    // Ring DRL tipis
    col(0.82f,0.88f,1.00f);
    glLineWidth(1.8f); circleOut(138,358,11,30); glLineWidth(1.0f);
    // Outline housing
    col(0.03f,0.03f,0.04f);
    glLineWidth(1.2f); circleOut(138,358,12,30); glLineWidth(1.0f);
    // Splitter — rata dengan bodi bawah X=136
    col(0.04f,0.04f,0.06f);
    glBegin(GL_POLYGON);
        glVertex2f(102,318); glVertex2f(207,318);
        glVertex2f(207,330); glVertex2f(106,330);
    glEnd();
}

// KACA 
void drawGlass(){
    // WINDSHIELD
    glBegin(GL_POLYGON);
        col(0.04f,0.07f,0.13f); glVertex2f(320,440);
        col(0.04f,0.06f,0.12f); glVertex2f(518,440);
        col(0.04f,0.06f,0.11f); glVertex2f(514,462);
        col(0.05f,0.08f,0.14f); glVertex2f(435,470);
        col(0.05f,0.08f,0.14f); glVertex2f(360,470);
        col(0.05f,0.08f,0.13f); glVertex2f(336,464);
        col(0.04f,0.07f,0.13f); glVertex2f(320,454);
    glEnd();

    // QUARTER WINDOW — B ke C pillar
    glBegin(GL_POLYGON);
        col(0.03f,0.05f,0.10f); glVertex2f(518,440);
        col(0.03f,0.05f,0.10f); glVertex2f(578,440);
        col(0.03f,0.05f,0.10f); glVertex2f(574,454);
        col(0.04f,0.06f,0.11f); glVertex2f(514,462);
    glEnd();

    // REFLEKSI
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(0.72f,0.80f,0.90f,0.20f);
    glBegin(GL_POLYGON);
        glVertex2f(324,454); glVertex2f(348,464);
        glVertex2f(398,440); glVertex2f(374,440);
    glEnd();
    col4(0.68f,0.76f,0.88f,0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(366,470); glVertex2f(392,470);
        glVertex2f(448,440); glVertex2f(422,440);
    glEnd();
    // Shimmer tepi atas kiri
    col4(0.80f,0.86f,0.95f,0.45f);
    glBegin(GL_POLYGON);
        glVertex2f(322,454); glVertex2f(350,464);
        glVertex2f(350,462); glVertex2f(322,451);
    glEnd();
    // Shimmer tepi atas kanan
    col4(0.76f,0.83f,0.93f,0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(455,468); glVertex2f(514,462);
        glVertex2f(514,460); glVertex2f(455,466);
    glEnd();
    // Quarter refleksi
    col4(0.65f,0.74f,0.86f,0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(522,458); glVertex2f(540,454);
        glVertex2f(564,440); glVertex2f(546,440);
    glEnd();
    glDisable(GL_BLEND);

    // FRAME OUTLINE
    glLineWidth(3.0f); col(0.06f,0.07f,0.08f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(320,440); glVertex2f(518,440);
        glVertex2f(514,462); glVertex2f(435,470);
        glVertex2f(360,470); glVertex2f(336,464);
        glVertex2f(320,454);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(518,440); glVertex2f(578,440);
        glVertex2f(574,454); glVertex2f(514,462);
    glEnd();
    glLineWidth(1.0f);

    // A-PILLAR
    col(0.05f,0.06f,0.07f);
    glBegin(GL_POLYGON);
        glVertex2f(312,440); glVertex2f(324,440);
        glVertex2f(322,456); glVertex2f(334,466);
        glVertex2f(326,468); glVertex2f(312,456);
    glEnd();
    // B-PILLAR
    glBegin(GL_POLYGON);
        glVertex2f(514,440); glVertex2f(524,440);
        glVertex2f(520,462); glVertex2f(510,462);
    glEnd();
    // C-PILLAR
    glBegin(GL_POLYGON);
        glVertex2f(574,440); glVertex2f(586,440);
        glVertex2f(580,454); glVertex2f(570,454);
    glEnd();
}

// LAMPU BELAKANG
void drawTailLight(){
    col(0.55f,0.04f,0.04f);
    glBegin(GL_POLYGON);
        glVertex2f(656,348); glVertex2f(666,354);
        glVertex2f(666,384); glVertex2f(656,386);
        glVertex2f(648,374); glVertex2f(648,358);
    glEnd();
    col(0.85f,0.06f,0.06f);
    glBegin(GL_QUADS);
        glVertex2f(659,355); glVertex2f(664,355);
        glVertex2f(664,383); glVertex2f(659,383);
    glEnd();
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    col4(1.0f,0.10f,0.10f,0.22f); circle(664,369,11,20);
    glDisable(GL_BLEND);
}

// DIFFUSER & KNALPOT 
void drawDiffuser(){
    col(0.05f,0.06f,0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(555,330); glVertex2f(658,330);
        glVertex2f(662,318); glVertex2f(551,318);
    glEnd();
    col(0.12f,0.12f,0.15f); circle(578,324,8,20); circle(616,324,8,20);
    col(0.03f,0.03f,0.04f); circle(578,324,5,20); circle(616,324,5,20);
    col(0.48f,0.48f,0.52f); circle(580,322,2,8); circle(618,322,2,8);
}

// SPOILER
void drawSpoiler(){
    col(0.05f,0.06f,0.08f);
    glBegin(GL_QUADS);
        glVertex2f(568,440); glVertex2f(578,440);
        glVertex2f(578,457); glVertex2f(568,457);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(610,440); glVertex2f(620,440);
        glVertex2f(620,457); glVertex2f(610,457);
    glEnd();
    col(0.06f,0.07f,0.09f);
    glBegin(GL_POLYGON);
        glVertex2f(558,457); glVertex2f(630,457);
        glVertex2f(632,449); glVertex2f(556,449);
    glEnd();
    col(0.18f,0.20f,0.26f);
    glBegin(GL_LINES); glVertex2f(558,453); glVertex2f(630,453); glEnd();
}



// BURUNG
void drawBird(){
    glPushMatrix(); glTranslatef(592,459,0);
    glLineWidth(1.5f);
    col(0.70f,0.45f,0.08f);
    glBegin(GL_LINES);
        glVertex2f(-4,0); glVertex2f(-5,-8);
        glVertex2f(-5,-8); glVertex2f(-8,-8);
        glVertex2f(-5,-8); glVertex2f(-4,-11);
        glVertex2f(-5,-8); glVertex2f(-2,-8);
        glVertex2f( 3,0); glVertex2f( 4,-8);
        glVertex2f( 4,-8); glVertex2f( 1,-8);
        glVertex2f( 4,-8); glVertex2f( 4,-11);
        glVertex2f( 4,-8); glVertex2f( 7,-8);
    glEnd();
    glLineWidth(1.0f);
    col(0.10f,0.11f,0.13f); ellipse(0,7,12,8,26);
    circle(-8,16,7,20);
    col(0.88f,0.68f,0.08f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-15,17); glVertex2f(-13,20); glVertex2f(-13,15);
    glEnd();
    col(0.86f,0.86f,0.86f); circle(-9,19,2.6f,12);
    col(0.02f,0.02f,0.02f); circle(-9,19,1.3f,10);
    col(1.0f,1.0f,1.0f);   circle(-8.4f,19.5f,0.5f,6);
    col(0.17f,0.19f,0.21f);
    glBegin(GL_POLYGON);
        glVertex2f(-1,4); glVertex2f(12,2); glVertex2f(14,7);
        glVertex2f(10,12); glVertex2f(-1,13);
    glEnd();
    col(0.30f,0.32f,0.36f); glLineWidth(1.1f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(0,7); glVertex2f(11,4); glVertex2f(13,8);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(0,10); glVertex2f(9,7); glVertex2f(12,10);
    glEnd();
    glLineWidth(1.0f);
    col(0.10f,0.11f,0.13f);
    glBegin(GL_POLYGON);
        glVertex2f(10,4); glVertex2f(21,0);
        glVertex2f(22,5); glVertex2f(10,10);
    glEnd();
    glPopMatrix();
}

//DISPLAY 
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawBackground();

    glPushMatrix(); // global car

        glPushMatrix(); drawSpoiler();   glPopMatrix();
        glPushMatrix(); drawTailLight(); glPopMatrix();
        glPushMatrix(); drawDiffuser();  glPopMatrix();

        // Roda belakang
        glPushMatrix();
            glTranslatef(575,318,0);
            drawCaliper(65); drawWheel(65);
        glPopMatrix();

        // Roda depan
        glPushMatrix();
            glTranslatef(235,318,0);
            drawCaliper(62); drawWheel(62);
        glPopMatrix();

        glPushMatrix(); drawCarBody();  glPopMatrix();
        glPushMatrix(); drawFrontEnd(); glPopMatrix();
        glPushMatrix(); drawHeadlight();glPopMatrix();
        glPushMatrix(); drawGlass();    glPopMatrix();
        glPushMatrix(); drawBird();     glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluOrtho2D(0,800,0,600);   // 800x600, Y=0 bawah
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(960,640);
    glutInitWindowPosition(60,40);
    glutCreateWindow("Mobil2d Arsy Thariq Munawar 24060124120009");
    glClearColor(0.03f,0.05f,0.12f,1.0f);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
