/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:31:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/06 19:03:25 by seongjko         ###   ########.fr       */
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


void	child_to_do(t_list *finder, t_process *process, t_data *env);
char	*ft_getenv(char *name, char **envp);
char	*joined_path(void *cmds, char **envp_path);
void	cmd_handler(t_list *finder, t_data *env);
int		execute_main(t_list **head, t_data *env);
int		how_many_pipes(t_list *finder);
t_list	*push_list(t_list *finder);
void	first_child_process(int read_end, int write_end, int pipe_cnt);
void	middle_child_process(int temp_fd, int read_end, int write_end);
void	last_child_process(int temp_fd, int read_end, int write_end);
void	first_or_middle_or_last_child(t_process *process);
char	*tmp_file_handling(char *here_doc_input, char *delimeter, int i);
char	*get_heredoc_input(char *delimeter, int i);
void	heredoc_pre_handler(t_list *finder);
void	parent_to_do(t_process *process);
void	redirect_input(t_list *finder);
void	redirect_output(t_list *finder);
void	redirect_output_append(t_list *finder);
void	redirec_handler(t_list *finder);
void	signal_handler(void);
int		check_cmd(t_list **head, t_data *env);
void    signal_handler_child(void);

#endif
