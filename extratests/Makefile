OLDCFLAGS:=${CFLAGS}
OLDLDFLAGS:=${LDFLAGS}

CFLAGS+=-std=gnu++11

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

.PHONY: clean all tests run

CFLAGS+=-I ..
LDFLAGS+=-L .. -l parser

all: tests run

tests: $(patsubst %.cpp,%.test,$(wildcard *.cpp))

%.test: %.o ../libparser.a
		${CXX} $< -o $@ ${LDFLAGS}

%.o: %.cpp ../parser.h
		${CXX} -c $< ${CFLAGS}

../libparser.a:
		CFLAGS="${OLDCFLAGS}" LDFLAGS="${OLDLDFLAGS}" make -C .. libparser.a

run: tests
		@for i in `ls *.test`; do echo "./$$i >/dev/null"; ./$$i >/dev/null || exit $$?; done

clean:
		rm -f *.o *.gcda *.gcno *.gcov core* *.test
