/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:31:32 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 10:39:54 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*free_funct(t_list *lst, void (*del)(void *))
{
	t_list	*elem;

	while (lst)
	{
		elem = lst->next;
		(*del)(lst->content);
		free(lst);
		lst = elem;
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*last;

	if (!lst)
		return (0);
	newlst = malloc(sizeof(t_list));
	if (!newlst)
		return (0);
	newlst->content = (*f)(lst->content);
	newlst->next = 0;
	last = newlst;
	lst = lst->next;
	while (lst)
	{
		last->next = malloc(sizeof(t_list));
		if (!(last->next))
			return (free_funct(newlst, (*del)));
		last = last->next;
		last->content = (*f)(lst->content);
		lst = lst->next;
	}
	last->next = 0;
	return (newlst);
}
