/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:29:27 by juwang            #+#    #+#             */
/*   Updated: 2025/05/02 18:09:31 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	m;

	m = 0;
	while (m < n)
	{
		if (!s1[m] || !s2[m] || s1[m] != s2[m])
			return ((unsigned char)s1[m] - (unsigned char)s2[m]);
		m++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*mys1;
// 	char	*mys2;
// 	size_t	i1;
// 	size_t	i2;

// 	i1 = 5;
// 	i2 = 6;
// 	mys1 = "what the";
// 	mys2 = "what THE";
// 	printf("%d\n", ft_strncmp(mys1, mys2, i1));
// 	printf("%d\n", ft_strncmp(mys1, mys2, i2));
// 	return (0);
// }
