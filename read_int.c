/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:32:55 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 18:51:29 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	left_justified(size_t zeros, size_t spaces,
							t_field field, long long x)
{
	if (x < 0)
		ft_putchar_fd('-', 1);
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && x == 0))
		ft_putnbr_fd(ft_abs(x), 1);
	ft_putchar_fd_num(' ', 1, spaces);
}

static void	right_justified(size_t zeros, size_t spaces,
							t_field field, long long x)
{
	ft_putchar_fd_num(' ', 1, spaces);
	if (x < 0)
		ft_putchar_fd('-', 1);
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && x == 0))
		ft_putnbr_fd(ft_abs(x), 1);
}

static long long	set_spaces(size_t sign, t_field field, long long x)
{
	long long	spaces;

	if (field.width > field.prec)
		spaces = ft_max(0,
				field.width - ft_max(field.prec + sign, ft_num_len(x)));
	else
		spaces = ft_max(0,
				field.prec - ft_max(field.prec + sign, ft_num_len(x)));
	if (field.prec_flag && field.prec == 0 && x == 0 && field.width != 0)
		spaces++;
	return (spaces);
}

static long long	ft_set_x(char type, va_list *ap, t_flag *flags)
{
	long long	x;

	if (type == 'i' || type == 'd')
		x = va_arg(*ap, int);
	else
	{
		x = va_arg(*ap, unsigned int);
		flags->space = 0;
		flags->plus = 0;
	}
	return (x);
}

int	read_int(va_list *ap, char type, t_flag flags, t_field field)
{
	long long	spaces;
	long long	zeros;
	long long	x;
	size_t		sign;

	x = ft_set_x(type, ap, &flags);
	sign = (flags.plus || flags.space || x < 0);
	spaces = set_spaces(sign, field, x);
	zeros = ft_max(0, field.prec + sign - ft_num_len(x));
	if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
	if (flags.minus)
		left_justified(zeros, spaces, field, x);
	else
	{
		if (flags.zero && !field.prec)
		{
			zeros += spaces;
			spaces = 0;
		}
		right_justified(zeros, spaces, field, x);
	}
	return (ft_max(ft_max(field.width, field.prec + sign), ft_num_len(x)));
}
