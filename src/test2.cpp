#include <GL/freeglut_std.h>
//#include <GL/glut.h>
#include <stdio.h>
#include <array>
#include <ctime>


/*
int points[20][2];

int no = 2;
*/



void drawCarrot(int,int,int);
void drawBlueberry(int,int,int);
void drawOnion(int, int, int);
void drawTool(int,int);


#pragma region GLOBAL_ENUMS

enum Actions
{
    WATER,
    TILL,
    PLANT,
    HARVEST

};

enum FieldStages{
    BARREN, 
    TILLED,
    SEEDED,A,B,C
    
};

enum PlantType
{
    CARROT,BLUEBERRY,ONION
};

enum Locations {
    MARKET,
    FIELD
};

#pragma endregion

#pragma region GLOBAL_VARIABLES

Actions SELECTED_ACTION = WATER;
Locations CURRENT_LOCATION = MARKET;
PlantType SELECTED_PLANT = CARROT;
char* ACTION_MESSAGE = "";
int MONEY = 0;
int FIELD_LENGTH = 150;
int FIELD_WIDTH = 100;


#pragma endregion

#pragma region CLASS_DEFS

class Plant
{
   

    GLfloat plantColors[3][3][3] = 
    {{{1.0f,0.0f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f}},
    {{1.0f,0.5f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f}},
    {{1.0f,0.5f,0.5f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f}}
    };

    int stageUpTimes[3][2] =
    {
        {3,10},
        {3,10},
        {3,10}
    };

    public:
        time_t last_state_update_time;
        PlantType type;
        int stage = 0;
        Plant(PlantType _type)
        {
            printf("got plant %d ", _type);
            last_state_update_time = time(nullptr);
            type = _type;
        }

        Plant()
        {
            last_state_update_time = time(nullptr);
            type = CARROT;
        }

        void drawPlant(int x, int y)
        {
            int xOff = 0;
            int yOff = 0;
            glColor3fv(plantColors[type][stage]);
            glPointSize(10.0f);

            y+= 10;
            x+=25;

            for(int i = 0; i<3; i++)
            {
                if(i)
                {
                y += 50;
                x -= 100;
                }
                for(int j = 0; j<3; j++)
                {
                if(j)
                x+=50;
                switch (type)
                {
                    case CARROT:
                    {
                        drawCarrot(x,y,stage);
                        break;
                    }
                    case BLUEBERRY:
                    {
                        drawBlueberry(x,y,stage);
                        break;
                    }
                    case ONION:
                    {
                        drawOnion(x,y,stage);
                        break;
                    }
                    
                }
                }

            }
        }

        void updatePlant()
        {
            time_t currentTime = time(nullptr);
            if(stage<2 && (currentTime - last_state_update_time) > stageUpTimes[type][stage])
            {
                stage++;
                last_state_update_time = time(nullptr);
                glutPostRedisplay();

            }

        }

        bool isHarvestable()
        {
            if(stage == 2)
                return true;
        }
};

class Field
{
    public:
    time_t creationTime = time(nullptr);
    time_t last_water_time;
    time_t last_planted_time;
    Plant plant = Plant();
    int x_cord;
    int y_cord;
    bool isWatered = true;
    bool isTilled = true;
    bool isPlanted = false;
    int dryUpTime = 0;
    FieldStages current_stage;
    GLfloat color[3];

    Field(int x, int y)
    {
       
        x_cord = x;
        y_cord = y;
       
        dryUpTime = 500 +  (rand() % (3 - (-3) + 1) + (-3)); 
  
    }

    GLfloat* getColor()
    {
        static GLfloat red_arr[] = {1.0f,1.0f,1.0f};
        static GLfloat blue_arr[] = {0.0f,0.0,1.0f};
        static GLfloat green_arr[] = {0.0f,1.0,0.0f};
        switch(current_stage)
        {
        case A:
            return red_arr;
        case B:
            return blue_arr;
        case C:
            return green_arr;
        }
    }
    void plantField()
    {}

    void tillField()
    {}

    void drawSelf()
    {
        if(isWatered)
        {
            glColor3f(0.504f, 0.306f, 0.106f);
        }
        else
        {
             glColor3f(0.709f, 0.434f, 0.156f);
        }
        glBegin(GL_POLYGON); 
            glVertex2i(x_cord,y_cord);
            glVertex2i(x_cord+FIELD_LENGTH,y_cord);
            glVertex2i(x_cord+FIELD_LENGTH,y_cord+FIELD_LENGTH);
            glVertex2i(x_cord,y_cord+FIELD_LENGTH);
        glEnd();
        
        if (isTilled)
        {
            glLineWidth(15);
            glColor3f(0.402f, 0.239f, 0.086f);
            glBegin(GL_LINES); 
                glVertex2i(x_cord,y_cord+10);
                glVertex2i(x_cord+FIELD_LENGTH,y_cord+10);
                glVertex2i(x_cord,y_cord+50);
                glVertex2i(x_cord+FIELD_LENGTH,y_cord+50);
                glVertex2i(x_cord,y_cord+90);
                glVertex2i(x_cord+FIELD_LENGTH,y_cord+90);
                glVertex2i(x_cord,y_cord+130);
                glVertex2i(x_cord+FIELD_LENGTH,y_cord+130);
            glEnd();
        }
        
        if(isPlanted)
        plant.drawPlant(x_cord,y_cord);
    }

    void onClick(int mouseX, int mouseY)
    {
        if(mouseX >= x_cord && mouseX <= x_cord + FIELD_LENGTH && mouseY >= y_cord && mouseY <= y_cord + FIELD_LENGTH)
         {
            switch (SELECTED_ACTION)
            {
            case WATER:
            {
                last_water_time = time(nullptr);
                isWatered = true;
                break;
            }
            
            case TILL:
            {
                isTilled = true;
            }
            break;

            case PLANT:
            {
  
                if(isWatered && isTilled && !isPlanted)
                {
                    isPlanted = true;
                    plant = Plant(SELECTED_PLANT);
                }
               // ACTION_MESSAGE = "Plantations Requirements not complete";
               // else if(isPlanted)
             //   ACTION_MESSAGE = "Already Planted";
                else
                {
                    last_planted_time = time(nullptr);
                    //plant = Plant(SELECTED_PLANT);
                }
                break;
            }
            case HARVEST:
            {
                if(isPlanted && plant.isHarvestable())
                {
                    glClear(GL_COLOR_BUFFER_BIT);
                    isPlanted = false;
                    isTilled = false;
                    
                }
            }
            default:
                break;
            }
             current_stage = C;
         }
    }

    void updateField()
    {
      
        if(isWatered && (time(nullptr) - last_water_time > dryUpTime))
        {
            isWatered = false;
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
    }

};


#pragma endregion 

#pragma region DRAW_FUNCTIONS

void drawWindow(int x, int y)
{
    int height = 30;
    int breadth = 45;
  glColor3f(0.512f, 0.58f, 0.727f);
    glBegin(GL_POLYGON);
        glVertex2i(x,y);
        glVertex2i(x,y+height);
        glVertex2i(x+breadth,y+height);
        glVertex2i(x+breadth,y);
    glEnd();
    glLineWidth(3.0f);
    glColor3f(0.371f, 0.42f, 0.527f);

    glBegin(GL_LINE_LOOP);
        glVertex2i(x,y);
        glVertex2i(x,y+height);
        glVertex2i(x+breadth,y+height);
        glVertex2i(x+breadth,y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(x+breadth/2,y);
        glVertex2i(x+breadth/2,y+height);
        glVertex2i(x,y+height/2);
        glVertex2i(x+breadth,y+height/2);
    glEnd();


}

void drawOnion(int x, int y, int stage)
{
    switch (stage)
    {
    case 0:
        y-=5;
        glColor3f(0.882f, 0.741f, 0.345f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2i(x,y+22);
        glVertex2i(x-3,y+19);
        glVertex2i(x+4,y+30);
        glVertex2i(x-5,y+32);
        glEnd();
        break;
        break;
    case 1:
        y+=10;
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glColor3f(0.2f, 0.275f, 0.208f);
        glVertex2i(x+2.5,y+7);
        glVertex2i(x+12.5,y+10);
        glVertex2i(x-1.5,y+3);
        glVertex2i(x-7.5,y+9);
        glColor3f(0.949f, 0.839f, 0.906f);
        glVertex2i(x,y);
        glColor3f(0.422f, 0.576f, 0.439f);
        glVertex2i(x,y+15);

        glEnd();
        break;

    case 2:
        y+=15;
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glColor3f(0.2f, 0.275f, 0.208f);
        glVertex2i(x+2.5,y+7);
        glVertex2i(x+12.5,y+10);
        glVertex2i(x-1.5,y+3);
        glVertex2i(x-7.5,y+9);
        glColor3f(0.949f, 0.839f, 0.906f);
        glVertex2i(x,y);
        glColor3f(0.422f, 0.576f, 0.439f);
        glVertex2i(x,y+15);
        glLineWidth(20.0f);
        glColor3f(0.824f, 0.275f, 0.769f);
        glVertex2i(x-5,y);
        glVertex2i(x+5,y);
        glEnd();

        
        break;
    }

}

void drawBlueberry(int x, int y, int stage)
{

    switch (stage)
    {
    case 0:
    y-=5;
        glColor3f(0.882f, 0.741f, 0.345f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2i(x,y+22);
        glVertex2i(x-3,y+19);
        glVertex2i(x+4,y+30);
        glVertex2i(x-5,y+32);
        glEnd();
        break;

    case 1:
        glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(x-5,y+10);
        glVertex2i(x,y+20); 
        glVertex2i(x+5,y+10);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2i(x-5,y+17);
        glVertex2i(x,y+7); 
        glVertex2i(x+5,y+17);
        glEnd();
        break;

    case 2:
        y+=10;

        glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(x-10,y);
        glVertex2i(x,y+20); 
        glVertex2i(x+10,y);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2i(x-10,y+15);
        glVertex2i(x,y-5); 
        glVertex2i(x+10,y+15);
        glEnd();

        glColor3f(0.164f, 0.266f, 0.718f);
        glPointSize(4.0f);
        glBegin(GL_POINTS);
        glVertex2i(x-7,y+13);
        glVertex2i(x,y-2); 
        glVertex2i(x+7,y+13);
        glVertex2i(x,y+7);
        glVertex2i(x-7,y);
        glVertex2i(x,y+17); 
        glVertex2i(x+7,y);
        glEnd();
        break;

    default:

        break;
    }
}

void drawCarrot(int x, int y,int stage)
{
    switch (stage)
    {
    case 0:
        glColor3f(0.882f, 0.741f, 0.345f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2i(x,y+22);
        glVertex2i(x-3,y+19);
        glVertex2i(x+4,y+30);
        glVertex2i(x-5,y+32);
        glEnd();
        break;

    case 1:
        glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(x,y+20);
        glVertex2i(x-5,y+30); 
        glVertex2i(x-7.5,y+25);
        glVertex2i(x-5,y+35); 
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2i(x,y+20);
        glVertex2i(x+5,y+30); 
        glVertex2i(x+7.5,y+25);
        glVertex2i(x+5,y+35); 
        glEnd();
        break;
    
    case 2:
        glColor3f(0.988f, 0.596f, 0.055f);
        glBegin(GL_POLYGON);
        glVertex2i(x-7,y+12); 
        glVertex2i(x-10,y+20);
        glVertex2i(x+10,y+20); 
        glVertex2i(x+7,y+12);
        glEnd();

         glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(x,y+20);
        glVertex2i(x-5,y+30); 
        glVertex2i(x-7.5,y+25);
        glVertex2i(x-5,y+35); 
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2i(x,y+20);
        glVertex2i(x+5,y+30); 
        glVertex2i(x+7.5,y+25);
        glVertex2i(x+5,y+35); 
        glEnd();
        break;
    }
    
}

void drawHouse()
{
    int height = 200;
    int width = 200;
    int x_cord = 400;
    int y_cord = 260;
//Body
    glColor3f(0.855f, 0.365f, 0.168f);
    glBegin(GL_POLYGON);
            glVertex2i(x_cord,y_cord);
            glVertex2i(x_cord+width,y_cord);
            glVertex2i(x_cord+width,y_cord+height);
            glVertex2i(x_cord,y_cord+height);
    glEnd();



    //Roof
    glColor3f(0.691f, 0.075f, 0.039f);
    glBegin(GL_QUADS);
        glVertex2i(x_cord,y_cord+150);
        glVertex2i(x_cord,y_cord+250);
        glVertex2i(x_cord+(width/2),y_cord+300);
        glVertex2i(x_cord+(width/2),y_cord+200);

        glVertex2i(x_cord+(width/2),y_cord+300);
        glVertex2i(x_cord+(width/2),y_cord+200);
        glVertex2i(x_cord+width,y_cord+150);
        glVertex2i(x_cord+width,y_cord+250);
  
    glEnd();

    //Sidebody
    glColor3f(0.737f, 0.379f, 0.239f);
    glBegin(GL_POLYGON);
        glVertex2i(x_cord,y_cord);
        glVertex2i(x_cord-200,y_cord);
        glVertex2i(x_cord-200,y_cord+150);
        glVertex2i(x_cord,y_cord+150);
    glEnd();

 //SideRoof
  glColor3f(0.691f, 0.075f, 0.039f);
    glBegin(GL_POLYGON);
        glVertex2i(x_cord,y_cord+150);
        glVertex2i(x_cord-200,y_cord+150);
        glVertex2i(x_cord-200,y_cord+250);
        glVertex2i(x_cord,y_cord+250);
    glEnd();

//Door
  glColor3f(0.691f, 0.075f, 0.039f);
    glBegin(GL_POLYGON);
        glVertex2i(x_cord+(width/2)-20,y_cord);
        glVertex2i(x_cord+(width/2)-20,y_cord+45);
        glVertex2i(x_cord+(width/2)+20,y_cord+45);
        glVertex2i(x_cord+(width/2)+20,y_cord);
    glEnd();

    glColor3f(0.856f, 0.682f, 0.105f);
    glBegin(GL_POLYGON);
        glVertex2i(x_cord+(width/2)+12,y_cord+25);
        glVertex2i(x_cord+(width/2)+12,y_cord+20);
        glVertex2i(x_cord+(width/2)+18,y_cord+20);
        glVertex2i(x_cord+(width/2)+18,y_cord+25);
    glEnd();

    drawWindow(x_cord + 130,y_cord+75);
    drawWindow(x_cord + 20,y_cord+75);

}

void drawTool(int x, int y)
{
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x+40,y+40);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(x+40,y+40);
    glVertex2i(x+35,y+30);
    glVertex2i(x+45,y+25);
    glEnd();

}

#pragma endregion

#pragma region MENU_FUNCTIONS

void actionMenuCallBack(int option) {
    SELECTED_ACTION = static_cast<Actions>(option);
}

void travelMenuCallBack(int option)
{
    CURRENT_LOCATION = static_cast<Locations>(option);
}

void plantSelectCallBack(int option)
{
    printf("Selected new plant %d",option);
    SELECTED_PLANT = static_cast<PlantType>(option);
}

void initializeMenu()
{
    int mainMenuId, actionSubMenuId,gotoSubMenuId,plantSelectMenuId;

    gotoSubMenuId = glutCreateMenu(actionMenuCallBack);
    glutAddMenuEntry("Water", WATER);
    glutAddMenuEntry("Plough", TILL); 
    glutAddMenuEntry("Harvest", HARVEST);
    glutAddMenuEntry("Seed", PLANT);

    plantSelectMenuId = glutCreateMenu(plantSelectCallBack);
    glutAddMenuEntry("CARROT",CARROT);
    glutAddMenuEntry("BLUEBERRY",BLUEBERRY);
    glutAddMenuEntry("ONION",ONION);

    mainMenuId = glutCreateMenu(travelMenuCallBack);
    glutAddMenuEntry("Market", MARKET);
    glutAddMenuEntry("Field", FIELD);

    actionSubMenuId = glutCreateMenu(nullptr);
    glutAddSubMenu("Action", gotoSubMenuId);
    glutAddSubMenu("Goto", mainMenuId);
    glutAddSubMenu("Plants",plantSelectMenuId);
    

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#pragma endregion


Field ACTIVE_FIELDS[] = {
    Field(1200,500),Field(1000,500),Field(800,500),
    Field(1200,300),Field(1000,300),Field(800,300),
    Field(1200,100),Field(1000,100),Field(800,100),
    };
int FIELDS_COUNT = 9;

float cameraY = 0.0f;
float cameraX = 0.0f;


void display() {

    glColor3f(0.066f, 0.329f, 0.082f);
    glBegin(GL_POLYGON);
    glVertex2i(0,750);
    glVertex2i(0,850);
    glVertex2i(2000,950);
    glVertex2i(2000,750);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(40,0);
    glVertex2i(40,850);
    glVertex2i(0,850);
    glVertex2i(0,0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(0,0);
    glVertex2i(0,40);
    glVertex2i(2000,40);
    glVertex2i(2000,0);
    glEnd();
    glColor3f(0.463f, 0.208f, 0.024f);
    glLineWidth(10.0f);
    glColor3f(0.611f, 0.275f, 0.027f);
    glBegin(GL_LINE_STRIP);
    glVertex2i(750,300);
    glVertex2i(750,75);
    glVertex2i(1400,75);
    glVertex2i(1400,680);
    glVertex2i(750,680);
    glVertex2i(750,430);
    glEnd();

    glLineWidth(15.0f);
    glColor3f(0.463f, 0.208f, 0.024f);
    glLineStipple(10,3);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
    glVertex2i(750,300);
    glVertex2i(750,75);
    glVertex2i(1400,75);
    glVertex2i(1400,680);
    glVertex2i(750,680);
    glVertex2i(750,430);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

     for(int i = 0; i<FIELDS_COUNT; i++)
     {
        ACTIVE_FIELDS[i].drawSelf();
     }

    drawHouse();
    drawTool(20,750);



    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        int mouseX, mouseY;
        mouseX = x + 30;
        mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y - 30;
        for(int i = 0; i<FIELDS_COUNT; i++)
        {
            ACTIVE_FIELDS[i].onClick(mouseX,mouseY);
        }

        glutPostRedisplay();
    }
}

void idleFunc()
{
    
    for(int i = 0; i<FIELDS_COUNT; i++)
     {
         ACTIVE_FIELDS[i].plant.updatePlant();
         ACTIVE_FIELDS[i].updateField();
     }
     
}

void handleKeyPress(unsigned char key, int x, int y) {
    switch(key) { 
        case 'w': // move camera up
            cameraY += 1.0f;
            glutPostRedisplay(); // adjust camera position in the y-axis
            break;
        case 's': // move camera up
            cameraY -= 1.0f;
            glutPostRedisplay(); // adjust camera position in the y-axis
            break;
        case 'a': // move camera up
            cameraX -= 1.0f;
            glutPostRedisplay(); // adjust camera position in the y-axis
            break;
        case 'd': // move camera up
            cameraX += 1.0f;
            glutPostRedisplay(); // adjust camera position in the y-axis
            break;
    }
}

void initializeGlut()
{
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL Red Dot");
    gluOrtho2D(0,1600,0,800);
    glutFullScreen();
    glClearColor(0.254f, 0.547f, 0.066f,0.0f);
}

void initializeFuncs()
{
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(handleKeyPress);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    initializeGlut();
    initializeFuncs();
    initializeMenu();
    glutMainLoop();
    return 0;
}