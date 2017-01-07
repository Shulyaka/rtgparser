include ../variables.mk

.PHONY: clean all tests run

CXXFLAGS+=-I ..
LDFLAGS+=-L .. -l parser

all: tests run

tests: $(patsubst %.cpp,%.test,$(wildcard *.cpp))

%.test: %.o ../libparser.a
		${CXX} $< -o $@ ${LDFLAGS}

%.o: %.cpp ../parser.h
		${CXX} -c $< ${CXXFLAGS} ${CPPFLAGS}

../libparser.a:
		CXXFLAGS="${OLDCXXFLAGS}" LDFLAGS="${OLDLDFLAGS}" make -C .. libparser.a

run: tests
		@for i in `ls *.test`; do echo "./$$i >/dev/null"; ./$$i >/dev/null || exit $$?; done

clean:
		rm -f *.o *.gcda *.gcno *.gcov core* *.test
