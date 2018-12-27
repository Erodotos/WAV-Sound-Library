#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"



int main(int argc, char *argv[]){



   if (argc == 1){
      printGPL();
      printf("No option and file are given\n");
      return EXIT_FAILURE;
    }

   if (argc == 2){
      if (strcmp(argv[1],"-man") == 0){
         printManual();
         return EXIT_SUCCESS;
      }else{
         if (*argv[1] == '-'){
            printGPL();
            printf("No file was given\n");
            return EXIT_FAILURE;
         }else{
            printGPL();
            printf("No option was given\n");
            return EXIT_FAILURE;
         }

      }
   }

    if (strcmp(argv[1], "-list")==0){
        int i;
        for (i=2;i<argc;i++){
            char * fileName = argv[i];
            list(fileName);
        }
    }else if (strcmp(argv[1], "-mono") == 0){
        int i;
        for (i=2;i<argc;i++){
            char * fileName = argv[i];
            mono(fileName);
        }
    }else if (strcmp(argv[1], "-mix")==0){
        if (argc!=4){
            printGPL();
            printf("Incorrect amount of files.\n");
            return EXIT_FAILURE;
        }
        mix(argv[2], argv[3]);
   }else if (strcmp(argv[1], "-chop")==0){
      if (argc!=5){
         printGPL();
         printf("Incorrect amount of given arguments.\n");
         return EXIT_FAILURE;
      }
      chop(argv[2],atoi(argv[3]) , atoi(argv[4]));
   }else if (strcmp(argv[1], "-reverse")==0){
      int i;
        for (i=2;i<argc;i++){
            char * fileName = argv[i];
            reverse(fileName);
      }
   }else if (strcmp(argv[1], "-similarity")==0){
      int i;
      if(argc == 3){
         printGPL();
         printf("Not enough audio files are given\n\n");
      }else{
         for (i=3;i<argc;i++){
            char * fileName = argv[i];
            similarity(argv[2],fileName);
         }
      }   
   }else if (strcmp(argv[1], "-encodeText")==0){
      if (argc!=4){
         printGPL();
         printf("Incorrect amount of arguments given.\n");
         return EXIT_FAILURE;
      }
      encryptMessage(argv[2],argv[3]);
   }else if (strcmp(argv[1], "-decodeText")==0){
      if (argc!=5){
         printGPL();
         printf("Incorrect amount of arguments given.\n");
         return EXIT_FAILURE;
      }
      decryptMessage(argv[2],argv[4], atoi(argv[3]));
   }else if (strcmp(argv[1], "-speedup")==0){
      int i;
        for (i=2;i<argc;i++){
            char * fileName = argv[i];
            speedup(fileName);
      }
   }else if (strcmp(argv[1], "-delay")==0){
      int i;
        for (i=2;i<argc;i++){
            char * fileName = argv[i];
            delay(fileName);
      }
   }else{
       printf("Unrecognized command\n\n");
       printManual();
   }

   

   return EXIT_SUCCESS;
}

