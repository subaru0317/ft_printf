/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:09:13 by smihata           #+#    #+#             */
/*   Updated: 2023/05/05 18:45:49 by smihata          ###   ########.fr       */
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
int					ft_min(int x, int y);
int					ft_max(int x, int y);
unsigned int		ft_abs(int n);

// libft_extend_utils
void				ft_putchar_fd_num(char c, int fd, int num);
void				dec_nbr_to_hex_str(unsigned long long dec, char **hex);
int					ft_plus_nbr_len(unsigned int n);

// set_options
int					set_flag(const char *fmt, t_flag *flags);
int					set_min_field_width(va_list *ap, const char *fmt,
						t_flag *flags, t_field *field);
int					set_precision(va_list *ap, const char *fmt, t_field *field);
int					set_directive(va_list *ap, const char *fmt,
						t_flag *flags, t_field *field);

// read_hex_num_utils
void				ft_str_toupper(char **str);
void				ft_put_nbr(char *str);

// read
int					read_pointer(va_list *ap, t_flag flags, t_field field);
int					read_int(va_list *ap, t_flag flags, t_field field);
int					read_uint(va_list *ap, t_flag flags, t_field field);
int					read_char(va_list *ap, t_flag flags, t_field field);
int					read_string(va_list *ap, t_flag flags, t_field field);
int					read_percent(t_flag flags, t_field field);
int					read_hex_num(va_list *ap, char type,
						t_flag flags, t_field field);

// ft_printf
int					ft_printf(const char *fmt, ...);

#endif