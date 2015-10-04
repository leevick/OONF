
/*
 * The olsr.org Optimized Link-State Routing daemon version 2 (olsrd2)
 * Copyright (c) 2004-2015, the olsr.org team - see HISTORY file
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of olsr.org, olsrd nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Visit http://www.olsr.org for more information.
 *
 * If you find this software useful feel free to make a donation
 * to the project. For more information see the website or contact
 * the copyright holders.
 *
 */

#ifndef _OLSRV2_HEAP_H
#define _OLSRV2_HEAP_H

#include "common/common_types.h"

/**
 * Element included into a olsrv2_heap.
 */
struct olsrv2_heap_node{
    /**
     * node's key based on the link cost type.
     */
    uint32_t key;

    /**
     * Pointer to parent node in the olsrv2_heap, NULL if root node.
     */
    struct olsrv2_heap_node *parent;

    /**
     * Pointer to left child, NULL if there isn't.
     */
    struct olsrv2_heap_node *left;

    /**
     * Pointer to right child, NULL if there isn't.
     */
    struct olsrv2_heap_node *right;
};

/**
 * Manager struct of the olsrv2_heap.
 * One of them is necessary for each olsrv2_heap.
 */
struct olsrv2_heap{
    /**
     * Number of nodes in the olsrv2_heap.
     */
    unsigned int count;

    /**
     * Pointer to the root node of the olsrv2_heap, NULL if olsrv2_heap is empty.
     */
    struct olsrv2_heap_node *root_node;

    /**
     * Pointer to the rightest node of the lowest level in the olsrv2_heap,
     * NULL if olsrv2_heap is empty.
     */
    struct olsrv2_heap_node *last_node;
};

void heap_init(struct olsrv2_heap *root);
void heap_decrease_key(struct olsrv2_heap *root, struct olsrv2_heap_node *node);
void heap_insert(struct olsrv2_heap *root, struct olsrv2_heap_node *node);
struct olsrv2_heap_node *heap_extract_min(struct olsrv2_heap *root);
bool heap_is_node_added(struct olsrv2_heap *root, struct olsrv2_heap_node *node);

/**
 * @param root pointer to binary olsrv2_heap
 * @return size of olsrv2_heap, 0 if is empty
 */
static INLINE unsigned int
heap_get_size(struct olsrv2_heap *root)
{
    return root->count;
}

/**
 * @param root pointer to binary olsrv2_heap
 * @return pointer to root node
 */
static INLINE struct olsrv2_heap_node*
heap_get_root_node(struct olsrv2_heap *root)
{
    return root->root_node;
}

/**
 * @param root pointer to binary olsrv2_heap
 * @return true if the olsrv2_heap is empty, false otherwise
 */
static INLINE bool
heap_is_empty(struct olsrv2_heap *root)
{
    return root->count == 0;
}

/**
 * Initialize a olsrv2_heap node
 * @param node pointer to the olsrv2_heap node
 */
static INLINE void
heap_init_node(struct olsrv2_heap_node *node)
{
    node->parent = node->left = node->right = NULL;
}

#endif /* _OLSRV2_HEAP_H */
