/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:18:24 by juwang            #+#    #+#             */
/*   Updated: 2025/05/05 12:42:37 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || (*s == 32))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = (n * 10) + (*s - '0');
		s++;
	}
	return (sign * n);
}

// int	main(void)
// {
// 	const char	*s1;
// 	const char	*s2;
// 	const char	*s3;
// 	const char	*s4;
// 	const char	*s5;

// 	s1 = "  \0 --fast move";
// 	s2 = "2147483700";//ft_atoi 函數會因為超出 int 最大值而發生整數溢出
// 	s3 = "-ataoka";
// 	s4 = "-2147483648";
// 	s5 = " \t\n\r\f12345";
// 	printf("%d\n", ft_atoi(s1));
// 	printf("%d\n", ft_atoi(s2));
// 	printf("%d\n", ft_atoi(s3));
// 	printf("%d\n", ft_atoi(s4));
// 	printf("%d\n", ft_atoi(s5));
// 	return (0);
// }
