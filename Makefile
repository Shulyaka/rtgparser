ifeq ($(COVERAGE),Y)
	CFLAGS+=--coverage
	LDFLAGS+=--coverage
	DEBUG=Y
endif

ifeq ($(DEBUG),Y)
	CFLAGS+=-ggdb -O0 -Wall -DDEBUG
else
	CFLAGS+=-Wall
endif

.PHONY: clean all tests extratests

all: libparser.a tests

clean:
		rm -f *.o *.gcda *.gcno *.gcov libparser.a testparse core* imessage* omessage*
		make -C extratests clean

testparse: libparser.a testparse.o
		${CXX} testparse.o -L . -l parser -o testparse ${LDFLAGS}

libparser.a: field.o fldformat.o parser.o builder.o frmiterator.o
		ar rcs libparser.a field.o fldformat.o parser.o builder.o frmiterator.o

%.o: %.cpp parser.h
		${CXX} -c $< ${CFLAGS}

tests: testparse
		@for i in `ls tests`; do echo "./testparse tests/$$i >/dev/null"; ./testparse tests/$$i >/dev/null || exit $$?; done

extratests: tests
		make -C extratests
