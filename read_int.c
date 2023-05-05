/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:32:55 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:45:56 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	set_sign(t_flag *flags, int target)
{
	int	sign;

	sign = 0;
	if (target < 0)
	{
		sign = 1;
		flags->plus = 0;
		flags->space = 0;
	}
	else if (flags->plus)
	{
		sign = 1;
		flags->space = 0;
	}
	else if (flags->space)
		sign = 1;
	return (sign);
}

static int	set_spaces(int sign, t_field field, int target)
{
	int	spaces;

	if (field.width > field.prec)
		spaces = ft_max(0,
				field.width
				- sign
				- ft_max(field.prec, ft_plus_nbr_len(ft_abs(target))));
	else
		spaces = 0;
	return (spaces);
}

static void	left_justified(t_field field, t_flag flags, int target, int sign)
{
	int	spaces;
	int	zeros;

	spaces = set_spaces(sign, field, target);
	zeros = ft_max(0, field.prec - ft_plus_nbr_len(ft_abs(target)));
	if (target < 0)
		ft_putchar_fd('-', 1);
	else if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && target == 0))
		ft_putnbr_fd(ft_abs(target), 1);
	ft_putchar_fd_num(' ', 1, spaces);
}

static void	right_justified(t_field field, t_flag flags, int target, int sign)
{
	int	spaces;
	int	zeros;

	spaces = set_spaces(sign, field, target);
	zeros = ft_max(0, field.prec - ft_plus_nbr_len(ft_abs(target)));
	if (flags.zero)
	{
		zeros += spaces;
		spaces = 0;
	}
	ft_putchar_fd_num(' ', 1, spaces);
	if (target < 0)
		ft_putchar_fd('-', 1);
	else if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && target == 0))
		ft_putnbr_fd(ft_abs(target), 1);
}

int	read_int(va_list *ap, t_flag flags, t_field field)
{
	int	target;
	int	sign;
	int	int_len;
	int	spaces;
	int	zeros;

	target = va_arg(*ap, int);
	sign = set_sign(&flags, target);
	if (field.prec_flag)
		flags.zero = 0;
	int_len = ft_max(ft_max(field.width, field.prec + sign),
			ft_plus_nbr_len(ft_abs(target)) + sign);
	if (field.prec_flag && field.prec == 0 && target == 0)
	{
		spaces = set_spaces(sign, field, target) + (field.width != 0);
		zeros = ft_max(0, field.prec - ft_plus_nbr_len(ft_abs(target)));
		ft_putchar_fd_num(' ', 1, spaces + zeros);
		return (spaces + zeros);
	}
	else if (flags.minus)
		left_justified(field, flags, target, sign);
	else
		right_justified(field, flags, target, sign);
	return (int_len);
}
