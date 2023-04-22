/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extend_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:32:27 by smihata           #+#    #+#             */
/*   Updated: 2023/04/22 15:32:40 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar_fd_num(char c, int fd, long long num)
{
	size_t	i;

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

void ft_str_toupper(char **c)
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
