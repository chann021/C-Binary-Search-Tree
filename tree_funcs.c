#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//function to initialize a binary search tree
void bst_init(bst_t *tree){
  tree->root = NULL;              //sets the tree's root to NULL
  tree->size = 0;                 //sets the tree's size to 0
}

//function to take a name/word and insert it correctly into the BST
int bst_insert(bst_t *tree, char name[]){
  node_t *cur = tree->root;                       //accesses the root of the tree and assigns it to the node pointer cur
  if(cur == NULL){                                //case to insert a name/word into an empty BST

    node_t *new_node = malloc(sizeof(node_t));    //allocates the necessary memory for a new node_t
    strcpy(new_node->name, name);                 //copys the name being inserted into the new node's field to store the name

    new_node->left = NULL;                        //initializes the left branch of the new node to NULL
    new_node->right = NULL;                       //initializes the right branch of the new node to NULL

    tree->root = new_node;                //sets the root of the BST to the newly created node
    tree->size++;                         //adds 1 to the size of the BST
    return 1;
  }else{                                  //usual case where this is already a node at the root of the tree

    node_t *tmp = cur;                     //assigns a temporary node to the root of the tree(cur)
    node_t *prev = NULL;                   //assigns a node pointer to NULL, to be used to track the previous node
    int lefty = 0;                         //integer value to keep track of which branch the new node will be added to

    while(tmp != NULL){                        //loop to break when tmp reaches the end of a branch
      int alpha = strcmp(tmp->name, name);     //compares the temporary node's name value to the one being inserted
      prev = tmp;                              //assigns prev to the tmp node to keep track of previous nodes

      if(alpha > 0){                        //if the value(alpha) that returns from comparing char arrays is greater than 0 then the name being inserted comes before(alphabetically) the tmp nodes name
        lefty = 1;                          //sets lefty to 1 so the function knows that the new node will be inserted to a left branch
        tmp = tmp->left;                    //sets tmp to the next node on the left branch
      }

      else if(alpha < 0){                   //if the value(alpha) that returns from comparing char arrays is less than 0 then the name being inserted comes after(alphabetically) the tmp nodes name
        lefty = 0;                          //sets lefty to 0 so the function knows that the new node will be inserted to a right branch
        tmp = tmp->right;                   //sets tmp to the next node on the right branch
      }

      else if(alpha == 0){                  //function returns 0 if the name is already in the BST
        return 0;
      }
    }
    node_t *new_node = malloc(sizeof(node_t));    //allocates the necessary space in memory for a new node
    new_node->left = NULL;                        //initializes the left branch of the new node to NULL
    new_node->right = NULL;                       //initializes the right branch of the new node to NULL
    strcpy(new_node->name, name);                 //copys the name being inserted into the new node's field to store the name

    if(lefty == 1){                           //determines if the new node being added is to be added to the left branch of the previous node
      prev->left = new_node;                  //inserts the new node into the correct position in the BST
    }

    else{                                     //if the new node is to be added to the right branch then it inserts it into the right branch of the previous node
      prev->right = new_node;
    }
  }
  tree->size++;                             //after inserting the function adds 1 to the BSTs size
  return 1;
}

//function the search the BST and determine if a given name is already in the BST
int bst_find(bst_t *tree, char name[]){
  if(tree->root == NULL){                   //if the tree is empty the function returns 0
    return 0;
  }

  else{
    int done = 0;                          //initializes an integer done to signify when the end of the tree was reached or the name was found
    node_t *next_node = tree->root;        //stores the trees root to the node next_node

    while(!done){                                  //doesn't stop looping until done is updated to 1
      int alpha = strcmp(next_node->name, name);       //compares the char array stored in next_node to the char array entered into the function
      if(alpha > 0){                               //if alpha is greater than 0 then the name the function is searching for comes before the next_node's name
        next_node = next_node->left;               //sets the next_node to the next node on the left branch of next_node

        if(next_node == NULL){                   //checks if the function reached the end of the branch and if so returns 0
          return 0;
        }
      }

      else if(alpha < 0){                         //if alpha is less than 0 then the name the function is searching for comes after the next_node's name
        next_node = next_node->right;             //sets the next_node to the next node on the right branch of next_node

        if(next_node == NULL){                  //checks if the function reached the end of the branch and if so returns 0
          return 0;
        }
      }

      else{                    //sets done to 1 to tell the loop that the name has been found and it can now exit
        done = 1;
      }
    }
  }
  return 1;                //returns 1 to signify the name was found
}

//function to clear the current BST and use the helper function node_remove_all to free all memory allocated
void bst_clear(bst_t *tree){
  node_remove_all(tree->root);      //calls function node_remove_all on the tree's root to free memory
  tree->root = NULL;                //resets the tree's root to NULL and its size to 0
  tree->size = 0;
  return;
}

//recursive helper function to free all allocated memory
void node_remove_all(node_t *cur){
  if(cur == NULL){                     //base case to determine when the ends of branches were reached
    return;
  }

  node_remove_all(cur->left);          //two recursive calls on each node's children to ensure all memory is freed
  node_remove_all(cur->right);

  free(cur);                          //frees the allocated memory for the node cur
  return;
}

//function to print the current BST in reverse order at differing indentation, calls on the helper function node_print_revorder
void bst_print_revorder(bst_t *tree){
  node_print_revorder(tree->root, -2);        //calls the function node_print_revorder on the tree root with the indentation level set to -2
  return;
}

//recursive helper function to manage the indentation level and print the BST in reverse order
void node_print_revorder(node_t *cur, int indent){
  indent += 2;                                            //adds 2 to the indentation for each level of the tree
  if(cur == NULL){                                        //ensures the tree isn't empty
    return;
  }

  node_print_revorder(cur->right, indent);              //recursive call on the right branch of the current node

  for(int i = 0; i < indent; i++){                  //for loop to print the correct indentation for each name
    printf(" ");
  }
  printf("%s\n", cur->name);                        //prints the name

  node_print_revorder(cur->left, indent);           //recursive call on the left branch of the current node
  return;
}

//function to print the current BST in preorder with the correct indentation
void bst_print_preorder(bst_t *tree){
  node_write_preorder(tree->root, stdout, -1);      //calls the function node_write_preorder on the tree's root with the terminal as its output device and -1 as the indentation level
  return;
}

//recursive helper function to write the current BST in preorder to the terminal or a given file
void node_write_preorder(node_t *cur, FILE *out, int depth){
  depth++;                                                   //adds 1 to the depth level
  if(cur != NULL){                                           //ensure the tree isn't empty and is used to determine when all the nodes have been printed

    for(int i = 0; i < depth*2; i++){                        //for loop to print the correct number of indents based on the level depth(2 indents per 1 level) to the correct file or output device
      fprintf(out, " ");
    }
    fprintf(out, "%s\n", cur->name);                        //prints the current nodes name to the file or output device

    node_write_preorder(cur->left, out, depth);           //recursive call on the current nodes left branch
    node_write_preorder(cur->right, out, depth);          //recursive call on the current nodes right branch
  }
  return;
}

//function to save the current BST to a file by using the helper function node_write_preorder
void bst_save(bst_t *tree, char *fname){
  FILE *opened = fopen(fname, "w");                         //opens the given file name to write the BST to
  node_write_preorder(tree->root, opened, -1);              //calls on node_write_preorder to write the BST in preorder with correct indentation to the open file, opened
  fclose(opened);                                      //closes the file to ensure no memory is lost
}

//function to load a file of BST names in preorder to create a new tree
int bst_load(bst_t *tree, char *fname){
  FILE *opened = fopen(fname, "r");               //opens the given file name to be read
  if(opened == NULL){                            //checks for an empty file
    return 0;
  }

  bst_clear(tree);                                 //calls on bst_clear to clear the current BST
  char storage[128];                               //char array to temporarily store names

  while(fscanf(opened, "%s",storage) == 1){         //reads one name at a time from the file
    bst_insert(tree, storage);                  //calls on bst_insert to insert the names into the BST
  }

  fclose(opened);                          //closes the file so no memory is lost
  return 1;
}
