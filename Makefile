all:
	gcc ./src/8085assembler.c -o ./build/8085assembler.out
clean:
	rm ./build/8085assembler.out
