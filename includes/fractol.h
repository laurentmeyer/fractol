/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:53:48 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/09 19:04:50 by lmeyer           ###   ########.fr       */
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

typedef struct		s_data
{
	void			*ptr;
	void			*win;
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
	t_fcomplex		***julia_pts;
}					t_data;

t_data				*init_data(void);
void				pixel_put(t_data *data, int x, int y, int color);
int					display_image(t_data *data);
void				print_data_details(t_data *data);
int					all_hooks(t_data *data);
void	julia_update_all(t_data *data, double cx, double cy);
void				mandel_update_all(t_data *data);




void	print_complex(t_fcomplex *c);
void	print_complex_array(t_fcomplex ***array);
double			x_to_real(t_data *data, int x);
double			y_to_imaginary(t_data *data, int y);
#endif
