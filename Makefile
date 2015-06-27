SRC_FILES = $(wildcard src/*.c)
CC_FLAGS = -Wall -Wextra -g -Iinclude/ -std=c99

all:
	@mkdir -p bin/
	${CC} ${CC_FLAGS} ${SRC_FILES} -o bin/gromp