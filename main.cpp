//COMP 361
//PA1
//Team 8
//Angela Gabereau 4867815

// Based on: Skeleton program for GLUT applications.

// Link with: opengl32.lib, glu32.lib, glut32.lib.

#include <GL/glut.h>
#include <math.h>
#include <iostream>

#include "strstream"
#include <stdio.h>
#include <string.h>

using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;
#include <iomanip>

using namespace std;
//COMP 361
//PA2
//Team 8
//Angela Gabereau 4867815

// Based on: Skeleton program for GLUT applications.

// Link with: opengl32.lib, glu32.lib, glut32.lib
/*
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#include <stdio.h>
#include <string.h>

#include <iomanip>

#define ESC 27
#define M_PI 3.14159265
*/
using namespace std;

#define ESC 27

// Initial size of graphics window.
const int WIDTH  = 1200;
const int HEIGHT = 800;

const int MAPX = 10;
const int MAPY = 10;

// Current size of window.
int width  = WIDTH;
int height = HEIGHT;

// Mouse positions, normalized to [0,1].
double xMouse = 0.5;
double yMouse = 0.5;

unsigned char key = ' ';	// Last key pressed

// Bounds of viewing frustum.
double nearPlane =  5;
double farPlane  = 100;

// Viewing angle.
double fovy = 40.0;

// Variables.
double alpha = 0;                                  // Set by idle function.
double beta = 0;                                   // Set by mouse X.
double mdistance = - (farPlane - nearPlane) / 2;    // Set by mouse Y.
GLUquadricObj *quadratic;

float moveX = 0.0f;
float moveY = 0.0f;
float tileSpacing = 2.0f;
int map[10][10];
int mapX = 28;
int mapY = 28;

// Vectors for colours and properties of materials.
const GLfloat off[] = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat yellow[] = { 1.0f, 1.0, 0.0, 1.0 };
const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat ambientlightColor[] = { 0.3, 0.5, 0.3, 1.0 };
const GLfloat streetlightColor[] = { 1.0, 1.0, 1.0, 0.0 };
const GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };


int light1Switch = 1;
int light2Switch = 1;
int light3Switch = 1;
int light4Switch = 1;

bool fillModeSwitch = true;


// Translation values for light.
GLfloat move_y = 0.0;
GLfloat move_z = 0.0;

// Attenuation factors for light.
GLfloat const_att = 1.0;

void cube()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, dull);
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)
	glNormal3f(0.0f,1.0f,1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
  //  glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
    glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
  //  glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();					// done with the polygon
}



void triangle()
{
// draw a triangle (in smooth coloring mode)
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, dull);
    glBegin(GL_POLYGON);				// start drawing a polygon
	glNormal3f(0.0f,0.0f,1.0f);
 //   glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue  glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f( 0.0f, 0.2f, 0.0f);		// Top
//    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
  //  glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left

    glEnd();
}

void digitalStrut()
{
    glPushMatrix();
    glScalef( 0.1, 0.2, 0.2 );

    glPushMatrix();
    glTranslatef(0.0f,2.5f,0.0f);		// Move up 3
    glScalef( 1.0, 0.5, 1.0 );
    triangle();
    glPopMatrix();

    glPushMatrix();
    glScalef( 1.0, 2.0, 1.0 );
    cube();
    glPopMatrix();
  /*  glPushMatrix();
	glRotatef(180.0f,0.0f,1.0f,0.0f); //Flip triangle
    glTranslatef(0.0f,-2.5f,0.0f); //move it down


    glScalef( 1.0, 0.5, 1.0 );
    triangle();
    glPopMatrix();*/
    glPopMatrix();

}

void eight()
{
    glPushMatrix();
    glPushMatrix();
    glRotatef(90.0f,0.0f,0.0f,1.0f);  //Draw horizontal struts

    glPushMatrix();
    glTranslatef(1.0f,0.0f,0.0f);	//Top
    digitalStrut();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);	//Middle
    digitalStrut();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f,0.0f,0.0f);	//Bottom
    digitalStrut();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    //     glRotatef(90.0f,0.0f,0.0f,1.0f);  //Draw vertical struts
    glTranslatef(-0.5f,-0.5f,0.0f);
    glPushMatrix();
    digitalStrut(); //Top Right
    glTranslatef(1.0f,0.0f,0.0f);	//Top
    digitalStrut(); //Top Left
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,1.0f,0.0f);	//Bottom
    digitalStrut(); //Bottom Right
    glTranslatef(1.0f,0.0f,0.0f);
    digitalStrut(); //Bottom Left
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

}

void whiteCube()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)
	glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
    glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
    glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
    glEnd();					// done with the polygon
  /*  if(fillModeSwitch)
        glutSolidCube(1.0);
    else
        glutWireCube(1.0);*/
}

void circle(float x, float y, float r, int segments)
{
    //http://stackoverflow.com/questions/5094992/c-drawing-a-2d-circle-in-opengl datenwolf
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f(x, y);
    for( int n = 0; n <= segments; ++n )
    {
        float const t = 2*M_PI*(float)n/(float)segments;
        glVertex2f(x + sin(t)*r, y + cos(t)*r);
    }
    glEnd();
}


void DrawPacmanHalf(GLfloat r)
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_AMBIENT, off);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
	glClipPlane (GL_CLIP_PLANE0, eqn);
    glEnable (GL_CLIP_PLANE0);
    if(fillModeSwitch)
        glutSolidSphere(r,24,24);
    else
        glutWireSphere(r,24,24);

    glDisable (GL_CLIP_PLANE0);

}

void DrawPacman(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat r)
{
    glPushMatrix();
    glTranslatef(xPos,yPos+r+r/4,zPos); //Place him at specified location, hovering
	glPushMatrix(); //Top
	DrawPacmanHalf(r);
    glPopMatrix();

    glPushMatrix(); //Bottom
    glRotatef(200.0,1.0f,0.0f,0.0f);
    DrawPacmanHalf(r); //Bottom
    glPopMatrix();

    glPushMatrix();  //Eye balls.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);
   // glColor3f(0.0f,1.0f,0.0f); //Grreen Paint Brush
    glTranslatef(-0.3f,0.6f,0.7f);
    if(fillModeSwitch)
     glutSolidSphere(0.15,24,24);
    else
        glutWireSphere(0.15,24,24);
    glTranslatef(0.6f,0.0f,0.0f);
    if(fillModeSwitch)
     glutSolidSphere(0.15,24,24);
    else
        glutWireSphere(0.15,24,24);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glScalef(0.5f,0.5f,0.5f);
    glTranslatef(0.0f,0.0f,-2.0f);
    eight();
    glPopMatrix();

    glPopMatrix();

}

void DrawGhost(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
	glColor4f(1.0f,1.0f,1.0f, 0.3f);
    glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, off);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, off);

    glRotatef(-90.0,1.0f,0.0f,0.0f); //Stand up the ghosts
	glTranslatef(xPos,yPos,zPos);
    quadratic=gluNewQuadric();
    gluCylinder(quadratic,0.6f,0.3f,1.8f,32,32);
    if(fillModeSwitch)
        glutSolidCone(1.0,1.8,24,24);
    else
        glutWireCone(1.0,1.8,24,24);
    glPopMatrix();

}


void DrawAllGhosts()
{
    glPushMatrix();
    DrawGhost(3.0f,0.0f,0.0f);
    DrawGhost(6.0f,0.0f,0.0f);
    DrawGhost(9.0f,0.0f,0.0f);
    glPopMatrix();
}

void floorTile(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
    glPushMatrix();
	glRotatef(90.0f,1.0f,0.0f,0.0f);
    glTranslatef(xPos,yPos,zPos); //Move to specified location, set the rotation point to the corner.
    whiteCube();
    glScalef( 0.8f, 0.8f, 0.8f );
    glTranslatef(0.0f,0.0f,-0.01f );
    eight();
    glPopMatrix();
}

void DrawFloor()
{
    moveX = 0.0f;
    for(int i=0; i<mapY; i++)
    {
        moveY = 0.0f;
        for(int j=0; j<mapX; j++)
        {
            floorTile(moveX,moveY,0.0f);
            moveY = moveY + tileSpacing;
        }
        moveX = moveX + tileSpacing;
    }

}

void DrawPellet(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
      GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};

    // Drawing Pellets
    glPushMatrix();
   // glColor3f(1.0f,0.0f,0.0f); //Red paint brush.
    glTranslatef(xPos,yPos,zPos);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    if(fillModeSwitch)
     glutSolidSphere(0.3,24,24);
    else
        glutWireSphere(0.3,24,24);

    glPopMatrix();
}

void DrawPellets()
{
    moveX = 0.0f;
    for(int i=0; i<mapY; i++)
    {
        moveY = 0.0f;
        for(int j=0; j<mapX; j++)
        {
            if(map[i][j]==1){//If this map location has a pellet, draw it
                DrawPellet(moveX+tileSpacing/2,1.0f,moveY+tileSpacing/2);
            }
            moveY = moveY + tileSpacing;
        }
        moveX = moveX + tileSpacing;
    }
}

void DrawAxis()
{
    // Draw model axes.
    glBegin(GL_LINES);
    // X axis
   // glColor3f(1, 0, 0); //Red
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, off);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    // Y axis
    glColor3f(0, 1, 0); //Blue
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, off);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    // Z axis
   // glColor3f(0, 0, 1); //Green
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, off);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();
}
int streetLight(int light, double a, double b, double c, double d, double e, double f)
{
	//Source: http://www.cs.montana.edu/files/techreports/2008/Museboyina.pdf
	/*
	a, b and c -- x, y and z co-ordinates for light position
	d, e and f -- x, y and z co-ordinates for spot light position
	*/

	GLfloat light_position[] = { a,b,c, 1.0 };
	GLfloat spotDir[] = { d,e,f };

	//This is what the light vector should be.
	//Why it is not working.... I have no idea.
	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, off);
    glVertex3f(a, b, c);
    glVertex3f(d, e, f);
	glEnd();

	glLightfv(light,GL_SPECULAR,streetlightColor);
	glLightfv(light,GL_AMBIENT_AND_DIFFUSE,streetlightColor);
	glLightfv(light,GL_POSITION,light_position);

	// Definig spotlight attributes
	glLightf(light,GL_SPOT_CUTOFF,25.0);
	//glLightf(light,GL_SPOT_EXPONENT,2.5);
	glLightfv(light,GL_SPOT_DIRECTION,spotDir);

    glPushMatrix();
	//Lightbulb
    glTranslated(a,b,c);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glMaterialfv(GL_FRONT, GL_SPECULAR,green);
	glMaterialfv(GL_FRONT, GL_SHININESS,dull);

    if(fillModeSwitch)
        glutSolidSphere(0.4,24,24);
    else
        glutWireSphere(0.4,24,24);

	//Lampost
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, off);
	glMaterialfv(GL_FRONT, GL_SHININESS, dull);
	glTranslated(0.0,b/-2.0,0.0);
	glScalef(0.4f, 4.0f,0.4f );


    if(fillModeSwitch)
        glutSolidCube(1.0);
    else
        glutWireCube(1.0);

    glPopMatrix();

return 0;
}
// This function is called to display the scene.
void display ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-28.0f,-20.0f,-100.0f);  //We move back 30 steps, so  we can see what is going on.
    glRotatef(90.0f,1.0f,0.0f,0.0f);
//	DrawAxis();

	DrawPacman(5.0f, 0.0f, 5.0f,1.0f);
	DrawPellets();
	DrawFloor();

	//Draw lights
	streetLight(GL_LIGHT1,0.0,4.0,0.0,4.0,0.0,4.0); //back left
    streetLight(GL_LIGHT2,0.0,4.0,56.0,4.0,0.0,52.0);//front left
	streetLight(GL_LIGHT3,56.0,4.0,0.0,52.0,0.0,4.0);//back right
	streetLight(GL_LIGHT4,56.0,4.0,56.0,52.0,0.0,52.0);//front right

	glDisable(GL_LIGHTING);
	DrawAllGhosts();
	glEnable(GL_LIGHTING);

glFlush ();
glutSwapBuffers();

}

void mouseMovement (int mx, int my)
{
    // Normalize mouse coordinates.
    xMouse = double(mx) / double(width);
    yMouse = 1 - double(my) / double(height);

    // Redisplay image.
    glutPostRedisplay();
}

void mouse_movement (int x, int y) {

	// Moving mouse right brings light closer to viewer.
	move_z = (10.0 * x) / width;

	// Moving mouse up moves light upwards.
	move_y = 5.0 - (10.0 * y) / height;
	glutPostRedisplay();
}
// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}


void initMap()
{
    //Initialize the pills
    for(int i=0; i<28; i++)
    {
        for(int j=0; j<28; j++)
        {
                map[i][j]=(i+j)%2; //Place a pill on every second square.

        }
    }
}


// Display some useful remarks in the Xterm window.

void help () {
	printf("Press a key to select a property.\n");
	printf(" w       wireframe mode          \n");
	printf(" p       point mode              \n");
	printf(" f       fill mode               \n");
	printf(" s       smooth shading			 \n");
	printf(" f       flat shading			\n\n");
	printf(" d       day			\n\n");
	printf(" n       night			\n\n");
    printf(" y       all lightposts			\n\n");
	printf(" u       lightpost 1			\n\n");
	printf(" i       lightpost 2			\n\n");
	printf(" o       lightpost 3			\n\n");
	printf(" p       lightpost 4			\n\n");
}

// Respond to a keystroke.  Some responses are processed here; the default
// action is to record the keystroke and use it in the display callback function.

void keys (unsigned char thiskey, int x, int y) {
	//wireframe, smooth, flat from http://mindfuck.de-brauwer.be/articles/polygon/index.php

	switch (thiskey) {
		case ESC:
			exit(0);
		case 'h':		// Display help in text window
			help();
			break;
		case 'w':
			cout << "Wireframe mode on " << endl;
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            fillModeSwitch = false;
			glutPostRedisplay();
			break;
		case 'f':
			cout << "Fill mode on " << endl;
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			fillModeSwitch = true;
			glutPostRedisplay();
			break;
		case 's':
			cout << "Smooth shading " << endl;
			glShadeModel(GL_SMOOTH);
			glutPostRedisplay();
			break;
		case 'b':
			cout << "Flat shading " << endl;
			glShadeModel(GL_FLAT);
			glutPostRedisplay();
			break;
		case 'd':
			cout << "Day time " << endl;
			glEnable(GL_LIGHT0);
			break;
		case 'n':
			cout << "Night time " << endl;
			glDisable(GL_LIGHT0);
			break;

		case 'y':
			if(light1Switch){
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHT4);
				light1Switch = 0;
				light2Switch = 0;
				light3Switch = 0;
				light4Switch = 0;
			}else{
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
				glEnable(GL_LIGHT4);
				light1Switch = 1;
				light2Switch = 1;
				light3Switch = 1;
				light4Switch = 1;
			}
			break;

		case 'u':
			if(light1Switch){
				glDisable(GL_LIGHT1);
				light1Switch = 0;
			}else{
				glEnable(GL_LIGHT1);
				light1Switch = 1;
			}
			break;
		case 'i':
			if(light2Switch){
				glDisable(GL_LIGHT2);
				light2Switch = 0;
			}else{
				glEnable(GL_LIGHT2);
				light2Switch = 1;
			}
			break;
		case 'o':
			if(light3Switch){
				glDisable(GL_LIGHT3);
				light3Switch = 0;
			}else{
				glEnable(GL_LIGHT3);
				light3Switch = 1;
			}
			break;
		case 'p':
			if(light4Switch){
				glDisable(GL_LIGHT4);
				light4Switch = 0;
			}else{
				glEnable(GL_LIGHT4);
				light4Switch = 1;
			}
			break;
		default:		// Save key value for display()
			key = thiskey;
			break;
	}
	glutPostRedisplay();
}


int main (int argc, char **argv)
{
    // GLUT initialization.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Comp 361 - PA2 - Team 8 -  Press 'h' for instructions.");

    // Register call backs.
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeMainWindow);
    glutMotionFunc(mouse_movement);
	glutKeyboardFunc(keys);
    glutIdleFunc(display);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glClearColor(0.0,0.0,0.0,0.0);

	// Initialize the light.
	glEnable(GL_LIGHTING);
	//Ambient Light
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlightColor);
//(GL_LIGHT0, GL_DIFFUSE, ambient);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, ambient);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

	glEnable(GL_DEPTH_TEST); //enabling z-buffer

	//Initialize the map.
    initMap();

    // Enter GLUT loop.
    glutMainLoop();
}
