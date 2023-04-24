/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:29:23 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 19:09:14 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	set_flag(const char *fmt, t_flag *flags)
{
	size_t	length;

	length = 0;
	while (1)
	{
		if (*fmt == '#')
			flags->sharp = 1;
		else if (*fmt == '0')
			flags->zero = 1;
		else if (*fmt == '-')
			flags->minus = 1;
		else if (*fmt == '+')
			flags->plus = 1;
		else if (*fmt == ' ')
			flags->space = 1;
		else
			break ;
		fmt++;
		length++;
	}
	return (length);
}

size_t	set_min_field_width(va_list *ap, const char *fmt,
					t_flag *flags, t_field *field)
{
	size_t	i;
	int		x;

	i = 0;
	if (ft_isdigit(fmt[i]))
	{
		while (ft_isdigit(fmt[i]))
			field->width = field->width * 10 + (fmt[i++] - '0');
	}
	else if (fmt[i] == '*')
	{
		x = va_arg(*ap, int);
		if (x < 0)
		{
			x *= -1;
			flags->minus = 1;
		}
		field->width = x;
		i++;
	}
	return (i);
}

size_t	set_precision(va_list *ap, const char *fmt, t_field *field)
{
	size_t	i;
	int		x;

	i = 0;
	if (fmt[i] == '.')
	{
		field->prec_flag = 1;
		i++;
		if (ft_isdigit(fmt[i]))
		{
			while (ft_isdigit(fmt[i]))
				field->prec = field->prec * 10 + (fmt[i++] - '0');
		}
		else if (fmt[i] == '*')
		{
			x = va_arg(*ap, int);
			if (x < 0)
				field->prec_flag = 0;
			field->prec = x;
			i++;
		}
	}
	return (i);
}
