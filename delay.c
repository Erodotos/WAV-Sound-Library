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

/** @file dealy.c
 *  @brief This is the source file that is responsible for adding the 
 *  delay effect to the audio file
 *
 *  @author Christakis Achilleos 
 *  @bug No known bugs. 
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"


int delay(char *filename){

   AUDIO_FILE *AF = NULL;

   AF = readBinaryFile(filename);
   if (AF == NULL){
      return EXIT_FAILURE;

   }
   byte *swp = AF->audioData;
   int i, j;
   int last = (AF->subChunk2Size) ;
   byte *newData = (byte*)malloc(sizeof(byte)*last);
   for(i = 0; i<last ;i++){
      newData[i] = swp[i];
   }
  
  for(i = 0, j= AF->byteRate; j< last-2; i+=8, j+=8){
     
      short tmp = 0x00; 
      tmp = tmp | swp[i];
      tmp = tmp << 8;
      tmp = tmp | swp[i+1];
     
      short tmp2 = 0x00;
      tmp2 = tmp2 | swp[j];
      tmp2 = tmp2 <<8;
      tmp2 = tmp2 | swp [j+1];

      newData[j+1] = 0x00;
      newData[j+1] = tmp | newData[j+1];
      tmp = tmp >>8;
      newData[j] = 0x00;
      newData[j] = tmp | newData[j]; 

        
      tmp = 0x00; 
      tmp = tmp | swp[i+2];
      tmp = tmp << 8;
      tmp = tmp | swp[i+3];
     
      tmp2 = 0x00;
      tmp2 = tmp2 | swp[j+2];
      tmp2 = tmp2 <<8;
      tmp2 = tmp2 | swp [j+3];

      newData[j+3] = 0x00;
      newData[j+3] = tmp | newData[j+3];
      tmp = tmp >>8;
      newData[j+2] = 0x00;
      newData[j+2] = tmp | newData[j+2]; 


     
   }

   byte *p = AF->audioData;
   free (p);
   AF->audioData = newData;
   newData = NULL;
   char *name = (char*) calloc(100, sizeof(char));

   strcat(name, "delay-");
   strcat(name, filename);
   writeFile(name, AF);
   free(AF->audioData);
   free(AF);
   free(name);
   return EXIT_SUCCESS;
}

