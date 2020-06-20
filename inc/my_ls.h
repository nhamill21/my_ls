#ifndef MY_LS_H
# define MY_LS_H

void print_log(unsigned flag);

# include <stdio.h>
# include <string.h>

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# define FLAG_STOP "--"
# define FLAG_FAIL 0x80000000

# define FLG_LWR_A (1 << FLAG_LWR_A)
# define FLG_UPR_A (1 << FLAG_UPR_A)
# define FLG_UPR_B (1 << FLAG_UPR_B)
# define FLG_LWR_C (1 << FLAG_LWR_C)
# define FLG_UPR_C (1 << FLAG_UPR_C)
# define FLG_LWR_D (1 << FLAG_LWR_D)
# define FLG_LWR_F (1 << FLAG_LWR_F)
# define FLG_UPR_F (1 << FLAG_UPR_F)
# define FLG_LWR_G (1 << FLAG_LWR_G)
# define FLG_UPR_G (1 << FLAG_UPR_G)
# define FLG_LWR_H (1 << FLAG_LWR_H)
# define FLG_UPR_H (1 << FLAG_UPR_H)
# define FLG_LWR_I (1 << FLAG_LWR_I)
# define FLG_LWR_L (1 << FLAG_LWR_L)
# define FLG_LWR_M (1 << FLAG_LWR_M)
# define FLG_LWR_N (1 << FLAG_LWR_N)
# define FLG_UPR_Q (1 << FLAG_UPR_Q)
# define FLG_LWR_R (1 << FLAG_LWR_R)
# define FLG_UPR_R (1 << FLAG_UPR_R)
# define FLG_LWR_S (1 << FLAG_LWR_S)
# define FLG_UPR_S (1 << FLAG_UPR_S)
# define FLG_LWR_T (1 << FLAG_LWR_T)
# define FLG_LWR_U (1 << FLAG_LWR_U)
# define FLG_LWR_V (1 << FLAG_LWR_V)
# define FLG_LWR_X (1 << FLAG_LWR_X)
# define FLG_LWR_Y (1 << FLAG_LWR_Y)
# define FLG_UPR_1 (1 << FLAG_UPR_1)

enum	e_position_flag_bits {
	FLAG_LWR_A, FLAG_UPR_A, FLAG_UPR_B, FLAG_LWR_C, FLAG_UPR_C, FLAG_LWR_D,
	FLAG_LWR_F, FLAG_UPR_F, FLAG_LWR_G, FLAG_UPR_G, FLAG_LWR_H, FLAG_UPR_H,
	FLAG_LWR_I, FLAG_LWR_L, FLAG_LWR_M, FLAG_LWR_N, FLAG_UPR_Q, FLAG_LWR_R,
	FLAG_UPR_R, FLAG_LWR_S, FLAG_UPR_S, FLAG_LWR_T, FLAG_LWR_U, FLAG_LWR_V,
	FLAG_LWR_X, FLAG_LWR_Y, FLAG_UPR_1
};
# define FLAGS "aABcCdfFgGhHilmnQrRsStuvxy1"

# define FLAG_DEFAULT (FLG_UPR_C | FLG_LWR_C | FLG_LWR_V)

# define FLAGS_SORT (FLG_LWR_S | FLG_LWR_V | FLG_LWR_Y | FLG_LWR_F | FLG_LWR_T)
# define FLAG_TO_NULL_SORT (~FLAGS_SORT)
# define FLAG_TIME (FLG_LWR_C | FLG_LWR_U)
# define FLAG_TO_NULL_TIME (~FLAG_TIME)
# define FLAG_LONG_LIST (FLG_LWR_L | FLG_LWR_G | FLG_UPR_G | FLG_LWR_N)
# define FLAG_TO_NULL_MANY_COLS ~(FLG_LWR_M | FLG_LWR_X | FLG_UPR_C)
# define FLAG_TO_NULL_EXCEPT_M ~(FLAG_LONG_LIST | FLG_UPR_C | FLG_LWR_X)
# define FLAG_MANY_COLS (FLG_UPR_C | FLG_LWR_X)
# define FLAG_TO_NULL_ONE_COL ~(FLAG_LONG_LIST | FLG_UPR_1 | FLG_LWR_M)

# define ERR_FLAG_FAIL "Wrong flag here"
# define ERR_HELP "Use help"
# define MGS_HELP "Help"

# define SEP_STD "\n"
# define SEP_FLAG_M ", "

typedef struct		s_heap {
	char			**arr;
	int				first;
	int				last;
	int				size;
}					t_heap;

# define START_HEAP_SIZE 1
# define COEF_HEAP_INC 2

void 		*get_heap_max(t_heap *heap, int (*f)(const char *, const char *));
void		heap_sort(t_heap *heap, int (*f)(const char *, const char *));
int			add_heap_elem(t_heap **heap, char *data, \
										int (*f)(const char *, const char *));

typedef struct		s_list {
	void 			*data;
	struct s_stack	*next;
}					t_list;

t_list	*ft_lstnew(void *data);
void 	ft_lstadd(t_list **alst, t_list *new);
void 	ft_lstdelone(t_list **del);

typedef struct		s_stack {
	t_heap			*data;
	struct s_stack	*next;
}					t_stack;

t_heap	*get_stack(t_stack *stack);
void 	push_stack(t_stack **stack, void *data);
void 	pop_stack(t_stack **stack);

typedef struct		s_ls {
	unsigned		flags;
	int 			(*func)(const char *s1, const char *s2);
	t_stack			*stack;
}					t_ls;

t_ls	*init_ls(int ac, char **av);
void 	work_ls(t_ls *ls);
int		ft_exit(int status, t_ls *ls);

char 	*ft_pathjoin(const char *s1, const char *s2);

void 	test_heap(t_ls *ls);
void 	print_flags(unsigned flag);
void	print_dirent(const char *name);

#endif
