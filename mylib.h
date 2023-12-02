#ifndef MYLIB_H
#define MYLIB_H

struct mydata {
	char *msg;
	int number;
	long bignumber;
};

void myfunction(int number);
void print_struct(struct mydata *data);

#endif
