OLDCXXFLAGS:=${CXXFLAGS}
OLDLDFLAGS:=${LDFLAGS}

CXXFLAGS+=-std=gnu++14

ifeq ($(COVERAGE),Y)
	CXXFLAGS+=--coverage
	LDFLAGS+=--coverage
	DEBUG=Y
endif

ifeq ($(DEBUG),Y)
	CXXFLAGS+=-ggdb -O0 -Wall -DDEBUG
else
	CXXFLAGS+=-Wall
endif
