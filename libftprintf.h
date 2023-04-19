/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:09:13 by smihata           #+#    #+#             */
/*   Updated: 2023/04/19 18:18:58 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct flag_list
{
	size_t	sharp;
	size_t	zero;
	size_t	minus;
	size_t	space;
	size_t	plus;
} flag_list;

typedef struct field_info
{
	size_t	width;
	size_t	precision_flag;
	int		precision;
} field_info;

int	ft_printf(const char *, ...);

#endif