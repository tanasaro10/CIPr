# CIPr
Thales Summer School - Quality Code Project

###Scurta descriere
Proiectul consta dintr-o serie de rutine pentru procesarea imaginilor folosind cod C (operatii precum: decupare, redimensionare, operatii geometrice, aritmetice, detectie de contur, etc). Programele au fost dezvoltate prin anii ’90 si publicate in cartea: D. Phillips - Image Processing in C: Analyzing and Enhancing Digital Images, RandD Publications, 1994. (web link: http://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/ ). Doar o parte din rutinele publicate au fost preluate in acest proiect. 
Codul a fost dezvoltat folosind standardul C90, disponibil la acea vreme. De asemenea aplicatiile nu permit decat lucrul cu imagini non-color bmp sau tiff pe 8 biti. 
###Obiective proiect
1.	Refactorizare cod astfel incat sa fie compliant cu regulile MISRA, si standardul C99. Functionalitatea, in acelasi timp, sa fie pastrata sau imbunatatita;
2.	Identificarea bug-urilor si eliminarea acestora din aplicatie; De asemenea eliminarea tuturor warning-urilor de compilator;
3.	Utilizarea de tool-uri automate pentru verificarea calitatii codului si identificarea instructiunilor cu probleme;
4.	Upgrade functionalitate cod (research & development):
a.	lucrul cu imagini color pe 8 biti
b.	lucrul cu imagini bmp pe 24 de biti.
c.	Meniu user-friendly
5.	Documentare / versionare a modificarilor operate asupra codului;

###Listing proiect:
bmp2tif.exe	/* Convert a bmp 8 bit image to tiff */

boolean.exe	/* Apply a boolean operation between 2 files: and, xor, or, nor, nand, not */

create.exe	/* Creates an empty tiff or bmp file of size l*ROWS , w*COLS */

dumpi.exe	/* Dumps the image number values to an ascii text */

geometry.exe	/* Main calling routine for geometric subroutines: displacement, rotation, stretching, cross product */

halftone.exe	/* Grey tones depending on a threshold value */

ilabel.exe	/* Write a block text inside an image (labeling)*/

invert.exe	/* Inverts an image*/

mainas.exe	/* Addition and subtraction between 2 files */

maincp.exe	/* Cuts a piece of an image and paste it to another image file */

mainover.exe	/* overlay an image on other */

round.exe	/* rounds off an image (cut it ) and copy it to a new file */

showi.exe	/* shows the image numbers on the screen (similar with dumpi) */

side.exe	/* takes 2 images and puts them together (side by side) */

stega.exe	/* hide/uncover one image to/from another image - steganography*/

stretch.exe	/* stretch an image */

tif2bmp.exe	/* convert tiff to bmp */

###Optiuni Makefile:  	make <file>.exe ; 	make all; 	make clean;

