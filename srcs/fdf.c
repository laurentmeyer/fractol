/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:26:40 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:50:33 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define FILENAME "fractol.fdf"

static void		itoa_to(char buffer[5], unsigned int u, int i)
{
	int		p;

	ft_memset(buffer, ' ', 4);
	p = 4;
	buffer[p--] = '\0';
	buffer[p--] = (i + 1) % WIN_W == 0 ? '\n' : ' ';
	buffer[p--] = u % 10 + '0';
	u /= 10;
	while (u)
	{
		buffer[p--] = u % 10 + '0';
		u /= 10;
	}
}

void			export_fdf(t_win *win)
{
	int		fd;
	char	buffer[WIN_H * WIN_W * 4 + 1];
	char	itoa_buff[12];
	int		i;

	unlink(FILENAME);
	if (win && (fd = open(FILENAME, O_WRONLY | O_CREAT,
					S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		exit(0);
	i = 0;
	while (i < WIN_H * WIN_W)
	{
		itoa_to(itoa_buff, ((unsigned char*)(win->img_addr))[i * 4] +
				((unsigned char*)(win->img_addr))[i * 4 + 1] +
				((unsigned char*)(win->img_addr))[i * 4 + 2] +
				((unsigned char*)(win->img_addr))[i * 4 + 3], i);
		ft_memcpy(buffer + (4 * i++), itoa_buff, 4);
	}
	buffer[WIN_H * WIN_W * 4] = '\0';
	write(fd, buffer, WIN_H * WIN_W * 4);
	close(fd);
}
