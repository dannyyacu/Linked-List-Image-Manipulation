#include "ppm_info.h"
//Daniel Yacu Fall 2021
//CPSC 1020
//PA1

//This is where all the other functions are
//Memory allocation, writing new images, and printing menus

// will create a header object, read in the header info from the file
// into the header object, and return the header object back to read_ppm()
// inputs:  file pointer to the input image
// outputs: the header object containing the header info from the input file

header_t read_header(FILE* image_file) {
	header_t theHeader;
   fscanf(image_file, "%s %d %d %d ",
      theHeader.magicNum, &theHeader.width, 
		&theHeader.height, &theHeader.maxVal);
   return theHeader;
}

// will write the header info to the output image file
// called from write_p6() function
// inputs:  file pointer to output image file & the header
// outputs:  none
void write_header(FILE* out_file, header_t header) {
   fprintf(out_file, "%s %d %d %d ",
      header.magicNum, header.width, header.height, header.maxVal);
}


// called from the main() function
// first calls read_header() to initialize header info
// then forwards the header on to  read_pixels() where
// space will be allocated for the entire image and 
// the pixel data will be read
// inputs:  the input file pointer
// outputs:  the image pointer
image_t* read_ppm(FILE* image_file) {
   header_t theHeader = read_header(image_file);

   image_t* image = NULL;

   image = read_pixels(image_file, theHeader); 

   return image;
}



// function to allocate memory for the image
// and read in the pixel data 
// inputs:  input image file pointer and the header
//			   that was already initialized
// outputs:  the image pointer
image_t* read_pixels(FILE* image_file, header_t header) {

   int row = 0, col = 0;
   unsigned char red, green, blue;
   red = green = blue = 0;
   image_t* image = allocate_memory(header);
	  
   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) {
         fscanf(image_file, "%c%c%c", &red, &green, &blue);
         image->pixels[row][col].r = red;
         image->pixels[row][col].g = green;
         image->pixels[row][col].b = blue;
      }
   }

   return image;
}


// will user the header info to allocate memory for the image
// inputs:  the header
// outputs:  the image pointer
image_t* allocate_memory(header_t header) {
   int row;
   image_t* image = (image_t*) malloc(sizeof(image_t));

   image->header = header;

   image->pixels = (pixel_t**)malloc(header.height * sizeof(pixel_t*)); 			
	
	for(row = 0; row< header.height; row++){
		image->pixels[row] = (pixel_t*)malloc(header.width * sizeof(pixel_t));

    }
    return image;
}

/*prints all the images in the linked list and 
prompts the user choice*/

filePtr_t* printList(filePtr_t* theList) {
   int fileNumber = 1, choice = 0;
   filePtr_t* current = theList;
   if (theList == NULL)
      fprintf(stderr, "\nThe list is empty.\n");
   else {
      fprintf(stderr, "\nYour image choicesare:\n");
      while(current != NULL){
         fprintf(stderr, "%d. %s\n", fileNumber, current->imageFileName);
         fileNumber++;
         current = current->next;
      }
      fprintf(stderr, "\n\n");
      fprintf(stderr, "Enter image choice or 0 to quit program:  ");
      fscanf(stdin, "%d", &choice);
   }
   if (choice == 0)
      exit(1);

      current = theList;
      for (int i = 1; i< choice; i++)
         current = current->next;
         
         return current;
      }
//prompts the user for manipulation choice
int printMenu1(){
   int manipChoice;
      printf("PA1 Image Manipulation\n");
      printf("0. exit program\n");
      printf("1. gray scale\n");
      printf("2. mirror\n");
      printf("3. green screen\n");
      scanf("%d", &manipChoice);
      return manipChoice;
}
//adds new image to the linked list
void addToList(filePtr_t* frontOfList, FILE* newImage, image_t* theNewImage, char* nameOfImage){
      filePtr_t* newNode = (filePtr_t*)malloc(sizeof(filePtr_t));
      newNode->theFile = newImage;
      newNode->theImage = theNewImage;
      newNode->imageFileName = nameOfImage; 
      newNode->next = NULL;

      if(frontOfList == NULL){
         frontOfList = newNode;
         return;
      }
      else{
         filePtr_t* currentNode = frontOfList;
         while(currentNode->next != NULL){
            currentNode = currentNode->next;
         }
         currentNode->next = newNode;
      }
   }
   
//writes out image to a new file 
void write_p6(FILE* out_file, image_t* image) {
   int row = 0;
   int col = 0;
   // unsigned char red,green,blue;
   header_t header = image->header;
   write_header(out_file, header);
   /*Loop through the image and print each pixel*/
   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) { 
			fprintf(out_file, "%c%c%c",
         image->pixels[row][col].r,
         image->pixels[row][col].g,
         image->pixels[row][col].b);
      }
   }
}


