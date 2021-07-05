/*
| DRAW PIXEL |
 This program create a matrix with your draw.
 Version: OpenGL 1.0;
*/

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <fstream>
#include <string>

//---{ Window Size }---
int width = 500;
int height = 500;
//---{ Important Variables }---
bool initContext = false;//Create the Context
int dPixel = 25;//Pixel Divisions
std::vector<std::vector<int>> pixels;//Matrix Pixels with the colors RGB
//---{ Colors }---
float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
bool changeColor = false;
char whichColor = 'n';
std::vector<std::vector<int>> colorsPallete;
//---{ State Variables }---
bool showPallete = false;
bool eraseMode = false;
bool copyColor = false;
//----------------

//---{ Initialization }---
void init(){
 glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
 gluOrtho2D(0,dPixel,0,dPixel);
}
//---{ Build Square }---
void buildSquare(int x, int y){
 glBegin(GL_QUADS);
  glVertex2f(x,y);
  glVertex2f(x+1,y);
  glVertex2f(x+1,y-1);
  glVertex2f(x,y-1);
 glEnd();
}

//---{ Loop to Draw }---
void draw(){
 glClear(GL_COLOR_BUFFER_BIT);
  //Grid
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINES);
   //Horizontal Lines
   for(int i=0;i<width;i++){
    glVertex2f(width,i);
    glVertex2f(0,i);
   }
   //Vertical Lines
   for(int j=0;j<height;j++){
    glVertex2f(j,height);
    glVertex2f(j,0);
   }
  glEnd();
  //Draw Pixels
  for(int i = 0;i<pixels.size();i++){
    glColor3f(
      ((float)pixels[i][2])/100,//Red
      ((float)pixels[i][3])/100,//Green
      ((float)pixels[i][4])/100//Blue
    );
    buildSquare(pixels[i][0], pixels[i][1]);
  }
  //------------
  if(changeColor){
   glColor3f(red,green,blue);
   buildSquare(0,dPixel);
  }
  //--- Show the Colors Pallete ---
  if(showPallete){
   for(int i = 0;i<colorsPallete.size();i++){
     glColor3f(
      ((float)colorsPallete[i][1])/100,//Red 
      ((float)colorsPallete[i][2])/100,//Green
      ((float)colorsPallete[i][3])/100//Blue
     );
     buildSquare(i,1);
   }
  }
 glutSwapBuffers();
}

//---{ Search for Pixel Paintend }---
bool searchPixel(int x, int y, int * position){
 for(int k = 0; k<pixels.size(); k++){
  if(pixels[k][0] == x and pixels[k][1] == y){
   *position = k;
   return true;
   break;
  }
 }
 return false;
}

//---{ Mouse Movement }---
void mouseClick(int button, int state, int x, int y){
 //Pixel coordenates 
 int xPixel = (int)(x/(width/dPixel));
 int yPixel = dPixel-(int)(y/(height/dPixel));

 if(button == GLUT_LEFT_BUTTON){
   if(state == GLUT_DOWN){
     bool palleteExists = false;

     if(showPallete){
       //If the Pixel Clicked have the Pallete
       for(int i = 0; i<colorsPallete.size(); i++){
         if(xPixel == colorsPallete[i][0] and yPixel == 1){
           red = ((float)colorsPallete[i][1])/100;
           green = ((float)colorsPallete[i][2])/100;
           blue = ((float)colorsPallete[i][3])/100;
           palleteExists = true;
           break;
         }
       }
     }
     //Change a Pixel
     int position = 0;
     bool resultPixel = searchPixel(xPixel, yPixel, &position);
     if(!palleteExists and resultPixel == false and !eraseMode and !copyColor){  
       //Paint Pixel
       pixels.push_back({xPixel, yPixel, (int)(red*100), (int)(green*100), (int)(blue*100)});
     }else{
       if(!eraseMode and !copyColor){
         //Change Pixel
         pixels[position] = {xPixel, yPixel, (int)(red*100), (int)(green*100), (int)(blue*100)};
       }else if(eraseMode and !palleteExists){
         //Erase with Click
         pixels.erase(pixels.begin() + position);
       }else if(copyColor and !palleteExists){
         //Copy Color with Click
         red = ((float)pixels[position][2])/100;
         green = ((float)pixels[position][3])/100;
         blue = ((float)pixels[position][4])/100;
       }
     }
  }

 }else if(button == GLUT_RIGHT_BUTTON){
   // Erase Pixels
   if(state == GLUT_DOWN){
     for(int i=0;i<pixels.size();i++){
      if(pixels[i][0] == xPixel and pixels[i][1] == yPixel){
        pixels.erase(pixels.begin() + i);
      }
     }
    }
 }
}
//---{ Shortcut Key }---
void shortcutKey(unsigned char key, int x, int y){
  if((char)key == 's'){
    //Save the Image
     int xRange[2] = {0,0};//The min X painted and max.
     int yRange[2] = {0,0};//The min Y painted and max.
     //The max value on X and Y Painted
     for(int i = 0; i<pixels.size(); i++){
       if(pixels[i][0]>xRange[1]){
        xRange[1] = pixels[i][0];
       }
       if(pixels[i][1]>yRange[1]){
        yRange[1] = pixels[i][1];
       }
     }
     xRange[0] = xRange[1];
     yRange[0] = yRange[1];
     //The min value on X and Y Painted
     for(int i=0; i<pixels.size(); i++){
      if(pixels[i][0]<xRange[0]){
        xRange[0] = pixels[i][0];
      }
      if(pixels[i][1]<yRange[0]){
        yRange[0] = pixels[i][1];
      }
     }
     //Saving in a file
     std::ofstream file;
     file.open("Text Image/matrix.txt");
     std::vector<std::vector<int>> pixelAddress;
     int pixel = 0;
     //Draw in the .txt
     for(int line=yRange[1]+1; line>yRange[0]; line--){
    
       for(int column = xRange[0]; column<xRange[1]+1; column++){
        if(searchPixel(column, line-1, &pixel)){
          file<<"l"<<yRange[1]+1-line
          <<"c"<<xRange[1]-column
          <<"r"<<pixels[pixel][2]
          <<"g"<<pixels[pixel][3]
          <<"b"<<pixels[pixel][4]<<".\n";
        }
       }
     }
     //Colors in the .txt
     file.close();
     std::cout<<" Function[3]: The File was Created"<<std::endl;
  }else if((char)key == 'c'){
    //Change Color Mode
    std::cout<<"--------------------------------------"<<std::endl;
    changeColor = !changeColor;
    if(changeColor){
     std::cout<<" Function[1][On]: Change Color"<<std::endl;
    }else{
     std::cout<<" Function[1][Off]: Change Color"<<std::endl;
    }
    std::cout<<"--------------------------------------"<<std::endl;
  }else if((char)key == 'p'){
    //See the Colors Pallete
    std::cout<<"--------------------------------------"<<std::endl;
    showPallete = !showPallete;
    if(showPallete){
      std::cout<<" Function[2][On]: Show the colors pallete"<<std::endl;
    }else{
      std::cout<<" Function[2][Off]: Show the colors pallete"<<std::endl;
    }
    std::cout<<"--------------------------------------"<<std::endl;
  }else if((char)key == 'a'){
    //Add the Color to the Pallete
    colorsPallete.push_back({
      (int)(colorsPallete.size()), // x Axi
      (int)(red*100),
      (int)(green*100),
      (int)(blue*100)}
    );
    std::cout<< "  Function[2][1]: Added new color to the pallete"<<std::endl;
  }else if((char)key == 'z'){
    //Remove the last item from colors pallete
    if(colorsPallete.size()>=1){
      colorsPallete.erase(colorsPallete.begin() + colorsPallete.size());
      std::cout<<"  Function[2][2]: Last color in pallet removed"<<std::endl;
    }
  }else if((char)key == 'e'){
    //Erase with Clicks
    std::cout<<"--------------------------------------"<<std::endl;
    eraseMode = !eraseMode;
    copyColor = false;
    if(eraseMode){
      std::cout<<" Function[4][On]: Erase Mode"<<std::endl;
    }else{
      std::cout<<" Function[4][Off]: Erase Mode"<<std::endl;
    }
    std::cout<<"--------------------------------------"<<std::endl;
  }else if((char)key == 'o'){
    //Copy Color
    std::cout<<"--------------------------------------"<<std::endl;
    copyColor = !copyColor;
    eraseMode = false;
    if(copyColor){
      std::cout<<" Function[5][On]: Copy Mode"<<std::endl;
    }else{
      std::cout<<" Function[5][Off]: Copy Mode"<<std::endl;
    }
    std::cout<<"--------------------------------------"<<std::endl;
  }
 //Change Color
 if(changeColor){
   switch((char)key){
    case 'r':
      //Change Red Color
      whichColor = 'r';
      std::cout<<"  Function[1][1]: Change Red Color"<<std::endl;
      break;
    case 'g':
      //Change Green Color
      whichColor = 'g';
      std::cout<<"  Function[1][2]: Change Green Color"<<std::endl;
      break;
    case 'b':
      whichColor = 'b';
      std::cout<<"  Function[1][3]: Change Blue Color"<<std::endl;
      break;
   }
 }
}
//---{ Function to Change Color }---
void analiseColorsTyped(char color,char comparativeColor, bool condition, float * colorVar, float inc_dec){
 if(condition and color == comparativeColor){
   *colorVar = *colorVar + inc_dec;
 }
}
//---{ Change Color }---
void arrowKeys(int key, int x, int y){
  if(changeColor){
   if(key == GLUT_KEY_UP){
    //Increment the color Value
    analiseColorsTyped('r',whichColor,red<0.99f,&red,0.01f);
    analiseColorsTyped('g',whichColor,green<0.99f,&green,0.01f);
    analiseColorsTyped('b',whichColor,blue<0.99f,&blue,0.01f);
   }else if(key = GLUT_KEY_DOWN){
    //Decrement the color Value
    analiseColorsTyped('r',whichColor,red>0.02f,&red,-0.01f);
    analiseColorsTyped('g',whichColor,green>0.02f,&green,-0.01f);
    analiseColorsTyped('b',whichColor,blue>0.02f,&blue,-0.01f);
   }
  }
}
//---{ Execution }---
int main(int argc, char** argv){
 //Creating the Context
 //Construct Window
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(width,height);//Window Size
 glutInitWindowPosition(100,100);//Window Position
 glutCreateWindow("Draw Basic Pixel");//Title
 glutDisplayFunc(draw);
 glutIdleFunc(draw);
 glutMouseFunc(mouseClick);
 glutKeyboardFunc(shortcutKey);
 glutSpecialFunc(arrowKeys);
 //--- Initialization ---
 init();
 glutMainLoop();
}