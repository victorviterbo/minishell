/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:33:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 20:40:05 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <float.h>
# include <stdbool.h>
# include <stdarg.h>

typedef enum e_Inplace_Type {
	NOFREE,
	FREE_S1,
	FREE_S2,
	FREE_S1S2
}	t_Inplace_Type;

typedef enum e_Tree_Travel_Type {
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}	t_Tree_Travel_Type;

typedef enum e_Datatype {
	SHORT,
	INT,
	FLOAT,
	DOUBLE,
	BOOL,
	CHAR
}	t_Datatype;

typedef struct s_coor {
	double	x;
	double	y;
	double	z;
}	t_coor;

typedef struct s_list
{
	union
	{
		void	*content;
		int		i;
	};
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// CHARACTERS
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_iswhitespace_eq(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
// CONVERSIONS
int			ft_atoi(const char *str);
float		ft_atof(char *str);
char		*ft_ctoa(char c);
char		*ft_itoa_base(long long n, char *base);
char		*ft_itoa(int n);
int			ft_number_len(long long n, int base_size);
char		*ft_utoa_base(unsigned long number, char *base);
// LISTS
t_list		*ft_lst_getn(t_list **lst, int n);
t_list		*ft_lst_isin_int(t_list **lst, int elem);
t_list		*ft_lst_isin_void(t_list **lst, void *elem, int size);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstcut(t_list **lst, void (*del)(void *), int start, int end);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap_void(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
double		ft_lstmax(t_list **lst, int dtype);
int			ft_lstmaxi(t_list **lst);
double		ft_lstmin(t_list **lst, int dtype);
int			ft_lstmini(t_list **lst);
t_list		*ft_lstnew_int(int i);
t_list		*ft_lstnew_void(void *content);
int			ft_lstsize(t_list *lst);
// MATH
double		ft_abs(double n);
double		ft_dotprod(t_coor v1, t_coor v2);
t_coor		ft_initvec(double x, double y, double z);
double		ft_max(double a, double b);
double		ft_min(double a, double b);
double		ft_norm(t_coor vector);
double		ft_prev_power(double n, int base_size);
t_coor		ft_vecadd(t_coor v1, t_coor v2);
t_coor		ft_vecscale(t_coor base, t_coor tip, float scale);
t_coor		vec_substr(t_coor v1, t_coor v2);
t_coor		ft_vecsubstr(t_coor v1, t_coor v2);
// MEMORY
void		ft_bzero(void *s, unsigned int n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t len);
// MISC
char		**ft_array_append(char **array, char *str, bool first);
size_t		ft_arrlen(char **array);
void		ft_dummy(void *ptr);
void		ft_free_array(void **array, int size);
double		ft_parse_as(void *ptr, t_Datatype dtype);
void		ft_print_array(char **arr, bool nl);
char		**ft_strarray_mapi(char **strarray, char *(*f)(const char *));
void		ft_swap_void(void **ptr1, void **ptr2);
// STRINGS
char		*ft_coalesce_char(char *str, char c, bool inplace);
int			ft_count_charocc(char *str, char c);
int			ft_count_strocc(char *str, char *to_count, bool distinct);
int			ft_isfloat(char *str);
int			ft_isint(char *str);
char		**ft_split(char const *s, char c);
char		*ft_str_replace(char *str, char *to_repl, char *repl_w);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *s));
char		*ft_strjoin_ip(char const *s1, char const *s2,
				t_Inplace_Type in_place);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f) (unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim_char(char	*str, char c, bool inplace);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
// TREE
void		ft_tree_clear(t_tree *tree, void (*del)(void *));
t_tree		*ft_tree_new(void *content);
void		ft_tree_trav(t_tree *node, void(*f)(void *),
				t_Tree_Travel_Type trav_type);
// WRITE_READ
char		*ft_get_next_line(int fd);
int			ft_printf(const char *str, ...);
size_t		print_format(const char **str, va_list argl);
char		*get_radix(char type, va_list argl);
char		*ft_utoa_base(unsigned long number, char *base);
char		*ft_itoa_base(long long n, char *base);
char		*ft_strdup_pf(const char *s1, int null);
size_t		print_format(const char **str, va_list argl);
char		*get_radix(char type, va_list argl);
char		*ft_strjoin_gnl(char const *s1, char const *s2, int in_place);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_readfile(int fd);

#endif
