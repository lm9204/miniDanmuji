/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:35:43 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/30 13:57:51 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *create_node(int flag, void *content)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->flag = flag;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

// Function to append a node to the linked list
void append_node(t_list **head, t_list *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    t_list *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}
