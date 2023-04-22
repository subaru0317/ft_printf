/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:09:13 by smihata           #+#    #+#             */
/*   Updated: 2023/04/22 15:32:56 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"

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

// math_utils
size_t	ft_min(long long x, long long y);
size_t	ft_max(long long x, long long y);
unsigned long long ft_abs(long long n);

// libft_extend_utils
void	ft_putchar_fd_num(char c, int fd, long long num);
void 	ft_str_toupper(char **c);
size_t	ft_num_len(long long n);


int		ft_printf(const char *fmt, ...);

#endif