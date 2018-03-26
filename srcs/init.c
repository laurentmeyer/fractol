/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:54:08 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:54:13 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "complex.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

static t_win	*init_win(t_data *data, char *title)
{
	t_win	*win;

	if ((win = (t_win *)malloc(sizeof(t_win))))
	{
		if (!(win->win_ptr = mlx_new_window(data->ptr, WIN_W, WIN_H, title))
				|| !(win->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(win->img_addr = mlx_get_data_addr(win->img_ptr,
						&(win->bits_per_pixel),
						&(win->size_line), &(win->endian))))
			return (NULL);
		win->destroyed = 0;
		win->data = data;
		win->mlx_ptr = data->ptr;
		win->win_hmin = -2;
		win->win_hmax = 2;
		win->win_wmin = -2;
		win->win_wmax = 2;
		win->mouse_on = 1;
		win->mouse_x = 0;
		win->mouse_y = 0;
	}
	return (win);
}

t_data			*init_data(long masks)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data)))
			|| !(data->ptr = mlx_init()))
		return (NULL);
	data->julia = NULL;
	data->mandel = NULL;
	data->newton = NULL;
	if (((masks & JULIA_MASK)
				&& (!(data->julia = init_win(data, "Julia set"))))
			|| ((masks & MANDEL_MASK)
				&& (!(data->mandel = init_win(data, "Mandelbrot set"))))
			|| ((masks & NEWTON_MASK)
				&& (!(data->newton = init_win(data, "Newton set")))))
		return (NULL);
	if (data->julia)
		julia_update_all(data->julia,
				(t_c){data->julia->mouse_x, data->julia->mouse_y});
	if (data->mandel)
		mandel_update_all(data->mandel);
	if (data->newton)
		newton_update_all(data->newton);
	return (data);
}
