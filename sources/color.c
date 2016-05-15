/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 14:16:13 by rabougue          #+#    #+#             */
/*   Updated: 2016/05/15 17:24:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Wolf3d.h"

void	red(t_wolf *wolf)
{
	wolf->red = 255;
	wolf->green = 95;
	wolf->blue = 0;
	wolf->alpha = 255;
}

void	green(t_wolf *wolf)
{
	wolf->red = 150;
	wolf->green = 170;
	wolf->blue = 100;
	wolf->alpha = 255;
}

void	blue(t_wolf *wolf)
{
	wolf->red = 0;
	wolf->green = 0;
	wolf->blue = 255;
	wolf->alpha = 255;
}

void	white(t_wolf *wolf)
{
	wolf->red = 255;
	wolf->green = 255;
	wolf->blue = 255;
	wolf->alpha = 255;
}

void	defaut(t_wolf *wolf)
{
	wolf->red = 0;
	wolf->green = 0;
	wolf->blue = 0;
	wolf->alpha = 255;
}
