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

/** @file encrypt.c
 *  @brief This is a .c file which implements the encryption process
 * 
 * This file includes implemented function which reads specifc bits from 
 * a string, a function that create permuations and the main core of
 * encryption.
 * 
 *  @author Erodotos Demetriou 
 *  @bug No known bugs. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

/** @brief This function prints gets a bit from a byte
 *        
 * This function takes as input a  string pointer and a bit
 * number.Then using mathematical calculations as shown below
 * it calculates the accurate position of the n-th bit in the given 
 * string. Finally using bitewise operations we extract the specific
 * bit value from the correct byte.
 * 
 *  @param char * a pointer to a string.
 *  @param int this is the number of the n-th bit we want to extract
 *  @return int. 
 */


PRIVATE int getBit(char *m, int n){

   int i;
   int characterPosition = 1;
   characterPosition = n/8;
   char byte;

   for(i=0;i<characterPosition;i++){
       m ++ ;
   }

   byte = *m;
   int bitArray[8];
   for(i = 7; 0 <= i; i --){
      bitArray[i]  = (byte >> i) & 0x01;
   }
   
   return bitArray[7-(n%8)];
}

int *createPermutationFunction(int N, unsigned int systemkey){
   int *premutationArray = (int *)malloc(N * sizeof(int));
   int i=0;

   for (i=0;i<N;i++){
      premutationArray[i] = i;
   }

   srand(systemkey);
   for (i=0;i<N;i++){
      
      int k,j;
      k=rand()%N;
      do{
         j = rand()%N;
      }while(k==j);

      //Swap array values using XOR in oreder to speedup the function
      premutationArray[k] = premutationArray[k] ^ premutationArray[j];  
      premutationArray[j] = premutationArray[k] ^ premutationArray[j];   
      premutationArray[k] = premutationArray[k] ^ premutationArray[j];

   }
   return premutationArray;
}

int encryptMessage(char *soundFileName, char *textFileName){

   AUDIO_FILE *AF = NULL;
   AF = readBinaryFile(soundFileName); 

   if (AF == NULL){
      return EXIT_FAILURE;
   }

   FILE *fp = NULL;
   char *stringBuffer;  // In this char pointer we will save the whole text file
   int length;

   if ((fp = fopen(textFileName, "rb")) == NULL) {
      printf("Error opening text file\n");
      free(AF->audioData);
      free(AF);
      return EXIT_FAILURE;
   }else{

      // Here we get the length of the text file in terms of characters including '\0'
      fseek (fp, 0, SEEK_END);
      length = ftell (fp);
      fseek (fp, 0, SEEK_SET);

      if (length*8 > AF->subChunk2Size){
         printGPL();
         printf("The text file is too large to be encrypted.\nChoose a larger .wav file or a smaller text file.\n");
         free(AF->audioData);
         free(AF);
         fclose(fp);
         return EXIT_FAILURE;
      }  

      stringBuffer = (char *) malloc(length*sizeof(char));     

      if (stringBuffer == NULL){
         printf("System out of memory. System could not read the text file\n");
         free(AF->audioData);
         free(AF);
         fclose(fp);
         return EXIT_FAILURE;
      }else{
         if ((fread(stringBuffer, length*sizeof(char) , 1 , fp)!=1)){
            printf("Error reading the text file\n");
            fclose (fp);
            free(stringBuffer);
            free(AF->audioData);
            free(AF);
            return EXIT_FAILURE;
         }    
      }
   } 
   fclose (fp);
   
   // Real Encryption starts here

   int i, x;
   int *permutation = createPermutationFunction(length*8, seedKey);
   
   for (i=0;i<length*8;i++){
      int u = getBit(stringBuffer,i);
      x = permutation[i];
      if (u){
         AF->audioData[x] = AF->audioData[x] | 0x01;
      }else{
         AF->audioData[x] = AF->audioData[x] & 0xfe;
      }
   }

   char outputFile[40] = {0};
   strcat(outputFile,"new-");
   strcat(outputFile,soundFileName); 
   writeFile(outputFile,AF);
   
   free(permutation);
   free(stringBuffer);
   free(AF->audioData);
   free(AF);
   return EXIT_SUCCESS;
}