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
#include "complex.h"
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

static int		mandelbrot_divergence(t_c z, t_c c)
{
	int			i;

	i = 0;
	while (z.r * z.r + z.i * z.i < MAX_MODULUS
			&& ++i < MAX_ITER)
	{
		z = c_mul(z, z);
		z = c_add(z, c);
	}
	return (mandelbrot_colors(i));
}

void			julia_update_all(t_win *win, t_c c)
{
	int			x;
	int			y;
	t_c			z;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			z = (t_c){x_to_real(win, x), y_to_imaginary(win, y)};
			pixel_put(win, x, y, mandelbrot_divergence(z, c));
			++x;
		}
		++y;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr,
				win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}

void			mandel_update_all(t_win *win)
{
	int			x;
	int			y;
	t_c			c;
	t_c			z;

	z = (t_c){0, 0};
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			c = (t_c){x_to_real(win, x), y_to_imaginary(win, y)};
			pixel_put(win, x, y, mandelbrot_divergence(z, c));
			++x;
		}
		++y;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr,
								 win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}
