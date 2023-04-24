/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extend_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:32:27 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 15:25:35 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar_fd_num(char c, int fd, long long num)
{
	long long	i;

	if (num > 0)
	{
		i = 0;
		while (i < num)
		{
			write(fd, &c, 1);
			i++;
		}
	}
}

size_t	ft_num_len(long long n)
{
	size_t			len;
	unsigned int	plus_n;

	len = 0;
	if (n < 0)
	{
		plus_n = n * -1;
		len++;
	}
	else
		plus_n = n;
	while (1)
	{
		len++;
		plus_n /= 10;
		if (plus_n == 0)
			break ;
	}
	return (len);
}

size_t	dec_to_hex_return_hex_len(unsigned long long dec, char **hex)
{
	unsigned long long	tmp;
	size_t				len;

	len = 0;
	while (1)
	{
		tmp = dec % 16;
		dec /= 16;
		if (0 <= tmp && tmp <= 9)
			tmp += '0';
		else if (10 <= tmp && tmp <= 15)
			tmp += 87;
		else
		{
			hex[0][len] = '\0';
			break ;
		}
		hex[0][len++] = tmp;
		if (dec == 0)
		{
			hex[0][len] = '\0';
			break ;
		}
	}
	return (len);
}
