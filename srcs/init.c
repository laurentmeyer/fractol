/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:54:08 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/08 19:40:05 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mycomplex.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

#include <stdio.h>
static t_fcomplex	***init_complex_array(void)
{
	t_fcomplex	***tmp;
	int			x;
	int			y;

	if ((tmp = (t_fcomplex ***)malloc(WIN_H * sizeof(t_fcomplex **))))
	{
		y = 0;
		while (y < WIN_H)
		{
			if (!(tmp[y] = (t_fcomplex **)malloc(WIN_W * sizeof(t_fcomplex *))))
				return (NULL);
			x = 0;
			while (x < WIN_W)
			{
				if (!(tmp[y][x] = fcomplex_new(
								2 * (double)(2 * y - WIN_H) / WIN_H,
								2 * (double)(2 * x - WIN_W) / WIN_W)))
					return (NULL);
				++x;
			}
			++y;
		}
	}
	return (tmp);
}

t_data			*init_data(void)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init())
				|| !(data->win = mlx_new_window(data->ptr, WIN_W, WIN_H, WIN_T))
				|| !(data->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(data->img_addr = mlx_get_data_addr(data->img_ptr,
						&(data->bits_per_pixel),
						&(data->size_line), &(data->endian)))
				|| !(data->julia_pts = init_complex_array()))
			return (NULL);
		data->mouse_on = 1;
		data->mouse_x = 0;
		data->mouse_y = 0;
		data->win_hmin = -2;
		data->win_hmax = 2;
		data->win_wmin = -2;
		data->win_wmax = 2;
	}
	return (data);
}
