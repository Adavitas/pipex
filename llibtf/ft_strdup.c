/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:06:18 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/02 21:06:34 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		buffer_size;

	if (!s)
		return (NULL);
	buffer_size = ft_strlen(s) + 1;
	str = malloc(buffer_size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, buffer_size);
	return (str);
}
