/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:53:39 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 14:43:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

static unsigned int	min(size_t n, size_t m)
{
	if (n <= m)
		return (n);
	return (m);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_to_copy;

	if (!size)
		return (ft_strlen(src));
	size_to_copy = min(size - 1, ft_strlen(src));
	ft_memcpy(dest, src, size_to_copy);
	dest[size_to_copy] = 0;
	return (ft_strlen(src));
}
