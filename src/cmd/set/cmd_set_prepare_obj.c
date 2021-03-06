/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_prepare_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			cmd_set_prepare_obj(t_parser *parser, t_obj *src)
{
	if (obj_init(&parser->object, parser->name, src->type))
		return (rt_err("cmd_set_cone(): malloc error"));
	ft_memcpy(parser->object, src, sizeof(t_obj));
	parser->group = parser->object->parent;
	parser->object->name = ft_strdup(parser->name);
	parser->transform = &parser->object->transform;
	parser->container = &parser->object->content.container;
	parser->material = src->content.container.material;
	return (0);
}
