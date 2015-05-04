PYLIB = /usr/lib/python3.2
PYINC = /usr/include/python3.2mu

build: file_buffer.c
	gcc file_buffer.c -g -I$(PYINC) -fPIC -shared -L$(PYLIB) -o file_buffer.so
clean:
	rm -f file_buffer.so
