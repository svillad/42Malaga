/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:02:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/13 19:17:16 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "pipex.h"
# include <stdlib.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define NOT_ASSIGNED -1
# define A 0
# define B 1
# define SRC 0
# define DST 1

typedef struct s_node
{
	int				value;
	int				index;
	int				position;
	int				cost;
	struct s_node	*next;
}					t_node;

// validations
/**
 * @brief Validates the input arguments.
 * This function validates the input arguments provided to the program. It checks
 * if the number of arguments (argc) and the arguments themselves (argv) are
 * valid for the program's expected usage. If the input is invalid, it may print
 * an error message and exit the program.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 */
void				validate_input(int argc, char **argv);
/**
 * @brief Checks if a string consists only of digits.
 * This function checks if a string consists only of digit characters (0-9) or 
 * signs (+ and -).
 * @param str The string to be checked.
 * @return 1 if the string consists only of digits, otherwise 0.
 */
int					are_digits(const char *str);
/**
 * @brief Checks if there are duplicates in an array up to a specified index.
 * This function checks if there are any duplicate elements in an array up to a
 * specified index.
 * @param numbers An array of integers to be checked for duplicates.
 * @param current_index The index up to which the array should be checked for
 * duplicates.
 * @return 1 if there are duplicates, otherwise 0.
 */
int					are_duplicates(int *numbers, int current_index);

// moves
/**
 * @brief Moves a node to the top of a stack.
 * This function moves a specified node to the top of a given stack. It takes the
 * address of the head of the stack, an array of nodes, and the index of the node
 * to be moved within the array.
 * @param head A pointer to a pointer to the head of the stack.
 * @param node An array of pointers to nodes.
 * @param stack The index of the stack where the node will be moved.
 */
void				move_node_to_top(t_node **head, t_node *node[], int stack);
/**
 * @brief Moves nodes from both stacks when both values are positive.
 * This function moves nodes between two stacks when both values being compared
 * are positive. It takes the addresses of the heads of both stacks, an array of
 * nodes, and the number of nodes to be moved from the source stack.
 * @param a A pointer to a pointer to the head of the first stack.
 * @param b A pointer to a pointer to the head of the second stack.
 * @param node An array of pointers to nodes.
 * @param nsrc The number of nodes to be moved from the source stack.
 */
void				move_both_positive(t_node **a, t_node **b, t_node *node[],
						int nsrc);
/**
 * @brief Moves nodes from both stacks when both values are negative.
 * This function moves nodes between two stacks when both values being compared
 * are negative. It takes the addresses of the heads of both stacks, an array of
 * nodes, and the number of nodes to be moved from the source stack.
 * @param a A pointer to a pointer to the head of the first stack.
 * @param b A pointer to a pointer to the head of the second stack.
 * @param node An array of pointers to nodes.
 * @param nsrc The number of nodes to be moved from the source stack.
 */
void				move_both_negative(t_node **a, t_node **b, t_node *node[],
						int nsrc);
/**
 * @brief Moves nodes between two stacks when one value is positive and the other
 * is negative.
 * This function moves nodes between two stacks when one value being compared
 * is positive and the other is negative. It takes the addresses of the heads of
 * both stacks, an array of nodes, and the number of nodes to be moved from the
 * source stack.
 * @param a A pointer to a pointer to the head of the first stack.
 * @param b A pointer to a pointer to the head of the second stack.
 * @param node An array of pointers to nodes.
 * @param nsrc The number of nodes to be moved from the source stack.
 */
void				move_pos_and_neg(t_node **a, t_node **b, t_node *node[],
						int nsrc);
// nodes
/**
 * @brief Creates a new node.
 * This function creates a new node in the linked list. It takes a pointer to the
 * head node and a node as arguments and returns a pointer to the newly created
 * node.
 * @param head A pointer to the head node of the linked list.
 * @param node The node to be added to the list.
 * @return A pointer to the newly created node.
 */
t_node				*create_node(t_node *head, t_node node);
/**
 * @brief Prints the data stored in a node.
 * This function prints the data stored in a node of the linked list.
 * @param node The node whose data will be printed.
 */
void				print_node(t_node *node);

// push swap
/**
 * @brief Prints a custom error message.
 * This function prints a custom error message to stderr.
 * @param error The error message to print.
 */
void				ft_error_with_message(char *error);
/**
 * @brief Prints a simple error message.
 * This function prints a simple error message to stderr.
 */
void				ft_simple_error(void);
/**
 * @brief Parses input arguments.
 * This function parses the input arguments provided on the command line.
 * It takes the number of arguments (argc), the array of arguments (argv), and a
 * pointer to the size of the arguments as input, and returns a pointer to an
 * array of integers representing the parsed values.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param size A pointer to the size of the arguments.
 * @return A pointer to the array of integers representing the parsed values.
 */
int					*parse_input(int argc, char **argv, int *size);
/**
 * @brief Joins arguments into a string.
 * This function joins the command-line arguments into a single string.
 * It takes the number of arguments (argc) and the array of arguments (argv) as
 * input and returns a pointer to a string containing the concatenation of the
 * arguments.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return A pointer to a string containing the concatenation of the arguments.
 */
char				*ft_join_args(int argc, char **argv);

// stacks
/**
 * @brief Initializes a stack with the given numbers.
 * This function initializes a stack with the given numbers. It takes an array of
 * integers and its size as input, and returns a pointer to the head of the
 * initialized stack.
 * @param numbers An array of integers to initialize the stack with.
 * @param size The size of the numbers array.
 * @return A pointer to the head of the initialized stack.
 */
t_node				*init_stack(int *numbers, int size);
/**
 * @brief Gets the length of a stack.
 * This function calculates and returns the length of a stack.
 * @param head A pointer to the head node of the stack.
 * @return The length of the stack.
 */
int					get_stack_len(t_node *head);
/**
 * @brief Prints the elements of a stack.
 * This function prints the elements of a stack.
 * @param name The name of the stack to be printed.
 * @param head A pointer to the head node of the stack.
 */
void				print_stack(char *name, t_node *head);
/**
 * @brief Prints the elements of both stacks.
 * This function prints the elements of both stacks side by side.
 * @param a A pointer to the head node of the first stack.
 * @param b A pointer to the head node of the second stack.
 */
void				print_stacks(t_node *a, t_node *b);
/**
 * @brief Checks if stack a is ordered and stack b is null.
 * This function checks if stack a is ordered in ascending order.
 * @param a A pointer to the head node of the first stack.
 * @param b A pointer to the head node of the second stack.
 * @return Returns 1 if a stack is ordered and b is null, otherwise returns 0.
 */
int					is_stack_ordered(t_node *a, t_node *b);
/**
 * @brief Sorts a stack in descending order.
 * This function sorts a stack in descending order.
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				sort_descending(t_node **head);
/**
 * @brief Sorts a stack in ascending order.
 * This function sorts a stack in ascending order. 
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				sort_ascending(t_node **head);
/**
 * @brief Frees the memory allocated for a stack.
 * This function frees the memory allocated for a stack.
 * @param head A pointer to the head node of the stack.
 */
void				ft_free_stack(t_node *head);
/**
 * @brief Finds the minimum value node in a stack without index.
 * This function finds the node with the minimum value in a stack without index.
 * @param head A pointer to the head node of the stack.
 * @return A pointer to the node with the minimum value.
 */
t_node				*find_min_node_without_index(t_node *head);
/**
 * @brief Sets the indexes of nodes in a stack.
 * This function sets the indexes of nodes in a stack starting from 0 for the top
 * node.
 * @param head A pointer to the head node of the stack.
 */
void				set_stack_indexes(t_node *head);

// sort
/**
 * @brief main function to sort the stacks.
 * This function sorts the stacks 'a' and 'b' using a sorting algorithm.
 * @param a A pointer to a pointer to the head node of stack 'a'.
 * @param b A pointer to a pointer to the head node of stack 'b'.
 */
void				sort(t_node **a, t_node **b);
/**
 * @brief Operates on the stacks.
 * This function performs stack operations based on the given source and
 * destination stacks and an array of nodes. It moves 'nsrc' number of nodes from
 * the source stack to the destination stack.
 * @param src A pointer to a pointer to the head node of the source stack.
 * @param dst A pointer to a pointer to the head node of the destination stack.
 * @param node An array (size 2) of pointers to nodes. This array represents the
 * 			nodes that will be operated on each stack (position 0 for stack 'a'
 * 			and position 1 for stack 'b')
 * @param nsrc The "stack name" of the source stack (0 for stack 'a'
 * 			and 1 for stack 'b').
 */
void				operate(t_node **src, t_node **dst, t_node *node[],
						int nsrc);
/**
 * @brief Checks if a stack is partially ordered (ascending).
 * This function checks if a stack is partially ordered. In the case that the
 * stack does not have all the indexes, but they are circularly ordered.
 * @param head A pointer to the head node of the stack.
 * @return Returns 1 if the stack is partially ordered, otherwise returns 0.
 */
int					is_stack_partially_ordered(t_node *head);
/**
 * @brief Sorts three nodes in a stack (special case).
 * This function sorts three nodes in a stack.
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				sort_3_nodes(t_node **head);

// operations
/**
 * @brief Swaps the top two elements of a stack.
 * This function swaps the positions of the top two elements of a stack.
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				swap_op(t_node **head);
/**
 * @brief Swaps the top two elements of stack 'a'.
 * This function swaps the positions of the top two elements of stack 'a'.
 * @param head A pointer to a pointer to the head node of stack 'a'.
 */
void				sa(t_node **head);
/**
 * @brief Swaps the top two elements of stack 'b'.
 * This function swaps the positions of the top two elements of stack 'b'.
 * @param head A pointer to a pointer to the head node of stack 'b'.
 */
void				sb(t_node **head);
/**
 * @brief Swaps the top two elements of both stacks.
 * This function swaps the positions of the top two elements of both stacks
 * 'a' and 'b'.
 * @param a A pointer to a pointer to the head node of stack 'a'.
 * @param b A pointer to a pointer to the head node of stack 'b'.
 */
void				ss(t_node **a, t_node **b);

/**
 * @brief Rotates the stack towards the top.
 * This function rotates the stack towards the top by moving the top element to
 * the bottom.
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				rotate_op(t_node **head);
/**
 * @brief Rotates stack 'a' towards the top.
 * This function rotates stack 'a' towards the top by moving the top element to
 * the bottom.
 * @param head A pointer to a pointer to the head node of stack 'a'.
 */
void				ra(t_node **head);
/**
 * @brief Rotates stack 'b' towards the top.
 * This function rotates stack 'b' towards the top by moving the top element to
 * the bottom.
 * @param head A pointer to a pointer to the head node of stack 'b'.
 */
void				rb(t_node **head);
/**
 * @brief Rotates both stacks towards the top.
 * This function rotates both stacks 'a' and 'b' towards the top by moving their
 * top elements to the bottom.
 * @param a A pointer to a pointer to the head node of stack 'a'.
 * @param b A pointer to a pointer to the head node of stack 'b'.
 */
void				rr(t_node **a, t_node **b);

/**
 * @brief Rotates the stack towards the bottom.
 * This function rotates the stack towards the bottom by moving the bottom
 * element to the top.
 * @param head A pointer to a pointer to the head node of the stack.
 */
void				reverse_rotate_op(t_node **head);
/**
 * @brief Rotates stack 'a' towards the bottom.
 * This function rotates stack 'a' towards the bottom by moving the bottom
 * element to the top.
 * @param head A pointer to a pointer to the head node of stack 'a'.
 */
void				rra(t_node **head);
/**
 * @brief Rotates stack 'b' towards the bottom.
 * This function rotates stack 'b' towards the bottom by moving the bottom
 * element to the top.
 * @param head A pointer to a pointer to the head node of stack 'b'.
 */
void				rrb(t_node **head);
/**
 * @brief Rotates both stacks towards the bottom.
 * This function rotates both stacks 'a' and 'b' towards the bottom by moving
 * their bottom elements to the top.
 * @param a A pointer to a pointer to the head node of stack 'a'.
 * @param b A pointer to a pointer to the head node of stack 'b'.
 */
void				rrr(t_node **a, t_node **b);

/**
 * @brief Pushes the top element from one stack to another.
 * This function pushes the top element from the source stack to the destination
 * stack.
 * @param dst A pointer to a pointer to the head node of the destination stack.
 * @param src A pointer to a pointer to the head node of the source stack.
 */
void				push_op(t_node **dst, t_node **src);
/**
 * @brief Pushes the top element from stack 'src' to stack 'dst'.
 * This function pushes the top element from stack 'src' to stack 'dst'.
 * @param dst A pointer to a pointer to the head node of the destination stack.
 * @param src A pointer to a pointer to the head node of the source stack.
 */
void				pa(t_node **dst, t_node **src);
/**
 * @brief Pushes the top element from stack 'src' to stack 'dst'.
 * This function pushes the top element from stack 'src' to stack 'dst'.
 * @param dst A pointer to a pointer to the head node of the destination stack.
 * @param src A pointer to a pointer to the head node of the source stack.
 */
void				pb(t_node **dst, t_node **src);

/**
 * @brief Calculates the positions of the nodes in a stack.
 * This function calculates the positions of the nodes in a stack. It assigns
 * a position starting from 0 for the top node and incrementing by 1 for each
 * subsequent node.
 * @param head A pointer to the head node of the stack.
 */
void				calculate_positions(t_node *head);
/**
 * @brief Gets the penultimate node of a stack.
 * This function returns a pointer to the penultimate node of a stack.
 * @param head A pointer to the head node of the stack.
 * @return A pointer to the penultimate node of the stack.
 */
t_node				*get_penultimate_node(t_node *head);
/**
 * @brief Gets the last node of a stack.
 * This function returns a pointer to the last (bottom) node of a stack.
 * @param head A pointer to the head node of the stack.
 * @return A pointer to the last node of the stack.
 */
t_node				*get_last_node(t_node *head);

#endif
