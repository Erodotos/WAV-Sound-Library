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

/** @file list.c
 *  @brief This is a .c file which runs function list
 * 
 * This file includes implemented function which reads a 
 * binary file and presents its header data in human
 * recognizable format
 * 
 *  @author Erodotos Demetriou 
 *  @bug No known bugs. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int list(char * fileName){

   AUDIO_FILE *AF = NULL;
   AF = readBinaryFile(fileName); 

   if (AF == NULL){
      return EXIT_FAILURE;
   }
   
   printf("RIFF_CHUNK_HEADER\n");
   printf("=================\n");


   printf("chunkID: %c%c%c%c\n", AF->chunkID[0], AF->chunkID[1], AF->chunkID[2], AF->chunkID[3]);
   printf("chunkSize: %u\n", AF->chunkSize);
   printf("format: %c%c%c%c\n\n", AF->format[0], AF->format[1], AF->format[2], AF->format[3]);

   printf("FMT_SUBCHUNK_HEADER\n");
   printf("===================\n");

   printf("chunkID: %c%c%c%c\n", AF->subChunk1D[0], AF->subChunk1D[1], AF->subChunk1D[2], AF->subChunk1D[3]);
   printf("subChunk1Size: %u\n", AF->subChunk1Size);
   printf("audioFormat: %hu\n", AF->audioFormat);
   printf("numChannels: %hu\n", AF->numChannels);
   printf("sampleRate: %u\n", AF->sampleRate);
   printf("byteRate: %u\n", AF->byteRate);
   printf("blockAlign: %u\n", AF->blockAlign);
   printf("bitsPerSample: %hu\n\n", AF->bitsPerSample);

   printf("DATA_SUBCHUNK_HEADER\n");
   printf("====================\n");
   
   printf("chunkID: %c%c%c%c\n", AF->subChunk2ID[0], AF->subChunk2ID[1], AF->subChunk2ID[2], AF->subChunk2ID[3]);
   printf("subChunk2Size: %u\n\n", AF->subChunk2Size);
   printf("******************************************\n");

   free(AF->audioData);
   free(AF);

   return EXIT_SUCCESS;
}