/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:36:50 by juwang            #+#    #+#             */
/*   Updated: 2025/05/05 13:06:25 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	let_me_count(long long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		len;
	long long	new_n;
	char		*s;

	len = let_me_count(n);
	new_n = n;
	s = (char *)malloc((sizeof(char)) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	if (new_n < 0)
	{
		s[i] = '-';
		new_n = -new_n;
	}
	while (new_n > 9)
	{
		s[len - i - 1] = (new_n % 10) + '0';
		new_n /= 10;
		i++;
	}
	s[len - i - 1] = (new_n % 10) + '0';
	s[len] = '\0';
	return (s);
}

// int	main(void)
// {
// 	int	n1;
// 	int	n2;
// 	int	n3;
// 	int	n4;

// 	n1 = 0;
// 	n2 = 123456789;
// 	n3 = -42;
// 	n4 = -2147483648;
// 	printf("%s\n", ft_itoa(n1));
// 	printf("%s\n", ft_itoa(n2));
// 	printf("%s\n", ft_itoa(n3));
// 	printf("%s\n", ft_itoa(n4));
// 	return (0);
// }
