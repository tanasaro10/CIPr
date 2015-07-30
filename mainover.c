/*********************************************
*
*   file mainover.c
*
*   Functions: This file contains
*      main
*
*   Purpose:
*      This file contains the main calling
*      routine that calls the overlay functions.
*
*
*   Modifications:
*      6 March 1993  created
*      22 August 1998  modified to work on 
*    entire images at once.
*      19 September 1998  modified to work with 
*    all I O routines in imageio.c.
*	
*		Modified date: 27/07/2015 
*		Author: Pardau Stefan  
*		Scoala de Vara  Thales 2015	
*
********************************************/

#include "mainover.h"

int main(sint32_t argc, char_t *argv[])
{
	errFlag = eReturnOK;
	char_t 		name1[80];
	char_t		name2[80];
	char_t		name3[80];
	char_t		type[80];
	sint32_t		count;	
	sint32_t		i;
	sint32_t		j;
	sint32_t     length, width;

/*********************************************
*
*   Interpret the command line parameters.
*
**********************************************/
 
	if(argc < 5)
	{	
    		printf(
    		"\n\nNot enough parameters:"
     		"\n"
     		"\n usage: mainover in-file1 in-file2 out-file "
     		"type"
     		"\n"
     		"\n recall type: nonzero zero greater less"
     		" average"
     		"\n the input images must be the same size"
     		"\n"
     		"\n");
    		errFlag = eNotSuffArg;
   	}

	if(errFlag == eReturnOK)
	{
		strcpy(name1,  argv[ARGV_ARGUMENT1]);
   		strcpy(name2, argv[ARGV_ARGUMENT2]);
   		strcpy(name3, argv[ARGV_ARGUMENT3]);
   		strcpy(type,  argv[ARGV_ARGUMENT4]);


		
	   	if(does_not_exist(name1))
		{
	    		printf("\nERROR input file %s does not exist", name1);
	    		errFlag = eNotInputFile1;
		}
		
		if(errFlag == eReturnOK)
		{
		   	if(does_not_exist(name2))
			{
		    		printf("\nERROR input file %s does not exist", name2);
		    		errFlag = eNotInputFile2;
		   	}

		/*********************************************
		*
		*   Read the input image headers.
		*   Ensure the input image are the same size.
		*   Allocate the image arrays and read
		*   the image data.
		*
		**********************************************/
			if(errFlag == eReturnOK)
			{
			   	if(are_not_same_size(name1, name2))
				{
			      		printf("\n Images %s and %s are not the same size", name1, name2);
			      		errFlag = eNotSameSize;
			   	}  /* ends if sizes not the same */

				if(errFlag == eReturnOK)
				{

				   	get_image_size(name1, &length, &width);
				   	the_image = allocate_image_array(length, width);
				   	out_image = allocate_image_array(length, width);
					if ((the_image== NULL)||(out_image== NULL))
					{
						printf("\n Images not created !");
						exit(0);
					}
				   	create_image_file(name1, name3);
				   	read_image_array(name1, the_image);
				   	read_image_array(name2, out_image);

				/*********************************************
				*
				*   Apply the desired overlay function.
				*
				**********************************************/

				      	/* non zero */

				char_t a = strncmp("non", type, 3);
				   	if(a == 0)
					{
				      		non_zero_overlay(the_image, out_image, length, width);
				   	}  /* ends non_zero operation */

				      	/* zero */
				char_t b = strcmp("zero", type);
				   	if(b == 0)
					{
				      		zero_overlay(the_image, out_image, length, width);
				   	}  /* ends zero operation */

				      	/* greater */

				char_t c = strncmp("gre", type, 3);
				   	if(c == 0)
					{
				      		greater_overlay(the_image, out_image, length, width);
				   	}  /* ends greater operation */

				      	/* less */

				char_t d = strncmp("les", type, 3);
				   	if(d == 0)
					{
				      		less_overlay(the_image, out_image, length, width);
				   	}  /* ends less operation */

				      	/* average */

				char_t e = strncmp("ave", type, 3);
				   	if(e == 0)
					{
				      		average_overlay(the_image, out_image, length, width);
				   	}  /* ends average operation */

				   	write_image_array(name3, out_image);
				   	free_image_array(out_image, length);
				   	free_image_array(the_image, length);

					}
				}
			}
		}
	return errFlag;
}  /* ends main  */
