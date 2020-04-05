CC=g++

compile:
	@reset
	@$(CC) main.cpp -o main && ./main
