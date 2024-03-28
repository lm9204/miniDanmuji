/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/24 14:54:43 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define EOF_G -2
# define NON_NL -1
# define READ_ERROR -3
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s, char const *s2);
char	*ft_strtrim(char const *s1, char const *s2);
char	*ft_allocword(char const *s, int size);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* ------------ gnl linked list ------------------*/
typedef struct s_gnl
{
	int				fd;
	int				nl_idx;
	char			*buf;
	struct s_gnl	*next;
}		t_gnl;

/* ------------ libft linked list ------------------*/
/* ------------ libft bonus ------------------*/
// int		ft_lstsize(t_list *lst);
// void	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_lstadd_front(t_list **lst, t_list *new);
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	*ft_lstclear(t_list **lst, void (*del)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// t_list	*ft_lstnew(void *content);
// t_list	*ft_lstlast(t_list *lst);

/* ------------ get_next_line ------------------*/
int		check_buffer(char *buf);
char	*get_next_line(int fd);
char	*alloc_line(t_gnl *node, int len);
char	*split_nl(t_gnl *node, int nl_idx);
void	fill_buffer(t_gnl *node, char **buf, int cur_len, int read_size);
void	delnode(t_gnl **lst, int fd);
t_gnl	*lstaddnew(t_gnl **lst, int fd);
t_gnl	*lstschfd(t_gnl **lst, int fd);

/* ------------ ft_printf ------------------*/
int		ft_printf(const char *arg, ...);
int		read_format(const char *arg, va_list *va_arg);
int		pr_num(va_list *args);
int		pr_uns(va_list *args);
int		pr_addr(va_list *args, const char *hex);
int		pr_hex(va_list *args, const char *hex);
int		pr_str(va_list *args);
int		pr_char(va_list *args);
void	print_format(char c, va_list *va_arg, int *totallen);
void	print_normal(const char *arg, int len, int *totallen);

#endif