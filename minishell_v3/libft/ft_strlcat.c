/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:18:46 by juwang            #+#    #+#             */
/*   Updated: 2025/05/06 05:19:32 by juwang           ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
	{
		return (src_len + size);
	}
	while ((src[i]) && (dst_len + i + 1) < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char		mystr1[] = "42tokyo";
// 	const char	*mystr2 = "unavailable";
// 	char		mystr3[] = "42tokyo";
// 	size_t		mysize1;

// 	mysize1 = 4;
// 	printf("%zu\n", ft_strlcat(mystr1, mystr2, mysize1));
// 	printf("%s\n", mystr1);
// 	printf("%zu\n", strlcat(mystr3, mystr2, mysize1));
// 	printf("%s\n", mystr3);
// 	return (0);
// }
