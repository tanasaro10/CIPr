#include "cips.h"
#include "mtypes.h"
#include "imageio.h"



#define argv1 1
#define argv2 2
#define argv3 3
#define argv4 4

void print_side_usage()
{
   printf(
	"\n"
	"\n usage: side in-file-1 in-file-2 "
	"out-file method"
	"\n        where method is Top-to-bottom "
	"or Side-by-side"
	"\n");
}


enum side_err{
	eReturnOK=0, 
      	eNotSuffArg=1, 
	eNotValidMethod=2, 
	eNoInputFile1=3, 
	eNoInputFile2=4,
	eNotSameWidth=5,
	eNotSameLength=6
	};
enum side_err errFlag_side;

