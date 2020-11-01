/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rts.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:46:25 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/31 21:04:25 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTS_H
# define RTS_H

# include <gtk/gtk.h>
# include "libft.h"
# include "gpu_types.h"
# include "rt_scene.h"
# include "srv_types.h"

typedef struct		s_texture
{
	int					index;
	int					width;
	int					height;
	int					stride;
	t_texture_rgba		*data;
}					t_texture;

typedef struct		s_rt
{
	GtkApplication		*app;
	t_gpu				gpu;
	t_scn				*scene;
	t_texture			*render_result;
	t_srv				*server;
}					t_rt;

#endif
