/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:14:21 by bojung            #+#    #+#             */
/*   Updated: 2022/10/21 15:14:22 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_init(void)
{
	t_dll	*pdll;

	pdll = (t_dll *)malloc(sizeof(t_dll));
	pdll->head = NULL;
	pdll->tail = NULL;
	pdll->size = 0;
	return (pdll);
}

int	dll_isempty(t_dll *pdll)
{
	if (pdll->head == NULL)
		return (TRUE);
	else
		return (FALSE);
}

void	dll_clear(t_dll *pdll)
{
	int			i;
	t_dllnode	*rnode;

	i = 0;
	if (pdll->head != NULL)
	{
		while (i++ < pdll->size)
		{
			rnode = pdll->tail;
			if (pdll->head == pdll->tail)
				free(pdll->head);
			else
			{
				pdll->tail = rnode->prev;
				free(rnode);
				rnode = NULL;
			}
		}
	}
	free(pdll);
	pdll->head = NULL;
	pdll->tail = NULL;
	pdll = NULL;
}

// void	dll_print(t_dll *pdll1, t_dll *pdll2)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = pdll1->size - pdll2->size;
// 	while (i < pdll1->size || i < pdll2->size)
// 	{
// 		if (size > 0)
// 		{
// 			ft_printf("%5d", pdll1->head->data);
// 			pdll1->head = pdll1->head->next;
// 			if (size <= i++)
// 			{
// 				ft_printf("%5d", pdll2->head->data);
// 				pdll2->head = pdll2->head->next;
// 			}
// 			ft_printf("\n");
// 		}
// 		else
// 		{
// 			if (-size <= i++)
// 			{
// 				ft_printf("%5d", pdll1->head->data);
// 				pdll1->head = pdll1->head->next;
// 			}
// 			else
// 				ft_printf("     ");
// 			ft_printf("%5d", pdll2->head->data);
// 			pdll2->head = pdll2->head->next;
// 			ft_printf("\n");
// 		}
// 	}
// 	ft_printf("   --------\n");
// 	ft_printf("    a    b\n\n");
// }
