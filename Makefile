all: reader writer

reader: reader.c
	gcc -Wall -g -o $@ $+

writer: writer.c
	gcc -Wall -g -o $@ $+

clean:
	rm -f a.out reader writer
