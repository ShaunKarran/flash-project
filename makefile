
all:
	gcc -std=gnu99 ./test/test.c ./src/ml.c -I./include -o ./test/test
