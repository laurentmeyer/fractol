/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:25:40 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:56:19 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mycomplex.h"
#include <stdlib.h>
#define MAX_ITER 80
#define MAX_MODULUS 4
#define COLOR_FACTOR 3
#define ROOT_DIFF 0.001

static int		mandelbrot_colors(int iter)
{
	int	m;

	m = iter % 16;
	if (m == 0 || m == 1)
		return (m == 0 ? 0x421E0F : 0x19071A);
	if (m == 2 || m == 3)
		return (m == 2 ? 0x09012F : 0x040449);
	if (m == 4 || m == 5)
		return (m == 4 ? 0x000764 : 0x0C2C8A);
	if (m == 6 || m == 7)
		return (m == 6 ? 0x1852B1 : 0x397DD1);
	if (m == 8 || m == 9)
		return (m == 8 ? 0x86B5E5 : 0xD3ECF8);
	if (m == 10 || m == 11)
		return (m == 10 ? 0xF1E9BF : 0xF8C95F);
	if (m == 12 || m == 13)
		return (m == 12 ? 0xFFAA00 : 0xCC8000);
	if (m == 14 || m == 15)
		return (m == 14 ? 0x995700 : 0x6A3403);
	return (0);
}

static int		mandelbrot_divergence(double zx, double zy,
										double cx, double cy)
{
	double		init[2];
	double		copy[2];
	t_fcomplex	*z;
	int			i;

	init[0] = zx;
	init[1] = zy;
	z = (t_fcomplex *)(&init);
	i = 0;
	while ((*z)[0] * (*z)[0] + (*z)[1] * (*z)[1] < MAX_MODULUS
			&& ++i < MAX_ITER)
	{
		copy[0] = (*z)[0];
		copy[1] = (*z)[1];
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_add_to_f(z, cx, cy);
	}
	return (mandelbrot_colors(i));
}

void			julia_update_all(t_win *win, double cx, double cy)
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
					x_to_real(win, zx), y_to_imaginary(win, zy), cx, cy);
			pixel_put(win, zx, zy, col);
			++zx;
		}
		++zy;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr,
				win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}

void			mandel_update_all(t_win *win)
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
					0, 0, x_to_real(win, cx), y_to_imaginary(win, cy));
			pixel_put(win, cx, cy, col);
			++cx;
		}
		++cy;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr,
				win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}
