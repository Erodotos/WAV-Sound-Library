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

/** @file similarity.c
 *  @brief This is a .c file to find the similarity of 2 files
 * 
 * This file includes implemented similarity functions of 
 * Euclidean similarity and LCS.
 * 
 *  @author Erodotos Demetriou 
 *  @bug No known bugs. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wave.h"

#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)>(y))?(x):(y))


int similarity(char *sourceFile, char *fileName){
   
   AUDIO_FILE *source = NULL;
   source = readBinaryFile(sourceFile); 

   if (source == NULL){
      return EXIT_FAILURE;
   }
   
   AUDIO_FILE *AF = NULL;
   AF = readBinaryFile(fileName); 

   if (AF == NULL){
      free(source->audioData);
      free(source);
      return EXIT_FAILURE;
   }

   // Computation of Euclidean Distance
   int i,j;
   unsigned long sum = 0;
   int maxWaveSize = MIN((source->subChunk2Size), (AF->subChunk2Size));
   for (i=0;i<maxWaveSize;i++){
      sum = sum + pow(abs(source->audioData[i] - AF->audioData[i]),2);
   }
   double euclideanDistance = sqrt(sum);
  
   printf("Euclidean Distance:%.3f\n", euclideanDistance);

   //Computation of LCS Distance

   int m= source->subChunk2Size;
   int n = AF->subChunk2Size;

   int **C =(int **) malloc(2*sizeof(int *));
   C[0] = (int*)malloc((n+1)*sizeof(int));
   C[1] = (int*)malloc((n+1)*sizeof(int));
   int binaryIndex = 0;

   for (i=0;i<m;i++){
      binaryIndex = i & 1;
      for (j=0;j<=n;j++){
         if (i==0 || j==0){
            C[binaryIndex][j]=0;
         }else if(source->audioData[i-1]==AF->audioData[j-1]){
            C[binaryIndex][j] = C[1 - binaryIndex][j - 1] + 1; 
         }else{
            C[binaryIndex][j] = MAX(C[1 - binaryIndex][j], C[binaryIndex][j - 1]); 
         }
      }
   }

   double lcs = C[binaryIndex][n];
   double min = MIN(m,n);
   double dLCS = 1 - (lcs/min);
   printf("LCSS distance\t  :%.3f\n",dLCS);

   free(C[0]);
   free(C[1]);
   free(C);
   free(AF->audioData);
   free(AF);
   free(source->audioData);
   free(source);
   return EXIT_SUCCESS;
}
