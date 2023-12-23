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
  char program_name[1024] = DEFAULT_PROGRAM_NAME;
  if (argv[1] != NULL) {
    strcpy(program_name, argv[1]);
  }
  
  //Creates the project directory if it doesn't exist already
  struct stat st = {0};
  if(stat(program_name, &st) == -1) {
    mkdir(program_name, 00700);
  } else {
    printf("A project already exists in this directory\n");
    return 1;
  }

  //Formats the src directory path
  char src[1024];
  strcpy(src, program_name);
  strcat(src, "/src");

  //Creates a src/ directory inside the project
  if(stat(src, &st) == -1) {
    mkdir(src, 00700);
  } else {
    printf("A project already exists in this directory\n");
    return 1;
  }

  //Default string for main.c
  char source_main[] = "#include <stdio.h>\n\nint main() {\n   printf(\"Hello world!\\n\");\n}\n";

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
  

  //Formats the path of the main.c file according to the program name
  char main_str[1024];
  strcpy(main_str, src);
  strcat(main_str, "/main.c");
  
  //Checks if the main.c file exists and opens it
  FILE* file = fopen(main_str, "w");
  if (file == NULL) {
    printf("Could not open the \"main.c\" file\n");
    return 1;
  }

  //Writes the default source code for the main.c file into the file
  if (fprintf(file, source_main) < 0) {
    printf("Could not write to the main.c file\n");
    return 1;
  }

  //Closes the file
  fclose(file);

  //Formats the Makefile path in order to place it inside our project's folder
  char makefile_str[1024];
  strcpy(makefile_str, program_name);
  strcat(makefile_str, "/Makefile");

  //Checks and opens the Makefile
  file = fopen(makefile_str, "w");
  if (file == NULL) {
    printf("Could not open the \"Makefile\" file\n");
    return 1;
  }

  //Writes the source code into the Makefile
  if (fprintf(file, base_makefile) < 0) {
    printf("Could not write to the \"Makefile\" file\n");
  }
  
  printf("Succesfully made the c project!\n");

  fclose(file);
}
