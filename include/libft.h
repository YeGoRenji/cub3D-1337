/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:21:49 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 17:07:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct e_map_line
{
	char				*line;
	size_t				len;
	struct e_map_line	*next;
}						t_map_line;

void					*ft_malloc(unsigned long size);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isdigit_string(char *str);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
size_t					ft_strlen(const char *s);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
int						ft_tolower(int c);
int						ft_toupper(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
int						ft_strcmp(char *s1, char *s2);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t					ft_strlcat(char *dest, const char *src, size_t dstsize);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
int						ft_atoi(const char *str);
char					*ft_itoa(int nbr);
void					*ft_calloc(size_t count, size_t size);
char					*ft_strdup(const char *s1);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
char					**ft_split(char const *s, char c);
void					*free_list(char **list);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
t_list					*ft_lstnew(void *content);
int						ft_lstsize(t_list *lst);
void					ft_lstadd_back(t_map_line **lst, t_map_line *_new);
void					ft_lstadd_front(t_list **lst, t_list *_new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_map_line				*ft_lstlast(t_map_line *lst);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
char					*get_next_line(int fd);
#endif
