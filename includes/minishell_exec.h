/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:31:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/21 13:21:23 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include "../minishell.h"

typedef struct s_process {
	int		*status;
	int		pid;
	int		i;
	int		pipe_cnt;
	int		temp_fd;
	int		fd[2];
}	t_process;

typedef struct s_fd {
	int	std_input;
	int	std_output;
}	t_fd;

typedef enum e_node {
	CMD = 0,
	PIPE = 1,
	REDIRECT = 2	
}	t_node;

typedef enum e_redirec {
	HEREDOC = 3,
	APPEND = 4,
	INPUT = 5,
	OUTPUT = 6,
}	t_redirec;

typedef enum e_signal{
	PARENT = 8,
	CHILD = 9,
	IGNORE = 10
}	t_signal;


void	write_in_tmp_file(char *res, char *new_file_name);
void	child_to_do(t_list *finder, t_process *process, t_data *data);
char	*ft_getenv(char *name, char **envp);
char	*assemble_cmd_path(void *cmds, char **envp_path);
void	cmd_handler(t_list *finder, t_data *data, t_process *process, t_fd *backup);
int		execute_main(t_list **head, t_data *data);
int		how_many_pipes(t_list *finder);
t_list	*push_list_to_back(t_list *finder);
void	first_child_process(int read_end, int write_end, int pipe_cnt);
void	middle_child_process(int temp_fd, int read_end, int write_end);
void	last_child_process(int temp_fd, int read_end, int write_end);
void	first_or_middle_or_last_child(t_process *process);
void	parent_to_do(t_process *process);
int		redirect_input(t_list *finder);
int		redirect_output(t_list *finder);
int		redirect_output_append(t_list *finder);
int		redirec_handler(t_list *finder);
int		check_cmd(t_list **head, t_data *data);
int		how_many_cmds(t_list *finder);
void	wait_child(int child_cnt, t_data *data);

//heredoc
void	heredoc_handler(t_list *finder, t_data *data);
void	convert_delimeter_to_file(t_list *finder, t_data *env);
char	*new_tmp_file(t_redirect *redirec, int i, t_data *env);
void	find_heredoc_and_get_input(t_list *finder);
void	write_in_file(char *res, t_redirect *redirec);
char	*get_input(t_redirect *redirec);
char	*append_input(char *origin, char *input);
char	*append_newline(char *input);

//signal
void	signal_handler(int flag);
void	signal_parent(void);
void	signal_child(void);
void	signal_heredoc(void);
void	signal_ignore(void);
void	sigterm_handler(char *nl, int flag);

//builtin
void	builtin_handler(t_cmd *cmd_ary, t_env **head, t_process *process, t_data *data);
int		is_it_builtin(t_cmd *cmd_ary);


int		pre_processor(t_list *finder, t_data *data, t_process *process);
void	unlink_heredoc_files(t_list *finder);
char	*error_header(char *input);


#endif
