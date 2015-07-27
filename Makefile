LIB      = -lm
CC       = gcc
COMPILE  = gcc -c
LINK     = gcc -o

imageio.o: imageio.c
	${COMPILE} imageio.c -I.
tiffio.o: tiffio.c
	${COMPILE} tiffio.c -I.
halftone.o: halftone.c
	${COMPILE} halftone.c -I.
bmp2tif.o: bmp2tif.c
	${COMPILE} bmp2tif.c -I.
round.o: round.c
	${COMPILE} round.c -I.
tif2bmp.o: tif2bmp.c
	${COMPILE} tif2bmp.c -I.
showi.o: showi.c
	${COMPILE} showi.c -I.
dumpi.o: dumpi.c
	${COMPILE} dumpi.c -I.
ht.o: ht.c
	${COMPILE} ht.c -I.
cutp.o: cutp.c
	${COMPILE} cutp.c -I.
boole.o: boole.c
	${COMPILE} boole.c -I.
geosubs.o: geosubs.c
	${COMPILE} geosubs.c -I.
addsub.o: addsub.c
	${COMPILE} addsub.c -I.
overlay.o: overlay.c
	${COMPILE} overlay.c -I.

SPSSRC	= imageio.c
	
SPSSRC1  = ${SPSSRC} numcvrt.c ht.c halftone.c
SPSOBJ1  = ${SPSSRC1:.c=.o}
halftone.exe: ${SPSOBJ1}
	${LINK} halftone.exe ${SPSOBJ1} -I.	
	
SPSSRC2  = ${SPSSRC} dumpi.c
SPSOBJ2  = ${SPSSRC2:.c=.o}
dumpi.exe: ${SPSOBJ2}
	${LINK} dumpi.exe ${SPSOBJ2} -I.		

SPSSRC3  = ${SPSSRC} showi.c
SPSOBJ3  = ${SPSSRC3:.c=.o}
showi.exe: ${SPSOBJ3}
	${LINK} showi.exe ${SPSOBJ3} -I.	

SPSSRC4  = ${SPSSRC} tif2bmp.c
SPSOBJ4  = ${SPSSRC4:.c=.o}
tif2bmp.exe: ${SPSOBJ4}
	${LINK} tif2bmp.exe ${SPSOBJ4} -I.		

SPSSRC5  = ${SPSSRC} bmp2tif.c
SPSOBJ5  = ${SPSSRC5:.c=.o}
bmp2tif.exe: ${SPSOBJ5}
	${LINK} bmp2tif.exe ${SPSOBJ5} -I.		

SPSSRC6  = ${SPSSRC} round.c
SPSOBJ6  = ${SPSSRC6:.c=.o}
round.exe: ${SPSOBJ6}
	${LINK} round.exe ${SPSOBJ6} -I.	

SPSSRC7  = ${SPSSRC} create.c
SPSOBJ7  = ${SPSSRC7:.c=.o}
create.exe: ${SPSOBJ7}
	${LINK} create.exe ${SPSOBJ7} -I.

SPSSRC8  = ${SPSSRC} cutp.c maincp.c
SPSOBJ8  = ${SPSSRC8:.c=.o}
maincp.exe: ${SPSOBJ8}
	${LINK} maincp.exe ${SPSOBJ8} -I.
		
SPSSRC9  = ${SPSSRC} boole.c boolean.c
SPSOBJ9  = ${SPSSRC9:.c=.o}
boolean.exe: ${SPSOBJ9}
	${LINK} boolean.exe ${SPSOBJ9} -I.

SPSSRC10  = ${SPSSRC} geosubs.c geometry.c
SPSOBJ10 = ${SPSSRC10:.c=.o}
geometry.exe: ${SPSOBJ10}
	${LINK} geometry.exe ${SPSOBJ10} -lm -I.

SPSSRC11  = ${SPSSRC} ilabel.c
SPSOBJ11 = ${SPSSRC11:.c=.o}
ilabel.exe: ${SPSOBJ11}
	${LINK} ilabel.exe ${SPSOBJ11} -I.

SPSSRC12  = ${SPSSRC} invert.c
SPSOBJ12 = ${SPSSRC12:.c=.o}
invert.exe: ${SPSOBJ12}
	${LINK} invert.exe ${SPSOBJ12} -I.

SPSSRC13  = ${SPSSRC} addsub.c mainas.c
SPSOBJ13 = ${SPSSRC13:.c=.o}
mainas.exe: ${SPSOBJ13}
	${LINK} mainas.exe ${SPSOBJ13} -I.

SPSSRC14  = ${SPSSRC} overlay.c mainover.c
SPSOBJ14 = ${SPSSRC14:.c=.o}
mainover.exe: ${SPSOBJ14}
	${LINK} mainover.exe ${SPSOBJ14} -I.

SPSSRC15  = ${SPSSRC} side.c
SPSOBJ15 = ${SPSSRC15:.c=.o}
side.exe: ${SPSOBJ15}
	${LINK} side.exe ${SPSOBJ15} -I.

SPSSRC16  = ${SPSSRC} stega.c
SPSOBJ16 = ${SPSSRC16:.c=.o}
stega.exe: ${SPSOBJ16}
	${LINK} stega.exe ${SPSOBJ16} -I.

SPSSRC17  = ${SPSSRC} geosubs.c stretch.c
SPSOBJ17 = ${SPSSRC17:.c=.o}
stretch.exe: ${SPSOBJ17}
	${LINK} stretch.exe ${SPSOBJ17} -lm -I.

all: 
	make halftone.exe
	make dumpi.exe
	make showi.exe
	make tif2bmp.exe
	make bmp2tif.exe
	make round.exe
	make create.exe
	make maincp.exe
	make boolean.exe
	make geometry.exe
	make ilabel.exe
	make invert.exe
	make mainas.exe
	make mainover.exe
	make side.exe
	make stega.exe
	make stretch.exe
	
clean:
	rm -f *.o *.exe
