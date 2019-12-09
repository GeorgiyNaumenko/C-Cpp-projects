#include "../headers/common.h"
#include "../headers/Geometry2D.h"
#include "../src/Geometry2D.c"
#include <stdio.h>
#include <math.h>
#include <string.h>


int main(){
  char choose[64];
  Geometry2D my_geometry;
  Geometry2D *pointer = &my_geometry;

  printf("Welcome to Geometry2D calculator! Here yo can find a lot of values of different planimetry objects.\n");
  printf("Firstly, you should create your triangle and line.\n");
  printf("You have triangle ABC with vertexes A(x1, y1), B(x2, y2) and C(x3, y3).\n");
  printf("Also, you have a line L: ax + by + c = 0.\n");
  printf("You work in space Dtype^2.\n\n\n");

  printf("Input 'console' to work with console\nInput 'binary' to work with binary file\nInput 'text' to work with text file\n\n\n");
  gets(choose);

  if(strcmp(choose, "console")==0){
    printf("\n\nYou are working with console!\n\n\n");
    inputGeometry2D(pointer);
    outputGeometry2D(*pointer);
  }
  else if(strcmp(choose, "binary")==0){
    printf("\n\nYou are working with binary file!\n\n\n");
    if (inputBinaryFile("Geometry2D_in.dat", pointer) == 0){
      printf("\nSucsessfully got data from binary file!\n");
    }
    else{
      printf("ERROR WHILE GETTING DATA FROM BINARY FILE 'Geometry2D_in.dat'!!!\n");
    }
    if (outputBinaryFile("Geometry2D_out.dat", *pointer) == 0){
      printf("\nSucsessfully created binary file with all values!\n");
    }
    else{
      printf("ERROR WHILE CREATING BINARY FILE 'Geometry2D_out.dat'!!!\n");
    }
  }
  else if(strcmp(choose, "text")==0){
    printf("\n\nYou are working with text file!\n\n\n");
    if (inputTextFile("Geometry2D_in.txt", pointer) == 0){
      printf("\nSucsessfully got data from text file 'Geometry2D_in.txt'!\n");
    }
    else{
      printf("ERROR WHILE GETTING DATA FROM TEXT FILE 'Geometry2D_in.txt'!!!\n");
    }
    if (outputTextFile("Geometry2D_out.txt", *pointer) == 0){
      printf("\nSucsessfully created text file 'Geometry2D_out.txt' with all values!\n");
    }
    else{
      printf("ERROR WHILE CREATING TEXT FILE 'Geometry2D_out.txt'!!!\n");
    }
  }
  else{
    printf("Incorrect desision!");
  }

}
