/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:01:51 by juwang            #+#    #+#             */
/*   Updated: 2025/05/05 20:13:39 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	n;

// 	n = 0;
// 	while (s[n])
// 		n++;
// 	return (n);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(s))
	{
		len = ft_strlen(s) - start;
	}
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	j = 0;
	while (j < len)
	{
		new_s[j++] = s[start++];
	}
	new_s[j] = '\0';
	return (new_s);
}

// int	main(void)
// {
// 	char	*s;
// 	char	*sub;

// 	s = "libft project";
// 	sub = ft_substr(s, 0, 5); // "libft"
// 	printf("1: %s\n", sub);
// 	free(sub);
// 	sub = ft_substr(s, 6, 7); // "project"
// 	printf("2: %s\n", sub);
// 	free(sub);
// 	sub = ft_substr(s, 20, 5); // ""
// 	printf("3: '%s'\n", sub);
// 	free(sub);
// 	return (0);
// }

// 在 ft_substr 的上下文中，你可能会想直接返回 ""，因为它也是一个空字符串。
// 然而，在一些更复杂的场景或者为了保持函数行为的一致性，使用 ft_strdup("") 可能更合适：

// 1.内存管理的一致性: 如果 ft_substr 函数的其他分支（当成功提取子字符串时）会分配新的内存并返回指向该内存的指针，
// 那么为了保持函数行为的一致性，即使是返回空字符串的情况也应该返回一个新分配的内存块。
// 这样，调用者总是需要对 ft_substr 返回的指针进行 free() 操作，而不需要区分返回的是字符串字面量还是动态分配的内存。
// 这可以降低调用者忘记释放内存的风险。

// 2.避免潜在的修改问题 (虽然对于空字符串不太可能): 虽然对于空字符串不太可能发生修改，但如果函数的设计理念是返回原始字符串的独立副本，
// 那么使用 ft_strdup 即使对于空字符串也是符合这种理念的。
