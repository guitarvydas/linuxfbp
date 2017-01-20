DEST=~/bin

all : ${DEST}/grash ${DEST}/tester ${DEST}/display ${DEST}/readfile ${DEST}/collate ${DEST}/dot

${DEST}/tester : tester.c
	gcc -o ${DEST}/tester tester.c

${DEST}/display : display.c
	gcc -o ${DEST}/display display.c

${DEST}/readfile : readfile.c
	gcc -o ${DEST}/readfile readfile.c

${DEST}/collate : collate.c
	gcc -o ${DEST}/collate collate.c

${DEST}/dot : dot.c
	gcc -o ${DEST}/dot dot.c

${DEST}/grash : grash.c
	gcc -o ${DEST}/grash grash.c
