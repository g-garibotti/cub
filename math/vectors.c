/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:08 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/12 13:56:33 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_vector_length(double x, double y)
{
	return (sqrt(x * x + y * y));
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = get_vector_length(*x, *y);
	if (length != 0)
	{
		*x = *x / length;
		*y = *y / length;
	}
}

double	get_vector_angle(double x, double y)
{
	double	angle;

	angle = atan2(y, x);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

// Calculate perpendicular vector (rotate 90 degrees clockwise)
void	get_perpendicular(double *x, double *y)
{
	double	temp;

	temp = *x;
	*x = *y;
	*y = -temp;
}
