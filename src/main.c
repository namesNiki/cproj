#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define DEFAULT_PROGRAM_NAME "exe"

int main(int argc, char* argv[]) {

  //Checks if the first argument is passed in, and sets the program_name variable to it. If not, it defalts to DEFAULT_PROGRAM_NAME
  char program_name[100] = DEFAULT_PROGRAM_NAME;
  if (argv[1] != NULL) {
    strcpy(program_name, argv[1]);
  }
  
  //Creates the src directory if it doesn't exist already
  struct stat st = {0};
  if(stat("src", &st) == -1) {
    mkdir("src", 00700);
  } else {
    printf("A project already exists in this directory\n");
    return 1;
  }

  //Default string for main.c
  char base_main[] = "#include <stdio.h>\n\nint main() {\n   printf(\"Hello world!\\n\");\n}\n";

  //This whole bit sets the Makefile source, concatanating the program_name where it needs to
  char bit1[50] = "none:\n\tgcc src/*.c -o ";
  char bit2[50] = "\nrun:\n\tgcc src/*.c -o ";
  char bit3[50] = "\n\t./";
  char bit4[50] = "\n";
  char base_makefile[1024];
  strcpy(base_makefile, bit1);
  strcat(base_makefile, program_name);
  strcat(base_makefile, bit2);
  strcat(base_makefile, program_name);
  strcat(base_makefile, bit3);
  strcat(base_makefile, program_name);
  strcat(base_makefile, bit4);
  

  //Checks if the main.c file exists and opens it
  FILE* file = fopen("src/main.c", "w");
  if (file == NULL) {
    printf("Could not open the \"main.c\" file\n");
    return 1;
  }

  //Writes the default source code for the main.c file into the file
  if (fprintf(file, base_main) < 0) {
    printf("Could not write to the main.c file\n");
    return 1;
  }

  //Closes the file
  fclose(file);

  //Checks and opens the Makefile
  file = fopen("Makefile", "w");
  if (file == NULL) {
    printf("Could not open the \"Makefile\" file\n");
    return 1;
  }

  //Writes the source code into the Makefile
  if (fprintf(file, base_makefile) < 0) {
    printf("Could not write to the \"Makefile\" file\n");
  }
  
  printf("Succesfully made the c project!\n");
}
