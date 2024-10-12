/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:14:04 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/18 20:01:50 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	if (ft_memcmp(dst, src, n) == 0)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}
// int main()
// {
// 	int src[] = {0, 1, 5, 6}; 
// 	int dst[4];
// 	size_t size = sizeof(src) / sizeof(dst[0]);
// 	ft_memcpy(dst, src, size);
// 	for(size_t i = 0; i < size; i++)
// 		printf("%d ", dst[i]);
// }
