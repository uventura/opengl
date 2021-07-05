/*
----| SNAKE |------
To open on Terminal:
 - Go to where is the file.
 - To create the executable:
   type: g++ snake.cpp -o snake -lglut -lGL -lGLU -lm
 - To Run:
  ./snake
------------------------------------
ERROS:
 - The Infinite movement.
 - The Head touch the Body.
IMPROVE:
 - Transform Width and Height in variables.
 - Velocity Snake.
 - Colors.
------------------------------------
[ OpenGL V1.0 ]
*/

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <random>
#include <fstream>


std::vector<std::vector<int>> body;//Body
int food [2] = {9,9};
int point = 0;
char lastKey = 'w';
bool newSection = false;
//Timer
clock_t timer;
//---{ Init }---
void init(){
 timer = clock();
 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 gluOrtho2D(0,20,0,20);
 //Making the Head and Initial Body
 body.push_back({2,3});
 body.push_back({2,4});
}
//---{ Build the Pixels }---
void buildSquare(int x, int y){
 glBegin(GL_QUADS);
  glVertex2f(x,y);
  glVertex2f(x+1,y);
  glVertex2f(x+1,y-1);
  glVertex2f(x,y-1);
 glEnd();
}
//---{ Infinite Moviment }---
void continueBody(int axi,int comparativeAxi,int newAxi){
 if(body[0][axi] == comparativeAxi){
  body[0][axi] = newAxi;
 }
}
//---{ Move Snake and Add new Section }---
void moveSnake(){
  //Move Snake
  int end[2] = {0,0};
  for(int i=body.size()-1;i>0;i--){
   if(newSection and i == body.size()-1){
    //Where is the New Section
    end[0] = body[i][0];
    end[1] = body[i][1];
   }
   body[i][0] = body[i-1][0];
   body[i][1] = body[i-1][1];
  }
  //Add New Section to the body
  if(newSection){
    body.push_back({end[0],end[1]});
    newSection = false;
  }
  //Make the Infinite Movement
   /*-- The if statement it's used to don't create a loop,Example:
      If you move the position 22 to 1 and compare if the thing is
   in 1 and move to 22. --*/
  continueBody(1,22,1);//Up to Down
  if(body[1][1]!=22){
   continueBody(1,1,22);//Down to Up
  }
  continueBody(0,-1,20);//Left to Right
  if(body[1][0]!=-1){
   continueBody(0,20,-1);//Right to Left
  }
}
//---{ Key Press Make Movement }---
void seeKey(char key, char comparKey,int axi,int value){
 if(key == comparKey){
  moveSnake();
  body[0][axi]+=value;
  lastKey = comparKey;
 }
}
//---{ Keys to Move }---
void keys(unsigned char key, int x, int y){
 if((char)key!=lastKey){
  seeKey((char)key,'w',1,1);
  seeKey((char)key,'a',0,-1);
  seeKey((char)key,'s',1,-1);
  seeKey((char)key,'d',0,1);
 }
}
//---{ Vector to Move }---
void keyVector(int key, int x, int y){
 if(key == GLUT_KEY_UP){
  seeKey('w','w',1,1);
 }else if(key == GLUT_KEY_DOWN){
  seeKey('s','s',1,-1);
 }else if(key == GLUT_KEY_LEFT){
  seeKey('a','a',0,-1);
 }else if(key == GLUT_KEY_RIGHT){
  seeKey('d','d',0,1);
 }
}
//---{ Generate Random Values(to the positions food) }---
int pseudoRand(int maxRange,int minRange = 0,int a = 3, int b = 4){
 clock_t time;
 time = clock();
 while(1){
   if((a*time+b)%maxRange>=minRange){
     return (a*time+b)%maxRange;
     break;
   }
 }
}
//---{ Draw the Frames }---
void draw(){
 glClear(GL_COLOR_BUFFER_BIT);
 //Eat Food
 if((body[0][0] == food[0]) and (body[0][1] == food[1]+1)){
  food[0] = pseudoRand(100)%21;
  food[1] = pseudoRand(100,1,4,5)%21;
  point+=1;
  newSection = true;
 }
 //Show Food
 glColor3f(1.0f,0.0f,0.0f);
 buildSquare(food[0],food[1]); 
 //Show Snake
 glColor3f(1.0f,1.0f,1.0f);
 for(int i=0;i<body.size();i++){
  buildSquare(body[i][0],body[i][1]-1);
 }
 //Frames
 if((float)(clock()-timer)/CLOCKS_PER_SEC>0.2 and (float)(clock()-timer)-CLOCKS_PER_SEC<0.3){
  timer = clock();
  seeKey(lastKey,'w',1,1);
  seeKey(lastKey,'a',0,-1);
  seeKey(lastKey,'s',1,-1);
  seeKey(lastKey,'d',0,1);
 }
 glutSwapBuffers();
}
//---{ Execution }---
int main(int argc, char** argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(600,600);
 glutInitWindowPosition(100,100);
 glutCreateWindow("Snake");
 glutDisplayFunc(draw);
 glutIdleFunc(draw);
 glutKeyboardFunc(keys);
 glutSpecialFunc(keyVector);
 //Inicializar
 init();
 //------------
 glutMainLoop();
 
}
