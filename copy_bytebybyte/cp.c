#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[]){

  // Check if the arguments are provided
  if(argc<3){
    printf("Usage %s <source file> <destination File>\n",argv[0]);
    return EXIT_FAILURE;
  }
  
  //open and check if source file open successfully
  FILE *source = fopen(argv[1], "rb");
  if(source == NULL)
  {
    perror("error opening source file.\n");
    return EXIT_FAILURE;
  }
  
  // open and check if destination file open successfully
  FILE *destination = fopen(argv[2], "wb");
  if(destination == NULL)
  {
    perror("error opening destination file.\n");
    fclose(source);
    return EXIT_FAILURE;
  }
  
  //allocate 1 byte to a temprory variable
  BYTE temp;
  
  //main copy loop (if BYTE is read then write it)
  while(fread(&temp,sizeof(temp),1,source)!=0){
    fwrite(&temp,sizeof(temp),1,destination);
  }
  
  //clean up
  fclose(source);
  fclose(destination);

  //print the processes was a success
  printf("copied successfully !\n");
  return EXIT_SUCCESS;
}
