/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_literal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:41:14 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:36:57 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	left_justified(int target_len, char *target,
							char padding_char, int padding_num)
{
	while (target_len-- > 0)
		ft_putchar_fd(*target++, 1);
	ft_putchar_fd_num(padding_char, 1, padding_num);
}

static void	right_justified(int target_len, char *target,
							char padding_char, int padding_num)
{
	ft_putchar_fd_num(padding_char, 1, padding_num);
	while (target_len-- > 0)
		ft_putchar_fd(*target++, 1);
}

int	read_char(va_list *ap, t_flag flags, t_field field)
{
	char	target;
	int		spaces;

	spaces = field.width - 1;
	target = va_arg(*ap, int);
	if (flags.minus)
	{
		ft_putchar_fd(target, 1);
		ft_putchar_fd_num(' ', 1, spaces);
	}
	else
	{
		ft_putchar_fd_num(' ', 1, spaces);
		ft_putchar_fd(target, 1);
	}
	return (ft_max(field.width, 1));
}

int	read_string(va_list *ap, t_flag flags, t_field field)
{
	char		*target;
	int			target_len;
	char		padding_char;
	int			padding_num;

	target = va_arg(*ap, char *);
	if (!target)
		target = "(null)";
	target_len = (int)ft_strlen(target);
	if (field.prec_flag)
		target_len = ft_min(target_len, field.prec);
	padding_char = ' ';
	if (flags.zero && !flags.minus)
		padding_char = '0';
	padding_num = field.width - target_len;
	if (flags.minus)
		left_justified(target_len, target, padding_char, padding_num);
	else
		right_justified(target_len, target, padding_char, padding_num);
	return (ft_max(field.width, target_len));
}

int	read_percent(t_flag flags, t_field field)
{
	int	padding_num;

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
