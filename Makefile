all:
	cc -o libmylib.so -shared -fPIC mylib.c
	cc -o mylib.so -shared -FPIC bindings.c -L . -l mylib
