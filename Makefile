
APP  := test
SRCS := mcp3008.c test.c
OBJS := $(SRCS:.c=.o)

LDFLAGS  := -L../io_spa
LDLIBS   := -lio_spa
CPPFLAGS := -I../io_spa/include -D PLATFORM_LINUX

.PHONY: all app clean

all: ${APP}

${APP}: ${OBJS}

clean:
	rm -f ${APP}
	rm -f ${OBJS}

