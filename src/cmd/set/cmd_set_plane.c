/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				cmd_set_plane_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->container == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cone_default(): was given a NULL pointer"));
	parser->object->content.container.shape_type = SHP_PLANE;
	parser->object->visible = TRUE;
	parser->object->type = OBJ_CONTAINER;
	parser->material = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME);
	parser->texture = scn_get_txr_by_name(rt->scene, DEFAULT_TEXTURE_NAME);
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg			cmd_set_plane_read(t_rt *rt, t_parser *parser, t_obj *dest)
{
	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (cmd_set_error(parser, "cmd_set_plane(): bad syntax"));
		if (cmd_read_transform_part(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_plane(): bad syntax transform"));
		if (cmd_set_obj_visibility(parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_plane(): bad syntax visibility"));
		if (cmd_set_obj_grp(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_plane(): bad syntax group"));
		if (cmd_set_obj_mat(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_plane(): bad syntax material"));
		if (cmd_set_obj_name(rt, parser) < 0)
			return (cmd_set_error(parser, ""
			"cmd_set_plane(): bad syntax name or name collision"));
	}
	return (cmd_set_obj_to_scn(rt, parser, dest));
}

t_msg			cmd_set_plane(t_rt *rt, t_parser *parser, t_obj *dest)
{
	if (rt == NULL || parser == NULL)
		return (msg_err("cmd_add_plane(): given NULL pointer in cmd_add()"));
	if (cmd_set_prepare_obj(parser, dest))
		return (msg_err("cmd_set_cone(): critical malloc error"));
	return (cmd_set_plane_read(rt, parser, dest));
}
