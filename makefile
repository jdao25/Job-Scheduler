CC=g++


compile-main:
	@clear
	@$(CC) main.cpp -o Job_Scheduler && ./Job_Scheduler


save-output:
	@clear
	@$(CC) main.cpp -o Job_Scheduler && ./Job_Scheduler > Output.txt
