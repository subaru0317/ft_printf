/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_literal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:41:14 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 17:14:38 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	left_justified(size_t s_len, char *s,
							char padding_char, long long padding_num)
{
	while (s_len-- > 0)
		ft_putchar_fd(*s++, 1);
	ft_putchar_fd_num(padding_char, 1, padding_num);
}

static void	right_justified(size_t s_len, char *s,
							char padding_char, long long padding_num)
{
	ft_putchar_fd_num(padding_char, 1, padding_num);
	while (s_len-- > 0)
		ft_putchar_fd(*s++, 1);
}

int	read_char(va_list *ap, t_flag flags, t_field field)
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

int	read_string(va_list *ap, t_flag flags, t_field field)
{
	char		*s;
	size_t		s_len;
	char		padding_char;
	long long	padding_num;

	s = va_arg(*ap, char *);
	if (!s)
		s = "(null)";
	s_len = ft_strlen(s);
	if (field.prec_flag)
		s_len = ft_min(s_len, field.prec);
	padding_char = ' ';
	if (flags.zero && !flags.minus)
		padding_char = '0';
	padding_num = field.width - s_len;
	if (flags.minus)
		left_justified(s_len, s, padding_char, padding_num);
	else
		right_justified(s_len, s, padding_char, padding_num);
	return (ft_max(field.width, s_len));
}

int	read_percent(t_flag flags, t_field field)
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
