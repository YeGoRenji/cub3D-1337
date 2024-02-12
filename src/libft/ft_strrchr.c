/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:39:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 14:43:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	ch;

	ptr = (char *)s + ft_strlen(s);
	ch = (unsigned char)c;
	while (ptr >= s)
	{
		if (*ptr == ch)
			return (ptr);
		ptr--;
	}
	return (0);
}
