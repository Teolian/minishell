/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:41:52 by juwang            #+#    #+#             */
/*   Updated: 2025/05/02 18:09:22 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

// int	main(void)
// {
// 	char	*mys1;
// 	char	*mys2;

// 	mys1 = "what the";
// 	mys2 = "what";
// 	printf("%d\n", ft_strlen(mys1));
// 	printf("%d\n", ft_strlen(mys2));
// 	return (0);
// }
