/* -*- mode: C -*- Time-stamp: "10/01/13 14:00:05 jemarch"
 *
 *       File:         rec-sex-ast.c
 *       Date:         Tue Jan 12 17:29:03 2010
 *
 *       GNU Records - SEX Abstract Syntax Trees
 *
 */

#include <config.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <rec-sex-ast.h>

/*
 * Data types
 */

#define REC_SEX_AST_MAX_CHILDREN 2

struct rec_sex_ast_node_s
{
  enum rec_sex_ast_node_type_e type;
  union {
    int integer;
    char *string;
    char *name;
  } val;

  int index;
  rec_sex_ast_node_t children[REC_SEX_AST_MAX_CHILDREN];
  size_t num_children;
};

struct rec_sex_ast_s
{
  rec_sex_ast_node_t top;
};

/*
 * Public functions
 */

rec_sex_ast_t
rec_sex_ast_new ()
{
  rec_sex_ast_t new;

  new = malloc (sizeof (struct rec_sex_ast_s));
  if (new)
    {
      new->top = NULL;
    }

  return new;
}

void
rec_sex_ast_destroy (rec_sex_ast_t ast)
{
  if (ast->top)
    {
      rec_sex_ast_node_destroy (ast->top);
    }
  
  free (ast);
}

rec_sex_ast_node_t
rec_sex_ast_node_new (void)
{
  rec_sex_ast_node_t new;

  new = malloc (sizeof(struct rec_sex_ast_node_s));
  if (new)
    {
      new->type = REC_SEX_NOVAL;
      new->num_children = 0;
      new->index = 0;  /* Important!!!  See rec_sex_eval_node.  */
    }

  return new;
}

void
rec_sex_ast_node_destroy (rec_sex_ast_node_t node)
{
  size_t i;

  /* Destroy children.  */
  for (i = 0; i < node->num_children; i++)
    {
      rec_sex_ast_node_destroy (node->children[i]);
    }

  /* Destroy values.  */
  if (node->type == REC_SEX_STR)
    {
      free (node->val.string);
    }
  else if (node->type == REC_SEX_NAME)
    {
      free (node->val.name);
    }
}

enum rec_sex_ast_node_type_e
rec_sex_ast_node_type (rec_sex_ast_node_t node)
{
  return node->type;
}

void
rec_sex_ast_node_set_type (rec_sex_ast_node_t node,
                           enum rec_sex_ast_node_type_e type)
{
  node->type = type;
}

int
rec_sex_ast_node_int (rec_sex_ast_node_t node)
{
  return node->val.integer;
}

void
rec_sex_ast_node_set_int (rec_sex_ast_node_t node,
                          int num)
{
  node->type = REC_SEX_INT;
  node->val.integer = num;
}

char *
rec_sex_ast_node_str (rec_sex_ast_node_t node)
{
  return node->val.string;
}

void
rec_sex_ast_node_set_str (rec_sex_ast_node_t node,
                          char *str)
{
  if (node->type == REC_SEX_STR)
    {
      free (node->val.string);
    }

  node->type = REC_SEX_STR;
  node->val.string = strdup (str);
}

char *
rec_sex_ast_node_name (rec_sex_ast_node_t node)
{
  return node->val.name;
}

void
rec_sex_ast_node_set_name (rec_sex_ast_node_t node,
                          char *name)
{
  if (node->type == REC_SEX_NAME)
    {
      free (node->val.name);
    }
 
  node->type = REC_SEX_NAME;
  node->val.string = strdup (name);
}

void
rec_sex_ast_node_link (rec_sex_ast_node_t parent,
                       rec_sex_ast_node_t child)
{
  if (parent->num_children < REC_SEX_AST_MAX_CHILDREN)
    {
      parent->children[parent->num_children++] = child;
    }
}

rec_sex_ast_node_t
rec_sex_ast_top (rec_sex_ast_t ast)
{
  return ast->top;
}

void
rec_sex_ast_set_top (rec_sex_ast_t ast,
                     rec_sex_ast_node_t node)
{
  ast->top = node;
}

void
rec_sex_ast_print_node (rec_sex_ast_node_t node)
{
  int i;
  
  for (i = 0; i < node->num_children; i++)
    {
      rec_sex_ast_print_node (node->children[i]);
    }

  printf ("------- node\n");
  printf ("type: %d\n", node->type);
  if (node->type == REC_SEX_INT)
    {
      printf("value: %d\n", node->val.integer);
    }
  if (node->type == REC_SEX_NAME)
    {
      printf("value: %s\n", node->val.name);
    }
  if (node->type == REC_SEX_STR)
    {
      printf("value: %s\n", node->val.string);
    }

  printf("\n");
}

int
rec_sex_ast_node_num_children (rec_sex_ast_node_t node)
{
  return node->num_children;
}

rec_sex_ast_node_t
rec_sex_ast_node_child (rec_sex_ast_node_t node,
                        int n)
{
  rec_sex_ast_node_t res;

  res = NULL;
  if (n < node->num_children)
    {
      res = node->children[n];
    }

  return res;
}

void
rec_sex_ast_node_reset (rec_sex_ast_node_t node)
{
  int i;

  for (i = 0; i < node->num_children; i++)
    {
      rec_sex_ast_node_reset (node->children[i]);
    }

  node->index = 0;
}

int
rec_sex_ast_node_index (rec_sex_ast_node_t node)
{
  return node->index++;
}

void
rec_sex_ast_print (rec_sex_ast_t ast)
{
  rec_sex_ast_print_node (ast->top);
}


/* End of rec-sex-ast.c */