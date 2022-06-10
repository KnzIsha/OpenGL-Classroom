// 1607060_ Hometask_3

#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

const int width = 800;   //1000;
const int height = 600;  //1000;

bool left_light = true;
bool right_light = false;
bool spot_light = false;

bool activate_amb = true;
bool activate_diff = true;
bool activate_spec = true;


int deg = 0;
const float rat = 1.0 * width / height;

float light_bright = 0.75;
float light_amb = 0.3;

bool flagScale=true;

GLfloat eyeX = 0; // 10
GLfloat eyeY = 58; // 0
GLfloat eyeZ = -90; //- 15

GLfloat lookX = 0;
GLfloat lookY = 58;
GLfloat lookZ = 0;

float room_width=80, room_height=100, room_length=120;
float floor_height=0.05, ceil_height=0.1;
float wall_thiickness=0.1;
float rot = 0;

static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

static void reshape(int width, int height)
{
    glViewport(0, 0, width, width/rat);
     //glFrustum(-rat, rat, -1.0, 1.0, 2.0, 100.0);

}


static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}



void cube(float r=0.5, float g=0.5, float b=0.5, float alpha=1)
{
    GLfloat mat_amb[] = {r*light_amb*light_bright,g*light_amb*light_bright,b*light_amb*light_bright,1.0};
    GLfloat mat_diff[] = {r*light_bright,g*light_bright,b*light_bright,1.0};
    GLfloat mat_spec[] = {1,1,1,1.0};
    GLfloat mat_shiny[] = {60};

    GLfloat m_emission[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void axes()
{
    float length = 100;
    float width = 0.2;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.0,1.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.0,0.0,1.0);
    glPopMatrix();

}

void fan()
{
    float length =1;
    float height =15;
    float width =1;

    float blade_length =20;
    float blade_height =1;
    float blade_width =4;


    glPushMatrix();
    glRotatef(deg,0,1,0);

    glPushMatrix();
    glTranslatef(0,room_height-height,0);
    glScalef(blade_width,blade_height,blade_length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,room_height-height,0);
    glScalef(blade_length,blade_height,blade_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,room_height,0);
    glScalef(width,height,length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    for (int i=1; i<=360; i++)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        glTranslatef(0,room_height-height+(10.3),0);
        glScalef(1,blade_height*10.3,0.5);
        glTranslatef(-0.5,-1,-0.5);
        cube(0.502, 0.000, 0.000);
        glPopMatrix();
    }

}


void floor_cube()
{

    glPushMatrix();
    glScalef(room_length*2,floor_height,room_width*2);
    glTranslatef(-.5,-.5,-.5);
    cube(0.878, 1.000, 1.000); // Light Cyan

    glPopMatrix();
}
void ceil_cube()
{

    glPushMatrix();
    glTranslatef(0,room_height+(ceil_height*.5),0);
    glScalef(room_length*2,ceil_height,room_width*2);
    glTranslatef(-.5,-.5,-.5);
    cube(0.902, 0.902, 0.980); // Lavender
    glPopMatrix();
}

void wall_cube()
{
    glPushMatrix();
    glTranslatef(0,(room_height*.5),room_width);
    glScalef(room_length*2,room_height,wall_thiickness);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.980, 0.980, 0.824);  //Light Golden Yellow
    glPopMatrix();
}


void left_cube()
{
    glPushMatrix();

    glTranslatef(room_length+(wall_thiickness*.5),(room_height*.5),0);
    glScalef(wall_thiickness,room_height,room_width*2);
    glTranslatef(-.5,-.5,-.5);
    cube(1.000, 1, 0.878);  //Light Yellow
    glPopMatrix();
}

void right_cube()
{
    glPushMatrix();

    glTranslatef(-room_length+(wall_thiickness*.5),(room_height*.5),0);
    glScalef(wall_thiickness,room_height,room_width*2);
    glTranslatef(-.5,-.5,-.5);
    cube(1.000, 1, 0.878);  //Light Yellow
    glPopMatrix();
}

void standing_dis()
{
    float stand_width=15, stand_length=60, stand_height=1, stand_ypos=10;
    float stand_z=room_width-1;

    float leg_x=1.5,  leg_height=stand_ypos-(stand_height);

    glPushMatrix();

    glPushMatrix();
    glTranslatef(0,stand_ypos-stand_height,(stand_z-(stand_width*.5)));
    glScalef(stand_length*2,stand_height*2,stand_width);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.545, 0.271, 0.075); // SaddleBrown
    glPopMatrix();

    //  right leg
    glPushMatrix();

    glPushMatrix();
    glTranslatef(-(stand_length)+(leg_x),leg_height/2,(stand_z-(stand_width*.5)));
    glScalef(leg_x*2,leg_height,stand_width);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.545, 0.271, 0.075); // SaddleBrown
    glPopMatrix();


    //  left leg
    glPushMatrix();

    glPushMatrix();
    glTranslatef((stand_length)-(leg_x),leg_height/2,(stand_z-(stand_width*.5)));
    glScalef(leg_x*2,leg_height,stand_width);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.545, 0.271, 0.075); // SaddleBrown
    glPopMatrix();

    glPopMatrix();

}

void black_board()
{
    float board_atheight=40, board_width=0.1, board_length=60, board_height=60;

    glPushMatrix();

    glPushMatrix();
    glTranslatef(0,board_height*.5+board_atheight,room_width-(board_width));
    glScalef(board_length*2,board_height,board_width);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.545, 0.271, 0.075); // blackborad boarder
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,board_height*.5+board_atheight,room_width-(board_width));
    glScalef((board_length*2)-4,board_height-4,board_width+.1);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.0, 0.0, 0.0); // black board
    glPopMatrix();

    glPopMatrix();

}
void cabinet()
{
    float cabinet_width=6, cabinet_length=20, cabinet_height=45;

    float cabinet_z=room_width-1, cabinet_x=85 ;

    glPushMatrix();

    glPushMatrix();
    glTranslatef(cabinet_x,cabinet_height,cabinet_z-cabinet_width);

    glScalef(cabinet_length*2,cabinet_height*2,cabinet_width*2);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.482, 0.408, 0.933); // wheat
    glPopMatrix();

//    glPushMatrix();
//     glTranslatef(cabinet_x,cabinet_height,cabinet_z-cabinet_width);
//    glScalef(cabinet_length-4,cabinet_height*2-4,0.6);
//    glTranslatef(-.5,-.5,-0.5);
//    cube(0.482, 0.408, 0.933); // wheat
//    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(5.6,4,6);
//    glScalef(2,7,.01);
//    glTranslatef(-.5,-.5,-0.5);
//    cube(0.282, 0.239, 0.545); // wheat
//    glPopMatrix();

    glPopMatrix();

}

void part_cabinet()
{
    float boarder_length=20, boarder_height=16.1 ,boarder_width=6 ,height = 0.0;


    for(int i = 0; i<3; i++)
    {

        glPushMatrix();
        glTranslatef(0,height,0);

        glPushMatrix();
        glScalef(boarder_length,boarder_height*2,boarder_width*2);
        glTranslatef(-0.5,0,-0.5);
        cube(0.282, 0.239, 0.545); //midnight blue
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,3,-boarder_width+(.8/2)-.02);
        glScalef((boarder_length)-6,(boarder_height*2)-4,.8);
        glTranslatef(-0.5,0,-0.5);
        cube(0.576, 0.439, 0.859); //Azure
        glPopMatrix();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(boarder_length,height,0);

        glPushMatrix();
        glScalef(boarder_length,boarder_height*2,boarder_width*2);
        glTranslatef(-0.5,0,-0.5);
        cube(0.282, 0.239, 0.545); //midnight blue
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,3,-boarder_width+(.8/2)-.02);
        glScalef((boarder_length)-6,(boarder_height*2)-4,.8);
        glTranslatef(-0.5,0,-0.5);
        cube(0.576, 0.439, 0.859); //Azure
        glPopMatrix();

        glPopMatrix();


        height += boarder_height*2;
    }


}


void table(float table_x=5, float table_z=-15)
{
    // float table_x =5, table_z= -15;

    float height=23;
    float width=25; // x axis
    float length=8;

    float base_height=2;
    float leg_height=height-base_height;

    float leg_width= 0.8, leg_length=2;

    // float leg_width=1.5;

    // whole table
    glPushMatrix();
    glTranslatef(table_x,leg_height,table_z);

    // base
    glPushMatrix();
    glScalef(width,base_height,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    // legs
    glPushMatrix();
    glTranslatef((width/2-leg_length/2),0,(length/2-leg_width/2));
    glScalef(leg_length,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((width/2-leg_length/2),0,-(length/2-leg_width/2));
    glScalef(leg_length,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_length/2),0,(length/2-leg_width/2));
    glScalef(leg_length,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_length/2),0,-(length/2-leg_width/2));
    glScalef(leg_length,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPopMatrix();
}
void animate()
{
    if (flagScale == true)
    {
        deg+= 2;
        if(deg > 360)
            deg = 1;
    }
    glutPostRedisplay();
}

void chair(float table_x =5, float table_z= -15)
{

    float height=15;
    float width=14;
    float length=4;

    float base_height=2;
    float leg_height=height-base_height;
    float leg_width= 0.9, leg_length=2;

    float extension=16.0;

    // whole table
    glPushMatrix();
    glTranslatef(table_x,leg_height,table_z);

    // base
    glPushMatrix();
    glScalef(width,base_height,length);
    glTranslatef(-0.5,0,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();



    // legs
    glPushMatrix();
    glTranslatef((width/2-leg_length/2),0,(length/2-leg_width/2));
    glScalef(leg_length,leg_height,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    // leg with extension
    glPushMatrix();
    glTranslatef((width/2-leg_length/2),0+extension,-(length/2-leg_width/2));
    glScalef(leg_length,leg_height+extension,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(width/2-leg_length/2),0,(length/2-leg_width/2));
    glScalef(leg_length,leg_height+0,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    // leg with extension
    glPushMatrix();
    glTranslatef(-(width/2-leg_width/2),0+extension,-(length/2-leg_width/2));
    glScalef(leg_width,leg_height+extension,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    // middle extension
    glPushMatrix();
    glTranslatef(0,0+extension/2,-(length/2-leg_width/2));
    glScalef(width,leg_width,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    // upper extension
    glPushMatrix();
    glTranslatef(0,0+extension,-(length/2-leg_width/2));
    glScalef(width,leg_width,leg_width);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.53,0.39,0.28);
    glPopMatrix();

    glPopMatrix();
}


void glass_cabinet()
{
   float boarder_length=14, boarder_height=8 ,boarder_width=8 ,height = 0.0;


    for(int i = 0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(0,height,0);

        glPushMatrix();
        glScalef(boarder_length*2,boarder_height*2,boarder_width*2);
        glTranslatef(-0.5,0,-0.5);
        cube(0.53,0.39,0.28); //saddle brown
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,3,-boarder_width+(.8/2)-.02);
        glScalef((boarder_length*2)-6,(boarder_height*2)-4,.8);
        glTranslatef(-0.5,0,-0.5);
        cube(0.941, 1.000, 1.000); //Azure
        glPopMatrix();

        glPopMatrix();

        height += boarder_height*2;
    }


    glPushMatrix();
    glTranslatef(-2,height,-boarder_width/2);
    glScalef(4,12,1);
    cube(0,0,0);
    glPopMatrix();

    height+=8*2;

    glPushMatrix();
    glTranslatef(-boarder_length+8,height-7,-boarder_width/2-3);

    glScalef(12,18,6);

    cube(0.698, 0.133, 0.133); //firebrick

    glPopMatrix();

}



void books()
{

    glPushMatrix();
    glTranslatef(-8.8,5,5);
    glScalef(1.5,.25,1);
    glTranslatef(-.5,-.5,-0.5);
    cube(0, 0.3, 0); // green
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.8,5,7);
    glScalef(1.5,.25,1);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.663, 0.663, 0.663); // dark grey
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.8,5.25,7);
    glScalef(1.5,.25,1);
    glTranslatef(-.5,-.5,-0.5);
    cube(0.098, 0.098, 0.439); // midnight blue
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.8,5.5,7);
    glScalef(1.5,.25,1);
    glTranslatef(-.5,-.5,-0.5);
    cube(1, 0, 0); // red
    glPopMatrix();

}

void wardrobe(float drawerHeight = 3, float drawerWidth = 4, float drawerLength = 3,int numOfDrawer = 2)
{
    int height = 0;
    for(int i = 0; i<numOfDrawer; i++)
    {
        glPushMatrix();
        glTranslatef(0,height,0);

        glPushMatrix();
        glScalef(drawerWidth,drawerHeight,drawerLength);
        glTranslatef(-0.5,0,-0.5);
        cube(0.545,0.271,0.075); //saddle brown
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,-drawerLength/2-0.1/2);
        glScalef(drawerWidth-0.6,drawerHeight-0.3, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.804, 0.522, 0.247); // peru
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,drawerHeight/2-0.1/2,-drawerLength/2-0.15/2);
        glScalef(drawerWidth/4,drawerHeight/8, 0.1);
        glTranslatef(-0.5,0,-0.5);
        cube(0.96, 1, 0.98); //mint white
        glPopMatrix();

        glPopMatrix();

        height += drawerHeight;
    }

    drawerWidth += 0.6;
    drawerLength += 0.45;
    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(0,height,0);
        glScalef(drawerWidth,0.3,drawerLength);
        glTranslatef(-0.5,0,-0.5);
        cube(0.545,0.271,0.075); //saddle brown
        glPopMatrix();

        height += 0.3;
        drawerWidth -= 0.1;
        drawerLength -= 0.1;

    }

}



void window(float width = 20, float length = 50)
{
    glPushMatrix();
    glScalef(width,length,0.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.545,0.271,0.075); //saddle brown
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.8)/2,-(0.1/2-0.05/2)-0.01);
    glScalef(width*0.8,length*0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0.941, 1.000, 1.000); //Azure
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.8)/2,-(0.1/2-0.05/2)-0.02);
    glScalef(0.2,length*0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+2*((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.8,0.05); // *
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,((length-length*0.8)/2)+3*((length*0.8)/4),-(0.1/2-0.05/2)-0.02);
    glScalef(width*0.8,0.8,0.05); // .2
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //Black
    glPopMatrix();
}

void light_left(float x_pos, float y_pos, float z_pos)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_amb[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diff[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { x_pos, y_pos, z_pos, 1.0 };

    glEnable( GL_LIGHT0);
    if(left_light)
    {
        if(activate_amb) glLightfv( GL_LIGHT0, GL_AMBIENT, light_amb);
        else  glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);

        if(activate_diff)    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diff);
        else             glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);

        if(activate_spec) glLightfv( GL_LIGHT0, GL_SPECULAR, light_spec);
        else  glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }
    else
    {
            glDisable(GL_LIGHT0);
    }
    glLightfv( GL_LIGHT0, GL_POSITION, light_pos);
}

void light_right(float x_pos, float y_pos, float z_pos)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_amb[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diff[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { x_pos, y_pos, z_pos, 1.0 };

    glEnable( GL_LIGHT1);
    if(right_light)
    {
        if(activate_amb)  glLightfv( GL_LIGHT1, GL_AMBIENT, light_amb);
        else   glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);


        if(activate_diff)     glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diff);
        else      glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);

        if(activate_spec)      glLightfv( GL_LIGHT1, GL_SPECULAR, light_spec);
        else glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }
    else
    {
             glDisable(GL_LIGHT1);
    }

    glLightfv( GL_LIGHT1, GL_POSITION, light_pos);
}

void spotLight(float x_pos, float y_pos, float z_pos)
{
    GLfloat light_no[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_amb[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diff[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { x_pos, y_pos, z_pos, 1.0 };
    GLfloat spot_direc[] = { 0.0, -1.0, 0.0 };
    GLfloat spot_cutOff[] = {60.0};

    glEnable( GL_LIGHT2);
    if(spot_light)
    {
        if(activate_amb)
        {
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_amb);
        }
        else
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_no);

        if(activate_diff)
        {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diff);
        }
        else
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_no);


        if(activate_spec)
        {
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_spec);
        }
        else
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_no);
    }

    else
    {
        glDisable(GL_LIGHT2);
    }

    glLightfv( GL_LIGHT2, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direc);
    glLightfv( GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutOff);
}

void ligh_handle()
{
    glPushMatrix();
    glScalef(.8,5,.3);
    glTranslatef(-.5,-.5,-.5);
    cube(1,1,1);
    glPopMatrix();
}

void sphere(float r, float g, float b)
{
    GLfloat mat_amb[] = {r*light_amb*light_bright,g*light_amb*light_bright,b*light_amb*light_bright,1.0};
    GLfloat mat_diff[] = {r*light_bright,g*light_bright,b*light_bright,1.0};
    GLfloat mat_spec[] = {1,1,1,1.0};
    GLfloat mat_shiny[] = {60};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);

    glPushMatrix();

     glutSolidSphere(5,10,10);
    glPopMatrix();

}

void light()
{
     glPushMatrix();

    glScalef(.6,6,40);
    glTranslatef(-.5,-.5,-.5);
    cube(0.941, 1.000, 1.000);
    glPopMatrix();
}


void clock(float width, float length)
{
glPushMatrix();
    glScalef(width,length,0.1);
    glTranslatef(-0.5,0,-0.5);
    cube(0,0,0); // indigo
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,(length-length*0.9)/2,-(0.1/2-0.05/2)-0.05);
    glScalef(width*0.9,length*0.9,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(00.941, 0.973, 1.000); //plain goldenrod
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,length/2,-(1/2-0.5/2)-0.6);
    glScalef(0.5,8,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-8/2,length/2,-(1/2-0.5/2)-0.6);
    glScalef(8,0.7,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5,length/2-8,-(0.1/2-0.05/2)-0.06);
    glRotatef(30,0,0,1);
    glScalef(0.5,10,0.05);
    glTranslatef(-0.5,0,-0.5);
    cube(0, 0, 0); //black
    glPopMatrix();
}



static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-6, 6, -6, 6, 3.0, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

    glRotatef(rot, 0,1,0);

//    glPushMatrix();
//    axes();
//    glPopMatrix();

    glPushMatrix();
    light();
    glPopMatrix();

    glPushMatrix();
    light_left(120,100,0);
    glPushMatrix();
    glTranslatef(120,95,0);
    light();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    light_right(-120,100,0);
    glPushMatrix();
    glTranslatef(-120,95,0);
    light();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
     glTranslatef(0,97.5,70);
    ligh_handle();

    glPopMatrix();


    glPushMatrix();
    spotLight(0,95,70);

    glPushMatrix();
    glTranslatef(0,90,70);
    sphere (0.941, 1.000, 1.000);  // SteelBlue);
    glPopMatrix();

    glPopMatrix();



   glPushMatrix();
     floor_cube();
   glPopMatrix();

   glPushMatrix();
      ceil_cube();
   glPopMatrix();


    glPushMatrix();
    wall_cube();
    glPopMatrix();

    glPushMatrix();
    left_cube();
    glPopMatrix();


    glPushMatrix();
    right_cube();
    glPopMatrix();

    glPushMatrix();
     standing_dis();
    glPopMatrix();


//    glPushMatrix();
//    cabinet();
//    glPopMatrix();

    glPushMatrix();
    glTranslatef(86,0,76);
    part_cabinet();
    glPopMatrix();
//



    glPushMatrix();
    glTranslatef(60,0,-15);
    fan();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,-15);
    fan();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-60,0,-15);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120,40,0);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-119,40,0);
    glRotatef(270,0,1,0);
    window();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-86,0,76);
    glass_cabinet();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-15,0);
    black_board();
    glPopMatrix();

    glPushMatrix();

    for(int i =-100; ; i=i+45)
    {
        if(i>=110)
            break;

        for(int j=20;  ; j=j-20)
        {
            if(j<=-70)
                break;
                 table(i,j);
                  chair(i,j-8);
        }
    }

    glPopMatrix();


   glPushMatrix();
   glTranslatef(-119,60,50);
    glRotatef(-90,0,1,0);

    clock(20,30);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    //case 27 :
    case 'a':
        activate_amb= !activate_amb;
        break;

    case 'd':
        activate_diff= !activate_diff;
        break;

    case 's':
        activate_spec= !activate_spec;
        break;


    case '1':
        left_light= !left_light;
        break;
    case '2':
        right_light= !right_light;
        break;

    case '3':
        spot_light= !spot_light;
        break;


    case 'l':
        rot++;
        break;
    case 'r':
        rot--;
        break;

    case 'u':
        eyeY++;
        break;
    case 'b':
        eyeY--;
        break;
    case '+':
        eyeZ++;
        lookZ++;
        break;
    case '-':
        eyeZ--;
        //lookZ--;
        break;

    case 'k':
        eyeX--;
        lookX--;
        break;
    case 'j':
        eyeX++;
        lookX++;
        break;
    case 'o':
        flagScale=true;
        break;

    case 'p':
        flagScale=false;
        break;

    case 'Q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Classroom 1607060");

    printf("\t********** FUNCTIONS AND CORRESPONDING KEYS **********\n \tFOR LEFT ROTATION, PRESS l \n \tFOR LEFT ROTATION, PRESS r\n ");
    printf("\tFOR UP DIRECTION, PRESS u \n");
    printf("\tFOR DOWN DIRECTION, PRESS b \n");
    printf("\tTO MOVE LEFT, PRESS k \n");
    printf("\tTO MOVE RIGHT, PRESS j \n");

    printf("\tFOR ZOOM IN, PRESS + \n");
    printf("\tFOR ZOOM OUT, PRESS - \n");
    printf("\tFOR FAN OFF, PRESS p \n");
    printf("\tFOR FAN ON, PRESS o \n");
    printf("\tTO QUIT, PRESS Q \n");

    printf("\tFOR LEFT LIGHT STATUS CHANGE, PRESS 1\n");
    printf("\tFOR RIGHT LIGHT STATUS CHANGE, PRESS 2 \n");
    printf("\tFOR SPOT LIGHT STATUS CHANGE, PRESS 3\n");

     printf("\tFOR   AMBIENT STATUS CHANGE, PRESS a \n");
     printf("\tFOR   DIFFUSE STATUS CHANGE, PRESS d \n");
     printf("\tFOR  SPECULAR STATUS CHANGE, PRESS s \n");

     printf("\tFOR LEFT RIGHT AMBIENT STATUS CHANGE, PRESS 4 \n");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glutIdleFunc(animate);

    glutMainLoop();

    return EXIT_SUCCESS;
}

