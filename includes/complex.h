/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     complex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:26:05 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:42:00 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

typedef	struct	s_c
{
	double		r;
	double		i;
}				t_c;


t_c				c_mul(t_c a, t_c b);
t_c				c_add(t_c a, t_c b);
t_c				c_div(t_c num, t_c den);

#endif
