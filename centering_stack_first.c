/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centering_stack_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calpha <calpha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:40:44 by calpha            #+#    #+#             */
/*   Updated: 2020/09/02 23:47:20 by calpha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_max_number_left(t_number **list_b, int *i)
{
	int max;
	int count;
	int n;

	max = (*list_b)->n;
	count = 0;
	n = (*list_b)->n;
	while (*list_b)
	{
		if ((*list_b)->prev != NULL)
		{
			*list_b = (*list_b)->prev;
			count++;
		}
		if ((*list_b)->n > max)
		{
			max = (*list_b)->n;
			*i = count;
		}
		if (n == (*list_b)->n)
			break ;
	}
	return (max);
}

static int	find_max_number_right(t_number **list_b, int *i)
{
	int max;
	int count;
	int n;

	max = (*list_b)->n;
	count = 0;
	n = (*list_b)->n;
	while (*list_b)
	{
		if ((*list_b)->next != NULL)
		{
			*list_b = (*list_b)->next;
			count++;
		}
		if ((*list_b)->n > max)
		{
			max = (*list_b)->n;
			*i = count;
		}
		if (n == (*list_b)->n)
			break ;
	}
	return (max);
}

static int	find_max_number(t_number **list_b, int *rotation_logic)
{
	int a;
	int b;

	a = 0;
	b = 0;
	find_max_number_left(list_b, &a);
	find_max_number_right(list_b, &b);
	if (a < b)
	{
		*rotation_logic = 1;
		return (a);
	}
	else
	{
		*rotation_logic = 0;
		return (b);
	}
	return (-1);
}

void			centering_stack_first(t_number **list_b)
{
	int step;
	int rotation_logic;

	rotation_logic = 0;
	step = find_max_number(list_b, &rotation_logic);
	// printf("step = %d\n", step);

	// usleep(3000000);
	while (step)
	{
		if (rotation_logic == 0)
			rb_three(&list_b);
		else
			rrb_three(&list_b);
		step--;
	}
}
