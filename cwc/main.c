#include <stdio.h>
#include "argparse.h"

// length of the line 
#define MAX_BUFFER_LENGTH 255

// function initialization
int count_chars(FILE *file);
int count_lines(FILE *file);
int count_words(FILE *file);


int main(int argc, char *argv[]){
  // defining parser
  struct argparse_parser *parser = argparse_new("cwc", "CWC is a simple utility to count characters, words, and lines in a file or given text.", "version 1.0.0");
  // adding arguments in our program
  argparse_add_argument(parser, 'v', "version", "Prints version of the programe", ARGUMENT_TYPE_FLAG);
  argparse_add_argument(parser, 'h', "help", "Print help message", ARGUMENT_TYPE_FLAG);
  argparse_add_argument(parser, 'c', "charc", "Count number of characters", ARGUMENT_TYPE_FLAG);
  argparse_add_argument(parser, 'w', "word", "Count number of words", ARGUMENT_TYPE_FLAG);
  argparse_add_argument(parser, 'l', "line", "Count number of lines", ARGUMENT_TYPE_FLAG);
  argparse_add_argument(parser, 'f', "file", "Enter the path of the file to read from", ARGUMENT_TYPE_VALUE);
  
  // parsing commandline arguments to the parser,
  argparse_parse(parser, argc, argv);

  // get values of the flag and value.
  unsigned int version = argparse_get_flag(parser, "version");
  unsigned int help = argparse_get_flag(parser, "help");
  unsigned int charc = argparse_get_flag(parser, "charc");
  unsigned int word = argparse_get_flag(parser, "word");
  unsigned int line = argparse_get_flag(parser, "line");
  char *filename = argparse_get_value(parser, "file");
  // file point to store file
  FILE *file;

  if(version){
    argparse_print_version(parser);
    return 0;
  }

  if(help){
    argparse_print_help(parser);
    return 0;
  }

  if(filename){
    file = fopen(filename, "r");
    if(file == NULL){
      perror("error");
      exit(0);
    }
  }
 
  int total_lines = count_lines(file);
  rewind(file);
  int total_words = count_words(file);
  rewind(file);
  int total_chars = count_chars(file);
  rewind(file);

  if(charc){
    printf("%d %s\n", total_chars, filename);
  }else if(line){
    printf("%d %s\n", total_lines, filename);
  }else if(word){
    printf("%d %s\n", total_words, filename);
  }else {
    printf("%d %d %d %s\n", total_lines, total_words, total_chars, filename);
  }
  
  // closing file and freeing up memory used by argument parser.
  fclose(file);
  argparse_free(parser);
  return 0;
};

int count_chars(FILE *file){
  int total_chars = 0;
  char buffer[MAX_BUFFER_LENGTH];

  while(fgets(buffer, sizeof(buffer), file) !=NULL){
    size_t length = strlen(buffer);
    if(length > 0 && buffer[length - 1] == '\n'){
      buffer[length - 1] = '\0';
    }
    for(int i=0; i < length; i++){
      if(buffer[i] != ' '){
        total_chars++;
      };
    }
  }
  return total_chars;
};

int count_lines(FILE *file){
  int total_lines = 0;
  char buffer[MAX_BUFFER_LENGTH];
  while(fgets(buffer, sizeof(buffer), file) !=NULL){
    size_t length = strlen(buffer);
    if(length > 0 && buffer[length - 1] == '\n'){
      buffer[length - 1] = '\0';
    }
    total_lines++;
  }
  return total_lines;
}

int count_words(FILE *file){
  int total_words = 0;
  char buffer[MAX_BUFFER_LENGTH];
  while(fgets(buffer, sizeof(buffer), file) !=NULL){
    size_t length = strlen(buffer);
    for(int i=0; i < length; i++){
      if(buffer[i] == ' ' || buffer[i] == '\n'){
        total_words++;
      }
    }
  }
  return total_words;
}

