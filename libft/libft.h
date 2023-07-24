/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:49:45 by abouram           #+#    #+#             */
/*   Updated: 2023/07/22 17:08:47 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*key_exp;
	char			*key;
	char			*value;
	char			*all;
	char			*ex_status;
	struct s_list	*next;
	int				y;
	int				x;
}					t_list;

int					ft_strcmp(char *s1, char *s2);
char				*ft_itoa(int n);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
long				ft_atoi(char *str, int *max);
int					ft_strlen(char *s);
char				*ft_strdup(char *s1);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strchr(char *s, int c);
int					ft_strchr2(char *s, char c, int end);
char				*ft_strchr_inc(char *s, int c);
char				*ft_strrchr(char *s, int c);
char				**ft_split(char *s, char c);
char				**ft_split_origin(char *s, char c);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memchr(void *s, int c, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
int					ft_memcmp(void *s1, void *s2, size_t n);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcat(char *dst, char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strnstr(char *haystack, char *needle, size_t len);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
char				*ft_strjoin_new(char *s1, char *s2, int x, int j);
char				*ft_strjoin_no_free(char *s1, char *s2);
int					ft_compare(char *dst, char *src);
long				ft_atoi_origin(char *str);
#endif