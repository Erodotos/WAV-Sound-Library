#ifndef __WAVE_H__
#define __WAVE_H__

//Definitions for printing manual words in Bold
#define BOLDBLACK   "\033[1m\033[30m"
#define RESET   "\033[0m"

//This is the seed key
#define seedKey 118
// We do this definition here to keep function getBit private,
//so no other .c file will be available to access it.
#define PRIVATE static 

// Type definitions
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

/**@brief This is a struct representing a .wav file
 * 
 * There are 40 fields in this struct. Each field
 * represents a metric for the .wav file. More info
 * about the struct can be found here : http://soundfile.sapp.org/doc/WaveFormat/
 * 
*/
typedef struct __attribute__((packed)) {
   //RIFF CHUNK DESCRIPTOR
   byte chunkID[4];
   dword chunkSize;
   byte format[4];

   //FMT SUB-CHUNK 
   byte subChunk1D[4];
   dword subChunk1Size;
   word audioFormat;
   word numChannels;
   dword sampleRate;
   dword byteRate;
   word blockAlign;
   word bitsPerSample;

   //DATA SUB-CHUNK
   byte subChunk2ID[4];
   dword subChunk2Size;

   //Data
   byte *audioData;

} AUDIO_FILE;

/** @brief This function reads a binary file
 *        
 * This function takes as input a file name. Then it reads
 * its binary data and constructs if no error occures an 
 * data stucture to save the wav file for further editing.
 * 
 *  @param char * The name of the file.
 *  @return AUDIO_FILE *. 
 */
AUDIO_FILE * readBinaryFile(char * );

/** @brief This function reads a binary file
 *        
 * This function takes as input a file name. Then it writes
 * its binary data to a new wav file.
 * 
 *  @param char * The name of the file.
 *  @return AUDIO_FILE *. 
 */
int writeFile(char *, AUDIO_FILE *);

/** @brief This function compares 2 audio files
 *        
 * This function takes as input a 2 file names. Then 
 * we read those files using method readBinaryFile and then the 2
 * audio structures are compared using 2 algorithms. The firstone 
 * is Euclidean Distance algorithm
 * (more here : https://en.wikipedia.org/wiki/Euclidean_distance)
 * and the second and more accurate algorithm is LCS distance 
 * (more here :  https://en.wikipedia.org/wiki/Edit_distance) 
 * using dynamicprogramming. This solution uses a 2D array with 
 * 2 lines and N columns in order to improove space complexity.
 * 
 *  @param char * The name of the first file.
 *  @param char * The name of the second file.
 *  @return int. 
 */
int similarity(char *, char *);

/** @brief This function converts to mono a wav file.
 *        
 * This function takes as input a  file name. Then it reads
 * its audio data using using method readBinaryFile. After that
 * subChunk2Size, chunkSize, numChannels, blockAlign and byteRate
 * are adjusted in order to fit to the new audio file requirements.
 * Also, the right chanel of the audio file is deleted. Finally,
 * the new audio file is creatred using the writeFile function.
 * 
 *  @param char * The name of the  file.
 *  @return int. 
 */
int mono(char * );


/** @brief This function prints .wav file header to the screen
 *        
 * This function takes as input a  file name. Then it reads
 * its audio data using using method readBinaryFile. After that 
 * it prints in a proper way its data to the screen.
 * 
 *  @param char * The name of the  file.
 *  @return int. 
 */
int list(char * );

/*
This should not be included in this .h file because the 
idea of private function is not used as all files that
include wave.h will get a copy of this function as well.

Comments avout this function can be found in encrypt.c

PRIVATE int getBit(char *, int );

*/

/** @brief This function creates permutation of anumber sequence
 *        
 * This function takes as input an integer which represents
 * the number of permutations we want to do and an unsigned int
 * which is a definition in the software. According to these key
 * we generate random numbers. First of all we fill an array 
 * with numbers from 0 to N -1. Then using rand() we chose 2 
 * cells of the array and then we swap them. After this suffeling 
 * is done N times the array is returned.
 * 
 *  @param int the number of bits in a string 
 *  @param unsigned int this is the seed Key
 *  @return int *. 
 */

int *createPermutationFunction(int , unsigned int );

/**
* @brief This function extracts the hidden message within the audio file
*
*
* @param audioFile This is name of the audio file
* @param outputfile This is the name of the file to save the extracted message
* @param length This is the length of the message
* @return Returns 0 if successfull or 1 if failed
*/
int decryptMessage (char *audioFile,char *outputfile, int length );
int decryptMessage (char *,char *, int );


/** @brief This function does the real encryption
 *        
 * This function takes as input 2 file names. The first one is
 * a wav file and the second is a text file. We actually get 
 * the string from the text file and hide in the wav file audio data
 * each bit of the string. This is done using the getBit and 
 * createPermutationFunction   functions. After the processing is
 * completed we generate a new audio file with text hidden in it.
 * 
 *  @param char * The name of the first file.
 *  @param char * The name of the second file.
 *  @return int *. 
 */
int encryptMessage(char *, char *);

/**
* @brief This function cuts a portion of the audio file and generates a new file with it
*
*
* @param filename This is name of the audio file
* @param begin This is the beginning second of the cut
* @param finish This is the finishing second of the cut 
* @return Returns 0 if successfull or 1 if failed
*/
int chop(char* filename, int begin, int finish);

/**
* @brief This function generates a new wave file that has the audio of the input file in reverse
*
*
* @param filename This is name of the audio file
* @return Returns 0 if successfull or 1 if failed
*/
int reverse(char *filename);

/**
* @brief This function that combines the audio from two audio files and generates a new audio file
*
* The audio file generated contains the right channel of the second file and the left channel
* of the first audio file
*
*
* @param af1 This is name of the first audio file
* @param af2 This is the name of the second audio file
* @return Returns 0 if successfull or 1 if failed
*/
int mix(char *af1, char *af2);

/** @brief This function prints GPL law on the screen
 *   
 *  @return void. 
 */
void printGPL();

/** @brief This function prints an extended manula of this software on the screen
 *   
 *  @return void. 
 */
void printManual();

/**
* @brief This function generates a new wave file that has the audio sped up
*
*
* @param filename This is name of the audio file
* @return Returns 0 if successfull or 1 if failed
*/
int speedup(char *filename);

/**
* @brief This function generates a new wave file that has a delay effect
*
*
* @param filename This is name of the audio file
* @return Returns 0 if successfull or 1 if failed
*/
int delay(char *filename);


#endif
