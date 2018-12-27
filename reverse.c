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

/** @file reverse.c
 *  @brief This is the source file that is responsible for reversing the 
 *  data from the audio file
 *
 *  @author Christakis Achilleos 
 *  @bug No known bugs. 
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"
#include "wave.h"

int reverse(char *filename){

	AUDIO_FILE *AF = NULL;
	
	AF = readBinaryFile(filename);
	if (AF == NULL){
		return EXIT_FAILURE;

	}
	byte *swp = AF->audioData;
	int i, j;
	int last = (AF->subChunk2Size) -1;

	if(AF->numChannels == 2){
   	for(i = 0, j = last; i<j;j-=4, i+=4){
		
	   	swp[i] = swp[i] ^ swp[j-3];
		swp[j-3] = swp[i] ^ swp[j-3];
		swp[i] = swp[i] ^ swp[j-3];

   		swp[i+1] = swp[i+1] ^ swp[j-2];
   		swp[j-2] = swp[i+1] ^ swp[j-2];
   		swp[i+1] = swp[i+1] ^ swp[j-2];

   		swp[i+2] = swp[i+2] ^ swp[j-1];
   		swp[j-1] = swp[i+2] ^ swp[j-1];
   		swp[i+2] = swp[i+2] ^ swp[j-1];

	   	swp[i+3] = swp[i+3] ^ swp[j];
	   	swp[j] = swp[i+3] ^ swp[j];
	   	swp[i+3] = swp[i+3] ^ swp[j];
	   }
	}
	
	else if(AF->numChannels == 1){
   	for(i = 0, j = last; i<j;j-=2, i+=2){
		
	   	swp[i] = swp[i] ^ swp[j-1];
	   	swp[j-1] = swp[i] ^ swp[j-1];
   		swp[i] = swp[i] ^ swp[j-1];

   		swp[i+1] = swp[i+1] ^ swp[j];
   		swp[j] = swp[i+1] ^ swp[j];
   		swp[i+1] = swp[i+1] ^ swp[j];
		}
	}

	else {
		printf("This software does not support the reverse\n feature for files with more than two channels\n" );
		free(AF->audioData);
		free(AF);
		return EXIT_FAILURE;
	}
 	char *name = (char*) calloc(100, sizeof(char));
	
	strcat(name, "reverse-");
	strcat(name, filename);
	writeFile(name, AF);
	free(AF->audioData);
	free(AF);
	free(name);
	return EXIT_SUCCESS;
}

