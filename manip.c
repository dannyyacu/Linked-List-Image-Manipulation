#include "ppm_info.h"
//Daniel Yacu Fall 2021
//CPSC 1020
//PA1
//Where all the manipulation functions are 

/*Functions loops through each pixel and sets it 
to the average value of its RGB values, making it gray
*/

void gray_scale(filePtr_t* imageFilePtr, filePtr_t** theList, int count){
   int row = 0;
   int col = 0;
   int avg =  0;
   char fileName[30] = "g";
   strcat(fileName, imageFilePtr->imageFileName); 

   // see if image already exists in the list
   // if the 2nd letter is a lower case 'g', then it already exists
               
   if(fileName[1] != 'g'){
      fileName[strlen(fileName)-4] = '\0';
      char* imageName = (char*)malloc(50);
      sprintf(imageName, "%s%02d.ppm", fileName, count+1);
   
   FILE* grayedImage = fopen(imageName, "w");      
   if (!grayedImage){
      fprintf(stderr, "grayed image file could not be opened\n");
      exit(1);
   }     

   header_t header = imageFilePtr->theImage->header;
   image_t* image = allocate_memory(header);
   image->header = header;
   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) {
			// calculate the average of the r, g, b values for the pixel
			avg = ( imageFilePtr->theImage->pixels[row][col].r +
			        imageFilePtr->theImage->pixels[row][col].g +
					  imageFilePtr->theImage->pixels[row][col].b ) / 3;

			// 6.  assign avg to each r, g, br value of the pixel
         
      			image->pixels[row][col].r = avg;
		       	image->pixels[row][col].g = avg;
			      image->pixels[row][col].b = avg;	
      }
   }
   write_p6(grayedImage, image);
   imageFilePtr->theFile = grayedImage;
   // imageFilePtr->imageFileName = imageName;

   fclose(grayedImage);
   addToList(*theList, grayedImage, image, imageName);

   printf("Done with gray scale\n");
   }
}



/*Function loops through image and swaps the 
first column of pixels with the last, repeating until its
halfway through the image, creating a mirror effect
*/

void mirror(filePtr_t* imageFilePtr, filePtr_t** theList, int count){
   int row = 0;
   int col = 0;
   pixel_t temp;

   char fileName[30] = "m";
   strcat(fileName, imageFilePtr->imageFileName); 
   
   if(fileName[1] != 'm'){
      fileName[strlen(fileName)-4] = '\0';
      char* imageName = (char*)malloc(50);
      sprintf(imageName, "%s%02d.ppm", fileName, count+1);
   
   FILE* mirroredImage = fopen(imageName, "w");      
   if (!mirroredImage){
      fprintf(stderr, "mirrored image file could not be opened\n");
      exit(1);
   }     

   header_t header = imageFilePtr->theImage->header;
   image_t* image = allocate_memory(header);
   image->header = header;
    for (row = 0; row < header.height; row++) {
            for (col = 0; col < header.width/2; col++) {
                temp = imageFilePtr->theImage->pixels[row][col];
                image->pixels[row][col]= imageFilePtr->theImage->pixels[row][header.width-col-1];
                image->pixels[row][header.width-col-1] = temp;
            }
      }
   write_p6(mirroredImage, image);
   fclose(mirroredImage);
   addToList(*theList, mirroredImage, image, imageName);
   printf("Done with mirror\n");
   }
}

/*Function replaces any green pixels in ClemsonPaw.ppm
with images from Disney.ppm, making Disney.ppm a background
for the ClemsonPaw.ppm image.
*/

void green_screen(filePtr_t* image1, filePtr_t* image2, filePtr_t** theList, int count){
   int row = 0;
   int col = 0;

   char fileName[30] = "gs";
   strcat(fileName, image2->imageFileName); 

   if(fileName[1] == 's'){
      fileName[strlen(fileName)-4] = '\0';
      char* imageName = (char*)malloc(50);
      sprintf(imageName, "%s%02d.ppm", fileName, count+1);
   
   FILE* greenScreenImage = fopen(imageName, "w");      
   if (!greenScreenImage){
      fprintf(stderr, "green screen image file could not be opened\n");
      exit(1);
   }   

   header_t header = image1->theImage->header; 
   image_t* image = allocate_memory(header);
   image->header = header;


       for (row = 0; row < header.height; row++) {
            for (col = 0; col < header.width; col++) {
               if(image1->theImage->pixels[row][col].r == 0){
                  if(image1->theImage->pixels[row][col].g == 255){
                     if(image1->theImage->pixels[row][col].b == 0){
                        image->pixels[row][col].r = image2->theImage->pixels[row][col].r;
                        image->pixels[row][col].g = image2->theImage->pixels[row][col].g;
                        image->pixels[row][col].b = image2->theImage->pixels[row][col].b;
                     }
                  }
               }
            else{
               image->pixels[row][col].r = image1->theImage->pixels[row][col].r;
               image->pixels[row][col].g= image1->theImage->pixels[row][col].g;
               image->pixels[row][col].b = image1->theImage->pixels[row][col].b;
               }
            }
         }
      write_p6(greenScreenImage, image);
      addToList(*theList, greenScreenImage, image, imageName);
      fclose(greenScreenImage);
      printf("Done with green screen\n");
      }
   }

   
