
    /******************************************
    *
    *  file d:\cips\numcvrt.c
    *
    *  Functions:
    *     get_integer
    *     get_short
    *     get_long
    *     get_float
    *
    *  Purpose: 
    *     These functions read numbers from
    *     the keyboard.
    *
    *  Modifications:
    *     12 May 1993 - recreated
    *
    *******************************************/




get_integer(n)
   int *n;
{
   char string[80];

   gets(string);
   *n = atoi(string);
}


get_short(n)
   short *n;
{
   char string[80];

   gets(string);
   *n = atoi(string);
}


get_long(n)
   long *n;
{
   char string[80];

   gets(string);
   *n = atol(string);
}


get_float(f)
   float *f;
{
   char string[80];

   gets(string);
   *f = atof(string);
}
