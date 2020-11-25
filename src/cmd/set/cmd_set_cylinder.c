//
// Created by Hugor Chau on 11/23/20.
//

#include "rt.h"

static int			cylinder_set_length(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-l"))
	{
		parser->cur += ft_strlen("-l");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cylinder.length))
			return (-1);
	}
	return (0);
}

static int			cylinder_set_radius(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		if (cmd_read_num(&parser->cur, &parser->container->shape.cylinder.radius))
			return (-1);
	}
	return (0);
}

int					cmd_set_cylinder_default(t_rt *rt, t_parser *parser)
{
	if (parser == NULL || parser->container == NULL || parser->object == NULL ||
		parser->transform == NULL)
		return (rt_err("cmd_set_cylinder_default(): was given a NULL pointer"));
	ft_bzero(parser->transform, sizeof(t_tfm));
	parser->container->shape.cylinder.radius = 0.0;
	parser->container->shape.cylinder.length = 0.0;
	parser->object->visible = TRUE;
	parser->object->content.container.shape_type = SHP_CYLINDER;
	parser->object->type = OBJ_CONTAINER;
	parser->material = scn_get_mat_by_name(rt->scene, DEFAULT_MATERIAL_NAME);
	parser->texture = scn_get_txr_by_name(rt->scene, DEFAULT_TEXTURE_NAME);
	parser->group = rt->scene->main_group;
	return (0);
}

t_msg				cmd_set_cylinder_read(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp;

	while (*parser->cur != '\0' && *parser->cur != '\n')
	{
		if (cmd_read_space_req(&parser->cur))
			return (msg_warn("cmd_set_cylinder(): bad syntax1"));
		if (cylinder_set_radius(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in rad"));
		if (cylinder_set_length(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in length"));
		if (cmd_read_transform_part(parser) < 0)
			return (msg_warn("cylinder_parse_flags(): bad syntax in transform"));
		if (cmd_set_visibility(parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
		if (cmd_set_grp(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax group"));
		if (cmd_set_material(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax material"));
		if (cmd_set_name(rt, parser) < 0)
			return (msg_warn("cmd_set_obj_attributes: bad syntax visibility"));
	}
	tmp = scn_get_obj_by_name(rt->scene, parser->object->name);
	ft_memcpy(tmp, parser->object, sizeof(t_obj));
	tmp->name = parser->name;
	tmp->content.container.material = parser->material;
	if (parser->group != tmp->parent)
		scn_move_obj(rt->scene, parser->group, tmp);
	return (msg_oks("it works!"));
}

t_msg				cmd_set_cylinder(t_rt *rt, t_parser *parser)
{
	t_obj		*tmp;

	if (parser == NULL)
		return(msg_err("cmd_add_camera(): given NULL pointer in cmd_add()"));
	if (cmd_read_space_req(&parser->cur))
		return (msg_warn("cmd_add_camera(): bad syntax"));
	if (cmd_read_string(&(parser->cur), &(parser->name)))
		return (msg_warn("cmd_add_camera(): bad name"));
	if (!(tmp = scn_get_obj_by_name(rt->scene, parser->name)))
		return (msg_warn("cmd_set_cylinder(): couldn\'t find object"));
	if (tmp->type != OBJ_CONTAINER || tmp->content.container.shape_type != SHP_CYLINDER)
		return (msg_warn("cmd_set_cylinder(): object is not a cylinder"));
	if (!(parser->object = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (msg_err("cmd_set_cylinder(): malloc error"));
	ft_memcpy(parser->object, tmp, sizeof(t_obj));
	parser->name = ft_strdup(tmp->name);
	parser->transform = &parser->object->transform;
	parser->material = tmp->content.container.material;
	return (cmd_set_cylinder_read(rt, parser));
}
