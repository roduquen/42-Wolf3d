/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 22:03:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/14 11:57:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	set_magicint_and_long(unsigned int *mint, unsigned long *mlong
	, unsigned char c)
{
	*mint = c;
	*mint |= c << 8;
	*mint |= *mint << 16;
	*mlong = *mint;
	*mlong |= *mlong << 32;
}

static int	do_long_work(unsigned long mlong, size_t *len, unsigned long *slong)
{
	int			i;
	int			wait;
	int			tmp;

	i = 0;
	wait = (*len - *len % 8);
	*len -= wait;
	tmp = wait;
	wait /= 8;
	while (i < wait)
		slong[i++] = mlong;
	return (tmp);
}

static int	do_int_work(unsigned int mint, size_t *len, unsigned int *sint
	, int actual)
{
	int			i;
	int			wait;
	int			tmp;

	i = 0;
	wait = (*len - *len % 4);
	*len -= wait;
	tmp = wait;
	wait /= 4;
	while (i < wait)
		sint[actual + i++] = mint;
	return (tmp + actual);
}

static void	do_char_work(char c, size_t len, unsigned char *str, int actual)
{
	size_t		i;

	i = 0;
	while (i < len)
		str[actual + i++] = c;
}

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*setchar;
	unsigned long	*setlong;
	unsigned int	*setint;
	unsigned int	magicint;
	unsigned long	magiclong;

	if (len == 0)
		return (b);
	setchar = (unsigned char*)b;
	setint = (unsigned int*)b;
	setlong = (unsigned long*)b;
	set_magicint_and_long(&magicint, &magiclong, c);
	if (len >= 8)
		magiclong = do_long_work(magiclong, &len, setlong);
	if (len >= 4)
		magicint = do_int_work(magicint, &len, setint, magiclong * 2);
	if (len)
		do_char_work(c, len, setchar, magicint * 4);
	return (b);
}

#include <stdlib.h>

int		main()
{
	char *str;

	str = malloc(10000);
	ft_memset(str, 48, 12);
	str[12] = 0;
	printf("%s", str);
	free(str);
	return (0);
}
