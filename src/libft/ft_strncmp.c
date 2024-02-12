/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:19:09 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 14:43:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

static int	min(size_t n, size_t m)
{
	if (n <= m)
		return (n);
	else
		return (m);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	return (ft_memcmp(s1, s2, min(n, ft_strlen(s1) + 1)));
}

int	ft_strcmp(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}
