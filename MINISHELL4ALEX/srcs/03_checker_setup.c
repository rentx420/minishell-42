/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_checker_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:47:49 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:47:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_checker  *ft_setup_checker(char **input)
{
	t_checker	*checker;
	t_checker	*next_checker;
	int			idx;

	idx = 0;
	checker = NULL;
	while (input[idx])
	{
		next_checker = ft_create_node(input[idx], idx);
		if (!next_checker)
			break ;
		ft_append_end(&checker, next_checker);
		idx++;
	}
	ft_free_spltinput(input);
	return (checker);
}

t_checker	*ft_create_node(char *input, int idx)
{
    t_checker *new_node;

    new_node = (t_checker *)malloc(sizeof(t_checker));
    if (!new_node)
        return (NULL);
    new_node->data = strdup(input);
    if (!new_node->data)
    {
        free(new_node);
        return (NULL);
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->data_type = ft_datatype(input);
    new_node->pos = idx;

    return (new_node);
}

void	ft_append_end(t_checker **checks, t_checker *new_node)
{
    t_checker *last;

    if (!new_node)
        return;
    if (*checks == NULL)
    {
        *checks = new_node;
        return;
    }
    last = *checks;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
}

int ft_datatype(char *input)
{
    if (ft_is_cmd(input) == 1)
        return (1);
    else if (input[0] == '|' && !input[1])
        return (2);
    else if (access(input, R_OK) == 0)
        return (3);
    else if (input[0] == '-' && input[1])
        return (4);
    else if (input[0] == '<' || input[0] == '>')
        return (5);
    else
        return (6);
}
