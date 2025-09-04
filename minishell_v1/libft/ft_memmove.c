/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:34:44 by juwang            #+#    #+#             */
/*   Updated: 2025/05/06 04:33:13 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (n--)
		{
			*(d++) = *(s++);
		}
	}
	else if (d > s)
	{
		d += n;
		s += n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char	mys1[] = "Ultimate question";

// 	ft_memmove(mys1 + 0, mys1 + 9, 8);
// 	printf("%s\n", mys1);
// 	return (0);
// }
