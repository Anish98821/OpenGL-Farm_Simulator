
#include<GL/freeglut_std.h>
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
    FIELD,
    CERTIFICATE_PAGE
};

#pragma endregion

#pragma region GLOBAL_VARIABLES

Actions SELECTED_ACTION = WATER;
Locations CURRENT_LOCATION = CERTIFICATE_PAGE;
PlantType SELECTED_PLANT = CARROT;
char* ACTION_MESSAGE = "";
int MONEY = 0;
int FIELD_LENGTH = 150;
int FIELD_WIDTH = 100;

bool isInventoryOpen = false;

unsigned char a_plough[] = "Plough";
unsigned char a_water[] = "Water";
unsigned char a_harvest[] = "Harvest";
unsigned char a_seed[] = "Seed";


unsigned char p_carrot[] = "Carrot";
unsigned char p_blueberry[] = "Blueberry";
unsigned char p_onion[] = "Onion";


struct manager
{
int carrot_cost;
int blueberry_cost;
int onion_cost;

int carrot_seeds = 8;
int blueberry_seeds = 6;
int onion_seeds = 6;

int carrots = 0;
int carrot_return_seeds = 8;
int carrot_per_field_seeds = 6;
int carrot_return;


int onions = 0;
int onion_return_seeds = 8;
int onion_per_field_seeds = 6;
int onion_return;

int blueberries = 0;
int blueberry_return_seeds = 4;
int bluberry_per_field_seed;
int blueberry_return;

} GameManager;

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
    bool isTilled = false;
    bool isPlanted = false;
    int dryUpTime = 0;
    FieldStages current_stage;
    GLfloat color[3];

    Field(int x, int y)
    {
       
        x_cord = x;
        y_cord = y;
       
        dryUpTime = 100 +  (rand() % (3 - (-3) + 1) + (-3)); 
  
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
         

                    switch (SELECTED_PLANT)
                    {
                    case CARROT:
                        if(GameManager.carrot_seeds >= 6 )
                        GameManager.carrot_seeds -= 6;
                        else
                            return;
                        break;
                        
                    case ONION:
                        if(GameManager.onion_seeds >= 6)
                            GameManager.onion_seeds -= 6;
                        else
                            return;
                        break;
                   
                    case BLUEBERRY:
                        if(GameManager.blueberry_seeds >= 6)
                        GameManager.blueberry_seeds -= 6;
                        else 
                            return;
                        break;
                        
                    }
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
                    
                    switch (plant.type)
                    {
                    case CARROT:
                        GameManager.carrot_seeds += GameManager.carrot_return_seeds;
                        GameManager.carrots += 6;
                        break;
                    case ONION:
                        GameManager.onion_seeds += GameManager.onion_return_seeds;
                        GameManager.onions += 6;
                        break;
                    case BLUEBERRY:
                        GameManager.blueberry_seeds += GameManager.blueberry_return_seeds;
                        GameManager.blueberries += 12;
                        break;
                
                    }
                   


                    
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
    int _x = 70;
    int _y = 627;
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(40,750);
    glVertex2i(40,690);
    glVertex2i(100,690);
    glVertex2i(100,750);
    glEnd();

    if(SELECTED_ACTION ==  PLANT)
    glBegin(GL_LINE_LOOP);
    glVertex2i(40,670);
    glVertex2i(40,610);
    glVertex2i(100,610);
    glVertex2i(100,670);
    glEnd();

    glRasterPos2i(110, 715);

 
  switch (SELECTED_ACTION)
  {
  case WATER:
    glColor3f(0.25f, 0.258f, 0.277f);
    glBegin(GL_POLYGON);
    glVertex2i(x+15,y);
    glVertex2i(x+35,y);
    glVertex2i(x+45,y+30);
    glVertex2i(x+5,y+30);
    glEnd();
    glColor3f(0.109f, 0.62f, 0.89f);
   
    glBegin(GL_POLYGON);
    glVertex2i(x+45,y+28);
    glVertex2i(x+5,y+28);
    glVertex2i(x+9,y+25);
    glVertex2i(x+41,y+25);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0; i<5;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a_water[i]);

      break;

  case TILL:
    glColor3f(0.525f, 0.286f, 0.184f);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x+40,y+40);
    glEnd();
    glColor3f(0.25f, 0.258f, 0.277f);
    glBegin(GL_POLYGON);
    glVertex2i(x+40,y+40);
    glVertex2i(x+35,y+30);
    glVertex2i(x+45,y+25);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0; i<6;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a_plough[i]);

  break;

  case PLANT:
        x+=23;
        y-=5;
        glColor3f(0.882f, 0.741f, 0.345f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2i(x,y+22);
        glVertex2i(x-3,y+19);
        glVertex2i(x+4,y+30);
        glVertex2i(x-5,y+32);
        glEnd();
            glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0; i<5;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a_seed[i]);
  break;

  case HARVEST:
    glColor3f(0.525f, 0.286f, 0.184f);
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(x+20,y+20);
    glEnd();

    glColor3f(0.25f, 0.258f, 0.277f);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+20,y+20);
    glVertex2i(x+13,y+30);
    glVertex2i(x+20,y+40);
    glVertex2i(x+35,y+40);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
    for(int i = 0; i<7;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a_harvest[i]);
  break;
  }
    
    glRasterPos2i(110, 635);

    if(SELECTED_ACTION == PLANT)
    switch (SELECTED_PLANT)
    {
    case ONION:
        _y+=10;
            glColor3f(1.0f,1.0f,1.0f);
        for(int i = 0; i<5;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p_onion[i]);
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glColor3f(0.2f, 0.275f, 0.208f);
        glVertex2i(_x+2.5,_y+7);
        glVertex2i(_x+12.5,_y+10);
        glVertex2i(_x-1.5,_y+3);
        glVertex2i(_x-7.5,_y+9);
        glColor3f(0.949f, 0.839f, 0.906f);
        glVertex2i(_x,_y);
        glColor3f(0.422f, 0.576f, 0.439f);
        glVertex2i(_x,_y+15);
        glLineWidth(20.0f);

        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.824f, 0.275f, 0.769f);
        glVertex2i(_x-10,_y);
        glVertex2i(_x+10,_y);
        glVertex2i(_x+7,_y-15);
        glVertex2i(_x-7,_y-15);
        glEnd();


        break;

    case BLUEBERRY:

        _y+=7;
            glColor3f(1.0f,1.0f,1.0f);
        for(int i = 0; i<9;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p_blueberry[i]);
        glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(_x-10,_y);
        glVertex2i(_x,_y+20); 
        glVertex2i(_x+10,_y);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2i(_x-10,_y+15);
        glVertex2i(_x,_y-5); 
        glVertex2i(_x+10,_y+15);
        glEnd();

        glColor3f(0.164f, 0.266f, 0.718f);
        glPointSize(4.0f);
        glBegin(GL_POINTS);
        glVertex2i(_x-7,_y+13);
        glVertex2i(_x,_y-2); 
        glVertex2i(_x+7,_y+13);
        glVertex2i(_x,_y+7);
        glVertex2i(_x-7,_y);
        glVertex2i(_x,_y+17); 
        glVertex2i(_x+7,_y);
        glEnd();

    break;

    case CARROT:
        glColor3f(1.0f,1.0f,1.0f);
        for(int i = 0; i<6;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, p_onion[i]);


        glColor3f(0.988f, 0.596f, 0.055f);
        glBegin(GL_POLYGON);
        glVertex2i(_x,_y-10); 
        glVertex2i(_x-10,_y+20);
        glVertex2i(_x+10,_y+20); 
        glEnd();

         glColor3f(0.145f, 0.301f, 0.203f);
        glBegin(GL_POLYGON);
        glVertex2i(_x,_y+20);
        glVertex2i(_x-5,_y+30); 
        glVertex2i(_x-7.5,_y+25);
        glVertex2i(_x-5,_y+35); 
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2i(_x,_y+20);
        glVertex2i(_x+5,_y+30); 
        glVertex2i(_x+7.5,_y+25);
        glVertex2i(_x+5,_y+35); 
        glEnd();
    break;

    }


}

#pragma endregion

#pragma region MENU_FUNCTIONS

void actionMenuCallBack(int option) {
    SELECTED_ACTION = static_cast<Actions>(option);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();

}

void travelMenuCallBack(int option)
{
    CURRENT_LOCATION = static_cast<Locations>(option);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();

}

void plantSelectCallBack(int option)
{
    SELECTED_PLANT = static_cast<PlantType>(option);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();

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

void drawFieldSurroundings()
{

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
    glutPostRedisplay();
}

void writeText(int x, int y, char* string)
{
   // glColor3f(colorR,colorG,colorB);
    glRasterPos2i(x,y);
    int l = strlen(string);
    for(int i = 0; i < l; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);

}

void certPage()
{
   // glClearColor(0,0,0,1);
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_POLYGON);
        glVertex2i(0,0);
        glVertex2i(0,900);
        glVertex2i(1800,900);
        glVertex2i(1800,0);
    glEnd();

	glColor3f(1.0, 0.0, 0.0);
	writeText(450, 700, "SAHYADRI COLLEGE OF ENGINEERING AND MANAGEMENT");
	glColor3f(1.0, 1.0, 1.0);
	writeText(450, 650, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(0.0, 0.0, 1.0);
	writeText(680, 550, "A MINI PROJECT ON ");
	glColor3f(1.0, 0.0, 1.0);
	writeText(668, 520,"Farming Simulator Game");
   	glColor3f(1.0, 0.7, 0.8);
	writeText(755, 450, "Created By");
	glColor3f(1.0, 1.0, 1.0);
    writeText(765, 400,"Anish U");
    glColor3f(1.0, 1.0, 1.0);
    writeText(738, 375, "4SF20CS014");

    glColor3f(1.0, 0.0, 0.0);
    writeText(690, 300,"Under the Guidance of");
    glColor3f(1.0, 1.0, 1.0);
    writeText(730, 270, "Ms Megha Rani");
    glColor3f(1.0, 1.0, 1.0);   
    writeText(710, 240, "Assistant Professor");
    glColor3f(1.0, 0.0, 0.0);
    writeText(730, 180, "Academic Year");
    glColor3f(1.0, 1.0, 1.0);
    writeText(755, 155, "2022-2023");
    glColor3f(1.0, 1.0, 1.0);
    writeText(650, 75, "Press ENTER to start the game");


}

void drawInventory()
{
    if(!isInventoryOpen)
        return;

    glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_POLYGON);
        glVertex2i(600,300);
        glVertex2i(1000,300);
        glVertex2i(1000,600);
        glVertex2i(600,600);
    glEnd();
    char temp[100];
    glColor3f(1,1,1);
    writeText(750,570,"Inventory");
    sprintf(temp,"Carrots                     x %d",GameManager.carrots);
    writeText(670,530,temp);
    sprintf(temp,"Carrot Seeds            x %d",GameManager.carrot_seeds);
    writeText(670,490,temp);
    sprintf(temp,"Onions                     x %d",GameManager.onions);
    writeText(670,450,temp);
    sprintf(temp,"Onion Seeds            x %d",GameManager.onion_seeds);
    writeText(670,410,temp);
    sprintf(temp,"Blueberries              x %d",GameManager.blueberries);
    writeText(670,370,temp);  
    sprintf(temp,"Blueberry Seeds      x %d",GameManager.blueberry_seeds);
    writeText(670,330,temp);



}

void display() {

    switch (CURRENT_LOCATION)
    {
        case FIELD:
            glClear(GL_COLOR_BUFFER_BIT);
            drawFieldSurroundings();
            glDisable(GL_LINE_STIPPLE);

            for(int i = 0; i<FIELDS_COUNT; i++)
            {
                ACTIVE_FIELDS[i].drawSelf();
            }

            drawHouse();
            drawTool(45,700);
            drawInventory();
        break;

        case CERTIFICATE_PAGE:
            certPage();
        break;
    }

    
    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        int mouseX, mouseY;
        mouseX = x + 30;
        mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y - 30;
        if(!isInventoryOpen)
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
        case 'i':
            isInventoryOpen = !isInventoryOpen;
            glutPostRedisplay();
            break;
        case 13:
            if(CURRENT_LOCATION == CERTIFICATE_PAGE)
            CURRENT_LOCATION = FIELD;
            glutPostRedisplay();
            glClear(GL_COLOR_BUFFER_BIT);
            break;
    }
}

void initializeGlut()
{
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Farming Simulator Game");
    gluOrtho2D(0,1600,0,800);
    glClearColor(0.254f, 0.547f, 0.066f,0.0f);
    glutFullScreen();

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