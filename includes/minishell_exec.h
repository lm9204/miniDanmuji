/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:31:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 19:15:24 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

#include <termios.h>
#include <sys/wait.h>
#include <signal.h>
#include "../minishell.h"

typedef struct s_process {
	int		*status;
	int		pid;
	int		i;
	int		pipe_cnt;
	int		temp_fd;
	int		fd[2];
}	t_process;

typedef enum e_node {
	CMD,
	PIPE,
	REDIRECT	
}	t_node;

typedef enum e_redirec {
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT,
	HEREINPUT,
}	t_redirec;


void	heredoc_pre_handler(t_list *finder);
void	check_heredoc(t_list *finder);
void	create_tmp_files(t_list *finder, int *is_heredoc);
void	new_tmp_file(char *delimeter, int i);
void	write_in_tmp_file(char *res, char *delimeter);
void	child_to_do(t_list *finder, t_process *process, t_data *env);
char	*ft_getenv(char *name, char **envp);
char	*joined_path(void *cmds, char **envp_path);
void	cmd_handler(t_list *finder, t_data *env);
int		execute_main(t_list **head, t_data *env);
int		how_many_pipes(t_list *finder);
t_list	*push_list_to_back(t_list *finder);
void	first_child_process(int read_end, int write_end, int pipe_cnt);
void	middle_child_process(int temp_fd, int read_end, int write_end);
void	last_child_process(int temp_fd, int read_end, int write_end);
void	first_or_middle_or_last_child(t_process *process);
void	parent_to_do(t_process *process);
void	redirect_input(t_list *finder);
void	redirect_output(t_list *finder);
void	redirect_output_append(t_list *finder);
void	redirec_handler(t_list *finder);
void	signal_handler_parent(void);
void    signal_handler_child(void);
void    signal_handler_heredoc(void);
int		check_cmd(t_list **head, t_data *env);
int		how_many_cmds(t_list *finder);
void    wait_child(int child_cnt);
void	delete_tmp_files(t_list *finder);

#endif
