#include "my_ls.h"

#include <assert.h>
#define TEST1 FLG_LWR_A | FLG_UPR_A | FLG_LWR_C | FLG_LWR_V | FLG_UPR_B | FLG_LWR_M
void 	print_log(unsigned flag);

int 	main(int ac, char **av)
{
	t_ls	*ls;

	ls = init_ls(ac, av);
	return (0);
}

void	print_log(unsigned flag)
{
	if (flag & FLG_LWR_A)
		printf("a");
	if (flag & FLG_UPR_A)
		printf("A");
	if (flag & FLG_UPR_B)
		printf("B");
	if (flag & FLG_LWR_C)
		printf("c");
	if (flag & FLG_UPR_C)
		printf("C");
	if (flag & FLG_LWR_D)
		printf("d");
	if (flag & FLG_LWR_F)
		printf("f");
	if (flag & FLG_UPR_F)
		printf("F");
	if (flag & FLG_LWR_G)
		printf("G");
	if (flag & FLG_UPR_G)
		printf("G");
	if (flag & FLG_LWR_H)
		printf("h");
	if (flag & FLG_UPR_H)
		printf("H");
	if (flag & FLG_LWR_I)
		printf("i");
	if (flag & FLG_LWR_L)
		printf("l");
	if (flag & FLG_LWR_M)
		printf("m");
	if (flag & FLG_LWR_N)
		printf("n");
	if (flag & FLG_UPR_Q)
		printf("Q");
	if (flag & FLG_LWR_R)
		printf("r");
	if (flag & FLG_UPR_R)
		printf("R");
	if (flag & FLG_LWR_S)
		printf("s");
	if (flag & FLG_UPR_S)
		printf("S");
	if (flag & FLG_LWR_T)
		printf("t");
	if (flag & FLG_LWR_U)
		printf("u");
	if (flag & FLG_LWR_V)
		printf("v");
	if (flag & FLG_LWR_X)
		printf("y");
	if (flag & FLG_LWR_Y)
		printf("y");
	if (flag & FLG_UPR_1)
		printf("1");
	printf("\n");
}