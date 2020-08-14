# include <stdlib.h>
# include <unistd.h>

typedef struct        s_number
{
    int                n;
    int                lb;
    int                rb;
    struct s_number    *next;
    struct s_number    *prev;
}                    t_number;

static int check_next_number_right(t_number **list_b)
{

    *list_b = (*list_b)->next;
    int a = (*list_b)->n;
    *list_b = (*list_b)->prev;
    return (a);
}

static int check_next_number_right_add(t_number **list_b)
{

    *list_b = (*list_b)->prev;
    int a = (*list_b)->n;
    *list_b = (*list_b)->next;
    return (a);
}

static int count_to_range_right(t_number **list_b, int max, int min, int **c)
{
    int count = 0;

    while (*list_b)
    {
        if (max == (*list_b)->n)
        {
            if (min == check_next_number_right(list_b))
                return (count);
            if (min == check_next_number_right_add(list_b))
                return (count);
        }
        *list_b = (*list_b)->next;
        count++;
        **c = count;
    }
    return (-1);
}

static int find_middle_number_right(t_number **list_a, t_number **list_b, int *c)
{
    int min = -2147483647;
    int max = 2147483647;
    int middle = (*list_a)->n;
    int n = (*list_b)->n;
    while (*list_b)
    {
        if ((*list_b)->n < max && (*list_b)->n > middle)
            max = (*list_b)->n;
        if ((*list_b)->n > min && (*list_b)->n < middle)
            min = (*list_b)->n;
        *list_b = (*list_b)->next;
        if (n == (*list_b)->n)
            break;
    }
    return (count_to_range_right(list_b, max, min, &c));
}


static int find_max_number_right(t_number **list_b, int *i)
{
    int max = (*list_b)->n;
    int count = 1;
    int n = (*list_b)->n;
    while(*list_b)
    {
        if ((*list_b)->next != NULL)
        {
            *list_b = (*list_b)->next;
            count++;
        }
        if ((*list_b)->n > max)
        {
            max = (*list_b)->n;
            *i = ++count;
        }
        if (n == (*list_b)->n)
            break;
    }
    return (max);
}

static int find_min_number_right(t_number **list_b, int *i)
{
    int min = (*list_b)->n;
    int count = 0;
    int n = (*list_b)->n;

    while(list_b)
    {
        if ((*list_b)->next != NULL)
        {
            *list_b = (*list_b)->next;
            count++;
        }
        if ((*list_b)->n < min)
        {
            min = (*list_b)->n;
            *i = count;
        }
        if (n == (*list_b)->n)
            break;
    }
    return (min);
}


static int step_right(t_number **list_a, t_number **list_b)
{
    int a = (*list_a)->n;
    int i = 0;
    int x = 0;
    int y;
    int c;

    if (a > (x = find_max_number_right(list_b, &i)))
        return (i);
    if (a < (x = find_min_number_right(list_b, &i)))
        return (i);

    y = find_middle_number_right(list_a, list_b, &c);
    while (c)
    {
        *list_b = (*list_b)->prev;
        c--;
    }
    return (y);
}

void count_step_in_b_for_struct_three_regular(t_number **list_a, t_number **list_b)
{
    (*list_a)->lb = step_right(list_a, list_b);
}

static t_number    *get_last(t_number *head)
{
    if (head == NULL)
        return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}

static void            push_ring(t_number *head, int j, int av[])
{
    t_number    *last;
    t_number    *tmp;

    last = get_last(head);
    tmp = (t_number *)malloc(sizeof(t_number));
    tmp->n = av[j];
    tmp->next = head;
    tmp->prev = last;
    last->next = tmp;
    head->prev = tmp;
}

static void            push_back(t_number *head, int j, int av[])
{
    t_number    *last;
    t_number    *tmp;

    last = get_last(head);
    tmp = (t_number *)malloc(sizeof(t_number));
    tmp->n = av[j];
    tmp->next = NULL;
    tmp->prev = last;
    last->next = tmp;
}

static void            push(t_number **head, int j, int av[])
{
    t_number    *tmp;

    tmp = (t_number *)malloc(sizeof(t_number));
    tmp->n = av[j];
    tmp->next = NULL;
    tmp->prev = NULL;
    *head = tmp;
}

t_number *create_stack_a(int ac, int av[])
{
    int j = 1;
    t_number *list;

    while (j < ac)
    {
        if (j == 1)
            push(&list, j, av);
        if (j != 1 && j != ac - 1)
            push_back(list, j, av);
        if ((j == ac - 1) && j > 1)
            push_ring(list, j, av);
        j++;
    }
    return (list);
}

void timsort(t_number *list_a, t_number *list_b)
{
  count_step_in_b_for_struct_three_regular(list_a, list_b);
}


int main() {
  int av[5] = {8, 15, 3, 16, 10};
  t_number *list_a;
  list_a = create_stack_a(5, av);

  int av1[4] = {25, 4, 18, 19};
  t_number *list_b;
  list_b = create_stack_a(4, av1);


  timsort(list_a, list_b);

  return 0;
}