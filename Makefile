
apc.out : main.o addition.o subtraction.o division.o multiplication.o  power.o Common.o
	gcc -o $@ $^

main.o : main.c apc.h
	gcc -c main.c -o main.o

addition.o : addition.c apc.h
	gcc -c $< -o $@

subtraction.o : subtraction.c apc.h
	gcc -c $< -o $@

multiplication.o : multiplication.c apc.h
	gcc -c $< -o $@

division.o : division.c apc.h
	gcc -c $< -o $@

clean :
	rm -f *.o apc.out