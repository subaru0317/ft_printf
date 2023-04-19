/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:39 by smihata           #+#    #+#             */
/*   Updated: 2023/04/19 18:32:12 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

void	ft_putchar_fd_num(char c, int fd, long long num)
{
	size_t	i;

	if (num > 0)
	{
		i = 0;
		while (i < num)
		{
			write(fd, &c, 1);
			i++;
		}
	}
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	return (c);
}

void ft_str_toupper(char **c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(c[0]);
	while (i < len)
	{
		c[0][i] = ft_toupper(c[0][i]);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

size_t	ft_min(long long x, long long y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

size_t	ft_max(long long x, long long y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

static unsigned long long ft_abs(long long n)
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


static size_t	ft_num_len(long long n)
{
	size_t			len;
	unsigned int	plus_n;

	len = 0;
	if (n < 0)
	{
		plus_n = n * -1;
		len++;
	}
	else
		plus_n = n;
	while (1)
	{
		len++;
		plus_n /= 10;
		if (plus_n == 0)
			break ;
	}
	return (len);
}

size_t	set_flag(const char *fmt, flag_list *flags)
{
	size_t	length;

	length = 0;
	while (1)
	{
		if (*fmt == '#') // o->0, x->0x, X->0X をつける
			flags->sharp = 1;
		else if (*fmt == '0') // 左側　0埋め
			flags->zero = 1;
		else if (*fmt == '-') // 左揃え
			flags->minus = 1;
		else if (*fmt == '+') // 正の場合に'+'を配置
			flags->plus = 1;
		else if (*fmt == ' ') // 正の場合に' 'を配置
			flags->space = 1;
		else
			break ;
		fmt++;
		length++;
	}
	return (length);
}

size_t	set_min_field_width(va_list *ap, const char *fmt,  flag_list *flags, field_info *field)
{
	size_t	length;
	int		x;

	length = 0;
	if (ft_isdigit(*fmt))
	{
		while (ft_isdigit(*fmt))
		{
			field->width = field->width * 10 + (*fmt - '0');
			fmt++;
			length++;
		}
	}
	else if (*fmt == '*')
	{
		x = va_arg(*ap, int);
		if (x < 0)
		{
			x *= -1;
			flags->minus = 1;
		}
		field->width = x;
		fmt++;
		length++;
	}
	return (length);
}

size_t	set_precision(va_list *ap, const char *fmt, field_info *field)
{
	size_t	length;
	int		x;

	length = 0;
	if (*fmt == '.')
	{
		field->precision_flag = 1;
		fmt++;
		length++;
		if (ft_isdigit(*fmt))
		{
			while (ft_isdigit(*fmt))
			{
				field->precision = field->precision * 10 + (*fmt - '0');
				fmt++;
				length++;
			}
		}
		else if (*fmt == '*')
		{
			x = va_arg(*ap, int);
			if (x < 0)
				field->precision_flag = 0;
			field->precision = x;
			fmt++;
			length++;
		}
	}
	return (length);
}

size_t	dec_to_hex_return_hex_len(unsigned long long dec, char **hex)
{
	unsigned long long	tmp;
	size_t				len;

	len = 0;
	while (1)
	{
		tmp = dec % 16;
		dec /= 16;
		if (0 <= tmp && tmp <= 9)
			tmp += '0';
		else if (10 <= tmp && tmp <= 15)
			tmp += 87;
		else
		{
			hex[0][len] = '\0';
			break ;
		}
		hex[0][len++] = tmp;
		if (dec == 0)
		{
			hex[0][len] = '\0';
			break ;
		}
	}
	return (len);
}

void	read_pointer(va_list *ap, flag_list flags, field_info field)
{
	unsigned long long	p;
	char		*c;
	size_t		len;

	p = va_arg(*ap, unsigned long long);
	c = malloc(sizeof(char) * 100);
	len = dec_to_hex_return_hex_len(p, &c);
	c[len] = '\0';
	if (flags.minus)
	{
		ft_putstr_fd("0x", 1);
		while (len--)
			ft_putchar_fd(c[len], 1);
		ft_putchar_fd_num(' ', 1, field.width - ft_strlen(c) - 2);
	}
	else
	{
		ft_putchar_fd_num(' ', 1, field.width - ft_strlen(c) - 2);
		ft_putstr_fd("0x", 1);
		while (len--)
			ft_putchar_fd(c[len], 1);
	}
	free(c);
}

void	read_char(va_list *ap, flag_list flags, field_info field)
{
	char		c;
	long long	space_num;

	space_num = field.width - 1;
	c = va_arg(*ap, int);
	if (flags.minus)
	{
		ft_putchar_fd(c, 1);
		ft_putchar_fd_num(' ', 1, space_num);
	}
	else
	{
		ft_putchar_fd_num(' ', 1, space_num);
		ft_putchar_fd(c, 1);
	}
}

void	read_string(va_list *ap, flag_list flags, field_info field)
{
	char		*s;
	size_t		s_len;
	char		padding_char;
	long long	padding_num;

	s = va_arg(*ap , char*);
	if (!s)
		s = "(null)"; 
	s_len = ft_strlen(s);
	if (field.precision_flag)
		s_len = ft_min(s_len, field.precision);
	padding_char = ' ';
	if (flags.zero && !flags.minus)
		padding_char = '0';
	padding_num = field.width - s_len;
	if (flags.minus)
	{
		while (s_len-- > 0)
			ft_putchar_fd(*s++, 1);
		ft_putchar_fd_num(padding_char, 1, padding_num);
	}
	else
	{
		ft_putchar_fd_num(padding_char, 1, padding_num);
		while (s_len-- > 0)
			ft_putchar_fd(*s++, 1);
	}
}

void read_int(va_list *ap, flag_list flags, field_info field)
{
	long long	space_num;
	long long	zero_num;
	long long	x; // INT_MINに対応する為にlonglong
	size_t		negative;

	x = va_arg(*ap, int);
	negative = 0;
	if (x < 0)
	{
		negative = 1;
		x = -x;
	}
	else if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
	if (field.width > field.precision)
		space_num = ft_max(0, field.width - (flags.plus || flags.space || negative) - ft_max(field.precision, ft_num_len(x)));
	else
		space_num = ft_max(0, field.precision - ft_max(field.precision, ft_num_len(x)));
	zero_num = ft_max(0, field.precision - ft_num_len(x));
	if (field.precision_flag && field.precision == 0 && x == 0 && field.width != 0)
		space_num++;
	if (flags.minus)
	{
		if (negative)
			ft_putchar_fd('-', 1);
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			ft_putnbr_fd(x, 1);
		ft_putchar_fd_num(' ', 1, space_num);
	}
	else
	{
		if (flags.zero && !field.precision)
			zero_num += space_num;
		else
			ft_putchar_fd_num(' ', 1, space_num);
		if (negative)
			ft_putchar_fd('-', 1);
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			ft_putnbr_fd(x, 1);
	}
}

void	read_lower_hex_number(va_list *ap, flag_list flags, field_info field)
{
	unsigned int	x;
	char			*c;
	size_t			len;
	long long		space_num;
	long long		zero_num;

	x = va_arg(*ap, unsigned int);
	if (flags.sharp && x != 0)
		ft_putstr_fd("0x", 1);
	c = malloc(sizeof(char) * 100);
	len = dec_to_hex_return_hex_len(x, &c);
	c[len] = '\0';
	space_num = ft_max(0, field.width - ft_max(field.precision, len));
	zero_num = ft_max(0, field.precision - len);
	if (field.precision_flag && field.precision == 0 && x == 0 && field.width != 0)
		space_num++;
	if (flags.minus)
	{
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			while (len--)
				ft_putchar_fd(c[len], 1);
		ft_putchar_fd_num(' ', 1, space_num);
	}
	else
	{
		if (flags.zero && !field.precision)
			zero_num += space_num;
		else
			ft_putchar_fd_num(' ', 1, space_num);
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			while (len--)
				ft_putchar_fd(c[len], 1);
	}
	free(c);
}

void	read_upper_hex_number(va_list *ap, flag_list flags, field_info field)
{
	unsigned int	x;
	char			*c;
	size_t			len;
	long long		space_num;
	long long		zero_num;

	x = va_arg(*ap, unsigned int);
	if (flags.sharp && x != 0)
		ft_putstr_fd("0X", 1);
	c = malloc(sizeof(char) * 100);
	len = dec_to_hex_return_hex_len(x, &c);
	ft_str_toupper(&c);
	c[len] = '\0';
	space_num = ft_max(0, field.width - ft_max(field.precision, len));
	zero_num = ft_max(0, field.precision - len);
	if (field.precision_flag && field.precision == 0 && x == 0 && field.width != 0)
		space_num++;
	if (flags.minus)
	{
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			while (len--)
				ft_putchar_fd(c[len], 1);
		ft_putchar_fd_num(' ', 1, space_num);
	}
	else
	{
		if (flags.zero && !field.precision)
			zero_num += space_num;
		else
			ft_putchar_fd_num(' ', 1, space_num);
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			while (len--)
				ft_putchar_fd(c[len], 1);
	}
	free(c);
}

void	read_percent(va_list *ap, flag_list flags, field_info field)
{
	long long	padding_num;

	padding_num = field.width - 1;
	if (flags.minus)
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd_num(' ', 1, padding_num);
	}
	else if (flags.zero)
	{
		ft_putchar_fd_num('0', 1, padding_num);
		ft_putchar_fd('%', 1);
	}
	else
	{
		ft_putchar_fd_num(' ', 1, padding_num);
		ft_putchar_fd('%', 1);
	}
}

void read_unsigned_int(va_list *ap, flag_list flags, field_info field)
{
	long long		space_num;
	long long		zero_num;
	unsigned int	x;

	x = va_arg(*ap, unsigned int);
	if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
	if (field.width > field.precision)
		space_num = ft_max(0, field.width - (flags.plus || flags.space) - ft_max(field.precision, ft_num_len(x)));
	else
		space_num = ft_max(0, field.precision - ft_max(field.precision, ft_num_len(x)));
	zero_num = ft_max(0, field.precision - ft_num_len(x));
	if (field.precision_flag && field.precision == 0 && x == 0 && field.width != 0)
		space_num++;
	if (flags.minus)
	{
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			ft_putnbr_fd(x, 1);
		ft_putchar_fd_num(' ', 1, space_num);
	}
	else
	{
		if (flags.zero && !field.precision)
			zero_num += space_num;
		else
			ft_putchar_fd_num(' ', 1, space_num);
		ft_putchar_fd_num('0', 1, zero_num);
		if (!(field.precision_flag && field.precision == 0 && x == 0))
			ft_putnbr_fd(x, 1);
	}
}

size_t	stdout_according_to_type(va_list *ap, char type, flag_list flags, field_info field)
{
	if (type == 'c')
		read_char(ap, flags, field);
	else if (type == 's')
		read_string(ap, flags, field);
	else if (type == 'p')
		read_pointer(ap, flags, field);
	else if (type == 'd' || type == 'i')
		read_int(ap, flags, field);
	else if (type == 'u')
		read_unsigned_int(ap, flags, field);
	else if (type == 'x')
		read_lower_hex_number(ap, flags, field);
	else if (type == 'X')
		read_upper_hex_number(ap, flags, field);
	else if (type == '%')
		read_percent(ap, flags, field);
	else
		ft_putchar_fd(type, 1); // あってるか？存在しない場合はそのまま文字として出力？
}

size_t	do_printf(va_list *ap, const char *fmt)
{
	size_t	len;

	len = 0;
	while (*fmt)
	{
		flag_list	flags = {0, 0, 0, 0, 0}; // 横着してここに宣言持ってきた。
		field_info	field = {0, 0, 0};
		while (*fmt && *fmt != '%')
		{
			ft_putchar_fd(*fmt, 1);
			fmt++;
			len++;
		}
		if (!(*fmt))
			break ;
		fmt++;
		fmt += set_flag(fmt, &flags);
		fmt += set_min_field_width(ap, fmt, &flags, &field);
		fmt += set_precision(ap, fmt, &field);
		len += type_length(*fmt, flags, field); // 未実装
		fmt += stdout_according_to_type(ap, *fmt, flags, field);
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list ap;
	size_t	len;

	va_start(ap, fmt);
	len = do_printf(&ap, fmt);
	va_end(ap);
	return (len);
}

// #include <stdio.h>
// #include <limits.h>
// int main(void)
// {
// 	ft_printf("%.*s", -3, "hello");

// }