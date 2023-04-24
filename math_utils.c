/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:34:40 by smihata           #+#    #+#             */
/*   Updated: 2023/04/22 18:08:49 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_min(long long x, long long y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

size_t	ft_max(long long x, long long y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

unsigned long long	ft_abs(long long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
