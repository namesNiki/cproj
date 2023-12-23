none:
	gcc src/*.c -o cproj
install:
	gcc src/*.c -o cproj
	cp cproj /usr/local/bin/
	
