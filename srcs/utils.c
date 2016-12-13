/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:08:09 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 19:50:04 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define MOVE_RATIO 0.05

double			x_to_real(t_win *win, int x)
{
	return (win->win_wmin + (double)x * (win->win_wmax - win->win_wmin) / WIN_W);
}

double			y_to_imaginary(t_win *win, int y)
{
	return (win->win_hmin + (double)(WIN_H - y) * (win->win_hmax - win->win_hmin) / WIN_H);
}

void			zoom(t_win *win, double ratio, double centerx, double centery)
{

	//printf("mouse x = %d, mouse_y = %d\n", win->mouse_x, win->mouse_y);
	//printf("SAVE mouse x = %d, mouse_y = %d\n", win->mouse_x_save, win->mouse_y_save);
	//printf("ratio = %g\nWMIN = %g, WMAX = %g, centerx = %g\nHMIN = %g, HMAX = %g centery = %g\n", ratio, win->win_wmin, win->win_wmax, centerx, win->win_hmin, win->win_hmax, centery);
	win->win_wmin += (centerx - win->win_wmin) * (1 - ratio);
	win->win_wmax -= (win->win_wmax - centerx) * (1 - ratio);
	win->win_hmin += (centery - win->win_hmin) * (1 - ratio);
	win->win_hmax -= (win->win_hmax - centery) * (1 - ratio);
	//printf("mouse real = %g imaginary = %g\n", x_to_real(win, win->mouse_x), y_to_imaginary(win, win->mouse_y));
	//win->win_wmax = centerx + (win->win_wmax - centerx) * ratio;
	//win->win_hmin = centery - (centery - win->win_hmin) * ratio;
	//win->win_hmax = centery + (win->win_hmax - centery) * ratio;
	//printf("WMIN = %g, WMAX = %g, HMIN = %g, HMAX = %g\n", win->win_wmin, win->win_wmax, win->win_hmin, win->win_hmax);
	//printf("=========================\n");
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
