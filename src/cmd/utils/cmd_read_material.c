
#include "rt.h"

/*
**	`-m` - metalness. Should be valid vector ????
**	`-r` - roughness. Should be be valid vector ????
**	`-i` - ior. Should be valid scalar
**	`-t` - transparency. Should be valid scalar
**	`-a` - albedo. Should be valid vector (values clamped 0..1)
**	`-f` - f0. Should be valid vector (values clamped 0..1)
*/

static int 		check_limited_vec(t_vec3 vec)
{
	if (vec.x < 0 || vec.x > 1.0
		|| vec.y < 0 || vec.y > 1.0
		|| vec.z < 0 || vec.z > 1.0)
		return (rt_err("cmd_read_material_limited_vecs(): "
					   "vec values should be clamped 0..1"));
	return (0);
}

static int 		cmd_read_material_limited_vecs(t_parser *parser)
{
	t_vec3			tmp;

	if (ft_str_next_is(parser->cur, "-a"))
	{
		parser->cur += ft_strlen("-a");
		cmd_read_space(&parser->cur);
		if (cmd_read_vec(&(parser->cur), &tmp))
			return (rt_err("couldn\'t parse vector"));
		if (check_limited_vec(tmp))
			return (-1);
		parser->material->content.pbr.albedo = tmp;
	}
	if (ft_str_next_is(parser->cur, "-f"))
	{
		parser->cur += ft_strlen("-f");
		cmd_read_space(&parser->cur);
		if (cmd_read_vec(&(parser->cur), &tmp))
			return (rt_err("couldn\'t parse vector"));
		if (check_limited_vec(tmp))
			return (-1);
		parser->material->content.pbr.f0 = tmp;

	}
	return (0);
}

int				cmd_read_material(t_parser *parser)
{
	if (ft_str_next_is(parser->cur, "-m"))
	{
		parser->cur += ft_strlen("-m");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.metalness)));
	}
	if (ft_str_next_is(parser->cur, "-r"))
	{
		parser->cur += ft_strlen("-r");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.roughness)));
	}
	if (ft_str_next_is(parser->cur, "-i"))
	{
		parser->cur += ft_strlen("-i");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.ior)));
	}
	if (ft_str_next_is(parser->cur, "-t"))
	{
		parser->cur += ft_strlen("-t");
		cmd_read_space(&parser->cur);
		return (cmd_read_num(&(parser->cur), &(parser->material->content.pbr.transparency)));
	}
	return (cmd_read_material_limited_vecs(parser));
}