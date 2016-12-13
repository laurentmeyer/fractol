/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:48 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 16:43:57 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "mycomplex.h"
# define WIN_W 500
# define WIN_H 500
# define WIN_T "FractLOL"
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
void				julia_update_all(t_win *win, double cx, double cy);
void				mandel_update_all(t_win *win);
void				newton_update_all(t_win *win);
int					all_hooks(t_data *data);
int					display_image(t_data *data);




void	print_complex(t_fcomplex *c);
void	print_complex_array(t_fcomplex ***array);
void				print_data_details(t_data *data);
#endif
