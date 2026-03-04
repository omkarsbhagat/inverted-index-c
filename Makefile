var := $(patsubst %.c,%.o,$(wildcard *.c))

inverted.exe: $(var)
	gcc -o inverted.exe $(var)

clean:
	rm *.o *.exe
