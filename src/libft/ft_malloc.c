/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:03:32 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/12 16:55:36 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_malloc(unsigned long size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "BUY MORE RAM BRO !\n", 20);
		exit(69);
	}
	return (ptr);
}
