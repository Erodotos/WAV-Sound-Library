# WAV-Sound-Library


@author Erodotos Demetriou , Christakis Achileos

This assignment lunches a program which can apply some basic filters to 
a .wav audio file.


   SOFTWARE MANUAL

NAME
	wavengine - edits .wav files

SYNOPSIS
	wavengine [OPTION] [FILE]...

DESCRIPTION
	Available Options

	-man, print this manual

	-list, prints on screen the file header/s

	-mono, takes 2 .wav files and converts them to use only one channel

	-mix, combines the audio from 2 audio files

	-chop, cut the sound on specific borders

	-reverse, generate audio file with the audio backwards

	-similarity, checks if 2 .wav files are similar using Euclidean and LCSS Algorithms

	-encodeText, hides a text message within the audio file

	-decodeText, extract hidden message from the audio file

EXAMPLES OF USE
	$./wavengine –list Windows_Error.wav Windows_Shutdown.wav

	$./wavengine –mono sound1.wav sound2.wav

	$./wavengine –mix sound1.wav sound2.wav

	$./wavengine –chop sound1.wav 2 4

	$./wavengine –reverse sound1.wav sound2.wav

	$./wavengine –similarity sound1.wav sound2.wav sound3.wav

	$./wavengine –encodeText sound1.wav inputText.txt

	$./wavengine –decodeText encryptedSound.wav msgLength output.txt

	$./wavengine -man 

