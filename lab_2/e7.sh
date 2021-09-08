find . -name '*.c' | while read line
do
	gcc $line
	./a.out
	rm a.out
done

echo "Finished compiling and execution of all C files in current directory."