/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:48 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:49:23 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include "complex.h"
# define WIN_W 500
# define WIN_H 500
# define JULIA_MASK (1L << 0)
# define MANDEL_MASK (1L << 1)
# define NEWTON_MASK (1L << 2)

typedef struct		s_win
{
	void			*data;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				mouse_on;
	int				mouse_x;
	int				mouse_y;
	int				destroyed;
	double			posx_save;
	double			posy_save;
	double			win_hmin;
	double			win_hmax;
	double			win_wmin;
	double			win_wmax;
}					t_win;

typedef struct		s_data
{
	void			*ptr;
	t_win			*julia;
	t_win			*mandel;
	t_win			*newton;
}					t_data;

t_data				*init_data(long masks);
double				x_to_real(t_win *win, int x);
double				y_to_imaginary(t_win *win, int y);
void				pixel_put(t_win *win, int x, int y, int color);
void				julia_update_all(t_win *win, t_c c);
void				mandel_update_all(t_win *win);
void				newton_update_all(t_win *win);
int					all_hooks(t_data *data);
int					display_image(t_data *data);
void				update_window(t_win *win);
void				zoom(t_win *win, double ratio,
							double centerx, double centery);
void				move_win(t_win *win, int up, int left);
void				export_fdf(t_win *win);

#endif
