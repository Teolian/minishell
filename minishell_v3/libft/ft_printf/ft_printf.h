/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:38:39 by juwang            #+#    #+#             */
/*   Updated: 2025/05/20 19:22:11 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_putchar_count(char c, int fd);
int		print_char(char c);
int		print_string(char *str);
int		print_pointer_hex(unsigned long n);
int		print_pointer(void *ptr);
int		print_int(int n);
int		print_unsigned(unsigned int n);
int		print_hex(unsigned int n, int uppercase);
size_t	let_me_count(long long n);
char	*ft_itoa(int n);
int		handle_format(char type, va_list args);
int		ft_printf(const char *format, ...);

#endif
