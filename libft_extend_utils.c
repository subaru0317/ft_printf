/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extend_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:32:27 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:46:02 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar_fd_num(char c, int fd, int num)
{
	int	i;

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

void	dec_nbr_to_hex_str(unsigned long long dec, char **hex)
{
	unsigned long long	nbr;
	int					i;

	i = 0;
	while (1)
	{
		nbr = dec % 16;
		dec /= 16;
		if (0 <= nbr && nbr <= 9)
			nbr += '0';
		else if (10 <= nbr && nbr <= 15)
			nbr += 87;
		else
		{
			hex[0][i] = '\0';
			break ;
		}
		hex[0][i++] = nbr;
		if (dec == 0)
		{
			hex[0][i] = '\0';
			break ;
		}
	}
}

int	ft_plus_nbr_len(unsigned int n)
{
	int	len;

	len = 0;
	while (1)
	{
		len++;
		n /= 10;
		if (n == 0)
			break ;
	}
	return (len);
}
