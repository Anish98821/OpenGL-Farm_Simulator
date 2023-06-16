#include <GL/freeglut_std.h>
#include<stdio.h>
#include <ctime>

int mouseX, mouseY;

bool updateExists = false;

enum field_stages{
    UNSEEDED,
    GROWING,
    READY,
};

enum plant_type{
    PLANT_1,
    PLANT_2,
    PLANT_3
};


class field
{
    public:
    int x_cord, y_cord;
    field_stages stage;
    plant_type plant;
    time_t creationTime = time(nullptr);

    field()
    {

    }
    field(int x, int y)
    {
        x_cord = x;
        y_cord = y;
    }

};


field activeFields[50];
int noOfFields = 3;
float cameraY = 0.0f; 


void mainDisplay()
{
    gluLookAt(0.0f, cameraY, 0.0f, // camera position (x,y,z)
              0.0f, 0.0f, 0.0f,   // camera target (x,y,z)
              0.0f, 1.0f, 0.0f);

    for(int i = 0; i<noOfFields; i++)
    {
        glBegin(GL_POLYGON);
             //   printf("Red Point: %d %d\n Mouse Click %d %d\n------------------------\n",mouseX + 27 ,mouseY - 25,mouseX,mouseY);
                int x = activeFields[i].x_cord;
                int y = activeFields[i].y_cord;
                printf("Drawing Fields now");
                glVertex2i(x, y);
                glVertex2i(x,y+50);
                glVertex2i(x+50,y+50);
                glVertex2i(x+50,y);
        glEnd();
    }
    glClear(GL_COLOR_BUFFER_BIT);

    //glutPostRedisplay();
    glFlush();
       glutSwapBuffers();
    
  
}

void progressUpdate()
{
    
}




void createNewField(int x, int y)
{
    
   /* glBegin(GL_POLYGON);
			printf("Red Point: %d %d\n Mouse Click %d %d\n------------------------\n",mouseX + 27 ,mouseY - 25,mouseX,mouseY);
            glColor3f(1.0f, 0.0f, 0.0f);
           // int x = mouseX + 30;
         //   int y = mouseY -30;
            glVertex2i(x, y);
        
            glVertex2i(x,y+50);
                glVertex2i(x+50,y+50);
            glVertex2i(x+50,y);
    glEnd();*/



    activeFields[noOfFields] = field(x,y);
    noOfFields++;
    printf("Fields : %d\n Coords: %d %d\n-------------",noOfFields,activeFields[noOfFields-1].x_cord,activeFields[noOfFields-1].y_cord);
               //glutPostRedisplay();

}

void display() {

}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      /*  mouseX = x;
        mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
      //  glPointSize(5.0f);
      //  createNewField(mouseX, mouseY);

        glFlush();*/
     
    }

    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        updateExists = true;
    }
}

void backgroundLoop()
{
    if(updateExists)
    {
        printf("Sending UPdate\n");
        glutPostRedisplay();
        updateExists = false;
    }

}


void handleKeyPress(unsigned char key, int x, int y) {
    switch(key) {
        case 'a': // move camera up
            cameraY += 1.0f;
            glutPostRedisplay(); // adjust camera position in the y-axis
            break;
        // other cases for handling other key presses
    }
}

int main(int argc, char** argv) {
    createNewField(700,400);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1600, 800);
    glutCreateWindow("OpenGL Red Dot");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1600, 0, 800);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glClearColor(0.3f,0.15f,0.0f,0.0f);
	glutFullScreen();
    glutDisplayFunc(mainDisplay);
    glutMouseFunc(mouse);
    glutKeyboardFunc(handleKeyPress);
   // glutIdleFunc(mainDisplay);

    //mainDisplay();
    glutMainLoop();
    return 0;
}
