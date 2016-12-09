/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:41:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/06 15:33:09 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		((unsigned int *)(data->img_addr))[y * WIN_W
			+ x] = mlx_get_color_value(data->ptr, color);
}

int		display_image(t_data *data)
{
	all_hooks(data);
	mlx_loop(data->ptr);
	return (1);
}
