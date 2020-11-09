/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:25:33 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/04 21:04:23 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				rt_init(t_rt **rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	*rt = (t_rt*)malloc(sizeof(t_rt));
	if (*rt == NULL)
		return (rt_err("rt malloc fail"));
	if (gpu_init(*rt))
		return (rt_warn("gpu_init() fail"));
	return (0);
}

int				rt_deinit(t_rt *rt)
{
	if (rt == NULL)
		return (rt_err("rt is NULL pointer"));
	free(rt);
	return (0);
}
