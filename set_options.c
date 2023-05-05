/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:29:23 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:39:45 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	set_flag(const char *fmt, t_flag *flags)
{
	int	len;

	len = 0;
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
		len++;
	}
	return (len);
}

int	set_min_field_width(va_list *ap, const char *fmt,
					t_flag *flags, t_field *field)
{
	int	i;
	int	target;

	i = 0;
	if (ft_isdigit(fmt[i]))
	{
		while (ft_isdigit((int)fmt[i]))
			field->width = field->width * 10 + (fmt[i++] - '0');
	}
	else if (fmt[i] == '*')
	{
		target = va_arg(*ap, int);
		if (target < 0)
		{
			target *= -1;
			flags->minus = 1;
		}
		field->width = target;
		i++;
	}
	return (i);
}

int	set_precision(va_list *ap, const char *fmt, t_field *field)
{
	int	i;
	int	target;

	i = 0;
	if (fmt[i] == '.')
	{
		field->prec_flag = 1;
		i++;
		if (ft_isdigit((int)fmt[i]))
		{
			while (ft_isdigit((int)fmt[i]))
				field->prec = field->prec * 10 + (fmt[i++] - '0');
		}
		else if (fmt[i] == '*')
		{
			target = va_arg(*ap, int);
			if (target < 0)
				field->prec_flag = 0;
			field->prec = target;
			i++;
		}
	}
	return (i);
}

int	set_directive(va_list *ap, const char *fmt,
						t_flag *flags, t_field *field)
{
	int	directive_strlen;
	int	tmp;

	directive_strlen = 0;
	tmp = set_flag(fmt, flags);
	fmt += tmp;
	directive_strlen += tmp;
	tmp = set_min_field_width(ap, fmt, flags, field);
	fmt += tmp;
	directive_strlen += tmp;
	tmp = set_precision(ap, fmt, field);
	fmt += tmp;
	directive_strlen += tmp;
	return (directive_strlen);
}
