# -*- MakeFile -*-

all: mem-alloc

mem-alloc: mem-alloc.o mem-manage.o
	gcc mem-alloc.o mem-manage.o -o mem-alloc

mem-alloc.o: mem-alloc.c mem-manage/mem-manage.h
	gcc -c mem-alloc.c mem-alloc.o

mem-manage.o: mem-manage/mem-manage.c mem-manage/mem-manage.h
	gcc -c mem-manage/mem-manage.c mem-manage.o

clean:
	rm -fr *.o mem-alloc
clean-temp:
	rm -fr *.o