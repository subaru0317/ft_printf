/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:34:40 by smihata           #+#    #+#             */
/*   Updated: 2023/04/26 20:55:56 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_min(int x, int y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
