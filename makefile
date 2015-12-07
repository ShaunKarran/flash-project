
all:
	gcc -std=gnu99 ./test/matlib_test.c ./src/ml.c -I./include -o ./test/matlib_test
