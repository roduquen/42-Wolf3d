/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 22:03:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:45:47 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*setter;

	if (len == 0)
		return (b);
	setter = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		setter[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
