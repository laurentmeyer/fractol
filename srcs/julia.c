/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:25:40 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 14:45:03 by lmeyer           ###   ########.fr       */
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

static int		color_set(int i)
{
	//	if (i == 0)
	//		return (0x000000);
	//	if (i < 2)
	//		return (0x
	if ((i = i >> 1) == 0)
		return (0x000000);
	if ((i = i >> 1) == 0)
		return (0x00000F);
	if ((i = i >> 1) == 0)
		return (0x0000F0);
	if ((i = i >> 1) == 0)
		return (0x000F00);
	if ((i = i >> 1) == 0)
		return (0x00F000);
	if ((i = i >> 1) == 0)
		return (0x0F0000);
	if ((i = i >> 1) == 0)
		return (0xF00000);
	if ((i = i >> 1) == 0)
		return (0xFF0000);
	if ((i = i >> 1) == 0)
		return (0x0000FF);
	if ((i = i >> 1) == 0)
		return (0x00FF00);
	return (0xFFFFFF);
}

double			x_to_real(t_win *win, int x)
{
	return (win->win_wmin + (double)x * (win->win_wmax - win->win_wmin) / WIN_W);
}

double			y_to_imaginary(t_win *win, int y)
{
	return (win->win_hmin + (double)(WIN_H - y) * (win->win_hmax - win->win_hmin) / WIN_H);
}

//static int		newton_root(double a, double b)
//{
//	double	cube[2];
//	double	sqrmod;
//
//	//printf("r = %g et i = %g\n", a, b);
//	cube[0] = a * a * a - 3 * a * b * b;
//	cube[1] = 3 * a * a * b - b * b * b;
//	sqrmod = cube[0] * cube[0] + cube[1] * cube[1];
//	//printf("sqrmod = %g, cube[0] = %g, cube[1] = %g\n", sqrmod, cube[0], cube[1]);
//	if (!(sqrmod - 1 < ROOT_DIFF && sqrmod - 1 > -ROOT_DIFF))
//		return (0);
//	if (a > 0.9)
//		return (1);
//	if (b > 0.8)
//		return (2);
//	return (3);
//}
//
//
//
//static int		newton_divergence(double zx, double zy)
//{
//	double		init[2];
//	double		copy[2];
//	t_fcomplex	*z;
//	int			i;
//	int			root;
//
//	//printf("======================\n");
//	init[0] = zx;
//	init[1] = zy;
//	z = (t_fcomplex *)(&init);
//	i = 0;
//	if (zx == 0 && zy == 0)
//		return (0);
//	while (!(root = newton_root(init[0], init[1])) && ++i <= 50)
//	{
//		//print_complex(z);
//		copy[0] = init[0];
//		copy[1] = init[1];
//		fcomplex_multiply_to_f(z, copy[0], copy[1]);
//		fcomplex_multiply_to_f(z, copy[0], copy[1]);
//		fcomplex_multiply_to_f(z, 2, 0);
//		init[0] += 1;
//		fcomplex_divide_to_f(z, copy[0], copy[1]);
//		fcomplex_divide_to_f(z, 3 * copy[0], 3 * copy[1]);
//	}
//	//printf("yolo root = %d i = %d\n", root, i);
//	return (((5 * i) << (8 * (root - 1))));
////	return (color_set(i));
//}

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
	while ((*z)[0] * (*z)[0] + (*z)[1] * (*z)[1] < MAX_MODULUS && ++i)
	{
		copy[0] = (*z)[0];
		copy[1] = (*z)[1];
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_add_to_f(z, cx, cy);
	}
	return ((3 * i) << 8);
//	return (color_set(i));
}

//void	mandel_update_all(t_data *data)
//{
//	int			cx;
//	int			cy;
//	int			col;
//
//	cy = 0;
//	while (cy < WIN_H)
//	{
//		cx = 0;
//		while (cx < WIN_W)
//		{
//			col = mandelbrot_divergence(
//					0,
//					0,
//					x_to_real(data, cx),
//					y_to_imaginary(data, cy));
//			pixel_put(data, cx, cy, col);
//			++cx;
//		}
//		++cy;
//		if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
//			exit(0);
//	}
//}
//
//void	newton_update_all(t_data *data)
//{
//	int			zx;
//	int			zy;
//	int			col;
//
//	zy = 0;
//	while (zy < WIN_H)
//	{
//		zx = 0;
//		while (zx < WIN_W)
//		{
//			col = newton_divergence(
//					x_to_real(data, zx),
//					y_to_imaginary(data, zy));
//			pixel_put(data, zx, zy, col);
//			++zx;
//		}
//		++zy;
//		if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
//			exit(0);
//	}
//}

void	julia_update_all(t_data *data, double cx, double cy)
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
					x_to_real(data->julia, zx),
					y_to_imaginary(data->julia, zy),
					cx,
					cy);
			printf("julia min = %g\n", data->julia->win_wmin);
			printf("x = %d, y = %d, col = %d\n", zx, zy, col);
			pixel_put(data->julia, zx, zy, col);
			++zx;
		}
		++zy;
	}
	if (!mlx_put_image_to_window(data->ptr, data->julia->win_ptr, data->julia->img_ptr, 0, 0))
		exit(0);
}
