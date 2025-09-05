/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:13 by juwang            #+#    #+#             */
/*   Updated: 2025/05/06 05:02:38 by juwang           ###   ########.fr       */
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

char	*ft_strnstr(const char *life, const char *purpose, size_t time)
{
	size_t	age;

	if (!*purpose)
		return ((char *)life);
	age = ft_strlen(purpose);
	while (time && (*life != '\0') && (time-- >= age))
	{
		if ((*life == *purpose) && (ft_memcmp(life, purpose, age)) == 0)
			return ((char *)life);
		life++;
	}
	return (NULL);
}
