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

/** @file wave.c
 *  @brief This is a .c file which runs core functionalities
 * useful for all other .c files
 * 
 * This file contains the implementation of 3 functions.
 * These functions concerns reading, writing to files
 * as well as printing functions for software amnual 
 * and GPL. 
 * 
 *  @author Erodotos Demetriou 
 *  @bug No known bugs. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"


AUDIO_FILE *readBinaryFile(char * fileName){
   
   AUDIO_FILE *AF = NULL;

   if ((AF = (AUDIO_FILE *)malloc(sizeof(AUDIO_FILE))) == NULL){
      printf("System out of memory. System can not allocate memory for file header\n");
      return NULL;
   }

   FILE *fp;

   fp = fopen(fileName, "rb");
   if (fp == NULL) {
      printf("Error opening file\n");
      return NULL;
   }

   if (fread(AF, 44 , 1, fp) != 1){
      printf("Error reading the file header!\n");
      return NULL;
   }

   if (!(AF->chunkID[0] == 'R' && AF->chunkID[1] == 'I' && AF->chunkID[2] == 'F' && AF->chunkID[3] == 'F')){
       printf("Wrong file format. Operation aborted.\n");
       return NULL;
   }else if(!(AF->format[0] == 'W' && AF->format[1] == 'A' && AF->format[2] == 'V' && AF->format[3] == 'E')){
       printf("Wrong file format. Operation aborted.\n");
       return NULL;
   }else if(AF->audioFormat != 1){
       printf("Wrong file format. Operation aborted.\n");
       return NULL;
   }

  
   

   if ((AF->audioData = (byte *)malloc(AF->subChunk2Size)) == NULL){
      printf("System out of memory. System can not allocate memory for audio data\n");
      return NULL;
   }

   if (fread(AF->audioData, AF->subChunk2Size , 1, fp) != 1){
      printf("Error reading the file data!\n");
      return NULL;
   }
   fclose (fp);

   return AF;
}

int writeFile(char* outputfile, AUDIO_FILE *AF){

	FILE *fp = NULL;

	if((fp = fopen(outputfile, "wb")) == NULL){
		printf("Failed to open file\n");
		return EXIT_FAILURE;
	}

   if ( fwrite(AF, sizeof(*AF) - sizeof(byte*), 1, fp) != 1){
      printf("Error writting the file header!\n");
      fclose(fp);
      return EXIT_FAILURE;
   }

   if ( fwrite(AF->audioData, AF->subChunk2Size, 1, fp) != 1){
      printf("Error writting the file data!\n");
      fclose(fp);
      return EXIT_FAILURE;
   }
	
	fclose(fp);
   
	return EXIT_SUCCESS;

}

void printGPL(){
    printf("\n\nSound processing software developed for educational purposes.\n\
Copyright (C) 2018 Christakis Achilleos, Erodotos Demetriou \n\
This program is free software: you can redistribute it and/or modify \n\
it under the terms of the GNU General Public License as published by \n\
the Free Software Foundation, either version 3 of the License, or \n\
at your option) any later version. \n\
This program is distributed in the hope that it will be useful, \n\
but WITHOUT ANY WARRANTY; without even the implied warranty of \n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n\
GNU General Public License for more details. \n\
Υou should have received a copy of the GNU General Public License \n\
along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n");
}

void printManual(){

    printf("\nBROYAL Audio Editor Copyright (C) 2018 Christakis Achilleos, Erodotos Demetriou \n\
\t\tThis program comes with ABSOLUTELY NO WARRANTY; \n\
\tThis is free software, and you are welcome to redistribute it \n\
\t\t\tunder certain conditions;\n\n");


    printf(BOLDBLACK "SOFTWARE MANUAL\n\n" RESET);

    printf( BOLDBLACK "NAME" RESET );
    printf("\n\twavengine - edits .wav files\n\n");

    printf(BOLDBLACK "SYNOPSIS\n" RESET);
    printf("\twavengine [OPTION] [FILE]...\n\n");

    printf(BOLDBLACK "DESCRIPTION\n" RESET);
    printf("\tAvailable Options\n\n");
    printf("\t-man, print this manual\n\n");
    printf("\t-list, prints on screen the file header/s\n\n");
    printf("\t-mono, takes 2 .wav files and converts them to use only one channel\n\n");
    printf("\t-mix, combines the audio from 2 audio files\n\n");
    printf("\t-chop, cut the sound on specific borders\n\n");
    printf("\t-reverse, generate audio file with the audio backwards\n\n");
    printf("\t-similarity, checks if 2 .wav files are similar using Euclidean and LCSS Algorithms\n\n");
    printf("\t-encodeText, hides a text message within the audio file\n\n");
    printf("\t-decodeText, extract hidden message from the audio file\n\n");
    printf("\t-delay, generate audio file with the delay effect\n\n");
    printf("\t-speedup, generate audio file with the audio fastforwarded\n\n");

    printf( BOLDBLACK "EXAMPLES OF USE\n" RESET );
    printf("\t$./wavengine –list Windows_Error.wav Windows_Shutdown.wav\n\n");
    printf("\t$./wavengine –mono sound1.wav sound2.wav\n\n");
    printf("\t$./wavengine –mix sound1.wav sound2.wav\n\n");
    printf("\t$./wavengine –chop sound1.wav 2 4\n\n");
    printf("\t$./wavengine –reverse sound1.wav sound2.wav\n\n");
    printf("\t$./wavengine –similarity sound1.wav sound2.wav sound3.wav\n\n");
    printf("\t$./wavengine –encodeText sound1.wav inputText.txt\n\n");
    printf("\t$./wavengine –decodeText encryptedSound.wav msgLength output.txt\n\n");
    printf("\t$./wavengine –delay sound1.wav sound2.wav\n\n");
    printf("\t$./wavengine –speedup sound1.wav sound2.wav\n\n");
    printf("\t$./wavengine -man \n\n");

}
