DEST=~/bin

all : ${DEST}/tester ${DEST}/display ${DEST}/readfile ${DEST}/collate

${DEST}/tester : tester.c
	gcc -o ${DEST}/tester tester.c

${DEST}/display : display.c
	gcc -o ${DEST}/display display.c

${DEST}/readfile : readfile.c
	gcc -o ${DEST}/readfile readfile.c

${DEST}/collate : collate.c
	gcc -o ${DEST}/collate collate.c
