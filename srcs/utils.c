/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:08:09 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 16:08:53 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double			x_to_real(t_win *win, int x)
{
	return (win->win_wmin + (double)x * (win->win_wmax - win->win_wmin) / WIN_W);
}

double			y_to_imaginary(t_win *win, int y)
{
	return (win->win_hmin + (double)(WIN_H - y) * (win->win_hmax - win->win_hmin) / WIN_H);
}

