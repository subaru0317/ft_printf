/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:36:15 by smihata           #+#    #+#             */
/*   Updated: 2023/04/22 18:32:34 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	left_justified(size_t len, char *str, t_field field)
{
	ft_putstr_fd("0x", 1);
	while (len--)
		ft_putchar_fd(str[len], 1);
	ft_putchar_fd_num(' ', 1, field.width - ft_strlen(str) - 2);
}

static void	right_justified(size_t len, char *str, t_field field)
{
	ft_putchar_fd_num(' ', 1, field.width - ft_strlen(str) - 2);
	ft_putstr_fd("0x", 1);
	while (len--)
		ft_putchar_fd(str[len], 1);
}

int	read_pointer(va_list *ap, t_flag flags, t_field field)
{
	unsigned long long	p;
	char				*str;
	size_t				len;

	p = va_arg(*ap, unsigned long long);
	str = malloc(sizeof(char) * 100);
	if (!str)
		return (-1);
	len = dec_to_hex_return_hex_len(p, &str);
	str[len] = '\0';
	if (flags.minus)
		left_justified(len, str, field);
	else
		right_justified(len, str, field);
	free(str);
	return (ft_max(field.width, len + 2));
}
