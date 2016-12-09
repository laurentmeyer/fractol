/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:54:18 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/08 18:20:44 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mycomplex.h"
#include <stdlib.h>
#include <math.h>

t_fcomplex		*fcomplex_new(double real, double imaginary)
{
	double	*new;

	if (!(new = (double *)malloc(2 * sizeof(double))))
		return (0);
	new[0] = real;
	new[1] = imaginary;
	return ((t_fcomplex *)new);
}

double			fcomplex_modulus(t_fcomplex *c)
{
	return (sqrt((*c)[0] * (*c)[0] + (*c)[1] * (*c)[1]));
}

void			fcomplex_multiply_to(t_fcomplex *at, t_fcomplex *c)
{
	double	tmpr0;
	double	tmpr1;
	double	tmpi0;
	double	tmpi1;

	tmpr0 = (*at)[0];
	tmpr1 = (*c)[0];
	tmpi0 = (*at)[1];
	tmpi1 = (*c)[1];
	(*at)[0] = tmpr0 * tmpr1 - tmpi0 * tmpi1;
	(*at)[1] = tmpr0 * tmpi1 + tmpr1 * tmpi0;
}

void			fcomplex_multiply_to_f(t_fcomplex *at, double r, double i)
{
	double	tmpr0;
	double	tmpi0;

	tmpr0 = (*at)[0];
	tmpi0 = (*at)[1];
	(*at)[0] = tmpr0 * r - tmpi0 * i;
	(*at)[1] = tmpr0 * i + r * tmpi0;
}

void			fcomplex_add_to(t_fcomplex *at, t_fcomplex *c)
{
	double	tmpr0;
	double	tmpr1;
	double	tmpi0;
	double	tmpi1;

	tmpr0 = (*at)[0];
	tmpr1 = (*c)[0];
	tmpi0 = (*at)[1];
	tmpi1 = (*c)[1];
	(*at)[0] = tmpr0 + tmpr1;
	(*at)[1] = tmpi0 + tmpi1;
}

void			fcomplex_add_to_f(t_fcomplex *at, double r, double i)
{
	double	tmpr0;
	double	tmpi0;

	tmpr0 = (*at)[0];
	tmpi0 = (*at)[1];
	(*at)[0] = tmpr0 + r;
	(*at)[1] = tmpi0 + i;
}
