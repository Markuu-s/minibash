files = main.c lib/*.h src/*.c
pathCompile = runningProgram

all:
	gcc $(files) -o $(pathCompile)/run 
#  gcc $(files) -fsanitize=address -o $(pathCompile)/san 
	gcc -g $(files) -o $(pathCompile)/debug
run:
	./$(pathCompile)/run
debug:
	gdb $(pathCompile)/debug
san:
	./$(pathCompile)/san
clean:
	rm $(pathCompile)/run
	rm $(pathCompile)/debug
	rm $(pathCompile)/san
	rm include/*.gch