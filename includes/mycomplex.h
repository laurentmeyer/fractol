/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mycomplex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:26:05 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/14 16:42:00 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYCOMPLEX_H
# define MYCOMPLEX_H

typedef double	t_fcomplex[2];

t_fcomplex		*fcomplex_new(double real, double imaginary);
void			fcomplex_multiply_to_f(t_fcomplex *at, double r, double i);
void			fcomplex_add_to_f(t_fcomplex *at, double r, double i);
void			fcomplex_divide_to_f(t_fcomplex *at, double r, double i);

#endif
