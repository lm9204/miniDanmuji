/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/06 22:02:21 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int signal_value = 0;

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	t_list		*head;
	t_env		*env_head;
	char		**res;
	char		*nl;
	t_data		*data;

	struct termios tty_orig, tty_new;

    // 현재 터미널 속성 가져오기
    if (tcgetattr(STDIN_FILENO, &tty_orig) != 0) {
        perror("tcgetattr");
        return 1;
    }

    // 새로운 터미널 속성 설정
    tty_new = tty_orig;

    // non-canonical 모드 설정
    // tty_new.c_lflag &= ~(ICANON);
	//ECHOCTL 안 나타나도록 설정
	tty_new.c_lflag &= ~ECHOCTL;
	//1로 설정하면 입력 버퍼에 1바이트 이상의 데이터가 있으면 read 호출이 반환됩니다.
    // tty_new.c_cc[VMIN] = 1;
	// 0으로 설정하면 타임아웃 없이 read 호출이 바로 반환됩니다.
    // tty_new.c_cc[VTIME] = 0;

    // 변경된 터미널 속성 적용
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty_new) != 0) {
        perror("tcsetattr");
        return 1;
    }

	argc = 0;
	argv = 0;
	rl_catch_signals = 0;
	head = NULL;
	env_head = NULL;
	init_envp(&env_head, envp);
	signal_handler();
	data = malloc(sizeof(t_data));
	data->envp = envp;
	data->splitted_envp_path = ft_split(ft_getenv("PATH", envp), ':');
	nl = readline(prompt_msg);
	while (nl)
	{
		res = split_cmds(nl, &env_head);
		parse_to_node(&head, res);
		if (head != NULL && check_cmd(&head, data))
        	execute_main(&head, data);
		// print_list(&head);
		free(nl);
		clear_head(&head);
		// printf("hello world?\n");
		nl = readline(prompt_msg);
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty_orig) != 0)
	{
		perror("tcsetattr");
		return 1;
	}
}
