/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hex_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:54 by smihata           #+#    #+#             */
/*   Updated: 2023/05/06 18:48:15 by smihata          ###   ########.fr       */
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

static int	left_justified(t_flag flags, t_field field,
						char *hex_str, char type)
{
	int	hexnbr_len;
	int	spaces;
	int	zeros;

	hexnbr_len = (int)ft_strlen(hex_str);
	if (flags.sharp && !(hex_str[0] == '0' && hexnbr_len == 1))
		field.width -= 2;
	spaces = ft_max(0, field.width - ft_max(field.prec, hexnbr_len));
	zeros = ft_max(0, field.prec - hexnbr_len);
	if (flags.sharp && !(hex_str[0] == '0' && hexnbr_len == 1))
		ft_put_prefix_fd(type, 1);
	ft_putchar_fd_num('0', 1, zeros);
	ft_put_nbr(hex_str);
	ft_putchar_fd_num(' ', 1, spaces);
	return (zeros + spaces + hexnbr_len);
}

static int	right_justified(t_flag flags, t_field field,
						char *hex_str, char type)
{
	int	hexnbr_len;
	int	spaces;
	int	zeros;

	hexnbr_len = (int)ft_strlen(hex_str);
	if (flags.sharp && !(hex_str[0] == '0' && hexnbr_len == 1))
		field.width -= 2;
	spaces = ft_max(0, field.width - ft_max(field.prec, hexnbr_len));
	zeros = ft_max(0, field.prec - hexnbr_len);
	if (flags.zero)
	{
		zeros += spaces;
		spaces = 0;
	}
	ft_putchar_fd_num(' ', 1, spaces);
	if (flags.sharp && !(hex_str[0] == '0' && hexnbr_len == 1))
		ft_put_prefix_fd(type, 1);
	ft_putchar_fd_num('0', 1, zeros);
	ft_put_nbr(hex_str);
	return (zeros + spaces + hexnbr_len);
}

static int	ft_put_hex_nbr(t_flag flags, t_field field,
							char *hex_str, char type)
{
	int	hexnbr_len;
	int	hex_len;
	int	spaces;
	int	zeros;

	hexnbr_len = (int)ft_strlen(hex_str);
	spaces = ft_max(0, field.width - ft_max(field.prec, hexnbr_len));
	zeros = ft_max(0, field.prec - hexnbr_len);
	if (flags.minus)
		hex_len = left_justified(flags, field, hex_str, type);
	else
		hex_len = right_justified(flags, field, hex_str, type);
	if (flags.sharp && !(hex_str[0] == '0' && hexnbr_len == 1))
		hex_len += 2;
	return (hex_len);
}

int	read_hex_num(va_list *ap, char type, t_flag flags, t_field field)
{
	unsigned int	target;
	char			*hex_str;
	int				hex_len;

	target = va_arg(*ap, unsigned int);
	if (field.prec_flag)
		flags.zero = 0;
	hex_str = malloc(sizeof(char) * 100);
	if (!hex_str)
		return (-1);
	dec_nbr_to_hex_str(target, &hex_str);
	if (type == 'X')
		ft_str_toupper(&hex_str);
	if (field.prec_flag && field.prec == 0 && target == 0)
	{
		ft_putchar_fd_num(' ', 1, field.width);
		hex_len = field.width;
	}
	else
		hex_len = ft_put_hex_nbr(flags, field, hex_str, type);
	free(hex_str);
	return (hex_len);
}
