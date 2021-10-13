#include "ppm_info.h"
//Daniel Yacu Fall 2021
//CPSC 1020
//PA1
//Main initializes reads two new images and then prompts the user for manipulation
//choice and image choice
int main(int argc, char* argv[]){
   if(argc != 3) {
      printf("USAGE: <executable> <oldImage> <newImage>\n\n");
      return -1;
   }
   //opening up images from command line
	FILE* oldImage1 = fopen(argv[1], "r");
   FILE* oldImage2 = fopen(argv[2], "r");
   
    if(!oldImage1 || !oldImage2) {
      printf("ERROR: File(s) could not be opened.\n");
      return -1;
   }
   //creating variables to hold images read in from command line


   filePtr_t* ImageFilePtr1 = (filePtr_t*)malloc(sizeof(filePtr_t));
   filePtr_t* ImageFilePtr2 = (filePtr_t*)malloc(sizeof(filePtr_t));
   filePtr_t* theList = NULL;
   image_t* image1;
   image_t* image2;

	image1 = read_ppm(oldImage1);
   image2 = read_ppm(oldImage2);

   int count = 0;

   //assigns imagefileptrs with data

   ImageFilePtr1->theImage = image1;
   ImageFilePtr1->theFile = oldImage1;
   ImageFilePtr1->imageFileName = argv[1];
   ImageFilePtr1->next = NULL;

   ImageFilePtr2->theImage = image2;
   ImageFilePtr2->theFile = oldImage2;
   ImageFilePtr2->imageFileName = argv[2];
   ImageFilePtr2->next = NULL;

   theList = ImageFilePtr1;
   ImageFilePtr1->next = ImageFilePtr2;

   /* do while loop below prompts the user for manipulation
   and image choice */
  int manipChoice = 0;
  filePtr_t* imageChoice = 0;
   do{
      manipChoice = printMenu1();
      
      if(manipChoice == 0){
         printf("Exiting Program\n");
         exit(1);
      }

      if((manipChoice != 0) && (manipChoice != 1) && (manipChoice != 2) && (manipChoice != 3)){
         printf("Not a valid manipulation option\n");
         return 0;
      }
      
      imageChoice = printList(theList);
      
      if(manipChoice == 1){
         gray_scale(imageChoice, &theList, count);
      }
      else if(manipChoice == 2){
         mirror(imageChoice, &theList, count);
      }
      else if(manipChoice == 3){
         green_screen(ImageFilePtr1, imageChoice, &theList, count);
      }
   
      ++count;

   }while(manipChoice != 0 && imageChoice != 0);

      fclose(oldImage1);
      fclose(oldImage2);
      return 0;
}


