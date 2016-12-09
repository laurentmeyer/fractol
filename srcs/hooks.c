/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:38 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/09 19:21:54 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include "/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"
#define ESC_KEY 0x35
#define LEFT_KEY 0x7B
#define RIGHT_KEY 0x7C
#define DOWN_KEY 0x7D
#define UP_KEY 0x7E
#define OPEN_KEY 0x21
#define CLOSE_KEY 0x1E
#define PLUS_KEY 0x45
#define MINUS_KEY 0x4e
#define P_KEY 0x23
#define O_KEY 0x1f
#define D_KEY 0x2
#define M_KEY 0x2e
#define PAGEUP_KEY 0x74
#define PAGEDOWN_KEY 0x79
#define MOUSEWHEEL_UP 5
#define MOUSEWHEEL_DOWN 4

#include <stdio.h>

static void				zoom(t_data *data, double ratio, double centerx, double centery)
{

	//printf("mouse x = %d, mouse_y = %d\n", data->mouse_x, data->mouse_y);
	//printf("SAVE mouse x = %d, mouse_y = %d\n", data->mouse_x_save, data->mouse_y_save);
	//printf("ratio = %g\nWMIN = %g, WMAX = %g, centerx = %g\nHMIN = %g, HMAX = %g centery = %g\n", ratio, data->win_wmin, data->win_wmax, centerx, data->win_hmin, data->win_hmax, centery);
	data->win_wmin += (centerx - data->win_wmin) * (1 - ratio);
	data->win_wmax -= (data->win_wmax - centerx) * (1 - ratio);
	data->win_hmin += (centery - data->win_hmin) * (1 - ratio);
	data->win_hmax -= (data->win_hmax - centery) * (1 - ratio);
	//printf("mouse real = %g imaginary = %g\n", x_to_real(data, data->mouse_x), y_to_imaginary(data, data->mouse_y));
	//data->win_wmax = centerx + (data->win_wmax - centerx) * ratio;
	//data->win_hmin = centery - (centery - data->win_hmin) * ratio;
	//data->win_hmax = centery + (data->win_hmax - centery) * ratio;
	//printf("WMIN = %g, WMAX = %g, HMIN = %g, HMAX = %g\n", data->win_wmin, data->win_wmax, data->win_hmin, data->win_hmax);
	//printf("=========================\n");
}

static int				key_hooks(int keycode, t_data *data)
{
	printf("keycode : 0x%x\n", keycode);
	if (keycode == M_KEY)
	{
		data->mouse_on = !data->mouse_on;
		data->posx_save = x_to_real(data, data->mouse_x);
		data->posy_save = y_to_imaginary(data, data->mouse_y);
	}
	if(keycode == PAGEUP_KEY || keycode == PAGEDOWN_KEY)
	{
		zoom(data, keycode == PAGEDOWN_KEY ? 1.1 : 0.9,
				x_to_real(data, data->mouse_x),
				y_to_imaginary(data, data->mouse_y));
		julia_update_all(data, data->posx_save, data->posy_save);
	}
	if (keycode == ESC_KEY)
		exit(0);
	return (1);
}

static int				mouse_wheel_hooks(int button, int x, int y, t_data *data)
{
	x = 0;
	y = 0;
	if (data)
		printf("button : %d\n", button);
	if (button == MOUSEWHEEL_UP || button == MOUSEWHEEL_DOWN)
	{
		zoom(data, button == MOUSEWHEEL_DOWN ? 1.1 : 0.9,
				x_to_real(data, data->mouse_x),
				y_to_imaginary(data, data->mouse_y));
		julia_update_all(data, data->posx_save, data->posy_save);
	}
	return (1);

}

static int				mouse_movement(int x, int y, t_data *data)
{
	data->mouse_x = x;
	data->mouse_y = y;
	//printf("mouse real = %g imaginary = %g\n", x_to_real(data, x), y_to_imaginary(data, y));
	if (data->mouse_on)
		julia_update_all(data,
				x_to_real(data, data->mouse_x),
				y_to_imaginary(data, data->mouse_y));
//	mandel_update_all(data);
	return (1);
}

int				all_hooks(t_data *data)
{
	t_data *d;

	d = (t_data *)data;
	mlx_key_hook(data->win, &key_hooks, d);
	mlx_mouse_hook(data->win, &mouse_wheel_hooks, d);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, &mouse_movement, d);
	return (1);
}
