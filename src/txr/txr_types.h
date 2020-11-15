/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:15:17 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/13 10:14:39 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TXR_TYPES_H
# define TXR_TYPES_H

typedef enum				s_txr_type
{
	TXR_NONE,
	TXR_BW_8,
	TXR_RGB_8
//	TXR_RGBA_8
}							t_txr_type;

typedef struct				s_texture
{
	t_id					id;
	char					*name;
	t_txr_type				type;
	size_t					w;
	size_t					h;
	size_t					stride;
	char					*content;
}							t_txr;

#endif
