#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>


 GLfloat points[][54][3] = 
    {
        //----------------------------- FACE - F --------------------------//

    {{0.0f,0.3f,0.3f},{0.1f,0.3f,0.3f},{0.1f,0.2f,0.3f},{0.0f,0.2f,0.3f}}, //0
    {{0.1f,0.3f,0.3f},{0.2f,0.3f,0.3f},{0.2f,0.2f,0.3f},{0.1f,0.2f,0.3f}}, //1
    {{0.2f,0.3f,0.3f},{0.3f,0.3f,0.3f},{0.3f,0.2f,0.3f},{0.2f,0.2f,0.3f}}, //2
    {{0.0f,0.2f,0.3f},{0.1f,0.2f,0.3f},{0.1f,0.1f,0.3f},{0.0f,0.1f,0.3f}}, //3
    {{0.1f,0.2f,0.3f},{0.2f,0.2f,0.3f},{0.2f,0.1f,0.3f},{0.1f,0.1f,0.3f}}, //4
    {{0.2f,0.2f,0.3f},{0.3f,0.2f,0.3f},{0.3f,0.1f,0.3f},{0.2f,0.1f,0.3f}}, //5
    {{0.0f,0.1f,0.3f},{0.1f,0.1f,0.3f},{0.1f,0.0f,0.3f},{0.0f,0.0f,0.3f}}, //6
    {{0.1f,0.1f,0.3f},{0.2f,0.1f,0.3f},{0.2f,0.0f,0.3f},{0.1f,0.0f,0.3f}}, //7
    {{0.2f,0.1f,0.3f},{0.3f,0.1f,0.3f},{0.3f,0.0f,0.3f},{0.2f,0.0f,0.3f}}, //8

    //---------------------------- FACE - D ---------------------------//

    {{0.0f,0.0f,0.3f},{0.1f,0.0f,0.3f},{0.1f,0.0f,0.2f},{0.0f,0.0f,0.2f}}, //9
    {{0.1f,0.0f,0.3f},{0.2f,0.0f,0.3f},{0.2f,0.0f,0.2f},{0.1f,0.0f,0.2f}}, //10
    {{0.2f,0.0f,0.3f},{0.3f,0.0f,0.3f},{0.3f,0.0f,0.2f},{0.2f,0.0f,0.2f}}, //11
    {{0.0f,0.0f,0.2f},{0.1f,0.0f,0.2f},{0.1f,0.0f,0.1f},{0.0f,0.0f,0.1f}}, //12
    {{0.1f,0.0f,0.2f},{0.2f,0.0f,0.2f},{0.2f,0.0f,0.1f},{0.1f,0.0f,0.1f}}, //13
    {{0.2f,0.0f,0.2f},{0.3f,0.0f,0.2f},{0.3f,0.0f,0.1f},{0.2f,0.0f,0.1f}}, //14
    {{0.0f,0.0f,0.1f},{0.1f,0.0f,0.1f},{0.1f,0.0f,0.0f},{0.0f,0.0f,0.0f}}, //15
    {{0.1f,0.0f,0.1f},{0.2f,0.0f,0.1f},{0.2f,0.0f,0.0f},{0.1f,0.0f,0.0f}}, //16
    {{0.2f,0.0f,0.1f},{0.3f,0.0f,0.1f},{0.3f,0.0f,0.0f},{0.2f,0.0f,0.0f}}, //17

    //---------------------------- FACE - B ---------------------------//

    {{0.0f,0.0f,0.0f},{0.1f,0.0f,0.0f},{0.1f,0.1f,0.0f},{0.0f,0.1f,0.0f}}, //18
    {{0.1f,0.0f,0.0f},{0.2f,0.0f,0.0f},{0.2f,0.1f,0.0f},{0.1f,0.1f,0.0f}}, //19
    {{0.2f,0.0f,0.0f},{0.3f,0.0f,0.0f},{0.3f,0.1f,0.0f},{0.2f,0.1f,0.0f}}, //20
    {{0.0f,0.1f,0.0f},{0.1f,0.1f,0.0f},{0.1f,0.2f,0.0f},{0.0f,0.2f,0.0f}}, //21
    {{0.1f,0.1f,0.0f},{0.2f,0.1f,0.0f},{0.2f,0.2f,0.0f},{0.1f,0.2f,0.0f}}, //22
    {{0.2f,0.1f,0.0f},{0.3f,0.1f,0.0f},{0.3f,0.2f,0.0f},{0.2f,0.2f,0.0f}}, //23
    {{0.0f,0.2f,0.0f},{0.1f,0.2f,0.0f},{0.1f,0.3f,0.0f},{0.0f,0.3f,0.0f}}, //24
    {{0.1f,0.2f,0.0f},{0.2f,0.2f,0.0f},{0.2f,0.3f,0.0f},{0.1f,0.3f,0.0f}}, //25
    {{0.2f,0.2f,0.0f},{0.3f,0.2f,0.0f},{0.3f,0.3f,0.0f},{0.2f,0.3f,0.0f}}, //26
    //---------------------------- FACE - T ---------------------------//

    {{0.0f,0.3f,0.0f},{0.1f,0.3f,0.0f},{0.1f,0.3f,0.1f},{0.0f,0.3f,0.1f}}, //27
    {{0.1f,0.3f,0.0f},{0.2f,0.3f,0.0f},{0.2f,0.3f,0.1f},{0.1f,0.3f,0.1f}}, //28
    {{0.2f,0.3f,0.0f},{0.3f,0.3f,0.0f},{0.3f,0.3f,0.1f},{0.2f,0.3f,0.1f}}, //29
    {{0.0f,0.3f,0.1f},{0.1f,0.3f,0.1f},{0.1f,0.3f,0.2f},{0.0f,0.3f,0.2f}}, //30
    {{0.1f,0.3f,0.1f},{0.2f,0.3f,0.1f},{0.2f,0.3f,0.2f},{0.1f,0.3f,0.2f}}, //31
    {{0.2f,0.3f,0.2f},{0.3f,0.3f,0.1f},{0.3f,0.3f,0.2f},{0.2f,0.3f,0.2f}}, //32
    {{0.0f,0.3f,0.2f},{0.1f,0.3f,0.2f},{0.1f,0.3f,0.3f},{0.0f,0.3f,0.3f}}, //33
    {{0.1f,0.3f,0.2f},{0.2f,0.3f,0.2f},{0.2f,0.3f,0.3f},{0.1f,0.3f,0.3f}}, //34
    {{0.2f,0.3f,0.2f},{0.3f,0.3f,0.2f},{0.3f,0.3f,0.3f},{0.2f,0.3f,0.3f}} ,//35

/*
    {{0,3,0},{1,3,0},{1,3,1},{0,3,1}}, //27
    {{1,3,0},{2,3,0},{2,3,1},{1,3,1}}, //28
    {{2,3,0},{3,3,0},{3,3,1},{2,3,1}}, //29
    {{0,3,1},{1,3,1},{1,3,2},{0,3,2}}, //30
    {{1,3,1},{2,3,1},{2,3,2},{1,3,2}}, //31
    {{2,3,2},{3,3,1},{3,3,2},{2,3,2}}, //32
    {{0,3,2},{1,3,2},{1,3,3},{0,3,3}}, //33
    {{1,3,2},{2,3,2},{2,3,3},{1,3,3}}, //34
    {{2,3,2},{3,3,2},{3,3,3},{2,3,3}}, //35
    */
    //---------------------------- FACE - D ---------------------------//
/*
    {{0,3,3},{0,2,3},{0,2,2},{0,3,2}}, //36
    {{0,2,3},{0,1,3},{0,1,2},{0,2,2}}, //37
    {{0,1,3},{0,0,3},{0,0,2},{0,1,2}}, //38
    {{0,3,2},{0,2,2},{0,2,1},{0,3,1}}, //39
    {{0,2,2},{0,1,2},{0,1,1},{0,2,1}}, //40
    {{0,1,2},{0,0,2},{0,0,1},{0,1,1}}, //41
    {{0,3,1},{0,2,1},{0,2,0},{0,3,0}}, //42
    {{0,2,1},{0,1,1},{0,1,0},{0,2,0}}, //43
    {{0,1,1},{0,0,1},{0,0,0},{0,1,0}}, //44
*/

{{0.0f,0.3f,0.3f},{0.0f,0.2f,0.3f},{0.0f,0.2f,0.2f},{0.0f,0.3f,0.2f}}, //36
{{0.0f,0.2f,0.3f},{0.0f,0.1f,0.3f},{0.0f,0.1f,0.2f},{0.0f,0.2f,0.2f}}, //37
{{0.0f,0.1f,0.3f},{0.0f,0.0f,0.3f},{0.0f,0.0f,0.2f},{0.0f,0.1f,0.2f}}, //38
{{0.0f,0.3f,0.2f},{0.0f,0.2f,0.2f},{0.0f,0.2f,0.1f},{0.0f,0.3f,0.1f}}, //39
{{0.0f,0.2f,0.2f},{0.0f,0.1f,0.2f},{0.0f,0.1f,0.1f},{0.0f,0.2f,0.1f}}, //40
{{0.0f,0.1f,0.2f},{0.0f,0.0f,0.2f},{0.0f,0.0f,0.1f},{0.0f,0.1f,0.1f}}, //41
{{0.0f,0.3f,0.1f},{0.0f,0.2f,0.1f},{0.0f,0.2f,0.0f},{0.0f,0.3f,0.0f}}, //42
{{0.0f,0.2f,0.1f},{0.0f,0.1f,0.1f},{0.0f,0.1f,0.0f},{0.0f,0.2f,0.0f}}, //43
{{0.0f,0.1f,0.1f},{0.0f,0.0f,0.1f},{0.0f,0.0f,0.0f},{0.0f,0.1f,0.0f}}, //44

    //---------------------------- FACE - D ---------------------------//

{{0.3f,0.0f,0.3f},{0.3f,0.1f,0.3f},{0.3f,0.1f,0.2f},{0.3f,0.0f,0.2f}}, //45
{{0.3f,0.1f,0.3f},{0.3f,0.2f,0.3f},{0.3f,0.2f,0.2f},{0.3f,0.1f,0.2f}}, //46
{{0.3f,0.2f,0.3f},{0.3f,0.3f,0.3f},{0.3f,0.3f,0.2f},{0.3f,0.2f,0.2f}}, //47
{{0.3f,0.0f,0.2f},{0.3f,0.1f,0.2f},{0.3f,0.1f,0.1f},{0.3f,0.0f,0.1f}}, //48
{{0.3f,0.1f,0.2f},{0.3f,0.2f,0.2f},{0.3f,0.2f,0.1f},{0.3f,0.1f,0.1f}}, //49
{{0.3f,0.2f,0.2f},{0.3f,0.3f,0.2f},{0.3f,0.3f,0.1f},{0.3f,0.2f,0.1f}}, //50
{{0.3f,0.0f,0.1f},{0.3f,0.1f,0.1f},{0.3f,0.1f,0.0f},{0.3f,0.0f,0.0f}}, //51
{{0.3f,0.1f,0.1f},{0.3f,0.2f,0.1f},{0.3f,0.2f,0.0f},{0.3f,0.1f,0.0f}}, //52
{{0.3f,0.2f,0.1f},{0.3f,0.3f,0.1f},{0.3f,0.3f,0.0f},{0.3f,0.2f,0.0f}} //53

    
    };


char COLOR_MATRIX[] = 
{
    //--FRONT-FACE--//
    'R','R','R',
    'R','R','R',
    'R','R','R',
    //--DOWN-FACE--//
    'Y','Y','Y',
    'Y','Y','Y',
    'Y','Y','Y',
    //--BACK-FACE--//
    'O','O','O',
    'O','O','O',
    'O','O','O',
    //--TOP-FACE--//
    'W','W','W',
    'W','W','W',
    'W','W','W',
    //--LEFT-FACE--//
    'G','G','G',
    'G','G','G',
    'G','G','G',
    //--RIGHT-FACE--//
    'B','B','B',
    'B','B','B',
    'B','B','B'
};


void setColor(char color)
{

    switch (color)
    {
    case 'R':
        glColor3f(1.0f,0.0f,0.0f);
        break;
    case 'G':
        glColor3f(0.0f,1.0f,0.0f);
        break;
    case 'B':
        glColor3f(0.0f,0.0f,1.0f);
        break;
    case 'W':
        glColor3f(1.0f,1.0f,1.0f);
        break;
    case 'Y':
        glColor3f(1.0f,1.0f,0.0f);
        break;
    case 'O':
        glColor3f(1.0f,0.5f,0.0f);
        break;
    default:
        break;
    }
}


void cube()
{
     
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0f, 1.0f, 0.1f, 200.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.3f, -0.6f, -1.5f);
      // move the camera back along the z-axis





  /*  GLfloat points[][54][3] = 
    {
    //----------------------------- FACE - F --------------------------//

    {{0,3,3},{1,3,3},{1,2,3},{0,2,3}}, //0
    {{1,3,3},{2,3,3},{2,2,3},{1,2,3}}, //1
    {{2,3,3},{3,3,3},{3,2,3},{2,2,3}}, //2
    {{0,2,3},{1,2,3},{1,1,3},{0,1,3}}, //3
    {{1,2,3},{2,2,3},{2,1,3},{1,1,3}}, //4
    {{2,2,3},{3,2,3},{3,1,3},{2,1,3}}, //5
    {{0,1,3},{1,1,3},{1,0,3},{0,0,3}}, //6
    {{1,1,3},{2,1,3},{2,0,3},{1,0,3}}, //7
    {{2,1,3},{3,1,3},{3,0,3},{2,0,3}}, //8

    //---------------------------- FACE - D ---------------------------//

    {{0,0,3},{1,0,3},{1,0,2},{0,0,2}}, //9
    {{1,0,3},{2,0,3},{2,0,2},{1,0,2}}, //10
    {{2,0,3},{3,0,3},{3,0,2},{2,0,2}}, //11
    {{0,0,2},{1,0,2},{1,0,1},{0,0,1}}, //12
    {{1,0,2},{2,0,2},{2,0,1},{1,0,1}}, //13
    {{2,0,2},{3,0,2},{3,0,1},{2,0,1}}, //14
    {{0,0,1},{1,0,1},{1,0,0},{0,0,0}}, //15
    {{1,0,1},{2,0,1},{2,0,0},{1,0,0}}, //16
    {{2,0,1},{3,0,1},{3,0,0},{2,0,0}}, //17

    //---------------------------- FACE - B ---------------------------//

    {{0,0,0},{1,0,0},{1,1,0},{0,1,0}}, //18
    {{1,0,0},{2,0,0},{2,1,0},{1,1,0}}, //19
    {{2,0,0},{3,0,0},{3,1,0},{2,1,0}}, //20
    {{0,1,0},{1,1,0},{1,2,0},{0,2,0}}, //21
    {{1,1,0},{2,1,0},{2,2,0},{1,2,0}}, //22
    {{2,1,0},{3,1,0},{3,2,0},{2,2,0}}, //23
    {{0,2,0},{1,2,0},{1,3,0},{0,3,0}}, //24
    {{1,2,0},{2,2,0},{2,3,0},{1,3,0}}, //25
    {{2,2,0},{3,2,0},{3,3,0},{2,3,0}}, //26

    //---------------------------- FACE - T ---------------------------//

    {{0,3,0},{1,3,0},{1,3,1},{0,3,1}}, //27
    {{1,3,0},{2,3,0},{2,3,1},{1,3,1}}, //28
    {{2,3,0},{3,3,0},{3,3,1},{2,3,1}}, //29
    {{0,3,1},{1,3,1},{1,3,2},{0,3,2}}, //30
    {{1,3,1},{2,3,1},{2,3,2},{1,3,2}}, //31
    {{2,3,2},{3,3,1},{3,3,2},{2,3,2}}, //32
    {{0,3,2},{1,3,2},{1,3,3},{0,3,3}}, //33
    {{1,3,2},{2,3,2},{2,3,3},{1,3,3}}, //34
    {{2,3,2},{3,3,2},{3,3,3},{2,3,3}}, //35
    
    //---------------------------- FACE - D ---------------------------//

    {{0,3,3},{0,2,3},{0,2,2},{0,3,2}}, //36
    {{0,2,3},{0,1,3},{0,1,2},{0,2,2}}, //37
    {{0,1,3},{0,0,3},{0,0,2},{0,1,2}}, //38
    {{0,3,2},{0,2,2},{0,2,1},{0,3,1}}, //39
    {{0,2,2},{0,1,2},{0,1,1},{0,2,1}}, //40
    {{0,1,2},{0,0,2},{0,0,1},{0,1,1}}, //41
    {{0,3,1},{0,2,1},{0,2,0},{0,3,0}}, //42
    {{0,2,1},{0,1,1},{0,1,0},{0,2,0}}, //43
    {{0,1,1},{0,0,1},{0,0,0},{0,1,0}}, //44

    //---------------------------- FACE - D ---------------------------//

    {{3,0,3},{3,1,3},{3,1,2},{3,0,2}}, //45
    {{3,1,3},{3,2,3},{3,2,2},{3,1,2}}, //46
    {{3,2,3},{3,3,3},{3,3,2},{3,2,2}}, //47
    {{3,0,2},{3,1,2},{3,1,1},{3,0,1}}, //48
    {{3,1,2},{3,2,2},{3,2,1},{3,1,1}}, //49
    {{3,2,2},{3,3,2},{3,3,1},{3,2,1}}, //50
    {{3,0,1},{3,1,1},{3,1,0},{3,0,0}}, //51
    {{3,1,1},{3,2,1},{3,2,0},{3,1,0}}, //52
    {{3,2,1},{3,3,1},{3,3,0},{3,2,0}}, //53
    
    };*/

    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    int colNo = 0;

    for(int i = 0; i<54; i++)
    {
            glBegin(GL_POLYGON);
    setColor(COLOR_MATRIX[i]);
    for(int j =0; j<4;j++)
    glVertex3fv(points[i][j]); 
    glEnd();
    }

    
    glFlush();
   // glutSwapBuffers();
}

char* U_EDGE[] = 
{
    &COLOR_MATRIX[2], &COLOR_MATRIX[1], &COLOR_MATRIX[0],
    &COLOR_MATRIX[36], &COLOR_MATRIX[39], &COLOR_MATRIX[42],
    &COLOR_MATRIX[24], &COLOR_MATRIX[25], &COLOR_MATRIX[26],
    &COLOR_MATRIX[53], &COLOR_MATRIX[50], &COLOR_MATRIX[47]
};

char* D_EDGE[] = 
{
    &COLOR_MATRIX[6], &COLOR_MATRIX[7], &COLOR_MATRIX[8],
    &COLOR_MATRIX[45], &COLOR_MATRIX[48], &COLOR_MATRIX[51],
    &COLOR_MATRIX[20], &COLOR_MATRIX[19], &COLOR_MATRIX[18],
    &COLOR_MATRIX[44], &COLOR_MATRIX[41], &COLOR_MATRIX[38]
};

char* F_EDGE[] = 
{
    &COLOR_MATRIX[33], &COLOR_MATRIX[34], &COLOR_MATRIX[35],
    &COLOR_MATRIX[47], &COLOR_MATRIX[46], &COLOR_MATRIX[45],
    &COLOR_MATRIX[11], &COLOR_MATRIX[10], &COLOR_MATRIX[9],
    &COLOR_MATRIX[38], &COLOR_MATRIX[37], &COLOR_MATRIX[36]
};

char* B_EDGE[] = 
{
    &COLOR_MATRIX[29], &COLOR_MATRIX[28], &COLOR_MATRIX[27],
    &COLOR_MATRIX[42], &COLOR_MATRIX[43], &COLOR_MATRIX[44],
    &COLOR_MATRIX[15], &COLOR_MATRIX[16], &COLOR_MATRIX[17],
    &COLOR_MATRIX[51], &COLOR_MATRIX[52], &COLOR_MATRIX[53]
};

char* MH_EDGE[] = 
{
    &COLOR_MATRIX[5], &COLOR_MATRIX[4], &COLOR_MATRIX[3],
    &COLOR_MATRIX[37], &COLOR_MATRIX[49], &COLOR_MATRIX[43],
    &COLOR_MATRIX[21], &COLOR_MATRIX[22], &COLOR_MATRIX[23],
    &COLOR_MATRIX[52], &COLOR_MATRIX[49], &COLOR_MATRIX[46]
};

char* MV_EDGE[] = 
{
    &COLOR_MATRIX[7], &COLOR_MATRIX[4], &COLOR_MATRIX[1],
    &COLOR_MATRIX[34], &COLOR_MATRIX[31], &COLOR_MATRIX[28],
    &COLOR_MATRIX[25], &COLOR_MATRIX[22], &COLOR_MATRIX[19],
    &COLOR_MATRIX[16], &COLOR_MATRIX[13], &COLOR_MATRIX[10]
};

char* MF_EDGE[] = 
{
    &COLOR_MATRIX[30], &COLOR_MATRIX[31], &COLOR_MATRIX[32],
    &COLOR_MATRIX[50], &COLOR_MATRIX[49], &COLOR_MATRIX[48],
    &COLOR_MATRIX[14], &COLOR_MATRIX[13], &COLOR_MATRIX[12],
    &COLOR_MATRIX[41], &COLOR_MATRIX[40], &COLOR_MATRIX[39]
};

char* R_EDGE[] = 
{
    &COLOR_MATRIX[8], &COLOR_MATRIX[5], &COLOR_MATRIX[2],
    &COLOR_MATRIX[33], &COLOR_MATRIX[32], &COLOR_MATRIX[29],
    &COLOR_MATRIX[26], &COLOR_MATRIX[23], &COLOR_MATRIX[20],
    &COLOR_MATRIX[17], &COLOR_MATRIX[14], &COLOR_MATRIX[11]
};

char* L_EDGE[] = 
{
    &COLOR_MATRIX[0], &COLOR_MATRIX[3], &COLOR_MATRIX[6],
    &COLOR_MATRIX[9], &COLOR_MATRIX[12], &COLOR_MATRIX[15],
    &COLOR_MATRIX[18], &COLOR_MATRIX[21], &COLOR_MATRIX[24],
    &COLOR_MATRIX[27], &COLOR_MATRIX[30], &COLOR_MATRIX[33]
};

//---------------------------------------------------------------//

char* F_FACE[] = 
{
    &COLOR_MATRIX[0], &COLOR_MATRIX[1], &COLOR_MATRIX[2],
    &COLOR_MATRIX[5], &COLOR_MATRIX[8], &COLOR_MATRIX[7],
    &COLOR_MATRIX[6], &COLOR_MATRIX[3]
};

char* B_FACE[] = 
{
    &COLOR_MATRIX[26], &COLOR_MATRIX[25], &COLOR_MATRIX[24],
    &COLOR_MATRIX[21], &COLOR_MATRIX[18], &COLOR_MATRIX[19],
    &COLOR_MATRIX[20], &COLOR_MATRIX[23]
};

char* R_FACE[] = 
{
    &COLOR_MATRIX[47], &COLOR_MATRIX[50], &COLOR_MATRIX[53],
    &COLOR_MATRIX[52], &COLOR_MATRIX[51], &COLOR_MATRIX[48],
    &COLOR_MATRIX[45], &COLOR_MATRIX[46]
};

char* L_FACE[] = 
{
    &COLOR_MATRIX[42], &COLOR_MATRIX[39], &COLOR_MATRIX[36],
    &COLOR_MATRIX[37], &COLOR_MATRIX[38], &COLOR_MATRIX[41],
    &COLOR_MATRIX[44], &COLOR_MATRIX[43]
};

char* U_FACE[] = 
{
    &COLOR_MATRIX[27], &COLOR_MATRIX[28], &COLOR_MATRIX[29],
    &COLOR_MATRIX[32], &COLOR_MATRIX[35], &COLOR_MATRIX[34],
    &COLOR_MATRIX[33], &COLOR_MATRIX[30]
};

char* D_FACE[] = 
{
    &COLOR_MATRIX[9], &COLOR_MATRIX[10], &COLOR_MATRIX[11],
    &COLOR_MATRIX[14], &COLOR_MATRIX[17], &COLOR_MATRIX[16],
    &COLOR_MATRIX[15], &COLOR_MATRIX[12]
};

void edgeTurnClockWise(char* faces[])
{
char temp1 = *faces[11];
char temp2 = *faces[10];
char temp3 = *faces[9];

for(int i = 11; i>=1; i--)
    *faces[i] = *faces[i-3];

*faces[0] = temp3;
*faces[1] = temp2;
*faces[2] = temp1;
}

void edgeTurnAntiClockWise(char* faces[])
{
  
char temp1 = *faces[0];
char temp2 = *faces[1];
char temp3 = *faces[2];

for(int i = 0; i<=8; i++)
    *faces[i] = *faces[i+3];
;
*faces[11] = temp3;
*faces[10] = temp2;
*faces[9] = temp1;
}


void faceTurnClockWise(char* faces[])
{
char temp1 = *faces[7];
char temp2 = *faces[6];

for(int i = 7; i>=1; i--)
    *faces[i] = *faces[i-2];

*faces[0] = temp2;
*faces[1] = temp1;
}

void faceTurnAntiClockWise(char* faces[])
{
char temp1 = *faces[0];
char temp2 = *faces[1];

for(int i = 0; i<=5; i++)
    *faces[i] = *faces[i+2];

*faces[6] = temp1;
*faces[7] = temp2;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(20);
    glBegin(GL_LINES);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void input(unsigned char key, int x, int y)
{
    if(key == 'w')
    {
        edgeTurnAntiClockWise(L_EDGE);
       
    }
        if(key == 'e')
    {
          edgeTurnAntiClockWise(R_EDGE);
       
    }

            if(key == 'r')
    {
          edgeTurnAntiClockWise(U_EDGE);
          faceTurnAntiClockWise(U_FACE);
       
    }


    glutPostRedisplay();

}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Line Animation");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  //  glEnable(GL_DEPTH_TEST);
   // glTranslatef(50.0f, 0.0f, -50.0f);
    
    glutDisplayFunc(cube);
    glutKeyboardFunc(input);
    glutMainLoop();
  
    return 0;
}


