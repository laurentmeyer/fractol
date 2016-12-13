/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:58:25 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 12:41:38 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdlib.h>
#define PIX_PER_LINE 20
#define PIX_PER_CHAR 10
#define WHITE 0xFFFFFF

#include <stdio.h>
void	print_complex(t_fcomplex *c)
{
	printf("%f + %f i\n", (*c)[0], (*c)[1]);
}

//void	print_complex_array(t_fcomplex ***array)
//{
//	int	x;
//	int	y;
//
//	y = 0;
//	while (y < WIN_H)
//	{
//		x = 0;
//		while (x < WIN_H)
//		{
//			printf("x = %d x = %d c = ", x, y);
//			print_complex(array[y][x]);
//			++x;
//		}
//		++y;
//	}
//}
//
//void	print_label(t_data *data, int line, char *label, double value)
//{
//	char *tmp;
//
//	if ((tmp = ft_itoa((int)value)))
//	{
//		mlx_string_put(data->ptr, data->win, 0,
//						line * PIX_PER_LINE, WHITE, label);
//		mlx_string_put(data->ptr, data->win, PIX_PER_CHAR * ft_strlen(label),
//				line * PIX_PER_LINE, WHITE, tmp);
//		free(tmp);
//	}
//}
//
//void	print_data_details(t_data *data)
//{
//	int		i;
//
//	i = 0;
//	print_label(data, i++, "   Mouse X: ", data->mouse_x);
//	print_label(data, i++, "   Mouse Y: ", data->mouse_y);
//}
