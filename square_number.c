#include <stdio.h>

/**
 * square_number - Calculates the square of a number.
 * @num: The number to be squared.
 *
 * Return: The square of the input number.
 */
int square_number(int num)
{
	int result;

	result = num * num;
	return (result);
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	int input = 5;
	int squared_result;

	squared_result = square_number(input);
	printf("The square of %d is %d\n", input, squared_result);

	return (0);
}
