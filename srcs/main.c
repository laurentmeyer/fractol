/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 13:32:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/13 14:09:21 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <stdio.h>

long	fractal_masks(int ac, char **av)
{
	int		i;
	long	m;

	i = 1;
	m = 0;
	while ((i + 1) < ac)
	{
		if (ft_strequ(av[i], "-f") && ft_strequ(av[i + 1], "julia"))
			m |= JULIA_MASK;
		if (ft_strequ(av[i], "-f") && ft_strequ(av[i + 1], "mandelbrot"))
			m |= MANDEL_MASK;
		if (ft_strequ(av[i], "-f") && ft_strequ(av[i + 1], "newton"))
			m |= NEWTON_MASK;
		++i;
	}
	printf("mask = %ld\n", m);
	return (m);
}

int		main(int ac, char **av)
{
	t_data	*data;
	long	masks;

	if (!(masks = fractal_masks(ac, av)))
	{
		ft_putstr("usage : fractol -f (julia | mandelbrot | newton) ...\n");
		return (0);
	}
	if ((data = init_data(masks)))
	{
		printf("youhou\n");
		display_image(data);
	}
	return (0);
}
