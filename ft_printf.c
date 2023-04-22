/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:39 by smihata           #+#    #+#             */
/*   Updated: 2023/04/22 17:52:12 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

int	read_pointer(va_list *ap, flag_list flags, field_info field)
{
	unsigned long long	p;
	char		*c;
	size_t		len;

	p = va_arg(*ap, unsigned long long);
	c = malloc(sizeof(char) * 100);
	if (!c)
		return (-1);
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
	len = ft_strlen(c);
	free(c);
	return (ft_max(field.width, len + 2));
}

int	read_char(va_list *ap, flag_list flags, field_info field)
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
	return (ft_max(field.width, 1));
}

int	read_string(va_list *ap, flag_list flags, field_info field)
{
	char		*s;
	size_t		s_len;
	int			return_value;
	char		padding_char;
	long long	padding_num;

	s = va_arg(*ap , char*);
	if (!s)
		s = "(null)"; 
	s_len = ft_strlen(s);
	return_value = s_len;
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
	return (ft_max(field.width, return_value));
}

size_t read_int(va_list *ap, flag_list flags, field_info field)
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
	return (ft_max(ft_max(field.width, field.precision + (flags.plus || flags.space || negative)), ft_num_len(x) + (flags.plus || flags.space || negative)));
}

int	read_lower_hex_number(va_list *ap, flag_list flags, field_info field)
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
	if (!c)
		return (-1);
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
	len = ft_strlen(c);
	free(c);
	return (ft_max(ft_max(field.width, field.precision), len));
}

int	read_upper_hex_number(va_list *ap, flag_list flags, field_info field)
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
	if (!c)
		return (-1);
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
	len = ft_strlen(c);
	free(c);
	return (ft_max(ft_max(field.width, field.precision), len));
}

int read_percent(va_list *ap, flag_list flags, field_info field)
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
	return (ft_max(field.width, 1)); 
}

int read_unsigned_int(va_list *ap, flag_list flags, field_info field)
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
	return (ft_max(ft_max(field.width, field.precision), ft_num_len(x)));
}

int	stdout_according_to_type(va_list *ap, char type, flag_list flags, field_info field)
{
	if (type == 'c')
		return (read_char(ap, flags, field));
	else if (type == 's')
		return (read_string(ap, flags, field));
	else if (type == 'p')
		return (read_pointer(ap, flags, field));
	else if (type == 'd' || type == 'i')
		return (read_int(ap, flags, field));
	else if (type == 'u')
		return (read_unsigned_int(ap, flags, field));
	else if (type == 'x')
		return (read_lower_hex_number(ap, flags, field));
	else if (type == 'X')
		return (read_upper_hex_number(ap, flags, field));
	else if (type == '%')
		return (read_percent(ap, flags, field));
	else
		ft_putchar_fd(type, 1); // あってるか？存在しない場合はそのまま文字として出力？
	if (type)
		return (1);
	else
		return (0);
}

int	do_printf(va_list *ap, const char *fmt)
{
	size_t	len;
	int		tmp;

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
		tmp = stdout_according_to_type(ap, *fmt, flags, field);
		if (tmp == -1)
			return (-1);
		len += tmp;
		if (*fmt)
			fmt++;
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
// int main(void)
// {
//     printf("1:ret = %d\n", printf("[%010d]\n", -8473));
//     printf("2:ret = %d\n", printf("[%10d]\n", -8473));
//     printf("3:ret = %d\n", printf("[%.5d]\n", -8473));
//     printf("4:ret = %d\n", printf("[%01.1d]\n", -8473));
//     printf("5:ret = %d\n", printf("[%010.1d]\n", -8473));
//     printf("6:ret = %d\n", printf("[%01.50d]\n", -8473));
//     printf("7:ret = %d\n", printf("[%1.50d]\n", -8473));
//     printf("8:ret = %d\n", printf("[%0100.50d]\n", -8473));
//     printf("9:ret = %d\n", printf("[%010d]\n", 8473));
//     printf("10:ret = %d\n", printf("[%10d]\n", 8473));
//     printf("11:ret = %d\n", printf("[%.5d]\n", 8473)); // Error
//     printf("12:ret = %d\n", printf("[%01.1d]\n", 8473));
//     printf("13:ret = %d\n", printf("[%010.1d]\n", 8473));
//     printf("14:ret = %d\n", printf("[%01.50d]\n", 8473));
//     printf("15:ret = %d\n", printf("[%1.50d]\n", 8473));
//     printf("16:ret = %d\n", printf("[%0100.50d]\n", 8473));
// }
