testfile := build/testfile.bin
all: build/zad1_lib build/zad1_sys build/zad2 build/zad3 build/zad4

clean:
	rm -f build/*

build/zad1_lib:
	$(CC) $(CFLAGS) src/zad1_lib.c -o build/zad1_lib

build/zad1_sys:
	$(CC) $(CFLAGS) src/zad1_sys.c -o build/zad1_sys

build/zad2:
	$(CC) $(CFLAGS) src/zad2.c -o build/zad2

build/zad3:
	$(CC) $(CFLAGS) src/zad3.c -o build/zad3

build/zad4:
	$(CC) $(CFLAGS) src/zad4.c -o build/zad4

$(testfile):
	dd if=/dev/urandom of=$(testfile) count=1M 

run1_lib: build/zad1_sys $(testfile)
	build/zad1_lib a b $(testfile) tmp

run1_sys: build/zad1_sys $(testfile)
	build/zad1_sys a b $(testfile) tmp

run2: build/zad2
	build/zad2 Makefile build/rev_Makefile

run3: build/zad3
	build/zad3

run4: build/zad4 
	build/zad4 .

runall: run1_lib run1_sys run2 run3 run4