// the goal of this program is to create a bird that can fly around the screen (then maybe create a flock of birds that can fly around the screen together)


// include the library code:
#include <GL/glut.h>
#include <math.h>


// global variables
#define PI 3.14159265;
int windowWidth = 1920; //these are desired window dimension use to convert from screen to window coordinates
int windowHeight = 1080; //these are desired window dimension use to convert from screen to window coordinates
int depth = 1000; //this is the depth of the window (this is all virtual used for 3D rendering)

int birdStartX = 720;
int birdStartY = 540;
int birdStartZ = 500;


//define the bird class
class Bird{
    public:
        int x;
        int y;
        int z;
        int vx;
        int vy;
        int vz;
        float angleTD; //angle top down  //used to determine the direction the bird is facing default is 0 which is looking to the right 
        float angleFB; //angle front back //used to determine the direction the bird is facing default is 0 which is looking to the right 
        float angleLR; //angle left right //used to determine the direction the bird is facing default is 0 which is looking to the right
        //constructor
        Bird(int x, int y, int z, int vx, int vy, int vz){
            this->x = x;
            this->y = y;
            this->z = z;
            this->vx = vx;
            this->vy = vy;
            this->vz = vz;
            //generate angle from velocity
            this->angleTD = atan(vy/vx);
            this->angleFB = atan(vz/vx);
            this->angleLR = atan(vy/vz);
        }
        //methods
        void move(){
            this->x += this->vx;
            this->y += this->vy;
            this->z += this->vz;
        }
        void updateAngle(){
            this->angleTD = atan(vy/vx);
            this->angleFB = atan(vz/vx);
            this->angleLR = atan(vy/vz);
        }        
        void draw(){
            //bird is a pointer triangle (one edge is dented inwards to make an arrow head shape)
            
        }
}



void display(){ //callback function
    glClear(GL_COLOR_BUFFER_BIT);//clear the screen

    //set the color to red
    glColor3f(1.0, 0.0, 0.0);


}