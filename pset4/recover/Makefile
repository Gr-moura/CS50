recover: recover.c
	clang -o recover recover.c -I/usr/local/include -L/usr/local/lib -lcs50

run: recover
	./recover card.raw

clean:
	rm -f *.jpg recover