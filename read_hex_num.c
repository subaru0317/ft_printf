/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hex_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:54 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 17:14:52 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_put_prefix_fd(char type, int fd)
{
	if (type == 'x')
		ft_putstr_fd("0x", fd);
	else if (type == 'X')
		ft_putstr_fd("0X", fd);
}

static void	left_justified(int zeros, int spaces, char *hex_str)
{
	ft_putchar_fd_num('0', 1, zeros);
	ft_put_nbr(hex_str);
	ft_putchar_fd_num(' ', 1, spaces);
}

static void	right_justified(int zeros, int spaces, char *hex_str)
{
	ft_putchar_fd_num(' ', 1, spaces);
	ft_putchar_fd_num('0', 1, zeros);
	ft_put_nbr(hex_str);
}

static int	ft_put_hex_nbr(t_flag flags, t_field field,
							char *hex_str, unsigned int target)
{
	int	spaces;
	int	zeros;
	int	hex_len;

	hex_len = (int)ft_strlen(hex_str);
	spaces = ft_max(0, field.width - ft_max(field.prec, hex_len));
	zeros = ft_max(0, field.prec - hex_len);
	if (field.prec_flag && field.prec == 0 && target == 0)
	{
		ft_putchar_fd_num(' ', 1, zeros + spaces + (field.width != 0));
		return (zeros + spaces + (field.width != 0));
	}
	else if (flags.minus)
		left_justified(zeros, spaces, hex_str);
	else
	{
		if (flags.zero)
		{
			zeros += spaces;
			spaces = 0;
		}
		right_justified(zeros, spaces, hex_str);
	}
	return (zeros + spaces + ft_strlen(hex_str));
}

int	read_hex_num(va_list *ap, char type, t_flag flags, t_field field)
{
	unsigned int	target;
	char			*hex_str;
	int				hex_len;

	target = va_arg(*ap, unsigned int);
	hex_len = 0;
	if (field.prec_flag)
		flags.zero = 0;
	if (flags.sharp && target != 0)
	{
		ft_put_prefix_fd(type, 1);
		hex_len += 2;
	}
	hex_str = malloc(sizeof(char) * 100);
	if (!hex_str)
		return (-1);
	dec_nbr_to_hex_str(target, &hex_str);
	if (type == 'X')
		ft_str_toupper(&hex_str);
	hex_len += ft_put_hex_nbr(flags, field, hex_str, target);
	free(hex_str);
	return (hex_len);
}
