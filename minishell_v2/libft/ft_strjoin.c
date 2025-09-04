/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:34:42 by juwang            #+#    #+#             */
/*   Updated: 2025/05/03 11:36:37 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = (char *)malloc(s1_len + s2_len + 1);
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1, s1_len);
	ft_memcpy(s3 + s1_len, s2, s2_len);
	s3[s1_len + s2_len] = '\0';
	return (s3);
}
