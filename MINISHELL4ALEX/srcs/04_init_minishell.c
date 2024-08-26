/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:48:21 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:48:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_minishell(char *input, char **envp)
{
	t_checker	*checker;

	(void)envp;
	checker = ft_setup_checker(ft_split(input, ' '));
	// ft_print_checker(checker);
	if (ft_check_input(checker) == 1)
		printf("ALEX CURRO.\n");
	else
		printf("Syntax Error.\n");
	ft_free_checker(checker);
	return ;
}

int	ft_check_input(t_checker *checker)
{
	if (ft_checks_00(checker) == 1)
	{
		if (ft_checks_01(checker) == 1)
			return (1);
	}
	return (0);
}

int	ft_checks_00(t_checker *checker)
{
	t_checker	*curr;

	curr = checker;
	while (curr->next)
	{
		if (curr->data_type == 2 && (!curr->next || !curr->prev))
			return (0);
		else if (curr->prev && curr->data_type == 4 && curr->prev->data_type != 1)
			return (0);
        else if (curr->data_type == 2 && curr->next->data_type == 2)
            return (0);
        else if (curr->data_type == 4 && curr->next->data_type == 4)
            return (0);
        else if (curr == checker && curr->data_type == 2)
            return (0);
        else if (curr->next == NULL && curr->data_type == 2)
            return (0);
		if (curr->next)
			curr = curr->next;		
	}
	return (1);
}

int	ft_checks_01(t_checker *checker)
{
	int			pipes_count;
	int			cmd_count;
	int			redir_count;
	int			arch_count;
	t_checker	*curr;
	
	arch_count = 0;
	redir_count = 0;
	cmd_count = 0;
	pipes_count = 0;
	curr = checker;
	while (curr)
	{
		if (curr->data_type == 1)
			cmd_count++;
		if (curr->data_type == 2)
			pipes_count++;
		if (curr->data_type == 5)
			redir_count++;
		if (curr->data_type == 4)
			arch_count++;
		curr = curr->next;
	}
	return (ft_checks_02(pipes_count, cmd_count, redir_count, arch_count));
}

int	ft_checks_02(int pipes_c, int cmd_c, int redir_c, int arch_c)
{
	if (pipes_c >= cmd_c)
		return (0);
	if (redir_c > cmd_c)
		return (0);
	if (cmd_c == 0 && (redir_c > 0 || pipes_c > 0 || arch_c > 0))
		return (0);
	return (1);
}

void	ft_print_checker(t_checker *checker)
{
	while (checker)
	{
		printf("data -> %s\n", checker->data);
		printf("datatype -> %i\n", checker->data_type);
		printf("pos -> %i\n", checker->pos);
		printf("-----------------------\n");
		checker = checker->next;
	}
}

void	ft_free_checker(t_checker *checker)
{
	t_checker *temp;

	while (checker != NULL)
	{
		temp = checker;
		checker = checker->next;
		ft_free_node(temp);
	}
}

void	ft_free_node(t_checker *node)
{
	if (node)
	{
		free(node->data);
		free(node);
	}
}
