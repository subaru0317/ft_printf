/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:36:15 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:38:41 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	left_justified(int target_len, char *target_str, t_field field)
{
	ft_putstr_fd("0x", 1);
	while (target_len--)
		ft_putchar_fd(target_str[target_len], 1);
	ft_putchar_fd_num(' ', 1, field.width - ft_strlen(target_str) - 2);
}

static void	right_justified(int target_len, char *target_str, t_field field)
{
	ft_putchar_fd_num(' ', 1, field.width - ft_strlen(target_str) - 2);
	ft_putstr_fd("0x", 1);
	while (target_len--)
		ft_putchar_fd(target_str[target_len], 1);
}

int	read_pointer(va_list *ap, t_flag flags, t_field field)
{
	unsigned long long	target;
	char				*target_str;
	int					target_len;

	target = va_arg(*ap, unsigned long long);
	target_str = malloc(sizeof(char) * 100);
	if (!target_str)
		return (-1);
	dec_nbr_to_hex_str(target, &target_str);
	target_len = ft_strlen(target_str);
	target_str[target_len] = '\0';
	if (flags.minus)
		left_justified(target_len, target_str, field);
	else
		right_justified(target_len, target_str, field);
	free(target_str);
	return (ft_max(field.width, target_len + 2));
}
