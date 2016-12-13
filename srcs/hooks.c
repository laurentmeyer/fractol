/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:38 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 16:43:19 by lmeyer           ###   ########.fr       */
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

static void				zoom(t_win *win, double ratio, double centerx, double centery)
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

static int				key_hooks(int keycode, t_win *win)
{
	printf("keycode : 0x%x\n", keycode);
	if (keycode == M_KEY)
	{
		win->mouse_on = !win->mouse_on;
		win->posx_save = x_to_real(win, win->mouse_x);
		win->posy_save = y_to_imaginary(win, win->mouse_y);
	}
	if(keycode == PAGEUP_KEY || keycode == PAGEDOWN_KEY)
	{
		zoom(win, keycode == PAGEDOWN_KEY ? 1.1 : 0.9,
				x_to_real(win, win->mouse_x),
				y_to_imaginary(win, win->mouse_y));
	if (win == ((t_data *)(win->data))->julia)
		julia_update_all(win, win->posx_save, win->posy_save);
	if (win == ((t_data *)(win->data))->mandel)
		mandel_update_all(win);
//	if (win == ((t_data *)(win->data))->newton)
//		newton_update_all(win);
	}
	if (win && keycode == ESC_KEY)
		exit(0);
	return (1);
}

static int				mouse_wheel_hooks(int button, int x, int y, t_win *win)
{
	x = 0;
	y = 0;
	if (win)
		printf("button : %d\n", button);
	if (button == MOUSEWHEEL_UP || button == MOUSEWHEEL_DOWN)
	{
		zoom(win, button == MOUSEWHEEL_DOWN ? 1.1 : 0.9,
				x_to_real(win, win->mouse_x),
				y_to_imaginary(win, win->mouse_y));
	if (win == ((t_data *)(win->data))->julia)
		julia_update_all(win, win->posx_save, win->posy_save);
	if (win == ((t_data *)(win->data))->mandel)
		mandel_update_all(win);
	if (win == ((t_data *)(win->data))->newton)
		newton_update_all(win);
	}
	return (1);
}

//static int				mouse_click_drag(int x, int y, t_win *w)
//{
//	printf("mouse real = %g imaginary = %g\n", x_to_real(w, x), y_to_imaginary(w, y));
//	//data->posx_save = x_to_real(data, data->mouse_x);
//	//data->posy_save = y_to_imaginary(data, data->mouse_y);
//	return (1);
//}

static int				mouse_movement(int x, int y, t_win *w)
{
	w->mouse_x = x;
	w->mouse_y = y;
	//printf("mouse real = %g imaginary = %g\n", x_to_real(w, w->mouse_x), y_to_imaginary(w, w->mouse_y));
	if ((w == ((t_data *)(w->data))->julia) && w->mouse_on)
		julia_update_all(w, x_to_real(w, w->mouse_x), y_to_imaginary(w, w->mouse_y));
	return (1);
}

int				all_hooks(t_data *data)
{
	t_data 	*d;
	t_win	*w;

	d = (t_data *)data;
	if ((w = d->julia))
	{
		mlx_key_hook(w->win_ptr, &key_hooks, w);
		mlx_hook(w->win_ptr, MotionNotify, PointerMotionMask, &mouse_movement, w);
		mlx_mouse_hook(w->win_ptr, &mouse_wheel_hooks, w);
//		mlx_hook(w->win_ptr, MotionNotify, (1L<<13), &mouse_click_drag, w);
	}
	if ((w = d->mandel))
	{
		mlx_key_hook(w->win_ptr, &key_hooks, w);
		mlx_hook(w->win_ptr, MotionNotify, PointerMotionMask, &mouse_movement, w);
		mlx_mouse_hook(w->win_ptr, &mouse_wheel_hooks, w);
//		mlx_hook(w->win_ptr, MotionNotify, (1L<<13), &mouse_click_drag, w);
	}
	if ((w = d->newton))
	{
		mlx_key_hook(w->win_ptr, &key_hooks, w);
		mlx_hook(w->win_ptr, MotionNotify, PointerMotionMask, &mouse_movement, w);
		mlx_mouse_hook(w->win_ptr, &mouse_wheel_hooks, w);
//		mlx_hook(w->win_ptr, MotionNotify, (1L<<13), &mouse_click_drag, w);
	}
	return (1);
}
