/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:39 by smihata           #+#    #+#             */
/*   Updated: 2023/05/06 15:09:44 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	stdout_according_to_type(va_list *ap, char type,
					t_flag flags, t_field field)
{
	if (!type)
		return (0);
	else if (type == 'c')
		return (read_char(ap, flags, field));
	else if (type == 's')
		return (read_string(ap, flags, field));
	else if (type == 'p')
		return (read_pointer(ap, flags, field));
	else if (type == 'd' || type == 'i')
		return (read_int(ap, flags, field));
	else if (type == 'u')
		return (read_uint(ap, flags, field));
	else if (type == 'x' || type == 'X')
		return (read_hex_num(ap, type, flags, field));
	else if (type == '%')
		return (read_percent(flags, field));
	else
		return (write(1, &type, 1));
}

static int	init_and_put_str(t_flag *flags, t_field *field, const char *fmt)
{
	int	len;

	flags->sharp = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->space = 0;
	flags->plus = 0;
	field->width = 0;
	field->prec_flag = 0;
	field->prec = 0;
	len = 0;
	while (*fmt && *fmt != '%')
	{
		ft_putchar_fd(*fmt++, 1);
		len++;
	}
	return (len);
}

static int	do_printf(va_list *ap, const char *fmt)
{
	int		len;
	int		tmp;
	t_flag	flags;
	t_field	field;

	len = 0;
	while (*fmt)
	{
		tmp = init_and_put_str(&flags, &field, fmt);
		if (tmp == -1)
			return (-1);
		fmt += tmp;
		len += tmp;
		if (!(*fmt))
			break ;
		fmt++;
		fmt += set_directive(ap, fmt, &flags, &field);
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
	int		len;

	va_start(ap, fmt);
	len = do_printf(&ap, fmt);
	va_end(ap);
	return (len);
}
