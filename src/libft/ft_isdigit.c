/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:48:21 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 14:43:49 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnotdigit(int c)
{
	return (c < '0' || c > '9');
}

int	ft_isdigit_string(char *str)
{
	int	res;

	if (!str)
		return (0);
	if ((*str == '-' || *str == '+') && ft_isdigit(str[1]))
		str++;
	res = 0;
	while (*str)
		res += ft_isnotdigit(*str++);
	return (res);
}
