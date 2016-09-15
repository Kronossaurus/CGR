#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;
int janela;
GLfloat spec[] = {.7, .7, .7, .7}, shin[] = {90.0}, luz_pos[] = {1.0,1.0,1.0,.0};
GLfloat corpo[] = {.6,.6,1,1},nariz[] = {1,.5,0,1};
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, corpo);
    // glColor3f(.7,.7,1.0);
    glTranslatef(.0f,-1.0f,-7.0f);
    glutSolidSphere(1.0,50,50);

    glTranslatef(.0f,1.4f,.0f);
    glutSolidSphere(.6,30,30);

    glTranslatef(.0f,.8f,.0f);
    glutSolidSphere(.3,25,25);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, nariz);
    glTranslatef(.0f,.0f,.3f);
    // glColor3f(1.0,.5,.0);
    glutSolidCone(.05,.15,20,20);
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)w/h,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
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
    janela = glutCreateWindow("Ice");
    glutDisplayFunc(&Draw);
    glutFullScreen();
    glutIdleFunc(&Draw);
    glutReshapeFunc(&Resize);
    glutKeyboardFunc(&fechar);
    InitGL(640,480);
    glutMainLoop();

    return 0;
}
