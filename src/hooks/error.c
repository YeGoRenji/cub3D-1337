/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:55:31 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 20:39:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hooks.h>

void	exit_failure(t_vars *vars)
{
	if (vars->mlx)
		mlx_close_window(vars->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

void	load_img_err(char *path)
{
	if (!path)
		return ;
	ft_putstr_fd("Error\nCouldn't Load image ", 2);
	ft_putendl_fd(path, 2);
}
