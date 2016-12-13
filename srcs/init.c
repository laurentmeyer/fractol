/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:54:08 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 14:39:14 by lmeyer           ###   ########.fr       */
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

static t_win			*init_win(t_data *data, char *title)
{
	t_win	*win;

	if ((win = (t_win *)malloc(sizeof(t_win))))
	{
		if (!(win->win_ptr = mlx_new_window(data->ptr, WIN_W, WIN_H, title))
				|| !(win->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(win->img_addr = mlx_get_data_addr(win->img_ptr,
						&(data->bits_per_pixel),
						&(data->size_line), &(data->endian)))
				|| !(win->pts_array = init_complex_array()))
			return (NULL);
		win->mlx_ptr = data->ptr;
		win->win_hmin = -2;
		win->win_hmax = 2;
		win->win_wmin = -2;
		win->win_wmax = 2;
	}
	return (win);
}

t_data			*init_data(long masks)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init()))
			return (NULL);
		data->julia = NULL;
		data->mandel = NULL;
		data->newton = NULL;
		printf("julia = %ld\n", (masks & JULIA_MASK));
		if (((masks & JULIA_MASK) && (!(data->julia = init_win(data, "Julia set"))))
				|| ((masks & MANDEL_MASK) && (!(data->mandel = init_win(data, "Mandelbrot set"))))
				|| ((masks & NEWTON_MASK) && (!(data->newton = init_win(data, "Newton set")))))
				return (NULL);
		data->mouse_on = 1;
		data->mouse_x = 0;
		data->mouse_y = 0;
		if (data->julia)
			julia_update_all(data, data->mouse_x, data->mouse_y);
//	if (!mlx_put_image_to_window(data->ptr, data->julia->win_ptr, data->julia->img_ptr, 0, 0))
//		exit(0);
		printf("init OK\n");
	}
	return (data);
}
