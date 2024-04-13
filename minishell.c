/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 21:41:57 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int signal_value = 0;

int	main(int argc, char **argv, char **envp)
{
	
	const char	*prompt_msg = "minishell$ ";
	// char		*prompt_cnt;
	t_list		*head;
	t_env		*env_head;
	char		**res;
	char		*nl;
	t_data		*data;

	struct termios term;

    //현재 터미널 속성 가져오기
    if (tcgetattr(STDIN_FILENO, &term) != 0) {
        perror("tcgetattr");
        return 1;
    }

	//ECHOCTL 안 나타나도록 설정
	term.c_lflag &= ~ECHOCTL;

	//uncanonical mode로 설정
	// term.c_lflag &= ~(ICANON | ECHO);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;

    // 변경된 터미널 속성 적용
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0) {
        // perror("tcsetattr");
        return 1;
    }
	argc = 0;
	argv = 0;
	rl_catch_signals = 0;
	head = NULL;
	env_head = NULL;
	init_envp(&env_head, envp);
	rl_clear_history();
	signal_handler_parent();
	data = malloc(sizeof(t_data));
	data->splitted_exec_path = ft_split(ft_getenv("PATH", envp), ':');
	data->env_head = &env_head;

	int i = 0;
	char *cnt;
	cnt = ft_itoa(i);
	char *prompt_check = ft_strjoin(prompt_msg, cnt);
	nl = readline(prompt_check);
	add_history(nl);
	i++;
	while (nl)
	{
		res = split_cmds(nl, &env_head);
		parse_to_node(&head, res);
		if (head != NULL && check_cmd(&head, data))
			execute_main(&head, data);
		free(nl);
		clear_head(&head);

		cnt = ft_itoa(i);
		prompt_check = ft_strjoin(prompt_msg, cnt);
		nl = readline(prompt_check);
		add_history(nl);
		i++;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	{
		// perror("tcsetattr");
		return 1;
	}
}
