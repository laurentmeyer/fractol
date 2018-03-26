/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:41:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:45:28 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	pixel_put(t_win *win, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		((unsigned int *)(win->img_addr))[y * WIN_W
			+ x] = mlx_get_color_value(win->mlx_ptr, color);
}

void	update_window(t_win *win)
{
	if (win == ((t_data *)(win->data))->julia)
		julia_update_all(win, (t_c){win->posx_save, win->posy_save});
	if (win == ((t_data *)(win->data))->mandel)
		mandel_update_all(win);
	if (win == ((t_data *)(win->data))->newton)
		newton_update_all(win);
}

int		display_image(t_data *data)
{
	all_hooks(data);
	mlx_loop(data->ptr);
	return (1);
}
