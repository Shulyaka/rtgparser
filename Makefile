CFLAGS+=-ggdb -Wall
ifeq ($(COVERAGE),Y)
	CFLAGS+=--coverage -O0
	LDFLAGS+=--coverage
endif

.PHONY: clean all tests

all: libparser.a testparse tests

clean:
		rm -f *.o *.gcda *.gcno libparser.a testparse core* imessage* omessage*

testparse: libparser.a testparse.o
		g++ testparse.o -L . -l parser -o testparse ${LDFLAGS}

libparser.a: field.o fldformat.o parser.o builder.o frmiterator.o
		ar rcs libparser.a field.o fldformat.o parser.o builder.o frmiterator.o

testparse.o: testparse.cpp parser.h
		g++ -c testparse.cpp ${CFLAGS}

parser.o: parser.cpp parser.h
		g++ -c parser.cpp ${CFLAGS}

builder.o: builder.cpp parser.h
		g++ -c builder.cpp ${CFLAGS}

field.o: field.cpp parser.h
		g++ -c field.cpp ${CFLAGS}

fldformat.o: fldformat.cpp parser.h
		g++ -c fldformat.cpp ${CFLAGS}

frmiterator.o: frmiterator.cpp parser.h
		g++ -c frmiterator.cpp ${CFLAGS}

tests: testparse
		@for i in `ls tests`; do echo "./testparse tests/$$i"; ./testparse tests/$$i >/dev/null || exit $$?; done
