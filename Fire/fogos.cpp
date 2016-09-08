#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#define MAX_PARTICLES 3500
#define GRAVITY 0.0003
#define MAX_FOGOS 50

int janela;
unsigned nfogos=0;
struct parts{
    float x,y,vx,vy;
    GLbyte cor[4];
    unsigned vida=0,wait=0;
}particle[MAX_FOGOS][MAX_PARTICLES], fogos[MAX_FOGOS];
void InitFogos(){
    int i;
    for(i=0; i<MAX_FOGOS;i++)
        if(fogos[i].vida<=0)
            break;
    //printf("%d\n",i);
    fogos[i].x = rand()%5 -2;
    fogos[i].y = -1;
    float v = (float)(rand()%60/1100.0);
    int a = rand()%90+45;
    fogos[i].vx = cos(M_PI*a/180)*v;
    fogos[i].vy = sin(M_PI*a/180)*v;
    fogos[i].vida = 80+rand()%60;
    fogos[i].wait = 127;
}
void InitParticle(int fogo){
    for(int j=0;j<3;j++)
        particle[fogo][0].cor[j] = rand()%128;
    particle[fogo][0].cor[3] = 127;
    for(int i=0; i<MAX_PARTICLES; i++){
        float v = (float)(rand()%100/5000.0);
        int a = rand()%360;
        particle[fogo][i].vx = cos(M_PI*a/180)*v;
        particle[fogo][i].vy = sin(M_PI*a/180)*v;
        particle[fogo][i].x = fogos[fogo].x;
        particle[fogo][i].y = fogos[fogo].y;
        particle[fogo][i].vida = 127;
    }
}
void Draw(){
    if(nfogos<MAX_FOGOS){
        InitFogos();
    }
    nfogos = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(.0f,.0f,-6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    for(int i=0; i<MAX_FOGOS; i++){
        if(--fogos[i].vida>0){
            InitFogos();
            nfogos++;
            fogos[i].x+=fogos[i].vx;
            fogos[i].y+=fogos[i].vy;
            fogos[i].vy-=GRAVITY;
            //fogos[i].vida--;
            glVertex3f(fogos[i].x,fogos[i].y,0.0f);
            //printf("C %lf\n",fogos[i].x);
        }
        else if(fogos[i].vida <= 0){
            if(--fogos[i].wait == 126)
                InitParticle(i);
        }
    }
    glEnd();
    glBegin(GL_POINTS);
    for(int j=0;j<MAX_FOGOS; j++){
        for(int i=0; i<MAX_PARTICLES; i++){
            if(particle[j][i].vida>0){
                particle[j][i].x += particle[j][i].vx;
                particle[j][i].y += particle[j][i].vy;
                particle[j][i].vy -= GRAVITY;
                particle[j][i].vida--;
                glColor4bv(particle[j][0].cor);
                glVertex3f(particle[j][i].x,particle[j][i].y,0.0f);
                //printf("%d\n",particle[j][0].cor[3]);
            }
        }
        if(particle[j][0].cor[3]>10)
            particle[j][0].cor[3]--;
    }
    glEnd();
    glutSwapBuffers();
}
void Resize(int w, int h){
    if(h==0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)w/h,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}
void InitGL(int w, int h){
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)w/h,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    InitFogos();
}
void fechar(unsigned char k, int x, int y){
    usleep(100);
    if(k == 27){
        glutDestroyWindow(janela);
        exit(0);
    }
}
int main(int argc, char **argv){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    janela = glutCreateWindow("Janela");
    glutDisplayFunc(&Draw);
    glutFullScreen();
    glutIdleFunc(&Draw);
    glutReshapeFunc(&Resize);
    glutKeyboardFunc(&fechar);
    InitGL(640,480);
    glutMainLoop();

    return 0;
}
