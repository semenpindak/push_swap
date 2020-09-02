/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_upten_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calpha <calpha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:01:43 by calpha            #+#    #+#             */
/*   Updated: 2020/09/02 20:38:00 by calpha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int find_max_number(t_number *list_b)
{
	int max;
	int n;

	max = list_b->n;
	n = list_b->n;
	while(list_b)
	{
		if (list_b->next != NULL)
			list_b = list_b->next;
		if (list_b->n > max)
			max = list_b->n;
		if (n == list_b->n)
			break;
	}
	return (max);
}

static int find_min_number(t_number *list_b)
{
	int min;
	int n;

	min = list_b->n;
	n = list_b->n;
	while(list_b)
	{
		if (list_b->next != NULL)
			list_b = list_b->next;
		if (list_b->n < min)
			min = list_b->n;
		if (n == list_b->n)
			break;
	}
	return (min);
}

static int check_next_num_two(t_number **list_a, int current, int max, int min)
{
	if ((*list_a)->next != NULL)
		*list_a = (*list_a)->next;
	if (current == max && (*list_a)->n == min)
	{
		if ((*list_a)->prev != NULL)
			*list_a = (*list_a)->prev;
		return (0);
	}
	if ((*list_a)->n < current)
	{
		if ((*list_a)->prev != NULL)
			*list_a = (*list_a)->prev;
		return(1);
	}
	else
	{
		if ((*list_a)->prev != NULL)
			*list_a = (*list_a)->prev;
		return (0);
	}
	return (-1);
}

static int count_step_sa_right(t_number **list_a, int max, int min)
{
	int n;
	int count;
	int check;
	int current;
	int i;
	int flag;

	n = (*list_a)->n;
	count = 0;
	current = 0;
	i = 0;
	flag = 0;
	while (*list_a)
	{
		current = (*list_a)->n;
		check = check_next_num_two(list_a, current, max, min);
		if (check == 1 && flag == 0)
		{
			i = count;
			flag = 1;
		}
		if ((*list_a)->next != NULL)
			*list_a = (*list_a)->next;
		count++;
		if (n == (*list_a)->n)
			break;
	}
	return (i);
}

static int count_step_sa_left(t_number **list_a, int max, int min)
{
	int n;
	int count;
	int check;
	int current;
	int i;
	int flag;

	n = (*list_a)->n;
	count = 0;
	current = 0;
	i = 0;
	flag = 0;
	while (*list_a)
	{
		current = (*list_a)->n;
		check = check_next_num_two(list_a, current, max, min);
		if (check == 1 && flag == 0)
		{
			i = count;
			flag = 1;
		}
		if ((*list_a)->prev != NULL)
			*list_a = (*list_a)->prev;
		count++;
		if (n == (*list_a)->n)
			break;
	}
	return (i);
}

static int rotation(t_number **list_a, int *rotation_logic, int max, int min)
{
	(*list_a)->ra = count_step_sa_right(list_a, max, min);
	(*list_a)->la = count_step_sa_left(list_a, max, min);
	if ((*list_a)->ra < (*list_a)->la)
	{
		*rotation_logic = 0;
		return ((*list_a)->ra);
	}
	else
	{
		*rotation_logic = 1;
		return ((*list_a)->la);
	}
	return (-1);
}

static void centering_stack_ten(t_number **list_a, int max, int min)
{
	int step;
	int rotation_logic;

	step = rotation(list_a, &rotation_logic, max, min);
	while (step)
	{
		if (rotation_logic == 0)
			ra_three(&list_a);
		else
			rra_three(&list_a);
		step--;
	}
}

static int checking_stack_sorted(t_number *list_a, int min, int n)
{
	int current;

	while (list_a)
	{
		if (list_a->n == min)
			break;
		if (list_a->next != NULL)
			list_a = list_a->next;
	};
	n--;
	while (list_a)
	{
		current = list_a->n;
		if (list_a->prev != NULL)
			list_a = list_a->next;
		if (current < list_a->n)
		{
			n--;
			if (n == 0)
				return (1);
		}
		else
			return (0);
	}
	return (-1);
}

static void start(t_number **list_a, t_number **list_b)
{
	if (*list_b == NULL)
		pb_three(&list_a, &list_b);
}

void sorting_upten_num(t_number *list_a, t_number *list_b)
{
	int n;
	int max;
	int min;
	int a;
	int i;

	i = 0;
	start(&list_a, &list_b);
	n = count_list(list_a);
	min = find_min_number(list_a);
	max = find_max_number(list_a);
	while(list_a)
	{
		centering_stack_ten(&list_a, max, min);


		a = checking_stack_sorted(list_a, min, n);
		if (a == 0)
			sa(list_a);
		a = checking_stack_sorted(list_a, min, n);
		if (a == 1)
			break;
	}
	insertion_sort_finish(&list_a, &list_b);
	centering_stack_a(&list_a);
}
