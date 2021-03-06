/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_set_read_attributes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:49:57 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/20 20:10:05 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** `-v` - visibility. Should be valid string - "true" or "false"
** `-n` - name. Should be valid string - name
** `-m` - material. Should be valid string - name of material
** `-g` - group. Should be valid string - name of group
*/

int				cmd_set_obj_visibility(t_parser *parser)
{
	int			quotes;

	if (ft_str_next_is(parser->cur, "-v"))
	{
		parser->cur += ft_strlen("-v");
		cmd_read_space(&parser->cur);
		quotes = ft_str_next_is(parser->cur, "\"");
		parser->cur += quotes;
		if (ft_str_next_is(parser->cur, "true"))
		{
			parser->object->visible = TRUE;
			parser->cur += ft_strlen("true");
		}
		else if (ft_str_next_is(parser->cur, "false"))
		{
			parser->object->visible = FALSE;
			parser->cur += ft_strlen("false");
		}
		else
			return (rt_err("cmd_set_visibility(): Bad syntax"));
		if (quotes == 1 && !(ft_str_next_is(parser->cur, "\"")))
			return (rt_err("cmd_set_obj_visibility(): Bad syntax"));
		parser->cur += quotes;
	}
	return (0);
}

int				cmd_set_obj_name(t_rt *rt, t_parser *parser)
{
	char		*tmp;

	if (ft_str_next_is(parser->cur, "-n"))
	{
		parser->cur += ft_strlen("-n");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &tmp))
			return (rt_err("cmd_add_sphere(): bad name"));
		if (scn_name_check(rt->scene, tmp))
		{
			ft_free(tmp);
			return (rt_err("cmd_set_name(): name collision"));
		}
		ft_free(parser->name);
		parser->name = tmp;
	}
	return (0);
}

int				cmd_set_obj_mat(t_rt *rt, t_parser *parser)
{
	char		*material_name;
	t_mat		*material;

	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(material_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		if ((material = scn_get_mat_by_name(rt->scene, material_name)) == NULL)
		{
			ft_free(material_name);
			return (rt_err("cmd_set_obj_mat(): material with given "
			"name does not exist"));
		}
		ft_free(material_name);
		parser->material = material;
	}
	return (0);
}

int				cmd_set_obj_grp(t_rt *rt, t_parser *parser)
{
	char		*group_name;
	t_obj		*group;

	if (ft_str_next_is(parser->cur, "-g"))
	{
		parser->cur += ft_strlen("-g");
		if (cmd_read_space_req(&parser->cur))
			return (rt_err("cmd_set_name(): Bad syntax"));
		if (cmd_read_string(&(parser->cur), &(group_name)))
			return (rt_err("cmd_add_sphere(): bad name"));
		if ((group = scn_get_obj_by_name(rt->scene, group_name)) == NULL)
		{
			ft_free(group_name);
			return (rt_err("cmd_add_sphere(): couldn't find group"));
		}
		if (group->type != OBJ_GROUP)
		{
			ft_free(group_name);
			return (rt_err("cmd_add_sphere(): object with given"
			" name is not a group"));
		}
		parser->group = group;
		ft_free(group_name);
	}
	return (0);
}
