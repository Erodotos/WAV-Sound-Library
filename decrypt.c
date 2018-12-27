/*
*
* Sound processing software developed for educational purposes.
* Copyright (C) 2018 Christakis Achilleos, Erodotos Demetriou 
* This program is free software: you can redistribute it and/or modify 
* it under the terms of the GNU General Public License as published by 
* the Free Software Foundation, either version 3 of the License, or 
* at your option) any later version. 
* This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
* GNU General Public License for more details. 
* Υou should have received a copy of the GNU General Public License 
* along with this program. If not, see <http://www.gnu.org/licenses/>.
* 
**/

/** @file decrypt.c
 *  @brief This .c file is responsible for extracting the hidden 
 *  data from the audio file
 *
 *  @author Christakis Achilleos 
 *  @bug No known bugs. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int decryptMessage(char *audioFile, char *outputfile, int length){

   FILE *fp = NULL;
   int msgLength = length;   

   fp = fopen(outputfile, "w");
   if (fp == NULL) {
      printf("Error opening text file\n");
      return EXIT_FAILURE;
   }


   AUDIO_FILE *AF = NULL;
   AF = readBinaryFile(audioFile); 
   if(AF == NULL){
      return EXIT_FAILURE;
   }

   char *decryptedMsg = (char*)malloc(sizeof(char)*msgLength);
   if(decryptedMsg == NULL){
      printf("System out of memory\n");
      free(AF->audioData);
      free(AF);
      return EXIT_FAILURE;

   }
   char *temp = decryptedMsg; 
   int i, j, x;
   int *permutation = createPermutationFunction(msgLength*8, seedKey);
   for (i=0;i<msgLength*8;i+=8){

      char character = 0x00;
      for(j= 0; j<8; j++){
         character = character << 1;
         x = permutation[i+j];
         byte tmp = AF->audioData[x];
         tmp = tmp & 0x01;
         character = character | tmp; 
      }      
   
      *temp = character;
      temp++;
   }
   
  
   fprintf(fp, "%s", decryptedMsg);
   temp = NULL;
   free(permutation);
   free(decryptedMsg);
   free(AF->audioData);
   free(AF);
   fclose (fp);

   return EXIT_SUCCESS;
}

