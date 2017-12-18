#include <stdio.h>
#include <stdlib.h>

void test1();
void test2();
void test3();

int main()
{
	test1();
	test2();
	test3();
	return 0;
}

void test1()
{
	int x = 2;
	int a = 1;
	int b = 3;
	printf("Testing between.s\n");
	int result1 = between(x, a, b);
	int result2 = between(a, b, x);
	if(result1 && !result2) printf("Success!\n");
	else printf("Failed\n");
}


void test2()
{
	int c = 44;
	int b = 20;
	int a = 12;
	int x = 7;
	printf("Testing poly.s\n");
	int result1 = poly(x, a, b, c);
	if(result1 == 772) printf("Success!\n");
	else printf("Failed\n");
}

void test3()
{
	int* arr = (int*)malloc(sizeof(int)*5);
	if(arr == NULL)
	{
		printf("Failed to allocate memory.");
		exit(1);
	}
	arr[0] = 20;
	arr[1] = 11;
	arr[2] = 44;
	arr[3] = 1000;
	arr[4] = 2;
	int result = dblit(arr, 5);

printf("Testing dblit.s\n");
	if(arr[0] == 40 && arr[1] == 22 && arr[2] == 88 && arr[3] == 2000 && arr[4] == 4)
	{
		printf("Success!\n");
	}else{
		printf("Failed\n");
	}

	free(arr);
}
