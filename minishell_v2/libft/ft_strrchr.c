/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:42:31 by juwang            #+#    #+#             */
/*   Updated: 2025/05/06 04:41:14 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	n;

// 	n = 0;
// 	while (s[n])
// 		n++;
// 	return (n);
// }

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int)ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "Hello, 42 and tokyo and candy!";
// 	char		c;
// 	char		*result;

// 	c = 'o';
// 	result = ft_strrchr(str, c);
// 	if (result)
// 	{
// 		printf("Found '%c' at position: %ld\n", c, result - str);
// 	}
// 	else
// 	{
// 		printf("Character '%c' not found.\n", c);
// 	}
// 	return (0);
// }
