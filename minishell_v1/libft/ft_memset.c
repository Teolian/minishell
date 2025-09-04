/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:38:20 by juwang            #+#    #+#             */
/*   Updated: 2025/05/02 18:08:16 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = (unsigned char *)s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p[i] = value;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	buffer[42];

// 	ft_memset(buffer, 'T', sizeof(buffer) - 1);
// 	buffer[41] = '\0';
// 	printf("%s\n", buffer);
// 	return (0);
// }
