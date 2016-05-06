/*
 * Copyright 2015 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#include <core/os.h>

/*XXX: this is just an unbalanced bst with linux's rbtree interface */

void
rb_link_node(struct rb_node *node, struct rb_node *parent, struct rb_node **ptr)
{
	node->parent = parent;
	node->rb_left = NULL;
	node->rb_right = NULL;
	*ptr = node;
}

void
rb_insert_color(struct rb_node *node, struct rb_root *root)
{
}

void
rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node **ptr;

	/* determine which parent pointer needs replacing */
	if (node->parent) {
		if (node == node->parent->rb_left)
			ptr = &node->parent->rb_left;
		else
			ptr = &node->parent->rb_right;
	} else {
		ptr = &root->rb_node;
	}

	if (node->rb_left && node->rb_right) {
		/* find the largest value to the left of the deleted
		 * node, this will take its place in the tree
		 */
		struct rb_node *lr = node->rb_left;
		while (lr->rb_right)
			lr = lr->rb_right;
		/* if this isn't the immediate left of the deleted node,
		 * search down to find the smallest value and link the
		 * immediate left of the deleted node there
		 */
		if (node->rb_left != lr) {
			struct rb_node *lrl = lr;
			while (lrl->rb_left)
				lrl = lrl->rb_left;
			lrl->rb_left = node->rb_left;
			lrl->rb_left->parent = lrl;
			lr->parent->rb_right = NULL;
		}
		/* link into the deleted node's position */
		lr->parent = node->parent;
		lr->rb_right = node->rb_right;
		lr->rb_right->parent = lr;
		*ptr = lr;
	} else
	if (node->rb_left) {
		/* move left node into the deleted node's position */
		node->rb_left->parent = node->parent;
		*ptr = node->rb_left;
	} else
	if (node->rb_right) {
		/* move right node into the deleted node's position */
		node->rb_right->parent = node->parent;
		*ptr = node->rb_right;
	} else {
		*ptr = NULL;
	}
}

struct rb_node *
rb_first(struct rb_root *root)
{
	struct rb_node *node = root->rb_node;
	while (node && node->rb_left)
		node = node->rb_left;
	return node;
}

struct rb_node *
rb_next(struct rb_node *node)
{
	struct rb_node *parent;
	if (node->rb_right) {
		node = node->rb_right;
		while (node->rb_left)
			node = node->rb_left;
		return node;
	}
	while ((parent = node->parent) && node == parent->rb_right)
		node = parent;
	return parent;
}
