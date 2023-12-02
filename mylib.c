#include <stdio.h>
#include "mylib.h"

void print_struct(struct mydata *data)
{
	printf("data: { %s %d %ld }\n", data->msg, data->number, data->bignumber);
}

void myfunction(int number)
{
	printf("your number is: %d\n", number);
}
