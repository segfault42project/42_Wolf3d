/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:40:10 by rabougue          #+#    #+#             */
/*   Updated: 2016/05/14 00:26:48 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Wolf3d.h"

	int world_map[MAPWIDTH][MAPHEIGHT] =
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

void	close_window(t_sdl_win *win)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	SDL_Quit();
}

void	sdl_clear(t_sdl_win *win)
{
	SDL_SetRenderDrawColor(win->render, 0, 0, 0, 0);
	SDL_RenderClear(win->render);
	SDL_RenderPresent(win->render);
}

int main(int argc, char **argv)
{
	t_sdl_win	win;
	SDL_Rect	rectangle;
	t_init		init;
	SDL_Event	event;

	double	pos_x = 22;
	double	pos_y = 12;
	double	dir_x = -1;
	double	dir_y = 0;
	double	plane_x = 0;
	double	plane_y = 0.66;
	int		width = 1920;
	int		height = 1080;
	int		x = 0;
	init_window("Wolf3d", width, height, &win);

	while (win.loop)
	{
		while(x < width)
		{
			double	camera_x = 2 * x / (double)width - 1;
			double	ray_pos_x = pos_x;
			double	ray_pos_y = pos_y;
			double	ray_dir_x = dir_x + plane_x * camera_x;
			double	ray_dir_y = dir_y + plane_y * camera_x;
			int		map_x = (int)ray_pos_x;
			int		map_y = (int)ray_pos_y;
			double	side_dist_x;
			double	side_dist_y;
			double	delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
			double	delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
			double	perp_wall_dist;
			int		step_x;
			int		step_y;
			int		hit = 0;
			int		side;
			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (ray_pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - ray_pos_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (ray_pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - ray_pos_y) * delta_dist_y;
			}
			while (hit == 0)
			{
				if (side_dist_x < side_dist_y)
				{
					side_dist_x += delta_dist_x;
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += delta_dist_y;
					map_y += step_y;
					side = 1;
				}
				if (world_map[map_x][map_y] > 0)
					hit = 1;
				if (side == 0)
					perp_wall_dist = (map_x - ray_pos_x + (1 - step_x) / 2) / ray_dir_x;
				else
					perp_wall_dist = (map_y - ray_pos_y + (1 - step_y) / 2) / ray_dir_y;
				int	line_height = (int)(height / perp_wall_dist);
				int	draw_start = -line_height / 2 + height / 2;
				if (draw_start < 0)
					draw_start = 0;
				int	draw_end = line_height / 2 + height / 2;
				if (draw_end >= height)
					draw_end = height -1;
				unsigned char	red;
				unsigned char	green;
				unsigned char	blue;
				unsigned char	alpha;
				if (world_map[map_x][map_y] == 1)
				{
					red = 255;
					green = 0;
					blue = 0;
					alpha = 255;
				}
				else if (world_map[map_x][map_y] == 2)
				{
					red = 0;
					green = 255;
					blue = 0;
					alpha = 255;
				}
				else if (world_map[map_x][map_y] == 3)
				{
					red = 0;
					green = 0;
					blue = 255;
					alpha = 255;
				}
				else if (world_map[map_x][map_y] == 4)
				{
					red = 255;
					green = 255;
					blue = 255;
					alpha = 255;
				}
				else
				{
					red = 0;
					green = 0;
					blue = 0;
					alpha = 255;
				}
				if (side == 1)
				{
					red /= 2;
					green /= 2;
					blue /= 2;
				}
				SDL_SetRenderDrawColor(win.render, red, green, blue, 255);
				SDL_RenderDrawLine(win.render, x, draw_start, x, draw_end);
			}
			x++;
		}
		x = 0;
		double	move_speed = 0.2;
		double	rot_speed = 0.1;
		double old_dir_x;
		double old_plane_x;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				win.loop = 0;
			if (SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					win.loop = 0;
				if (event.key.keysym.sym == SDLK_w)
				{
					if (world_map[(int)(pos_x + dir_x * move_speed)][(int)pos_y] == 0)
						pos_x += dir_x * move_speed;
					if (world_map[(int)pos_x][(int)(pos_y + dir_y * move_speed)] == 0)
						pos_y += dir_y * move_speed;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					if (world_map[(int)(pos_x - dir_x * move_speed)][(int)pos_y] == 0)
						pos_x -= dir_x * move_speed;
					if (world_map[(int)pos_x][(int)(pos_y - dir_y * move_speed)] == 0)
						pos_y -= dir_y * move_speed;
				}
				old_dir_x = dir_x;
				old_plane_x = plane_x;
				if (event.key.keysym.sym == SDLK_d)
				{
					dir_x = dir_x * cos(-rot_speed) - dir_y * sin(-rot_speed);
					dir_y = old_dir_x * sin(-rot_speed) + dir_y * cos(-rot_speed);
					plane_x = plane_x * cos(-rot_speed) - plane_y *sin(-rot_speed);
					plane_y = old_plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed);
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
					dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
					plane_x = plane_x * cos(rot_speed) - plane_y *sin(rot_speed);
					plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
				}
			}
		}
		SDL_RenderPresent(win.render);
	}
	close_window(&win);
	return (0);
}
