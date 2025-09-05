/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:07:52 by juwang            #+#    #+#             */
/*   Updated: 2025/05/20 19:27:57 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(char type, va_list args)
{
	if (type == 'c')
		return (print_char(va_arg(args, int)));
	else if (type == 's')
		return (print_string(va_arg(args, char *)));
	else if (type == 'p')
		return (print_pointer(va_arg(args, void *)));
	else if (type == 'd' || type == 'i')
		return (print_int(va_arg(args, int)));
	else if (type == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (type == 'x')
		return (print_hex(va_arg(args, unsigned int), 0));
	else if (type == 'X')
		return (print_hex(va_arg(args, unsigned int), 1));
	else if (type == '%')
		return (print_char('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			ret = handle_format(format[i], args);
		}
		else
			ret = print_char(format[i]);
		if (ret == -1)
			return (va_end(args), -1);
		count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
