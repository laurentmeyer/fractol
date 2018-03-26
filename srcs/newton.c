/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:37:08 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:55:11 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "complex.h"
#include <stdlib.h>

enum			e_newton_states
{
	NEWTON_CONTINUE,
	NEWTON_RED,
	NEWTON_GREEN,
	NEWTON_BLUE
};

static int		newton_root(t_c z)
{
	t_c				cube;
	double			sqrmod;
	const double	root_diff = 0.000001;

	cube = c_mul(z, z);
	cube = c_mul(cube, z);
	sqrmod = cube.r * cube.r + cube.i * cube.i;
	if (!(sqrmod - 1 < root_diff && sqrmod - 1 > -root_diff))
		return (NEWTON_CONTINUE);
	if (z.r > 0.9)
		return (NEWTON_RED);
	if (z.i > 0.8)
		return (NEWTON_GREEN);
	return (NEWTON_BLUE);
}

static int		newton_divergence(t_c z)
{
	t_c			copy;	
	int			i;
	int			root;

	i = 0;
	if (0 == z.r && 0 == z.i)
		return (0);
	while (NEWTON_CONTINUE == (root = newton_root(z)) && ++i <= 50)
	{
		copy = z;
		z = c_mul(z, copy);
		z = c_mul(z, copy);
		z = c_mul(z, (t_c){2, 0});
		z = c_add(z, (t_c){1, 0});
		z = c_div(z, copy);
		z = c_div(z, c_mul(copy, (t_c){3, 0}));
	}
	return (((5 * i) << (8 * (root - 1))));
}

void			newton_update_all(t_win *win)
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
			pixel_put(win, x, y, newton_divergence(z));
			++x;
		}
		++y;
	}
	if (!mlx_put_image_to_window(win->mlx_ptr,
				win->win_ptr, win->img_ptr, 0, 0))
		exit(0);
}
