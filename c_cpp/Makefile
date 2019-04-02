.PHONY: all clean

CFLAGS+=
LDFLAGS+=-lm     # link to math library

TARGET=train test

all: $(TARGET)
# type make/make all to compile test_hmm

train: train.c hmm.h
	gcc -O3 -o train train.c

test: test.c hmm.h
	gcc -O3 -o test test.c

clean:
	$(RM) $(TARGET)   # type make clean to remove the compiled file
