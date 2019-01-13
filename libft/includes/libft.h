/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:10:16 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 02:39:04 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

/*
** ft_btree
*/

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

void				*ft_btree_find(t_btree *btree, const void *target, \
						int (*cmp)(const void *, const void *));
void				ft_btree_iter(t_btree *btree, void (*f)(void *));
void				ft_btree_del(t_btree **btree, void (*del)(void *));
void				ft_btree_recursivedel(t_btree **btree, void (*del)(void *));

/*
** ft_io
*/

void				ft_cat(const int fd);
void				ft_perr(const char *s);
void				ft_putchar(char c);
int					ft_puts(const char *s);
void				ft_putstr(char const *s);
int					ft_printf(const char *format, ...);

/*
** ft_maths
*/

int					ft_abs(int n);
int					ft_sqrt(unsigned int n);
int					ft_gcd(unsigned int a, unsigned int b);
int					ft_intlen(int n);
int					ft_pow(int n, unsigned int power);
int					ft_fac(unsigned int n);

/*
** ft_mem
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);

/*
** ft_str
*/

int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
long				ft_atol(const char *str);
long long			ft_atoll(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
void				ft_itoa_base_s(int value, int base, char *numb);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(char *s, int c);
int					ft_strchrn(char *str, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
int					ft_strequ(const char *s1, const char *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strlaststr(const char *big, const char *small);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
size_t				ft_strnlen(const char *s, const size_t n);
char				*ft_strnstr(const char *big, const char *small, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *small);
char				*ft_strtolower(char *str);
char				*ft_strtoupper(char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
size_t				ft_wcslen(wchar_t *s);

#endif
