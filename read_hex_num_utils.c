/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hex_num_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:13:07 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 17:15:48 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_str_toupper(char **hex_str)
{
	size_t	i;
	size_t	hex_len;

	i = 0;
	hex_len = ft_strlen(hex_str[0]);
	while (i < hex_len)
	{
		hex_str[0][i] = ft_toupper(hex_str[0][i]);
		i++;
	}
}

void	ft_put_nbr(char *hex_str)
{
	size_t	hex_len;

	hex_len = ft_strlen(hex_str);
	while (hex_len--)
		ft_putchar_fd(hex_str[hex_len], 1);
}
