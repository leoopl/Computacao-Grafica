#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float x = -5.0f, z = 18.0f;
float angle = 0.0f, yAngle = 0.0;
float roll = 0.0f;
float fanrot = 0.0f;
float door_angle, window_angle = 0.0f;

float halfWidth = (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

unsigned int id_art;
unsigned int id_closet;
unsigned int id_tv;
unsigned int id_floor;
unsigned int id_gav;

//mapeando img no plano
void draw()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(0.5, 0.5, 0);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5, 0.5, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5, -0.5, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0.5, -0.5, 0);
    glEnd();
}

void draw_cube()
{
    glutSolidCube(1);
}

//carregando img
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        printf("tenstnasodamsdmw\n");
    }
    return textureID;
}



void display()
{
    glColor3f(1.0f, 0.961f, 0.933f);
    
    glPushMatrix();//parede do fundo
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(10, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//parede da frente
    glTranslatef(0.75f, 2.5f, 5.0f);
    glScalef(8.5f, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//parede esquerda
    glTranslatef(-5.0f, 2.5f, 2.5f);
    glRotatef(90, 0, 1, 0);
    glScalef(5, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//parede direta
    glTranslatef(5.0f, 2.5f, 3.25f);
    glRotatef(90, 0, 1, 0);
    glScalef(3.5, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//parede janela cima
    glTranslatef(5.0f, 4.0f, 0.75f);
    glRotatef(90, 0, 1, 0);
    glScalef(1.5, 2, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//parede janela baixo
    glTranslatef(5.0f, 1.0f, 0.75f);
    glRotatef(90, 0, 1, 0);
    glScalef(1.5, 2, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//chao
    glColor3f(0.827f, 0.827f, 0.827f);
    glTranslatef(0.0f, 0.005f, 2.5f);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//teto
    glColor3f(0.412f, 0.412f, 0.412f);
    glTranslatef(0.0f, 5.0f, 2.5f);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 5, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//cama
    glColor3f(0.529f, 0.808f, 0.980f);
    glTranslatef(4.0f, 0.5f, 3.0f);
    glScalef(2, 1, 3.5f);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//traveseiro
    glColor3f(0.690f, 0.769f, 0.871f);
    glTranslatef(4.0f, 1.1f, 4.5f);
    glScalef(1.5f, 0.15f, 0.5f);
    draw_cube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id_closet);
    glPushMatrix();//guarda roupa
    glColor3f(0.871f, 0.722f, 0.529f);
    glTranslatef(1.25f, 1.0f, 4.0f);
    glScalef(3, 6, 1.5);
    draw_cube();
    glColor3f(1, 1, 1);
    glTranslatef(-0.0f, -0.0f, -0.51f);
    draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();//pé da mesa de estudo (parede esquerda)
    glColor3f(0.871f, 0.722f, 0.529f);
    glTranslatef(-4.5f, 0.5f, 3.5f);
    glScalef(1, 1.6f, 0.1f);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//mesa de estudo (parede esquerda)
    glTranslatef(-4.5f, 1.25f, 1.75f);
    glScalef(1, 0.1f, 3.5f);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//mesa de estudo (parede do fundo)
    glTranslatef(-2.0f, 1.25f, 0.5f);
    glScalef(4.0f, 0.1f, 1);
    draw_cube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id_gav);
    glPushMatrix();//pé da mesa de estudo (parede do fundo)
    glTranslatef(0.0f, 0.5f, 0.5f);
    glScalef(1.0f, 1.6f, 1);
    draw_cube();
    glColor3f(1,1,1);
    glTranslatef(0.0f, 0.0f, 0.51f);
    glScalef(0.9, 0.9, 0.9);
    draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id_art);
    glPushMatrix();//quadro
    glColor3f(0, 0, 0);
    glTranslatef(0.0f, 3.5f, 0.15f);
    glScalef(0.5, 1, 0.13);
    draw_cube();
    glColor3f(1, 1, 1);
    glTranslatef(0.0f, 0.0f, 0.51f);
    glScalef(0.9, 0.9, 0.9);
    draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id_tv);
    glPushMatrix();//tv
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(3.5f, 2.75f, 0.15f);
    glScalef(1.75f, 1.5f, 0.13);
    draw_cube();
    glColor3f(1, 1, 1);
    glTranslatef(0.0f, 0.0f, 0.51f);
    glScalef(0.9, 0.9, 0.9);
    draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();//base tv
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(3.5f, 2.0f, 0.2f);
    glScalef(1.75f, 0.25f, 0.25f);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//porta
    glColor3f(0.545f, 0.271f, 0.075f);
    glTranslatef(-4.25f, 2.5f, 5.0f);
    glRotatef(door_angle, 0,1,0);
    glScalef(1.5, 5, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//janela
    glTranslatef(5.0f, 2.5f, 0.75f);
    glRotatef(90, 0, 1, 0);
    glRotatef(window_angle, 0,1,0);
    glScalef(1.5f, 1, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//esfera de luz
    glTranslatef(-4.5f, 1.6f, 0.25f);
    glColor3f(1,1,0);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    glPushMatrix();//base esfera de luz
    glColor3f(0.184f, 0.310f, 0.310f);
    glTranslatef(-4.5f, 1.5f, 0.25f);
    glScalef(0.25f, 0.25f, 0.25f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();//pé cadeira
    glColor3f(0,0,0);
    glTranslatef(-3.0f, 0.5f, 2.65f);
    glScalef(0.1, 0.75, 0.1);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//banco cadeira
    glColor3f(0,0,0);
    glTranslatef(-3.0f, 0.85f, 2.65f);
    glScalef(0.65, 0.1, 0.65);
    draw_cube();
    glPopMatrix();

    glPushMatrix();//encosto cadeira
    glColor3f(0,0,0);
    glTranslatef(-2.72f, 1.25f, 2.65f);
    glScalef(0.1, 0.75, 0.75);
    draw_cube();
    glPopMatrix();



    //VENTILADO ___________________________________________________________________________
    //def draw_fan(x, y, z, rot):
    /*
    glPushMatrix() //begin fan
    glTranslatef(x, y, z)
    glColor3ub(100, 100, 100)
    glScalef(1.75f, 0.25f, 0.25f);
    draw_cube();
    draw_block(0, 0, 0, 1, 1, 0.1) // base
    draw_block(0.4, 0.1, 0.4, 0.3, 0.3, 1)// haste
    glColor3ub(50, 50, 50)
    draw_block(0.35, 1.1, 0.35, 0.4, 0.6, 0.4)// motor
    //centro helices

    glTranslatef(0.55, 1.3, 1)
    glRotatef(-fanrot, 0, 0, 1)  // <<<<ISSO AQUI RODA O VENLILADOR
    glPushMatrix()
    glColor3ub(15, 15, 15)
    draw_block(0, 0, 0, 0.8, 0.02, 0.2)
    draw_block(0, 0, 0, -0.8, 0.02, -0.2)
    draw_block(0, 0, 0, 0.2, 0.02, -0.8)
    draw_block(0, 0, 0, -0.2, 0.02, 0.8)
    glPopMatrix()

    glPopMatrix()


    if (fanrot >= 360)
    {
        fanrot = 0.0;
    }
    fanrot += 3;
    */
    //VENTILADO ________________________________________________________________

}

void keyboard(int key, int w, int y)
{
	switch (key)
    {
        case GLUT_KEY_LEFT:
            angle -= 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        case GLUT_KEY_RIGHT:
            angle += 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        case GLUT_KEY_UP:
            x += lx*0.5f;
            z += lz*0.5f;
        break;
        case GLUT_KEY_DOWN:
            x -= lx*0.5f;
            z -= lz*0.5f;
        break;      
    }
}

void processMouseMovement(int xx, int yy){

    mouseX = (float)(halfWidth - xx)/halfWidth;
    mouseY = (float)(halfHeight - yy)/halfHeight;
    angle -= (0.001f * mouseX);
    lx = sin(angle);
    lz = -cos(angle);

    if(abs(yAngle) < (M_PI/2)){
        yAngle += (0.001f * mouseY);
    }
    ly = sin(yAngle);

}

void processNormalKeys(unsigned char key, int x, int y) {
    switch(key){
        case 'o':
            if(door_angle <= 118.0f) door_angle += 4.0f;
            glutPostRedisplay();
        break;

        case 'c':
            if(door_angle >= 4.0f) door_angle -= 4.0f;
            glutPostRedisplay();
        break;

        case 'j':
            if(window_angle <= 118.0f) window_angle += 4.0f;
            glutPostRedisplay();
        break;

        case 'w':
            if(window_angle >= 4.0f) window_angle -= 4.0f;
            glutPostRedisplay();
        break;

        case 27:
            exit(0);
        break;
    }
}

void lightsSetup()
{
  GLfloat ambientLight[4]={0.8,0.8,0.8,1.0};
  GLfloat diffuseLight[4]={0.09,0.09,0.09,09.0};
  GLfloat specularLight[4]={0.7, 0.7, 0.7, 1.0};
  GLfloat specularity[4]={0.1,0.1,0.1,1};
  GLfloat lightPosition[4] = {-4.5f, 1.6f, 0.25f, 1};

  glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight );
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight );
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition );
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, 2.5f, z,
        x + lx, 2.5f + ly, z + lz,
        roll + 0.0f, 2.5f, 0.0f);
    lightsSetup();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.f, 0.0f, -100.0f);
		glVertex3f(-100.f, 0.0f, 100.0f);
		glVertex3f(100.f, 0.0f, 100.0f);
		glVertex3f(100.f, 0.0f, -100.0f);
	glEnd();

	display();

	glFlush();
	glutSwapBuffers();
}

void changeSize(int w, int h){

    if (h == 0) h = 1;
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	//inicialização com o display(dupla visão, cor e profundidade), tamanho e nome da tela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("ProjetoCG");

	glClearColor(0.0, 0.7, 1.0, 1.0);


	//registra o callback de redenrização
	//glutDisplayFunc(display);
	glutDisplayFunc(renderScene);

	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(keyboard);
    glutKeyboardFunc(processNormalKeys);
    glutPassiveMotionFunc(processMouseMovement);
    id_closet = loadTexture("closet.jpg");
    id_art = loadTexture("VGogh.jpg");
    id_tv = loadTexture("tv.png");
    id_gav = loadTexture("gav.jpg");

	//inicia o loop dos eventos da GLUT
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glShadeModel(GL_SMOOTH);

	glutMainLoop();

	return 1;
}