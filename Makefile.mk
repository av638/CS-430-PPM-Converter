all:	main.c
	gcc main.c -o pixmap

clean:
	rm -rf pixmap *~
