/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:25:40 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/09 19:16:46 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mycomplex.h"
#include <stdlib.h>
#define	MAX_ITER 80
#define MAX_MODULUS 4
#define COLOR_FACTOR 3

#include <stdio.h>

//static int		color_set(int i)
//{
//	if ((i = i >> 1) == 0)
//		return (0x000000);
//	if ((i = i >> 1) == 0)
//		return (0x00000F);
//	if ((i = i >> 1) == 0)
//		return (0x0000F0);
//	if ((i = i >> 1) == 0)
//		return (0x000F00);
//	if ((i = i >> 1) == 0)
//		return (0x00F000);
//	if ((i = i >> 1) == 0)
//		return (0x0F0000);
//	if ((i = i >> 1) == 0)
//		return (0xF00000);
//	if ((i = i >> 1) == 0)
//		return (0xFF0000);
//	if ((i = i >> 1) == 0)
//		return (0x0000FF);
//	if ((i = i >> 1) == 0)
//		return (0x00FF00);
//	return (0xFFFFFF);
//}

double			x_to_real(t_data *data, int x)
{
	return (data->win_wmin + (double)x * (data->win_wmax - data->win_wmin) / WIN_W);
}

double			y_to_imaginary(t_data *data, int y)
{
	return (data->win_hmin + (double)(WIN_H - y) * (data->win_hmax - data->win_hmin) / WIN_H);
}

static int		julia_update_pix(double zx, double zy, double cx, double cy)
{
	double		init[2];
	double		copy[2];
	t_fcomplex	*z;
	int			i;

	init[0] = zx;
	init[1] = zy;
	z = (t_fcomplex *)(&init);
	i = 0;
	while ((*z)[0] * (*z)[0] + (*z)[1] * (*z)[1] < MAX_MODULUS && ++i <= MAX_ITER)
	{
		copy[0] = (*z)[0];
		copy[1] = (*z)[1];
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_add_to_f(z, cx, cy);
	}
	return ((3 * i) << 8);
	//return (color_set(i));
}

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
			col = julia_update_pix(
					x_to_real(data, zx),
					y_to_imaginary(data, zy),
					cx,
					cy);
			pixel_put(data, zx, zy, col);
			++zx;
		}
		++zy;
		if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
			exit(0);
	}
}
