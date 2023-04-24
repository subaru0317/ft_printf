/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hex_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:54 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 16:04:49 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_str_toupper(char **c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(c[0]);
	while (i < len)
	{
		c[0][i] = ft_toupper(c[0][i]);
		i++;
	}
}

static void	ft_put_prefix_fd(unsigned int x, t_flag flags, char type, int fd)
{
	if (flags.sharp && x != 0)
	{
		if (type == 'x')
			ft_putstr_fd("0x", fd);
		else if (type == 'X')
			ft_putstr_fd("0X", fd);
	}
}

static void	ft_put_hex_num(t_field field, unsigned int x, char *c)
{
	size_t	len;

	len = ft_strlen(c);
	if (!(field.prec_flag && field.prec == 0 && x == 0))
		while (len--)
			ft_putchar_fd(c[len], 1);
}

static void	ft_put(t_flag flags, t_field field, char *c, unsigned int x)
{
	size_t	spaces;
	size_t	zeros;
	size_t	len;

	len = ft_strlen(c);
	spaces = ft_max(0, field.width - ft_max(field.prec, len));
	zeros = ft_max(0, field.prec - len);
	if (field.prec_flag && field.prec == 0 && x == 0 && field.width != 0)
		spaces++;
	if (flags.minus)
	{
		ft_putchar_fd_num('0', 1, zeros);
		ft_put_hex_num(field, x, c);
		ft_putchar_fd_num(' ', 1, spaces);
	}
	else
	{
		if (flags.zero && !field.prec)
			zeros += spaces;
		else
			ft_putchar_fd_num(' ', 1, spaces);
		ft_putchar_fd_num('0', 1, zeros);
		ft_put_hex_num(field, x, c);
	}
}

int	read_hex_num(va_list *ap, char type, t_flag flags, t_field field)
{
	unsigned int	x;
	char			*c;
	size_t			len;

	x = va_arg(*ap, unsigned int);
	ft_put_prefix_fd(x, flags, type, 1);
	c = malloc(sizeof(char) * 100);
	if (!c)
		return (-1);
	len = dec_to_hex_return_hex_len(x, &c);
	if (type == 'X')
		ft_str_toupper(&c);
	c[len] = '\0';
	ft_put(flags, field, c, x);
	free(c);
	return (ft_max(ft_max(field.width, field.prec), len));
}
