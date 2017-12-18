#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define INIT_SIZE 4
#define EPSILON 0.01

#define FILE_ERROR 1

/*
    This lab requires you to write functions that manage
    and process double precision data vectors.  The includes,
    defines, Vector struct, function prototypes, skeleton
    functions and test code in main have been included to
    get you started.

    I suggest writing the functions in order
    of appearance below because some functions, either directly
    or indirectly depend on others.  You have to create a vector
    and insert elements before printing a vector.  The sum function
    can be used in avg, avg can be used in var and var in stdv.  The
    dbl_equals function should be used to compare doubles within a
    threshold to account for arithmetic precision errors on doubles.

    Make sure that you check that file open and memory allocation
    is successful before using the file or memory.  Points will be
    deducted if you code can crash in any way.  So be sure to
    consider and handle all possible threats that may crash your
    application.

    This code will be used in your final project to create static
    and dynamic libraries.

    Good luck!
*/


/*
    Struct for a vector of double.  It contains a pointer
    to a vector of double, an integer for allocated length
    of the vector and and integer for the count of double
    inserted.
*/
typedef struct{
    double *vector;
    int count;
    int length;
}Vector;


// Prototypes
Vector create_vector(int length);
Vector empty_vector();
int insert(Vector *vec, double dbl);
void print_vec(Vector vec);
void delete_vector(Vector *vec);
Vector copy(Vector vec);
Vector copy_range(Vector vec, int from, int to);
void clear_vector(Vector *vec);
void zeros(Vector *vec);
void fill(Vector *vec, double dbl);
Vector read_from_file(char *filename);
int write_to_file(Vector vec, char *filename);
Vector get_from_con();
void add_from_con(Vector *vec);
void swap(Vector *vec, int i, int j);
void sort(Vector *vec);
void reverse(Vector *vec);
int dbl_equals(double d1, double d2);
int search(Vector vec, double dbl);
double sum(Vector vec);
double avg(Vector vec);
double var(Vector vec);
double stdv(Vector vec);
Vector add(Vector v1, Vector v2);
Vector sub(Vector v1, Vector v2);
Vector mul(Vector v1, Vector v2);
Vector divv(Vector v1, Vector v2);
double dot(Vector v1, Vector v2);
int equals(Vector v1, Vector v2);


// Main
int main(){

    // Test create, insert and print
    printf("Test create, insert and print\n");
    Vector v1 = create_vector(2);
    insert(&v1, 1.0);
    insert(&v1, 2.0);
    insert(&v1, 3.0);
    insert(&v1, 4.0);
    insert(&v1, 5.0);
    print_vec(v1);
    printf("\n");

    // Test copy and copy range
    printf("Test copy and copy range\n");
    Vector v2 = copy(v1);
    print_vec(v2);
    Vector v3 = copy_range(v1, 1, 3);
    print_vec(v3);
    printf("\n");

    // Test zeros and fill
    printf("Test zeros and fill\n");
    zeros(&v3);
    print_vec(v3);
    fill(&v2, 1.0);
    print_vec(v2);
    printf("\n");

     // Test read and write
    printf("Test read and write\n");
    Vector v4 = read_from_file("array_in.txt");
    print_vec(v4);
    write_to_file(v1, "array_out.txt");
    printf("\n");
    // Test get from con and add from con
    Vector v5 = get_from_con();
    print_vec(v5);
    add_from_con(&v5);
    print_vec(v5);
    printf("\n");

    // Test swap, sort, reverse and search
    printf("Test swap, sort, reverse and search\n");
    swap(&v1, 0, 4);
    swap(&v1, 1, 3);
    print_vec(v1);
    sort(&v1);
    print_vec(v1);
    reverse(&v4);
    print_vec(v4);
    int i = search(v4, 6.0);
    printf("Found at %d\n\n", i);

    // Test sum, avg, var and stdv
    printf("Test sum, avg, var and stdv\n");
    printf("Sum = %f\n", sum(v4));
    printf("Avg = %f\n", avg(v4));
    printf("Var = %f\n", var(v4));
    printf("Stdv = %f\n\n", stdv(v4));

    // Test add, sub, mul, divv, dot and equals
    printf("Test add, sub, mul, divv, dot and equals\n");
    Vector v6 = add(v1, v4);
    print_vec(v6);
    Vector v7 = sub(v6, v4);
    print_vec(v7);
    Vector v8 = mul(v1, v4);
    print_vec(v8);
    Vector v9 = divv(v8, v4);
    print_vec(v9);
    double dbl = dot(v1, v4);
    printf("Dot = %f\n", dbl);
    i = equals(v1, v4);
    printf("Equals = %d\n", i);
    i = equals(v1, v1);
    printf("Equals = %d\n", i);


    // Free memory
    delete_vector(&v1);
    delete_vector(&v2);
    delete_vector(&v3);
    delete_vector(&v4);
   	delete_vector(&v5);
    delete_vector(&v6);
    delete_vector(&v7);
    delete_vector(&v8);
    delete_vector(&v9);

    return 0;
}

/*

    Single vector functions

*/

/*
    Function to create a vector of double.  It accepts the
    integer length of the vector to be created and returns
    a Vector struct containing the length of the allocated
    vector, the count (initialized to zero) of doubles
    inserted, and the allocated vector.
*/
Vector create_vector(int length){
	Vector vec;
	vec.vector = (double*) malloc((length)*sizeof(double));

	// memory was not allocated
	if(vec.vector == NULL){
		printf("ERROR: Memory did not allocate");
		vec.length = 0;
		vec.count = 0;
		return vec;
	}

	vec.count = 0;
	vec.length = length;
	return vec;
}


/*
    Create an empty vector with vector pointer set to NULL,
    length set to zero and count set to zero.  This is used
    when something fails during the creation of a Vector or
    other functions that return a Vector.
*/
Vector empty_vector(){
	Vector vec;
	vec.vector = NULL;
	vec.length = 0;
	vec.count = 0;
	return vec;
}


/*
    Inserts a double into a vector of double.  If the
    vector is full (i.e. count == length), the length of
    the vector should be doubled and the data from the old
    vector should be copied and the old vector freed.  If
    the length is zero, use the defined initial size.
    You can use malloc, which requires you to manually copy
    and free the old vector or try realloc.
*/
int insert(Vector *vec, double dbl){
	if(vec->length == 0)
	{
		vec->length = INIT_SIZE;
	}

	if(vec->count == vec->length) //vector is full
	{
		int length = vec->length;
		double *temp = (double*) malloc(sizeof(double)*length*2);
		if(temp == NULL) //memory didnt allocate
		{
			printf("ERROR: Memory did not allocate");
		}
		int i;
		for(i = 0; i < vec->length; i++)
		{
			temp[i] = vec->vector[i];
		}
		temp[i] = dbl;
		vec->count = (vec->count) + 1;

		double *temp2 = vec->vector;
		vec->vector = temp;
		vec->length = length*2;
		free(temp2);
	}
	else // vector isnt full and is initialized
	{
		int count = vec->count;
		vec->vector[count] = dbl;
		vec->count = count+1;
	}
}


/*
    Prints the count, length and elements of a vector to
    screen.
*/
void print_vec(Vector vec){

	int count = vec.count;
	int length = vec.length;

	printf("count: %d\n", count);
	printf("length: %d\n", length);

	int x;

	for(x = 0; x < count; x++)
	{
		double v = vec.vector[x];
		printf("vector[%d] = %f\n", x, v);
	}
}


/*
    Frees the memory allocated for the vector, and sets
    the count and length to zero.  Make sure not the free
    an empty (NULL) vector.
*/
void delete_vector(Vector *vec){
	vec->count = 0;
	vec->length = 0;

	if(vec->vector != NULL)
	{
		double* vector = vec->vector;
		free(vector);
	}
}


/*
    Creates a new vector with equal count, length and
    elements and returns the vector.
*/
Vector copy(Vector vec){
	Vector out;
	out = create_vector(vec.length);

	if(vec.vector == NULL)
	{
		out.vector = NULL;
	}
	else
	{
		int x;
		for(x = 0; x < vec.count; x++)
		{
			insert(&out, vec.vector[x]);
		}
	}
	return out;
}


/*
    Copies a range from a vector to a new vector and
    returns the new vector.  The count and length should
    be equal to the number of elements copied.  Remember
    to check for invalid operations:
        to less than from
        to less than zero
        from greater than or equal to count
*/
Vector copy_range(Vector vec, int from, int to){
	Vector out;
	if(to < from) // invalid
	{
		printf("Range error\n");
	}
	else if(to < 0 || from < 0) // invalid
	{
		printf("Range error\n");
	}
	else if(from >= vec.count) // invalid
	{
		printf("Range error\n");
	}
	else
	{
		int length = to - from + 1;
		out = create_vector(length);

		int x;
		for(x = from; x <= to; x++)
		{
			insert(&out, vec.vector[x]);
		}
	}
	return out;
}


/*
    Writes zeros to the elements of a vector and sets
    the count to zero.
*/
void clear_vector(Vector *vec){
	if(vec->vector != NULL)
	{
		vec->count = 0;
		int length = vec->length;
		int x;
		for(x = 0; x < length; x++)
		{
			vec->vector[x] = 0.0;
		}
	}
}


/*
    Writes zeros to a vector's elements.
*/
void zeros(Vector *vec){
	clear_vector(vec);
	vec->count = vec->length;
}


/*
    Fills a vector's elements with the value in dbl.
*/
void fill(Vector *vec, double dbl){
	int x;
	int length = vec->length;
	int count = 0;
	for(x = 0; x < length; x++)
	{
		vec->vector[x] = dbl;
		count++;
	}
	vec->count = count;
}


/*
    Reads a vector from a file with one double on
    each line in the file and returns the vector.
    Remember that scanf returns a -1 after reading
    the last element in a file.
*/
Vector read_from_file(char *filename){
	FILE *fp = fopen(filename, "r");

	if(fp == NULL)
	{
		printf("ERROR: File not opened\n");
		exit(FILE_ERROR);
	}

	Vector v;
	v = create_vector(2);
	double dbl;
	while(fscanf(fp,"%lf", &dbl) != -1){
		insert(&v, dbl);
	}

	fclose(fp);
	return v;
}


/*
    Writes a vector's elements to a file.
*/
int write_to_file(Vector vec, char *filename){
	FILE *fp = fopen(filename, "w");

	if(fp == NULL)
	{
		printf("ERROR: File not opened\n");
		exit(FILE_ERROR	);
	}

	int x;
	int count = vec.count;
	for(x = 0; x < count; x++)
	{
		fprintf(fp, "%lf\n", vec.vector[x]);
	}
	return 0;

}


/*
    Creates a new vector and gets the elements from
    keyboard input.  Accepts and inserts doubles into
    the vector until Enter is pressed (without any other
    chars).  Remember that scanf will not work unless a
    required data type is entered.  You should use gets
    and check for '\0', when Enter only is pressed.
*/
Vector get_from_con(){
	Vector v;
	v = create_vector(2);
	double dbl;
	char input[100];
	input[0] = 'a';
	while(input[0] != '\0')
	{
		gets(input, sizeof(input), stdin);
		dbl = atof(input);
		if(input[0] != '\0') insert(&v, dbl);
	}
	return v;
}


/*
    Adds elements to a vector and gets the elements from
    keyboard input.  Accepts and inserts doubles into
    the vector until Enter is pressed (without any other
    chars).  Remember that scanf will not work unless a
    required data type is entered.  You should use gets
    and check for '\0', when Enter only is pressed.
*/
void add_from_con(Vector *vec){
	double dbl;
	char input[100];
	input[0] = 'a';
	while(input[0] != '\0')
	{
		gets(input, sizeof(input), stdin);
		dbl = atof(input);
		if(input[0] != '\0') insert(vec, dbl);
	}
}


/*
    Swaps two elements in a vector.
*/
void swap(Vector *vec, int i, int j){
	double temp = vec->vector[i];
	vec->vector[i] = vec->vector[j];
	vec->vector[j] = temp;
}


/*
    Sorts a vector.  Can use selection or bubble
    sort.

*/
void sort(Vector *vec){
	// bubble sort
	int i, j;
	int count = vec->count;
	for(i = 0; i < count; i++ )
	{
		for(j = 0; j < count - 1; j++)
		{
			if(vec->vector[j] > vec->vector[j+1])
			{
				swap(vec, j, j+1);
			}
		}
	}

}


/*
    Reverses the elements of a vector.
*/
void reverse(Vector *vec){
	int count = vec->count;

	int left = 0;
	int right = count - 1;

	while(left < right)
	{
		double temp = vec->vector[left];
		vec->vector[left] = vec->vector[right];
		vec->vector[right] = temp;

		left++;
		right--;
	}
}


/*
    Checks if two doubles are equal given the defined
    EPSILON.  Remember that there should be a threshold
    for which two do floating point values are considered
    equal due to computation of arithmetic operations.
*/
int dbl_equals(double d1, double d2){
	double delta;
	if(d1 > d2) delta = d1-d2;
	else delta = d2-d1;

	return (EPSILON > delta);
}


/*
    Perform a binary search on a sorted vector and return
    the index of the element if found and -1 if not found.
*/
int search(Vector vec, double dbl){
	int left = 0;
	int right = vec.count - 1;
	int mid;

	while(left <= right)
	{
		mid = (left+right)/2;

		if(vec.vector[mid] > dbl) right = mid - 1;
		else if (vec.vector[mid] < dbl) left = mid + 1;
		else return mid;
	}
	return -1;

}


/*
    Calculate and return the sum of the elements in
    a vector.
*/
double sum(Vector vec){
	double s;
	int count = vec.count;
	int x;

	for(x = 0; x < count; x++)
	{
		s += vec.vector[x];
	}
	return s;
}


/*
    Calculate and return the average of the elements in
    a vector.
*/
double avg(Vector vec){
	double s = sum(vec);
	double count = (double)vec.count;
	return s/count;
}


/*
    Calculate and return the variance of the elements in
    a vector.
*/
double var(Vector vec){
	double mean = avg(vec);
	double out = 0;
	int x;
	for(x = 0; x < vec.count; x++)
	{
		out += (vec.vector[x] - mean) * (vec.vector[x] - mean);
	}
	return out/(vec.count);

}


/*
    Calculate and return the standard deviation of the
    elements in a vector.
*/
double stdv(Vector vec){
	return var(vec) / (vec.count);
}



/*

    Multiple vector functions

*/

/*
    Perform an element by element addition of two vectors,
    where v3[i] = v1[i] + v2[i] and return the resulting
    vector.
*/
Vector add(Vector v1, Vector v2){
	Vector v3;
	int count, count2;

	if(v1.count > v2.count)
	{
		count = v1.count;
		count2 = v2.count;
	}
	else
	{
		count2 = v1.count;
		count = v2.count;
	}

	v3 = create_vector(count);

	int x;
	for(x = 0; x < count2; x++)
	{
		int sum = v1.vector[x] + v2.vector[x];
		insert(&v3, sum);
	}
	if(count != count2)
	{
		while(x < count)
		{
			x++;
			if(count == v1.count)
			{
				insert(&v3, v1.vector[x]);
			}else{
				insert(&v3, v2.vector[x]);
			}
			x++;
		}
	}
	return v3;

}


/*
    Perform an element by element subtraction of one vector from
    another, where v3[i] = v1[i] - v2[i] and return the resulting
    vector.
*/
Vector sub(Vector v1, Vector v2){
	int count = v2.count;

	Vector negV2;
	negV2 = create_vector(count);

	int x;
	for(x = 0; x < count; x++)
	{
		double neg = v2.vector[x] * (-1.0);
		insert(&negV2, neg);
	}

	Vector v3;
	v3 = add(v1, negV2);
	return v3;
}


/*
    Perform an element by element multiplication of two vectors,
    where v3[i] = v1[i] * v2[i] and return the resulting
    vector.
*/
Vector mul(Vector v1, Vector v2){
	Vector v3;
	int count, count2;

	if(v1.count > v2.count)
	{
		count = v1.count;
		count2 = v2.count;
	}
	else
	{
		count2 = v1.count;
		count = v2.count;
	}

	v3 = create_vector(count);

	int x;
	for(x = 0; x < count2; x++)
	{
		int mult = v1.vector[x] * v2.vector[x];
		insert(&v3, mult);
	}
	if(count != count2)
	{
		while(x < count)
		{
			x++;
			if(count == v1.count)
			{
				insert(&v3, v1.vector[x]);
			}else{
				insert(&v3, v2.vector[x]);
			}
			x++;
		}
	}
	return v3;
}


/*
    Perform an element by element division of two vectors,
    where v3[i] = v1[i] / v2[i] and return the resulting
    vector.
*/
Vector divv(Vector v1, Vector v2){
	int count = v2.count;
	Vector inverseV2;
	inverseV2 = create_vector(count);

	int x;
	for(x = 0; x < count; x++)
	{
		double inverse = (1.0/v2.vector[x]);
		insert(&inverseV2, inverse); //o
	}

	Vector v3;
	v3 = mul(v1, inverseV2);
	return v3;
}


/*
    Perform the calculation of the dot product of two vectors,
    where dbl += v1[i] * v2[i] and return the resulting
    double.
*/
double dot(Vector v1, Vector v2){
	int count;

	if(v1.count > v2.count)
	{
		count = v2.count;
	}
	else
	{
		count = v1.count;
	}

	double dbl;
	int x;
	dbl = 0;
	for(x = 0; x < count; x++)
	{
		dbl += (v1.vector[x] * v2.vector[x]);
	}
	return dbl;
}


/*
    Perform an element by element comparison of two vectors.
    If for every i, v1[i] == v2[i], and the count is equal
    return 1, otherwise zero.
*/
int equals(Vector v1, Vector v2){
	int TRUE = 1, FALSE = 0;
	if(v1.count != v2.count) return FALSE;
	int x;
	for(x = 0; x < v1.count; x++)
	{
		if(v1.vector[x] != v2.vector[x]) return FALSE;
	}
	return TRUE;
}
