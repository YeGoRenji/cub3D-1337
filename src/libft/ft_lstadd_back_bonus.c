/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:19:25 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/11 14:43:00 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_map_line **lst, t_map_line *_new)
{
	t_map_line	*ptr;

	if (!lst || !_new)
		return ;
	ptr = *lst;
	if (ptr)
	{
		ptr = ft_lstlast(ptr);
		ptr->next = _new;
	}
	else
		*lst = _new;
}
