/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:37:08 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 16:43:45 by lmeyer           ###   ########.fr       */
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

static int		newton_root(double a, double b)
{
	double	cube[2];
	double	sqrmod;

	//printf("r = %g et i = %g\n", a, b);
	cube[0] = a * a * a - 3 * a * b * b;
	cube[1] = 3 * a * a * b - b * b * b;
	sqrmod = cube[0] * cube[0] + cube[1] * cube[1];
	//printf("sqrmod = %g, cube[0] = %g, cube[1] = %g\n", sqrmod, cube[0], cube[1]);
	if (!(sqrmod - 1 < ROOT_DIFF && sqrmod - 1 > -ROOT_DIFF))
		return (0);
	if (a > 0.9)
		return (1);
	if (b > 0.8)
		return (2);
	return (3);
}

static int		newton_divergence(double zx, double zy)
{
	double		init[2];
	double		copy[2];
	t_fcomplex	*z;
	int			i;
	int			root;

	//printf("======================\n");
	init[0] = zx;
	init[1] = zy;
	z = (t_fcomplex *)(&init);
	i = 0;
	if (zx == 0 && zy == 0)
		return (0);
	while (!(root = newton_root(init[0], init[1])) && ++i <= 50)
	{
		//print_complex(z);
		copy[0] = init[0];
		copy[1] = init[1];
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_multiply_to_f(z, copy[0], copy[1]);
		fcomplex_multiply_to_f(z, 2, 0);
		init[0] += 1;
		fcomplex_divide_to_f(z, copy[0], copy[1]);
		fcomplex_divide_to_f(z, 3 * copy[0], 3 * copy[1]);
	}
	//printf("yolo root = %d i = %d\n", root, i);
	return (((5 * i) << (8 * (root - 1))));
	//	return (color_set(i));
}

void	newton_update_all(t_win *win)
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
			col = newton_divergence(
					x_to_real(win, zx),
					y_to_imaginary(win, zy));
			pixel_put(win, zx, zy, col);
			++zx;
		}
		++zy;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}
