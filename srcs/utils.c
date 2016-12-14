/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:08:09 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:56:33 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define MOVE_RATIO 0.05

double			x_to_real(t_win *win, int x)
{
	return (win->win_wmin + (double)x
			* (win->win_wmax - win->win_wmin) / WIN_W);
}

double			y_to_imaginary(t_win *win, int y)
{
	return (win->win_hmin + (double)(WIN_H - y)
			* (win->win_hmax - win->win_hmin) / WIN_H);
}

void			zoom(t_win *win, double ratio, double centerx, double centery)
{
	win->win_wmin += (centerx - win->win_wmin) * (1 - ratio);
	win->win_wmax -= (win->win_wmax - centerx) * (1 - ratio);
	win->win_hmin += (centery - win->win_hmin) * (1 - ratio);
	win->win_hmax -= (win->win_hmax - centery) * (1 - ratio);
}

void			move_win(t_win *win, int up, int left)
{
	double	h_diff;
	double	v_diff;

	h_diff = win->win_hmax - win->win_hmin;
	v_diff = win->win_wmax - win->win_wmin;
	if (up != 0)
	{
		win->win_hmin += h_diff * (up > 0 ? +MOVE_RATIO : -MOVE_RATIO);
		win->win_hmax += h_diff * (up > 0 ? +MOVE_RATIO : -MOVE_RATIO);
	}
	if (left != 0)
	{
		win->win_wmin += v_diff * (left < 0 ? +MOVE_RATIO : -MOVE_RATIO);
		win->win_wmax += v_diff * (left < 0 ? +MOVE_RATIO : -MOVE_RATIO);
	}
}
