/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:09:13 by smihata           #+#    #+#             */
/*   Updated: 2023/04/24 18:08:09 by smihata          ###   ########.fr       */
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
}	t_flag;

typedef struct field_info
{
	int		width;
	size_t	prec_flag;
	int		prec;
}	t_field;

// math_utils
size_t				ft_min(long long x, long long y);
size_t				ft_max(long long x, long long y);
unsigned long long	ft_abs(long long n);

// libft_extend_utils
void				ft_putchar_fd_num(char c, int fd, long long num);
size_t				ft_num_len(long long n);
size_t				dec_to_hex_return_hex_len(unsigned long long dec,
						char **hex);

// set_options
size_t				set_flag(const char *fmt, t_flag *flags);
size_t				set_min_field_width(va_list *ap, const char *fmt,
						t_flag *flags, t_field *field);
size_t				set_precision(va_list *ap, const char *fmt, t_field *field);

// read
int					read_pointer(va_list *ap, t_flag flags, t_field field);
int					read_int(va_list *ap, char type,
						t_flag flags, t_field field);
int					read_char(va_list *ap, t_flag flags, t_field field);
int					read_string(va_list *ap, t_flag flags, t_field field);
int					read_percent(t_flag flags, t_field field);
int					read_hex_num(va_list *ap, char type,
						t_flag flags, t_field field);

// ft_printf
int					ft_printf(const char *fmt, ...);

#endif