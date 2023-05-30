/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:47:51 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 11:51:01 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;

	chr = 0;
	while (*s)
	{
		if (*s == (char)c)
			chr = (char *)s;
		s++;
	}
	if (chr && *chr == (char)c)
		return (chr);
	if (!chr && !c)
		return ((char *)s);
	return (0);
}
