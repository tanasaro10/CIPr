/***************************************
*	Modified date: 27/07/2015 
*	Author: Pardau Stefan  
*	Scoala de Cara - Thales -2015	
****************************************/

#include "cips.h"
#include "mtypes.h"

int16_t **the_image;
int16_t **out_image;

#define ARGV_ARGUMENT1 1
#define ARGV_ARGUMENT2 2
#define ARGV_ARGUMENT3 3
#define ARGV_ARGUMENT4 4

enum eTag{
	eReturnOK=0, 
      	eNotSuffArg=1, 
	eNotInputFile1=2, 
	eNotInputFile2=3, 
	eNotSameSize=4
	}error;
enum eTag errFlag;
