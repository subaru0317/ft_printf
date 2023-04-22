#include <unistd.h>
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

unsigned long long ft_abs(long long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}


void	ft_putnbr_fd(long long n, int fd)
{
	unsigned long long	plus_n;
	char				c[20];
	size_t				len;

	if (n < 0)
		ft_putchar_fd('-', fd);
	plus_n = ft_abs(n);
	len = 0;
	while (1)
	{
		c[len++] = plus_n % 10 + '0';
		plus_n /= 10;
		if (plus_n == 0)
			break ;
	}
	while (len--)
		ft_putchar_fd(c[len], fd);
}

int main(void)
{
	unsigned int x = -8000;
	ft_putnbr_fd(x, 1);
}