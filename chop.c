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

/** @file chop.c
 *  @brief This is the source file for the function that cuts a portion 
 *  of an audio file
 *
 *  @author Christakis Achilleos 
 *  @bug No known bugs. 
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"


int chop(char *filename, int begin, int finish){

   if (finish < begin){
      printf("The final second can't be before the beginning second.\n");
      return EXIT_FAILURE;
   }
   else if (finish == begin ){
      printf("Finish is equal to beginning.\n");
      return EXIT_FAILURE;
   }
   else if(begin < 0 || finish <0 ){
      printf("Can't have a negative time.\n");
      return EXIT_FAILURE;
   }
   

   if (filename ==NULL){
      printf("The file name given is null.\n");
      return EXIT_FAILURE;
   }



   AUDIO_FILE *AF = NULL;

   AF  = readBinaryFile(filename);
   if (AF == NULL){
      printf("Failed to open file\n");
      return EXIT_FAILURE;

   }  
  
   dword sampleRate = AF->byteRate;
   dword start = sampleRate * begin;
   if (start >= AF->subChunk2Size){
      printf("The starting second is not within the size of the audio file.\n");
      free(AF->audioData);
      free(AF);
      return EXIT_FAILURE;
   }
   dword end = sampleRate * finish;
   if (end >= AF->subChunk2Size){
      printf("The ending second is not within the size of the audio file.\n");
      free(AF->audioData);
      free(AF);
      return EXIT_FAILURE;
   }
   dword dataSize = end - start;	
   byte *newData = NULL;
   newData = AF->audioData;

   AF->subChunk2Size = dataSize;
   AF->chunkSize = dataSize + 56;

   AF->audioData = newData + start;

   char name[100] ;
   *name ='\0';
   strcat(name, "chopped-");
   strcat(name, filename);

   writeFile(name, AF);
   free(newData);
   free(AF);

   return EXIT_SUCCESS;
}





