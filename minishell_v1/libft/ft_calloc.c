/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:18:35 by juwang            #+#    #+#             */
/*   Updated: 2025/05/06 14:41:27 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*p;
// 	size_t			i;

// 	p = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		p[i] = '\0';
// 		i++;
// 	}
// }

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*s;

	if (size != 0 && count > SIZE_MAX / size)
	{
		return (NULL);
	}
	total_size = count * size;
	s = malloc(total_size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, total_size);
	return (s);
}

// int	main(void)
// {
// 	size_t	count1;
// 	size_t	count2;
// 	size_t	size1;
// 	size_t	size2;

// 	count1 = 0;
// 	size1 = 98;
// 	printf("%p", ft_calloc(count1, size1));
// 	count2 = 240989572;
// 	size2 = 3535;
// 	printf("%p", ft_calloc(count2, size2));
// 	return (0);
// }
