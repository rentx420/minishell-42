/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:42:47 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 13:42:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_h

typedef struct s_checker
{
	struct s_checker	*prev;
	char				*data;
	int					data_type;
	int					pos;
	struct s_checker	*next;
}						t_checker;

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>

int					ft_strlen(char *string);
char				*ft_clean_input(char *pre_input);
char				*ft_create_input(char *old_input);
int					ft_error(int x);
void				ft_dollar_exp(char **input, int *dquotes);
void 				ft_new_input(char **input, int new_len);
int					ft_cpy_value(char **input, char *new_input, int *idx, int idy);
int					ft_var_newlen(char *input);
int					ft_var_len(char *input, int idx);
void				ft_elevate_doll(int *new_len, int *idx);
void				ft_init_doll(int *new_len, int *idx);
int	                ft_previous_checks(char *input, int dquotes);
int	                ft_atoi(const char *str);
int	                ft_strncmp(const char *str, const char *str2, size_t c);
int	                ft_builtin(char *input, char **envp);
void	            ft_exit_check(char *input);
int	                ft_exit_num(char *input);
int	                ft_env(char *input, char **envp);
int	                ft_pwd(char *input, char **envp);
int	                ft_unset(char *input, char **envp);
int	                ft_export(char *input, char **envp);
int	                ft_cd(char *input);
int	                ft_echo(char *input);
t_checker	        *ft_create_node(char *input, int idx);
t_checker           *ft_setup_checker(char **input);
void	            ft_free_spltinput(char **input);
void	            ft_init_minishell(char *input, char **envp);
int	                ft_check_input(t_checker *checker);
int	                ft_checks_00(t_checker *checker);
int	                ft_checks_01(t_checker *checker);
int	                ft_checks_02(int pipes_c, int cmd_c, int redir_c, int arch_c);
void	            ft_append_end(t_checker **checks, t_checker *new_node);
int                 ft_datatype(char *input);
int	                ft_is_cmd(char *input);
char	            *ft_strdup(const char *s1);
char		        **ft_split(char *s, char c);
char 				*ft_strtok(char *str, const char *delim);
char				*ft_strcat(char *dest, const char *src);
int 				ft_are_cmds(char *input);
void				ft_print_checker(t_checker *checker);
void				ft_free_checker(t_checker *checker);
void				ft_free_node(t_checker *node);
char				*ft_append_input(char *original, char *add);
int					ft_count_q(char *input, int x);
void				ft_heredoc(char *pre_input);
void				ft_remove_nl(char *pre_input);

#endif