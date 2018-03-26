/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:38 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:53:19 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "complex.h"
#include <stdlib.h>
// #include "/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"
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
#define E_KEY 0xe
#define PAGEUP_KEY 0x74
#define PAGEDOWN_KEY 0x79
#define MOUSEWHEEL_UP 5
#define MOUSEWHEEL_DOWN 4
#define MOTIONNOTIFY 6
#define POINTERMOTIONMASK (1L<<6)

static int	key_hooks(int keycode, t_win *win)
{
	if (keycode == E_KEY)
		export_fdf(win);
	if (keycode == M_KEY)
	{
		win->mouse_on = !win->mouse_on;
		win->posx_save = x_to_real(win, win->mouse_x);
		win->posy_save = y_to_imaginary(win, win->mouse_y);
	}
	if (keycode == PAGEUP_KEY || keycode == PAGEDOWN_KEY)
	{
		zoom(win, keycode == PAGEDOWN_KEY ? 1.1 : 0.9,
				x_to_real(win, win->mouse_x),
				y_to_imaginary(win, win->mouse_y));
	}
	if (keycode == UP_KEY || keycode == DOWN_KEY)
		move_win(win, keycode == UP_KEY ? 1 : -1, 0);
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		move_win(win, 0, keycode == LEFT_KEY ? 1 : -1);
	if (win && keycode == ESC_KEY)
		exit(0);
	update_window(win);
	return (1);
}

static int	mouse_wheel_hooks(int button, int x, int y, t_win *win)
{
	x = 0;
	y = 0;
	if (button == MOUSEWHEEL_UP || button == MOUSEWHEEL_DOWN)
	{
		zoom(win, button == MOUSEWHEEL_DOWN ? 1.1 : 0.9,
				x_to_real(win, win->mouse_x),
				y_to_imaginary(win, win->mouse_y));
		update_window(win);
	}
	return (1);
}

static int	mouse_movement(int x, int y, t_win *w)
{
	t_c pos;

	w->mouse_x = x;
	w->mouse_y = y;
	if ((w == ((t_data *)(w->data))->julia) && w->mouse_on)
	{
		pos = (t_c){x_to_real(w, w->mouse_x), y_to_imaginary(w, w->mouse_y)};
		julia_update_all(w, pos);
	}
	return (1);
}

static void	all_hooks_for_window(t_win *win)
{
	if (win)
	{
		mlx_key_hook(win->win_ptr, &key_hooks, win);
		mlx_mouse_hook(win->win_ptr, &mouse_wheel_hooks, win);
		mlx_hook(win->win_ptr, MOTIONNOTIFY,
					POINTERMOTIONMASK, &mouse_movement, win);
	}
}

int			all_hooks(t_data *data)
{
	t_data	*d;

	d = (t_data *)data;
	all_hooks_for_window(d->julia);
	all_hooks_for_window(d->mandel);
	all_hooks_for_window(d->newton);
	return (1);
}
