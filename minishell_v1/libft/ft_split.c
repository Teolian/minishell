/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:58:17 by juwang            #+#    #+#             */
/*   Updated: 2025/05/07 15:07:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*whos_next(char const **s, char c)
{
	size_t		j;
	const char	*start = *s;

	j = 0;
	while (**s && **s != c)
	{
		(*s)++;
		j++;
	}
	return (ft_substr(start, 0, j));
}

char	**set_free(char **arr, size_t i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**_2ds;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	_2ds = (malloc(sizeof(char *) * (how_many_words(s, c) + 1)));
	if (!_2ds)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			_2ds[i++] = whos_next(&s, c);
			if (!_2ds[i - 1])
			{
				return (set_free(_2ds, i));
			}
		}
		else
			s++;
	}
	_2ds[i] = NULL;
	return (_2ds);
}

// char **_2ds: 这表示 _2ds 是一个数组，其每个元素都是一个 char *，也就是指向字符串（字符数组）的指针。
// ft_split 的目的是将原始字符串 s 根据分隔符 c 分割成多个独立的子字符串，并将这些子字符串的指针存储在 _2ds 这个数组中。

// 字符串的终止符 \0: 空字符 \0 用于标记单个字符串的结束。
// 例如，一个 char * 指向的字符串 "hello" 在内存中实际上是 h e l l o \0 这样的存储结构。

// 指针数组的终止符 NULL: 对于一个指针数组（比如我们的 _2ds），我们需要一个方法来标记数组中有效指针的结束。
// 通常的做法是将数组的最后一个元素设置为 NULL。
// 这使得遍历这个指针数组的函数（比如用于打印或释放内存）能够知道何时到达了子字符串列表的末尾。
