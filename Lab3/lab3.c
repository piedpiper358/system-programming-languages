#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* sqrt */
#define maxStrSize 128

int sum( const int * const array, size_t n);
int is_prime( unsigned long num );


int array[] = {1,2,3,4,5,6,7,8,9,10};

int main( int argc, char** argv ) {
	int isValidNumber = 0;
	unsigned long num=0L;
	
	int i;
	int count;
	int* dynamic_array=NULL;
	char* str;
	
	/* int* p=calloc(128, sizeof(int));
	int* r=p+128;
	
	void* sub = (void*)r-(void*)p; */
	
	printf("%c  %lu  %lu  %lu  %lu  %lu\n",2["abc"], 1L/* sizeof(void) */, sizeof(void*), sizeof(0), sizeof('x'), sizeof("hello"));
	
	printf("1. Sum of the static array elements = %i\n\n", sum(array, sizeof(array)/sizeof(array[0])));
	
	printf("2. Enter the number and we will check is it prime or not: ");
	
	do{
	isValidNumber = scanf("%lu", &num);
	}while(!isValidNumber);
	
	if(is_prime(num))
	{
		printf("\tNumber is prime\n\n");
	}
	else
	{
		printf("\tNumber isn't prime\n\n");
	}
	
	printf("3. Enter the number of elements in a dynamic array, and then the elements\n\t");
	
	
	scanf("%i", &count);
	if(count<0){
		printf("\tError!!\n");
		return 1;
	}
	dynamic_array=calloc(count, sizeof(int));
	str=calloc(maxStrSize, sizeof(char));
	
	for(i=0; i<count; i++)
	{
		printf("\t");
		/* scanf("%i", &dynamic_array[i]); */
		scanf("%s", str);
		dynamic_array[i]=strtoul(str, NULL, 10);
	}
	
	printf("\tSum of the dynamic array elements = %i\n", sum(dynamic_array, count));
	free(dynamic_array);
	return 0;

}

int sum( const int * const array, size_t count) {
	int total=0;
	size_t i;
	for (i=0; i<count ; i++)
	{
		total+=array[i];
	}
	return total;
	
}

int is_prime( unsigned long num ) {
	int i;
	
	if(num<=1)
	{
		return 0;
	}
	else
	{
		for(i=2; (double)i<=/* num/2 */ sqrt((double)num) ; i++)
		{
			if (num%i==0)
			{
				return 0;
			}
		}
		return 1;
	}
}




