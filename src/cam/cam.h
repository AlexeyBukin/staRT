//
// Created by Hugor Chau on 11/16/20.
//

#ifndef CAM_H
#define CAM_H

#include "cam_types.h"

//int		cam_init(t_cam **cam, char *name);
//int		cam_init_default(t_cam **dest);
//int		cam_deinit(t_cam *cam);
int		cam_deinit(t_obj *cam);
int		cam_init_default(t_obj **dest);
int		cam_init(t_obj **dest, char *name);

#endif //CAM_H
