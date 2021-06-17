all:
	gcc main.c -o executable/run 
	gcc -g main.c -o executable/debug
run:
	./executable/run
debug:
	gdb executable/debug
clean:
	rm executable/run
	rm executable/debug