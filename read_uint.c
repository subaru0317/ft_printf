/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:23:56 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 17:26:16 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_num_len(unsigned int n)
{
	int	len;

	len = 0;
	while (1)
	{
		len++;
		n /= 10;
		if (n == 0)
			break ;
	}
	return (len);
}

static void	left_justified(int zeros, int spaces,
							t_field field, unsigned int target)
{
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && target == 0))
		ft_putnbr_fd(target, 1);
	ft_putchar_fd_num(' ', 1, spaces);
}

static void	right_justified(int zeros, int spaces,
							t_field field, unsigned int target)
{
	ft_putchar_fd_num(' ', 1, spaces);
	ft_putchar_fd_num('0', 1, zeros);
	if (!(field.prec_flag && field.prec == 0 && target == 0))
		ft_putnbr_fd(target, 1);
}

static void	set_spaces_and_zeros(t_field field, unsigned int target,
						int *spaces, int *zeros)
{
	if (field.width > field.prec)
		*spaces = ft_max(0,
				field.width - ft_max(field.prec, ft_num_len(target)));
	else
		*spaces = 0;
	if (field.prec_flag && field.prec == 0 && target == 0 && field.width != 0)
		*spaces += 1;
	*zeros = ft_max(0, field.prec - ft_num_len(target));
}

int	read_uint(va_list *ap, t_flag flags, t_field field)
{
	unsigned int	target;
	int				spaces;
	int				zeros;

	target = va_arg(*ap, unsigned int);
	if (field.prec_flag)
		flags.zero = 0;
	set_spaces_and_zeros(field, target, &spaces, &zeros);
	if (field.prec_flag && field.prec == 0 && target == 0)
	{
		ft_putchar_fd_num(' ', 1, spaces + zeros);
		return (spaces + zeros);
	}
	else if (flags.minus)
		left_justified(zeros, spaces, field, target);
	else
	{
		if (flags.zero)
		{
			zeros += spaces;
			spaces = 0;
		}
		right_justified(zeros, spaces, field, target);
	}
	return (ft_max(ft_max(field.width, field.prec), ft_num_len(target)));
}
