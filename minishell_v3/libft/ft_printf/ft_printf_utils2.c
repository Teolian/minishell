/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:58:54 by juwang            #+#    #+#             */
/*   Updated: 2025/05/20 10:45:57 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	while (num[len])
	{
		write(1, &num[len], 1);
		len++;
	}
	free(num);
	return (len);
}

int	print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += print_unsigned(n / 10);
	len += print_char((n % 10) + '0');
	return (len);
}

int	print_hex(unsigned int n, int uppercase)
{
	int		len;
	char	c;
	int		digit;

	len = 0;
	if (n >= 16)
		len += print_hex(n / 16, uppercase);
	digit = n % 16;
	if (digit < 10)
		c = digit + '0';
	else
	{
		if (uppercase)
			c = digit - 10 + 'A';
		else
			c = digit - 10 + 'a';
	}
	len += print_char(c);
	return (len);
}
