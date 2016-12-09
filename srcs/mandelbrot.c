/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 16:48:31 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/08 19:36:51 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mycomplex.h"
#include <stdlib.h>
#define	MAX_ITER 30
#define MAX_MODULUS 4
#define COLOR_FACTOR 15
#define X_INIT 0.5
#define Y_INIT 0.5

#include <stdio.h>

static int		mandel_update_pix(double x, double y, int init_color)
{
	double		init[2];
	t_fcomplex	*c;
	int			i;

	init[0] = (double)(2 * x - WIN_W) / WIN_W;
	init[1] = (double)(2 * y - WIN_H) / WIN_H;
	c = (t_fcomplex *)(&init);
	i = 0;
	while (fcomplex_modulus(c) < MAX_MODULUS && i++ < MAX_ITER)
	{
		init_color += COLOR_FACTOR;
		fcomplex_multiply_to(c, c);
		fcomplex_add_to_f(c, X_INIT, Y_INIT);
	}
	return (init_color << 8);
}

void	mandel_update_all(t_data *data)
{
	int			x;
	int			y;
	int			col;
	double		zx;
	double		zy;

	y = 0;
	zx = X_INIT;
	zy = Y_INIT;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			col = mandel_update_pix(
					x,
					y,
					0x00);
			pixel_put(data, x, y, col);
			++x;
		}
		++y;
		if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
			exit(0);
	}
}
