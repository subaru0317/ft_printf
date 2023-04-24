/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:39 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 18:07:24 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	stdout_according_to_type(va_list *ap, char type,
					t_flag flags, t_field field)
{
	if (type == 'c')
		return (read_char(ap, flags, field));
	else if (type == 's')
		return (read_string(ap, flags, field));
	else if (type == 'p')
		return (read_pointer(ap, flags, field));
	else if (type == 'd' || type == 'i' || type == 'u')
		return (read_int(ap, type, flags, field));
	else if (type == 'x' || type == 'X')
		return (read_hex_num(ap, type, flags, field));
	else if (type == '%')
		return (read_percent(flags, field));
	else
		ft_putchar_fd(type, 1);
	if (type)
		return (1);
	else
		return (0);
}

static size_t	init_and_put_str(t_flag *flags, t_field *field, const char *fmt)
{
	size_t	x;

	flags->sharp = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->space = 0;
	flags->plus = 0;
	field->width = 0;
	field->prec_flag = 0;
	field->prec = 0;
	x = 0;
	while (*fmt && *fmt != '%')
	{
		ft_putchar_fd(*fmt++, 1);
		x++;
	}
	return (x);
}

static int	do_printf(va_list *ap, const char *fmt)
{
	size_t	len;
	int		tmp;
	t_flag	flags;
	t_field	field;

	len = 0;
	while (*fmt)
	{
		tmp = init_and_put_str(&flags, &field, fmt);
		fmt += tmp;
		len += tmp;
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
	va_list	ap;
	size_t	len;

	va_start(ap, fmt);
	len = do_printf(&ap, fmt);
	va_end(ap);
	return (len);
}
