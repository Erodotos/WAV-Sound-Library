/*

Sound processing software developed for educational purposes.
Copyright (C) 2018 Christakis Achilleos, Erodotos Demetriou 
This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
at your option) any later version. 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 
Υou should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

/** @file mono.c
 *  @brief This is a .c file the mono sound filter
 * 
 * This file includes implemented function which reads a 
 * .wav file and converts it from stereo to mono if is not
 * already mono.
 * 
 *  @author Erodotos Demetriou 
 *  @bug No known bugs. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int mono(char * fileName){
   AUDIO_FILE *AF = NULL;
   AF = readBinaryFile(fileName); 

   if (AF == NULL){
      printf("Error creating the audio struct!\n");
      return EXIT_FAILURE;
   }

   if (AF->numChannels == 1){
      printf("The file is already mono.\n");
      free(AF->audioData);
      free(AF);
      return EXIT_SUCCESS;
   }
     
   byte *newAudioData = (byte *)malloc((AF->subChunk2Size)/2 * sizeof(byte));
   
   int i =0;
   int j =i;
   for (i=0;i<AF->subChunk2Size;i++){
      if ((i%AF->blockAlign) < (AF->blockAlign/2))
         newAudioData[j++] = AF->audioData[i];
   }

   free(AF->audioData); 
   AF->audioData = newAudioData;
   AF->subChunk2Size = (AF->subChunk2Size)/2 ;
   AF->chunkSize = (AF->subChunk2Size)+36 ;
   AF->numChannels = 1;
   AF->blockAlign = AF->blockAlign /2 ;
   AF->byteRate = AF->byteRate / 2;
   
   FILE *fp = NULL;
   char outputFile[40] = {0};
   strcat(outputFile,"new-");
   strcat(outputFile,fileName); 
  
   if((fp = fopen(outputFile, "wb")) == NULL){
		printf("Failed to open file\n");
            free(AF->audioData);
            free(AF);
		return EXIT_FAILURE;
   }

   writeFile(outputFile, AF);

   fclose(fp);
   free(AF->audioData);
   free(AF); 
   newAudioData = NULL;

   return EXIT_SUCCESS;
}
