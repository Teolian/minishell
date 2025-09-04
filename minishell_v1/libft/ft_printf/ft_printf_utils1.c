/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:58:57 by juwang            #+#    #+#             */
/*   Updated: 2025/05/20 11:30:39 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar_count(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	print_char(char c)
{
	ft_putchar_count(c, 1);
	return (1);
}

int	print_string(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (str[len])
	{
		ft_putchar_count(str[len], 1);
		len++;
	}
	return (len);
}

int	print_pointer_hex(unsigned long n)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += print_pointer_hex(n / 16);
	len += print_char(base[n % 16]);
	return (len);
}

int	print_pointer(void *ptr)
{
	int	len;

	len = 0;
	if (ptr == NULL)
		return (print_string("(nil)"));
	len += print_string("0x");
	len += print_pointer_hex((unsigned long)ptr);
	return (len);
}
