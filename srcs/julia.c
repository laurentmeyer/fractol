/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:25:40 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 16:26:20 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mycomplex.h"
#include <stdlib.h>
#define	MAX_ITER 80
#define MAX_MODULUS 4
#define COLOR_FACTOR 3
#define ROOT_DIFF 0.001

#include <stdio.h>

static int		mandelbrot_divergence(double zx, double zy, double cx, double cy)
{
	double		init[2];
	double		copy[2];
	t_fcomplex	*z;
	int			i;

	init[0] = zx;
	init[1] = zy;
	z = (t_fcomplex *)(&init);
	i = 0;
	while ((*z)[0] * (*z)[0] + (*z)[1] * (*z)[1] < MAX_MODULUS && ++i < MAX_ITER)
	{
		copy[0] = (*z)[0];
		copy[1] = (*z)[1];
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_add_to_f(z, cx, cy);
	}
	return ((3 * i) << 8);
}

void	julia_update_all(t_win *win, double cx, double cy)
{
	int			zx;
	int			zy;
	int			col;

	zy = 0;
	while (zy < WIN_H)
	{
		zx = 0;
		while (zx < WIN_W)
		{
			col = mandelbrot_divergence(
					x_to_real(win, zx),
					y_to_imaginary(win, zy),
					cx,
					cy);
			//printf("x = %d, y = %d, col = %d\n", zx, zy, col);
			pixel_put(win, zx, zy, col);
			++zx;
		}
		++zy;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}

void	mandel_update_all(t_win *win)
{
	int			cx;
	int			cy;
	int			col;

	cy = 0;
	while (cy < WIN_H)
	{
		cx = 0;
		while (cx < WIN_W)
		{
			col = mandelbrot_divergence(
					0,
					0,
					x_to_real(win, cx),
					y_to_imaginary(win, cy));
			pixel_put(win, cx, cy, col);
			++cx;
		}
		++cy;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}
