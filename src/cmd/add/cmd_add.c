/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtacos <rtacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:20:28 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/14 17:18:08 by rtacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_msg				cmd_add_obj_to_scn(t_rt *rt, t_parser *parser)
{
	if (parser->object->type == OBJ_CONTAINER ||
			parser->object->type == OBJ_COPY)
	{
		parser->object->content.container.material = parser->material;
	}
	parser->object->transform.rot_local.x =
			vec3_normalize(parser->object->transform.rot_local.x);
	parser->object->transform.rot_local.y =
			vec3_normalize(parser->object->transform.rot_local.y);
	parser->object->transform.rot_local.z =
			vec3_normalize(parser->object->transform.rot_local.z);
	if (scn_add_to_group(rt->scene, parser->group, parser->object))
	{
		obj_deinit(parser->object);
		return (msg_warn("couldn\'t add obj to scene"));
	}
	return (msg_oks("added object to scene successfully"));
}

static t_msg		cmd_add_shape(t_rt *rt, t_parser *parser, char *str)
{
	if (ft_str_next_is(str, "sphere"))
		return (cmd_add_sphere(rt, parser));
	if (ft_str_next_is(str, "plane"))
		return (cmd_add_plane(rt, parser));
	if (ft_str_next_is(str, "cylinder"))
		return (cmd_add_cylinder(rt, parser));
	if (ft_str_next_is(str, "cone"))
		return (cmd_add_cone(rt, parser));
	return (msg_warn("Syntax error: Unknown object type"));
}

t_msg				cmd_add(t_rt *rt, t_parser *parser)
{
	char			*str;

	if (parser == NULL)
		return (msg_warn("Given NULL pointer in cmd_add()"));
	parser->cur += ft_strlen("add");
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("Bad syntax"));
	str = parser->cur;
	if (ft_str_next_is(str, "group"))
		return (cmd_add_group(rt, parser));
	if (ft_str_next_is(str, "camera"))
		return (cmd_add_camera(rt, parser));
	if (ft_str_next_is(str, "material"))
		return (cmd_add_material(rt, parser));
	if (ft_str_next_is(str, "light"))
		return (cmd_add_light(rt, parser));
	if (ft_str_next_is(str, "copy"))
		return (cmd_add_copy(rt, parser));
	if (ft_str_next_is(str, "texture"))
		return (cmd_add_txr(rt, parser));
	return (cmd_add_shape(rt, parser, str));
}
