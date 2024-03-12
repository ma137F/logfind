//Includes 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> 
#include <assert.h> 
//# include "dbg.h"
#include <unistd.h>
#include <glob.h>

//Constants 
#define MAX_DATA 100 

//Function declerations
char argv_to_command(char *command[MAX_DATA], int argc, char *argv[], int i);
int fopen_and_read_to_buffer(char *filename[MAX_DATA], char *buffer[MAX_DATA], FILE *fp,int k, int n);
char match_print(char *buffer[MAX_DATA], char *command[MAX_DATA], char *filename[MAX_DATA], char *match,int n);

//Start of user defined functions 

char argv_to_command(char *command[MAX_DATA], int argc, char *argv[], int i) {
    command[i] = calloc(1, MAX_DATA-1);
    command[i] = argv[i];
}

int fopen_and_read_to_buffer(char *filename[MAX_DATA], char *buffer[MAX_DATA], FILE *fp, int k, int n){  
    fp = fopen(filename[k], "r");     
    
    if (!fp){
        return errno;
    }
    
    fseek(fp, 0, SEEK_SET); 
    buffer[n] = calloc(1, MAX_DATA-1);         
    
    if (!buffer[n]){
        printf("Failed to allocate buffer \n");
        return errno;
    }

    fread(buffer[n], MAX_DATA-1, 1, fp);
    
    if (buffer[n] == NULL){
        printf("Failed to assign buffer \n");
        return errno;
    }                    
}

char match_print(char *buffer[MAX_DATA],char *command[MAX_DATA],char *filename[MAX_DATA],char *match,int n){
    if (match == buffer[n] || command[1]){  
        printf("%s \n", filename[n]);          
     }        
}
  
// Main function 
int main (int argc, char *argv[]) {   
// Variable declaration and intiazliation,    
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 0;
    char c;
    FILE *fp;    
    char *buffer[MAX_DATA]; 
    char *filename[MAX_DATA];
    char *command[MAX_DATA];

    //saftey check, 
    if (argc == 1){
        fprintf(stderr, "Usage: %s [string ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //Logic for  -o argument while loop, 
    int oflag; 
    
    while ((c = getopt(argc, argv, "o:")) != -1){
     switch (c) {
      case 'o':
        oflag = 1;                   
        break;
      default:
      fprintf(stderr, "Usage: %s [-o string_1 string_2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
      }
    }  

    // safety check, 
    if (oflag==1 && argc==3){
      fprintf(stderr, "Usage: %s [-o string_1 string_2 ...]\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    //assgning argv to array command, 
    for (i = 1;i < argc; i++){    
        argv_to_command(command, argc, argv, i);
    }

    //Definition of glob for file actions later,
    glob_t g;
    g.gl_offs = 2;    
    //setting the parameters for files in directory,using .txt files as an example,
    glob("*.txt", GLOB_DOOFFS, NULL, &g); 
    //lc should act as argc for the amount of files in DIR, 
    int lc = g.gl_pathc+1; 

    //assgning results of pathv to array filename, 
    char *pv;  
    for (k = 0; k <= lc; k++){
        if (g.gl_pathv[k] == NULL)
            continue;               
        pv = g.gl_pathv[k];        
        filename[k] = pv;
    } 

    //assigning results of fopen and seek to buffer,
    //decided to use 'n' for buffer to avoid confusion,    
    k = 2;   
    n = 2;

    while (filename[k]){            
        fopen_and_read_to_buffer(filename, buffer, fp, k, n);     
        k++;
        n++;
    }    

    // Variable reassignment - 'for' loop usage, 
    k = 2;
    n = 2;
    i = 2; 
    
    //match will hold the result of strstr,
    char *match;
    for (n = 2;n <= lc; n++){        
        if (argc == 2 && oflag != 1){
            match=strstr(buffer[n], command[1]);
        
            if (match != NULL)
                match_print(buffer, command, filename, match, n);
        }
    
        if (oflag == 1 && argc >=3){
        i = 2;         
        for (i = 2;i < argc; i++){
            match=strstr(buffer[n], command[i]);
    
            if (match != NULL)
                match_print(buffer, command, filename, match, n);           
         }                
        }                     
     free(buffer[n]);        
    }    
 
 return 0;
} // end of main function 

