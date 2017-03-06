#include <windows.h>

#include <GL/glew.h>
#include <GL/glut.h>



#include "Shader.h"
#include "Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#define PI 3.14159265358979323846

GLuint gSampler;
Texture* pTexture = NULL;
GLuint gWorldLocation;
GLuint gViewLocation;
GLuint gProjectLocation;
static float Scale = 0.0f;
static float vertical = 0.0f;
static float horizontal = 0.0f;

glm::mat4 trans;
glm::mat4 view;
glm::mat4 projection;

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    Scale += 0.005f;



    std::cout << Scale << std::endl;
    /*
	  glPointSize(1.0f);

	  glBegin(GL_LINE_STRIP);//必须是加上s，要不然显示不了
	  float i=-180;
	  float j=-90;
	  float widthStep=180/180;
	  float heightStep=90/90;
	  for(i=-180;i<=180;i+=widthStep)
	  {
	  for(j=-90;j<=90;j+=heightStep)
	  {
	  float x=fabs(cos(j*PI/180))*sin(i*PI/180);
	  float y=sin(j*PI/180);
	  float z=fabs(cos(j*PI/180))*cos(i*PI/180);
	  glVertex3f(x,y,z);
	  }

	  }
	  glEnd();
    */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutSolidSphere(1.0f, 50, 50);

    trans = glm::rotate(trans, (GLfloat)Scale*5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, glm::value_ptr(trans));

    view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(sin(horizontal + PI)*fabs(cos(vertical)), sin(vertical), fabs(cos(vertical))*cos(horizontal + PI)), glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(gViewLocation, 1, GL_FALSE, glm::value_ptr(view));

    projection = glm::perspective(70.0f, 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(gProjectLocation, 1, GL_FALSE, glm::value_ptr(projection));

    glFlush();
    glutSwapBuffers();//交换当前窗口使用层的缓存
}

void ProcessKeyboard(unsigned char key, int x, int y)
{

    if (key == 'a')
    {
	fprintf(stderr, "Error: '%c'\n", key);
	horizontal+=0.1;
    }
    if (key== 'd')
    {
	fprintf(stderr, "Error: '%c'\n", key);
	horizontal-=0.1;
    }
    if (key == 'w')
    {
	vertical+=0.1;
	if(vertical >= PI/2)
	{
	    vertical=PI/2;
	}
    }
    if (key == 's')
    {
	vertical-=0.1;
	if(vertical <= PI/2*(-1))
	{
	    vertical=(-1)*PI/2;
	}
    }
    view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(sin(horizontal + PI)*fabs(cos(vertical)), sin(vertical), fabs(cos(vertical))*cos(horizontal + PI)), glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(gViewLocation, 1, GL_FALSE, glm::value_ptr(view));
}

int main(int argc,char ** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(200,200);

    glutCreateWindow("color");

    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutKeyboardFunc(ProcessKeyboard);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
	fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	return 1;
    }

    printf("GL version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Shader shader("shader.vs","shader.fs");
    shader.Use();
    gSampler = shader.getUniform("gSampler");
    gWorldLocation = shader.getUniform("model");
    gViewLocation = shader.getUniform("view");
    gProjectLocation = shader.getUniform("project");
    glUniform1i(gSampler, 0);

    Texture texture(GL_TEXTURE_2D, argv[1]);
    texture.Load();
    texture.Bind(GL_TEXTURE_2D);
    glutMainLoop();
    return(0);
}
