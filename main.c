#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------------------------ constants ------------------------------------------------------------------------------------------ */
#define CHANGE 'c'
#define DELETE 'd'
#define PRINT 'p'
#define UNDO 'u'
#define REDO 'r'
#define QUIT 'q'
#define FIX_VALUES 'f'
#define POINT '.'
#define NEWLINE '\n'
#define RED 'r'
#define BLACK 'b'
#define MAXLINESIZE 1024

/* ------------------------------------------------------------------------------------------ Struct definitions ------------------------------------------------------------------------------------------ */
/**
 * RB-tree node
 */
typedef struct node_s {
    struct node_s* left;
    struct node_s* right;
    struct node_s* p;
    int key; //The number of the row is the key of the nodes of the tree
    char* text_line; //Text content of the lines
    char col;
} node_t;

/**
 * RB-tree
 */
typedef struct tree_s {
    node_t* root;
    node_t* nil;
    int number_of_keys;
} tree_t;

/**
 * Node of a list of commands used to implement a stack
 */
typedef struct list_of_commands_s{
    int begin;
    int end;
    int command_id;
    char command;
    char* text_line;
    struct list_of_commands_s* next;
} list_of_commands_t;

/**
 * Stack with the commands performed. It is used to implement the undo/redo operation
 */
typedef struct stack_s{
    list_of_commands_t* top;
    int size;
}stack_t;

/* ------------------------------------------------------------------------------------------ trees prototypes ------------------------------------------------------------------------------------------ */
/**
 * Initializes the tree
 * @param t tree to initialize
 */
void tree_create(tree_t* t);

/**
 * Destroys a subtree of a tree
 * @param t tree in which the subtree is contained
 * @param node root of the subtree to destroy
 */
void destroy_subtree(tree_t* t, node_t* node);

/**
 * Looks up for the node with the key given in input
 * @param t tree in which the search has to be performed
 * @param key key to look for
 * @return the node with the corresponding key, NULL if not present
 */
node_t* tree_search(tree_t* t, int key);

/**
 * Creates a node of the tree
 * @param t tree in which the node will be added
 * @param key key of the node
 * @param text_line text of the node
 * @return the node created
 */
node_t* make_tree_node(tree_t* t, int key, char* text_line);

/**
 * Creates the NIL node of the tree
 */
node_t* make_node_nil();

/**
 * Inserts a new node in a tree
 * @param t tree in which the node will be added
 * @param key key of the node
 * @param text_line text of the node
 * @param command_id id that identifies the command (used to execute undo/redo operations)
 * @param s undo stack in which the command will be added in order to undo the operation
 */
void tree_insert(tree_t* t, int key, char* text_line, int command_id, stack_t* s);

/**
 * Destroys a node of a tree
 * @param n node to destroy
 */
void destroy_tree_node(node_t* n);
/**
 * Deletes a node of a tree
 * @param t tree in which there is the node do delete
 * @param x node to delete
 * @param command_id id that identifies the command (used to execute undo/redo operations)
 * @param s undo stack in which the command will be added in order to undo the operation
 */
void tree_delete(tree_t* t, node_t* x, int command_id, stack_t* s);

/**
 * Fixes the nodes of the tree in order to satisfy RB-trees properties after it has been modified
 * @param t tree
 * @param x root of the tree
 * @param start initial address of the command
 * @param end ending address of the command
 */
void tree_key_fixup (tree_t* t, node_t *x, int start, int end);

/**
 * Fixes the nodes of the tree in order to satisfy RB-trees properties after an insertion
 * @param t tree
 * @param z node inserted
 */
void tree_insert_fixup(tree_t* t, node_t* z);

/**
 * Fixes the ndoes of the tree in order to satisfy RB-trees properties after a deletion
 * @param t tree
 * @param x node deleted
 */
void tree_delete_fixup(tree_t* t, node_t* x);

/**
 * Rotates to the left a subtree of the tree in order to satisfy RB-trees properties
 * @param t tree
 * @param x node from which the rotation will be performed
 */
void left_rotate(tree_t* t, node_t* x);

/**
 * Rotates to the right a subtree of the tree in order to satisfy RB-trees properties
 * @param t tree
 * @param x node from which the rotation will be performed
 */
void right_rotate(tree_t* t, node_t* x);

/**
 * Retrieves the node containing the minimum of the given subtree. It is used in the delete in order to execute in the correct way the "transplant" and substitution of the subtree
 * @param t tree
 * @param x root of the subtree
 * @return the node with the minimum value of the subtree
 */
node_t* tree_minimum(tree_t* t, node_t* x);

/**
 * Retrieves the node containing the minimum of the given subtree. It is used in the delete in order to execute in the correct way the "transplant" and substitution of the subtree
 * @param t tree
 * @param x root of the subtree
 * @return the node with the maximum value of the subtree
 */
node_t* tree_maximum (tree_t* t, node_t* x);

/**
 * Retrieves the node containing the successor value of the one given in input
 * @param t tree in which the lookup has to be performed
 * @param x node from which the successor will be looked for
 * @return the node containing the successor key
 */
node_t* tree_successor(tree_t* t, node_t* x);

/**
 * Retrieves the node containing the predecessor value of the one given in input
 * @param t tree in which the lookup has to be performed
 * @param x node from which the successor will be looked for
 * @return the node containing the predecessor key
 */
node_t* tree_predecessor(tree_t* t, node_t* x);

/* ------------------------------------------------------------------------------------------ stack prototypes ------------------------------------------------------------------------------------------ */
/**
 * Initializes a stack
 * @param s stack to initialize
 */
void stack_create(stack_t* s);

/**
 * @return true if the stack is empty, false otherwise
 */
int is_empty (stack_t*);

/**
 * Pops a command from a stack
 * @param s stack from which the pop will be performed
 * @return the command popped from the stack
 */
list_of_commands_t* pop (stack_t** s);

/**
 * Removes all the elements from the given stack
 * @param s stack to empty
 */
void make_empty_stack(stack_t* s);

/**
 * Creates and add a command in a stack
 * @param s stack in which the command is added
 * @param begin beginning address of the command
 * @param end ending address of the command
 * @param command_id id of the command
 * @param command type of command
 * @param text_line text of the line
 */
void stack_push_values (stack_t* s, int begin, int end, int command_id, char command, char* text_line);

/**
 * Adds an already existing node in the stack
 * @param s stack in which the command is added
 * @param node command to add
 */
void stack_push_node(stack_t* s, list_of_commands_t* node);

/**
 * Performs an undo operation. Adds an element in the redo stack
 * @param t tree
 * @param undo_stack stack containing the commands that can be undo
 * @param redo_stack stack containing the commands that can be redo
 */
void undo_command (tree_t* t, stack_t* undo_stack, stack_t* redo_stack);

/**
 * Performs a redo operation. Adds an element in the undo stack
 * @param t tree
 * @param undo_stack stack containing the commands that can be undo
 * @param redo_stack stack containing the commands that can be redo
 */
void redo_command (tree_t* t, stack_t* undo_stack, stack_t* redo_stack);

/**
 * Inserts an element in the tree after an undo/redo operation
 * @param t tree in which the insertion will be performed
 * @param key key of the node to add
 * @param text_line  text of the node to add
 */
void tree_insert_from_do(tree_t* t, int key, char* text_line);

/**
 * Deletes an element in a tree after an undo/redo operation
 * @param t  tree in which the delete will be performed
 * @param x node to delete
 */
void tree_delete_from_do(tree_t* t, node_t* x);

/**
 * Performs a fixup of the tree after an undo/redo operation
 * @param t tree to fix
 * @param x node from which the fixup will be applied
 * @param start beginning of the command
 * @param end  ending of the command
 */
void tree_key_fixup_from_do (tree_t* t, node_t *x, int start, int end);

/* ------------------------------------------------------------------------------------------ other prototypes ------------------------------------------------------------------------------------------ */

/**
 * Performs an in-order-tree-walk and prints the text_values of the tree
 * @param t tree to print
 * @param x root of the tree
 * @param start first value to print
 * @param end last value to print
 */
void in_order_iterative (tree_t * t, node_t* x, int start, int end);
/* ------------------------------------------------------------------------------------------ functions ------------------------------------------------------------------------------------------ */
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

node_t* make_tree_node(tree_t* t, int key, char* text_line) //node creation
{
    node_t* n = (node_t*) malloc(sizeof(node_t));
    n->col = RED;
    n->p = t->nil;
    n->left = t->nil;
    n->right = t->nil;
    n->key = key;
    n->text_line = text_line; //"copies" the text in the text_line field of the node

    return n;
}

void destroy_tree_node(node_t* n)
{
    free(n);
}

node_t* make_node_nil() //nil-node creation
{
    node_t* nil = (node_t*) malloc(sizeof(node_t));
    nil->col = BLACK;
    nil->key = -1;
    nil-> p = NULL;
    nil->left = NULL;
    nil->right = NULL;

    return nil;
}

void tree_create(tree_t* t)
{
    t->nil = make_node_nil();
    t->root = t->nil; //at the beginning root and NIL coincide
    t->number_of_keys = 0;
}

void destroy_subtree(tree_t* t, node_t* node)
{
    if (node == t->nil)
        return;
    else if (node->p != t->nil){
        if (node == node->p->left)
            node->p->left = t->nil;
        else
            node->p->right = t->nil;
    } else if (node == t->root){
        t->root = t-> nil;
    }

    node_t* left = node->left;
    if (left != t->nil)
        left->p = t->nil;

    node_t* right = node->right;
    if (right != t->nil)
        right->p = t->nil;
    destroy_tree_node(node);
    destroy_subtree(t, left);
    destroy_subtree(t, right);
}

node_t* tree_search(tree_t* t, int key)
{
    node_t* x = t->root;
    while (x != t->nil){
        int cmp;
        cmp = (key - x->key);
        if (cmp == 0)
            return x;
        else if (cmp < 0)
            x = x->left;
        else
            x = x->right;
    }
    return NULL;
}

void tree_insert (tree_t* t, int key, char* text_line, int command_id, stack_t* s)
{
    node_t* y;
    if ((y = tree_search(t,key))){ //checks the node is not already present in the tree, in this case the values of the tree are updated
        stack_push_values(s, y->key, y->key, command_id, CHANGE, y->text_line); // saves in the undo stack, the already present values of the stack, as a change command
        y->key = key;
        y->text_line = text_line;
        stack_push_values(s, key, key, command_id, DELETE, text_line); //saves in the undo stack as a "delete" command
        return;
    }
    else{ //the node is not in the tree: it has to be created and inserted
        node_t* x = make_tree_node(t,key,text_line);

        node_t* pre = t->nil;
        node_t* cur = t->root;
        while (cur != t->nil){
            pre = cur;
            if (x->key < cur->key)
                cur = cur -> left;
            else
                cur = cur -> right;
        }
        x->p = pre;
        if (pre == t->nil) {
            t->root = x;
        } else if (x->key < pre->key)
            pre->left = x;
        else
            pre->right = x;

        x->left = t->nil;
        x->right = t->nil;
        x->col = RED;
        tree_insert_fixup(t,x);

        t->number_of_keys++; //increases the number of the keys, used to print eventual "."

        stack_push_values(s, x->key, x->key, command_id, DELETE, x->text_line); //the node was not present: only previous deletes are added
    }

}

void tree_insert_from_do(tree_t* t, int key, char* text_line)
{
    if (key == -1){ //case in which the value to pop from the stack is a "NULL" text or empty
        return;
    }

    node_t* y;
    if ((y = tree_search(t,key))){ //checks the node is not already present in the tree. If yes, the values of the tree are updated
        y->key = key;
        y->text_line = text_line;
        return;
    }
    else{ //the node is not already present in the tree. It has to be inserted
        node_t* x = make_tree_node(t, key, text_line);

        node_t* pre = t->nil;
        node_t* cur = t->root;
        while (cur != t->nil){
            pre = cur;
            if (x->key < cur->key)
                cur = cur -> left;
            else
                cur = cur -> right;
        }
        x->p = pre;
        if (pre == t->nil) {
            t->root = x;
        } else if (x->key < pre->key)
            pre->left = x;
        else
            pre->right = x;

        x->left = t->nil;
        x->right = t->nil;
        x->col = RED;
        tree_insert_fixup(t,x);

        t->number_of_keys++; //increases the number of the keys, used to print eventual "."
    }
}

void tree_insert_fixup(tree_t* t, node_t* z)
{
    while (z->p->col == RED) {
        if (z->p == z->p->p->left) {
            node_t* y = z->p->p->right;
            if (y->col == RED){        //Case 1 - the "uncle" y is red, position of z is irrelevant
                z->p->col = BLACK;
                y->col = BLACK;
                z->p->p->col = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right){ //Case 2: the "uncle" y is black and z == x.right --> rotate z
                    z = z->p;
                    left_rotate(t, z);
                }
                z->p->col = BLACK; // Caso 3: lo "zio" y è nero, z = x.left
                z->p->p->col = RED;
                right_rotate(t, z->p->p);
            }
        } else { //like from node_t* y = z->p->p->right; to right_rotate(t, z->p->p); but replacing right with left
            node_t* y = z->p->p->left;
            if (y->col == RED){
                z->p->col = BLACK;
                y->col = BLACK;
                z->p->p->col = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(t, z);
                }
                z->p->col = BLACK;
                z->p->p->col = RED;
                left_rotate(t, z->p->p);
            }
        }
    }
    t->root->col = BLACK;
}

void tree_delete(tree_t* t, node_t* x, int command_id, stack_t* s)
{

    node_t* subt;
    node_t* to_del;

    if (x == NULL) {
        stack_push_values(s, -1, -1, command_id, CHANGE, "\0");
        return;
    }
    stack_push_values(s, x->key, x->key, command_id, CHANGE, x->text_line); //saves on the undo_stack the values that will be cancelled as a CHANGE command

    if ((x->left == t->nil) || (x->right == t->nil)){
        to_del = x;
    }
    else{
        to_del = tree_predecessor(t, x);
    }
    if (to_del->left != t->nil){
        subt = to_del->left;
    }
    else{
        subt = to_del->right;
    }
    subt->p = to_del->p;
    if (to_del->p == t->nil){
        t->root = subt;
    }
    else if (to_del == to_del->p->left){
        to_del->p->left = subt;
    }
    else{
        to_del->p->right = subt;
    }

    if (to_del != x){
        x->key = to_del->key;//if to_del has other fields, they have to be copied
        x->text_line = to_del->text_line; //"copies" the text_line of to_del to x
    }
    if (to_del->col == BLACK) {
        tree_delete_fixup(t, subt);
    }
    t->number_of_keys--;

    free(to_del);
}

void tree_delete_from_do(tree_t* t, node_t* x)
{
    node_t* subt;
    node_t* to_del;

    if (x == NULL)
        return;

    if ((x->left == t->nil) || (x->right == t->nil)){
        to_del = x;
    }
    else{
        to_del = tree_predecessor(t, x);
    }
    if (to_del->left != t->nil){
        subt = to_del->left;
    }
    else{
        subt = to_del->right;
    }
    subt->p = to_del->p;
    if (to_del->p == t->nil){
        t->root = subt;
    }
    else if (to_del == to_del->p->left){
        to_del->p->left = subt;
    }
    else{
        to_del->p->right = subt;
    }

    if (to_del != x){
        x->key = to_del->key;//if to_del has other fields, they have to be copied
        x->text_line = to_del->text_line; //"copies" the text_live of to_del to x
    }
    if (to_del->col == BLACK) {
        tree_delete_fixup(t, subt);
    }
    t->number_of_keys--;

    free(to_del);
}

void tree_delete_fixup(tree_t* t, node_t* x)
{
    while (x != t->root && x->col == BLACK) {
        if (x == x->p->left){
            node_t* w = x->p->right;
            if (w->col == RED) { // case 1
                w->col = BLACK;
                x->p->col = RED;
                left_rotate(t, x->p);
                w = x->p->right;
            }
            if (w->left->col == BLACK && w->right->col == BLACK) { // case 2
                w->col = RED;
                x = x->p;
            } else {
                if (w->right->col == BLACK) { // case 3
                    w->left->col = BLACK;
                    w->col = RED;
                    right_rotate(t, w);
                    w = x->p->right;
                }
                w->col = x->p->col; //case 4
                x->p->col = BLACK;
                w->right->col = BLACK;
                left_rotate(t, x->p);
                x = t->root;
            }
        } else { //like from node_t* w = x->p->right; to x = t->root; but replacing "right" and "left"
            node_t* w = x->p->left;
            if (w->col == RED) {
                w->col = BLACK;
                x->p->col = RED;
                right_rotate(t, x->p);
                w = x->p->left;
            }
            if (w->right->col == BLACK && w->left->col == BLACK) {
                w->col = RED;
                x = x->p;
            } else {
                if (w->left->col == BLACK) {
                    w->right->col = BLACK;
                    w->col = RED;
                    left_rotate(t, w);
                    w = x->p->left;
                }
                w->col = x->p->col;
                x->p->col = BLACK;
                w->left->col = BLACK;
                right_rotate(t, x->p);
                x = t->root;
            }
        }
    }
    x->col = BLACK;
}

void left_rotate (tree_t* t, node_t* x)
{
    node_t* y = x->right; //computes y
    x->right = y->left; //moves the subtree of beta
    if (y->left != t->nil) // fixes the referring systems to p of the radix of beta
        y->left->p = x;
    y->p = x->p; //Fixes the reffering system to the father of node y
    if (x->p == t->nil) { //Fixes the referring system to the son of the father of y
        t->root = y;
    } else if (x == x->p->left)
        x->p->left = y;
    else {
        x->p->right = y;
    }
    y->left = x; //Hooks x to the left of y
    x->p =y;
}

void right_rotate (tree_t* t, node_t* x)
{
    node_t* y = x->left;
    x->left = y->right;
    if (y->right != t->nil)
        y->right->p = x;
    y->p = x->p;
    if (x->p == t->nil) {
        t->root = y;
    } else if (x == x->p->left)
        x->p->left = y;
    else {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
}

node_t* tree_maximum (tree_t* t, node_t* x)
{
    while (x->right != t->nil)
        x = x->right;

    return x; //Time: O(h). h: height of the tree
}

node_t* tree_minimum (tree_t* t, node_t* x) //function used to retrieve the minimum of the given subtree. It is used in the delete in order to execute in the correct way the "transplant" and substitution of the subtree
{
    while (x->left != t->nil)
        x = x->left;

    return x; //Time: O(h). h: height of the tree
}

node_t* tree_predecessor(tree_t* t, node_t* x)
{
    if (x->left != t->nil)
        return tree_maximum(t,x->left);
    node_t* y = x->p;
    while (y != t->nil && x == y->left){
        x = y;
        y = y->p;
    }
    return y; //Time: O(h). h: height of the tree
}

node_t* tree_successor(tree_t* t, node_t* x)
{
    if (x->right != t->nil)
        return tree_minimum(t,x->right);
    node_t* y = x->p;
    while (y != t->nil && x == y->right){
        x = y;
        y = y->p;
    }
    return y; //Time: O(h). h: height of the tree
}

void tree_key_fixup (tree_t* t, node_t *x, int start, int end)
{
    if (x != t->nil){
        tree_key_fixup(t, x->left, start, end);
        if (x->key >= end)
            x->key = x->key - (end-start+1);
        tree_key_fixup(t, x->right, start, end);
    }
}

void tree_key_fixup_from_do (tree_t* t, node_t *x, int start, int end)
{
    if (x != t->nil){
        tree_key_fixup_from_do(t, x->left, start, end);
        if (x->key >= start)
            x->key = x->key + (end-start+1);
        tree_key_fixup_from_do(t, x->right, start, end);
    }
}

void stack_create(stack_t* s)
{
    s->size = 0;
    s->top = NULL;
}

int is_empty (stack_t* s)
{
    return s->top == NULL;
}

list_of_commands_t* pop (stack_t** s)
{
    list_of_commands_t* old_top;

    if(!((*s)->top))
        return NULL;

    old_top = (*s)->top;
    (*s)->top = (*s)->top->next;

    return old_top;
}

void make_empty_stack(stack_t* s)
{
    list_of_commands_t* to_del;
    while (!is_empty(s)){
        to_del = pop(&s);
        free(to_del);
    }
    s->size = 0;
}

void stack_push_values (stack_t* s, int begin, int end, int command_id, char command, char* text_line)
{
    list_of_commands_t *new_node = (list_of_commands_t*) malloc(sizeof (list_of_commands_t));

    if (new_node){
        new_node->begin = begin;
        new_node->end = end;
        new_node->command_id = command_id;
        new_node->command = command;
        new_node->text_line = text_line;

        new_node->next = s->top;
        s->top = new_node;
    } else
        printf("Memory allocation error!\n");

}

void stack_push_node(stack_t* s, list_of_commands_t* node)
{
    node->next = s->top;
    s->top = node;
}

void undo_command (tree_t* t, stack_t* undo_stack, stack_t* redo_stack)
{
    list_of_commands_t* node_to_redo;

    if (undo_stack->top->command == CHANGE){
        tree_insert_from_do(t, undo_stack->top->begin, undo_stack->top->text_line);
        node_to_redo = pop(&undo_stack);
        stack_push_node(redo_stack, node_to_redo);
    } else if (undo_stack->top->command == DELETE){
        tree_delete_from_do(t, tree_search(t,undo_stack->top->begin));
        node_to_redo = pop(&undo_stack);
        stack_push_node(redo_stack, node_to_redo);
    } else if (undo_stack->top->command == FIX_VALUES){
        tree_key_fixup_from_do(t, t->root, undo_stack->top->begin, undo_stack->top->end);
        node_to_redo = pop(&undo_stack);
        stack_push_node(redo_stack, node_to_redo);
    }
}

void redo_command (tree_t* t, stack_t* undo_stack, stack_t* redo_stack) //N.B. The nodes of the redo stack are equivalent to the ones of the undo stack, but they are executed in a mirrored way
{
    list_of_commands_t* node_to_undo;

    if (redo_stack->top->command == CHANGE){
        tree_delete_from_do(t, tree_search(t, redo_stack->top->begin));
        node_to_undo = pop(&redo_stack);
        stack_push_node(undo_stack, node_to_undo);
    } else if (redo_stack->top->command == DELETE){
        tree_insert_from_do(t, redo_stack->top->begin, redo_stack->top->text_line);
        node_to_undo = pop(&redo_stack);
        stack_push_node(undo_stack, node_to_undo);
    } else if (redo_stack->top->command == FIX_VALUES){
        tree_key_fixup(t,t->root,redo_stack->top->begin, redo_stack->top->end);
        node_to_undo = pop(&redo_stack);
        stack_push_node(undo_stack, node_to_undo);
    }
}


int main () {

    int start, end, i;
    int line_number;
    int tree_number_of_keys;
    int command;
    int command_id = 1;
    int starting_command_id;

    int start_do; //variable used to implement an "algebraic sum" between undo-s and redo-s in order to speed up the undo/redo commands
    int temporary_undo_stack_size;
    int temporary_redo_stack_size;
    int a;

    char text[MAXLINESIZE+1];
    char * effective_string;

    tree_t* t = (tree_t*)malloc(sizeof(tree_t));
    stack_t* undo_stack = (stack_t*)malloc(sizeof(stack_t));
    stack_t* redo_stack = (stack_t*)malloc(sizeof(stack_t));

    tree_create(t);
    stack_create(undo_stack);
    stack_create(redo_stack);

    do {
        scanf("%d,%d", &start, &end);
        command = getchar_unlocked();

        //analysis of the various commands
        if (command == UNDO){
            getchar_unlocked();
            temporary_undo_stack_size = undo_stack->size;
            temporary_redo_stack_size = redo_stack->size;
            a = min(start, temporary_undo_stack_size);
            start_do = a;  //undo-s are counted as positive
            temporary_undo_stack_size = temporary_undo_stack_size - a;
            temporary_redo_stack_size = temporary_redo_stack_size + a;
            do{
                scanf("%d,%d", &start, &end);
                command = getchar_unlocked();
                if (command == UNDO){
                    a = min(start, temporary_undo_stack_size);
                    start_do = start_do+a;  //undo-s are counted as positive
                    temporary_undo_stack_size = temporary_undo_stack_size - a;
                    temporary_redo_stack_size = temporary_redo_stack_size + a;
                }
                else if (command == REDO){
                    a = min(start, temporary_redo_stack_size);
                    start_do = start_do-a;
                    temporary_redo_stack_size = temporary_redo_stack_size - a;
                    temporary_undo_stack_size = temporary_undo_stack_size + a;
                }
            } while (command == UNDO || command == REDO);
            if (start_do > 0){
                for (i = 0; i < start_do; i++){
                    starting_command_id = undo_stack->top->command_id;
                    while (undo_stack->top != NULL && (undo_stack->top->command_id == starting_command_id))
                        undo_command(t,undo_stack,redo_stack);
                    undo_stack->size--;
                    redo_stack->size++;
                }
            } else if (start_do < 0 ){
                for (i = 0; i < (-start_do); i++){
                    starting_command_id = redo_stack->top->command_id;
                    while (redo_stack->top != NULL && (redo_stack->top->command_id == starting_command_id))
                        redo_command(t, undo_stack,redo_stack);
                    redo_stack->size--;
                    undo_stack->size++;
                }
            }
        }
        else if (command == REDO){
            getchar_unlocked();

            //undo-s are counted as positive, redo-s as negative
            temporary_undo_stack_size = undo_stack->size;
            temporary_redo_stack_size = redo_stack->size;
            a = min(start, temporary_redo_stack_size);
            start_do = - a;
            temporary_redo_stack_size = temporary_redo_stack_size - a;
            temporary_undo_stack_size = temporary_undo_stack_size + a;
            do{
                scanf("%d,%d", &start, &end);
                command = getchar_unlocked();
                if (command == UNDO){
                    a = min(start, temporary_undo_stack_size);
                    start_do = start_do + a;  //undo-s are counted as positive
                    temporary_undo_stack_size = temporary_undo_stack_size - a;
                    temporary_redo_stack_size = temporary_redo_stack_size + a;
                }
                else if (command == REDO) {
                    a = min(start, temporary_redo_stack_size);
                    start_do = start_do-a;
                    temporary_redo_stack_size = temporary_redo_stack_size - a;
                    temporary_undo_stack_size = temporary_undo_stack_size + a;
                }
            } while (command == UNDO || command == REDO);
            if (start_do > 0){
                for (i = 0; i < start_do; i++){
                    starting_command_id = undo_stack->top->command_id;
                    while (undo_stack->top != NULL && (undo_stack->top->command_id == starting_command_id)) {
                        undo_command(t,undo_stack,redo_stack);
                    }
                    undo_stack->size--;
                    redo_stack->size++;
                }
            } else if (start_do < 0 ){
                for (i = 0; i < (-start_do); i++){
                    starting_command_id = redo_stack->top->command_id;
                    while (redo_stack->top != NULL && (redo_stack->top->command_id == starting_command_id))
                        redo_command(t, undo_stack,redo_stack);
                    redo_stack->size--;
                    undo_stack->size++;
                }
            }
        }

        if (command == CHANGE){
            getchar_unlocked();
            for (line_number = start; line_number <= end; line_number++){
                fgets(text, MAXLINESIZE+1, stdin);
                effective_string = malloc(strlen(text)+1);
                strcpy(effective_string, text);
                tree_insert (t, line_number, effective_string, command_id, undo_stack);
            }
            undo_stack->size++;
            make_empty_stack(redo_stack);

            command_id++;
        }

        else if (command == DELETE){
            getchar_unlocked();

            tree_number_of_keys = t->number_of_keys;
            for (line_number = start; line_number <= end; line_number++){
                if (line_number > tree_number_of_keys || line_number < 1)
                    stack_push_values(undo_stack, -1, -1, command_id, CHANGE, "\0");
                else
                    tree_delete(t, tree_search(t, line_number), command_id, undo_stack);
            }
            if(end < tree_number_of_keys){
                tree_key_fixup(t, t->root, start, end);
                stack_push_values(undo_stack, start, end, command_id, FIX_VALUES, "\0");
            }
            undo_stack->size++;
            make_empty_stack(redo_stack);

            command_id++;
        }

        else if (command == PRINT){
            getchar_unlocked();
            while (start<1){
                fputc_unlocked(POINT, stdout);
                fputc_unlocked(NEWLINE, stdout);
                start++;
            }
            if (start > t->number_of_keys){
                for (i = start; i <= end; i++){
                    fputc_unlocked(POINT, stdout);
                    fputc_unlocked(NEWLINE, stdout);
                }
            } else {
                in_order_iterative(t, tree_search(t, start), start, end);
                for (i = t->number_of_keys; i < end; i++){
                    fputc_unlocked(POINT, stdout);
                    fputc_unlocked(NEWLINE, stdout);
                }
            }
        }
    } while (command != QUIT);

    return 0;
}

void in_order_iterative (tree_t * t, node_t* x, int start, int end)
{
    while ((start <= end) && (start <= t->number_of_keys)){
        fputs(x->text_line, stdout);
        x = tree_successor(t,x);
        start++;
    }
}
