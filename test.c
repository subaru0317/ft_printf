#include "libftprintf.h"
#include <stdio.h>
int main(void)
{
	
	int x,y;
	// printf("[%03.0x]\n",0);
	// ft_printf("[%03.0x]\n",0);
	// p
	// width, -
	// int p;
	printf("%p\n", NULL);
	ft_printf("%p\n", NULL);
	// x = printf("%20p\n", &p);
	// y = ft_printf("%20p\n", &p);
	// printf("x:%d, y:%d\n", x, y);
	// y = ft_printf("%-20p\n", &p);
	// y = ft_printf("%-20p\n", &p);
	// printf("x:%d, y:%d\n", x, y);
	// i, d
	// width, (prec, -) > 0, ' ' < +
	// int z = -3;
	// x = printf("%+0.3d\n", z);
	// y = ft_printf("%+0.3d\n", z);
	// x = printf("%10.0d\n", z);
	// y = ft_printf("%10.0d\n", z);
	// x = printf("%3.0d\n", 0);
	// y = ft_printf("%3.0d\n", 0);
	// x = printf("[%0 10.21i %- 1.29d]\n",2, INT_MIN);
	// y = ft_printf("[%0 10.21i %- 1.29d]\n",2, INT_MIN);
	// printf("x:%d, y:%d\n", x, y);

	// u
	// x = printf("[%0 10.21u %- 1.29u %.0d %10.0d]\n",2, UINT_MAX, 0, 0);
	// y = ft_printf("[%0 10.21u %- 1.29u %.0d %10.0d]\n",2, UINT_MAX, 0, 0);
	// printf("x:%d, y:%d\n", x, y);
	// c
	// width, -
	// x = printf("%11c\n", 'a');
	// y = ft_printf("%11c\n", 'a');
	// printf("x:%d, y:%d\n", x, y);
	// y = ft_printf("%-11c\n", 'a');
	// y = ft_printf("%-11c\n", 'a');
	// printf("x:%d, y:%d\n", x, y);

	// s
	x = printf("%-.s %20.10s %2.s\n", "abc", "def", "");
	y = ft_printf("%-.s %20.10s %2.s\n", "abc", "def", "");
	printf("x:%d, y:%d\n", x, y);

	// %

	// x, X
	// printf("x: [%1.0x]\n", 0);
	// ft_printf("x: [%1.0x]\n", 0);
}