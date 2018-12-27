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

/** @file mixer.c
 *  @brief This is the source file that is responsible
 *  for mixing two audio files together
 *
 *  @author Christakis Achilleos 
 *  @bug No known bugs. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int mix(char *af1,char *af2){


   if (af1 == NULL || af2 ==NULL){
      printf("Please dont give null file names as parameters.\n");
      return EXIT_FAILURE;
   }


   AUDIO_FILE *f1 = NULL;
   AUDIO_FILE *f2 = NULL;

   f1 = readBinaryFile(af1);

   if(f1==NULL){
      return EXIT_FAILURE;
   }

   f2 = readBinaryFile(af2);
   if(f2==NULL){
      free(f1->audioData);
      free(f1);
      return EXIT_FAILURE;
   }


   int smallest = 0;
   if( f1->subChunk2Size < f2->subChunk2Size)
      smallest = 1;
   else
      smallest = 2;

   if(smallest == 1){
      int i;
      for(i =0; i< f1->subChunk2Size; i+=4){

         f1->audioData[i] = f2->audioData[i]; 
         f1->audioData[i+1] = f2->audioData[i+1]; 

      }
      char temp[100]= {0};
      strcpy(temp , "mix-");

      char tmp[50] = {0};   
      i=0;
      char *p = af1;
      while(*p != '.'){
         tmp[i] = *p;
         i++;
         p++;
      }
      tmp[i] = '\0';
      strcat(temp, tmp);

      strcat(temp,"-");
      strcat(temp, af2);

      writeFile(temp, f1);	
   }
   else if(smallest == 2){
      int i;
      for(i =2; i< f2->subChunk2Size; i+=4){

         f2->audioData[i] = f1->audioData[i]; 
         f2->audioData[i+1] = f1->audioData[i+1]; 

      }	
      char temp[100]= {0};
      strcpy(temp , "mix-");
      char tmp[50] = {0};   
      i=0;
      char *p = af2;
      while(*p != '.'){
         tmp[i] = *p;
         i++;
         p++;
      }
      tmp[i] = '\0';
      strcat(temp, tmp);
      strcat(temp,"-");
      strcat(temp, af1);
      writeFile(temp, f2);	

   }
   free(f2->audioData);
   free(f2);
   free(f1->audioData);
   free(f1);	

   return EXIT_SUCCESS;

}

