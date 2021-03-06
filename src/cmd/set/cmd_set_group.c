/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				cmd_set_group_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_group_default(): was given a NULL pointer"));
	parser->object->visible = TRUE;
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg			cmd_set_group_params(t_rt *rt,
				t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, "cmd_set_group(): bad syntax"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_group(): bad syntax transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_group(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_group(): bad syntax group"));
		if (cmd_set_obj_name(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_group(): bad syntax name"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg			cmd_set_group(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_group(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_group(): critical malloc error"));
	if (dest->parent == NULL)
		return (msg_warn("cmd_set_group(): can\'t modify main group. Stop."));
	return (cmd_set_group_params(rt, parser, dest));
}
