/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:54:18 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:42:33 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.h"

t_c		c_mul(t_c a, t_c b)
{
	t_c		ret;

	ret.r = a.r * b.r - a.i * b.i;
	ret.i = a.r * b.i + a.i * b.r;
	return (ret);
}

t_c		c_add(t_c a, t_c b)
{
	t_c		ret;

	ret.r = a.r + b.r;
	ret.i = a.i + b.i;
	return (ret);
}

t_c		c_div(t_c num, t_c den)
{
	double	norm;

	num = c_mul(num, (t_c){den.r, -den.i});
	norm = den.r * den.r + den.i * den.i;
	num.r /= norm;
	num.i /= norm;
	return (num);
}
