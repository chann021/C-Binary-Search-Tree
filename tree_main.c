#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


//main function to process command line arguments and print the commands implemented for the user to use
int main(int argc, char *argv[]){
  int echo = 0;
  if(argc > 1 && strcmp("-echo", argv[1]) == 0){         //Checks the command line for "-echo" and if it is found then it sets echo to 1
    echo = 1;
  }
  //Prints the "BST Demo" to show the user what commands they can use and a mini definition of what they do
  printf("BST Demo\n");
  printf("Commands:\n");
  printf("  print:           shows contents of the tree in reverse sorted order\n");
  printf("  clear:           eliminates all elements from the tree\n");
  printf("  quit:            exit the program\n");
  printf("  add <name>:      inserts the given string into the tree, duplicates ignored\n");
  printf("  find <name>:     prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:     clears the current tree and loads the one in the given file\n");

  char cmd[128];
  bst_t tree;
  int success;                               //Initializes a variable success to be used when scaning from files and when using the find function
  bst_init(&tree);                           //Calls on bst_init to initialize a binary search tree

  while(1){
    printf("BST> ");
    success = fscanf(stdin,"%s",cmd);        //read a command
    if(success == EOF){                    //check for end of input
      printf("\n");
      break;
    }
//condition to check if user typed print and if so call on function bst_print_revorder
    if(strcmp("print", cmd)== 0){
      if(echo){                            //prints "print" to terminal if user turned echo on
        printf("print\n");
      }
      bst_print_revorder(&tree);
    }
//condition to check if user typed clear and if so calls on function bst_clear
    else if(strcmp("clear", cmd)== 0){
      if(echo){                           //prints "clear" to terminal if user turned echo on
        printf("clear\n");
      }
      bst_clear(&tree);
    }
//condition to check if user typed quit and if so exits out of the while loop
    else if(strcmp("quit", cmd)== 0){
      if(echo){                          //prints "quit" to terminal if user turned echo on
        printf("quit\n");
      }
      break;
    }
//condition to check if user typed add and if so calls the function bst_insert to place the next command line argument into the BST
    else if(strcmp("add", cmd)== 0){
      fscanf(stdin, "%s", cmd);          //reads the name/word the user wants added to the BST
      if(echo){                          //prints "add <name/word>" to terminal if user turned echo on
        printf("add %s\n", cmd);
      }
      bst_insert(&tree, cmd);
    }
//condition to check if user typed find and if so calls the function bst_find
    else if(strcmp("find", cmd)== 0){
      fscanf(stdin, "%s", cmd);          //reads the name/word the user wants to search the BST for
      if(echo){                          //prints "find <name/word>" to terminal if user turned echo on
        printf("find %s\n", cmd);
      }
//checks to see if the word cmd is already in the BST and sets success to 1 if it is and 0 if not
      success = bst_find(&tree, cmd);
      if(!success){                      //if the name/word wasnt found in the BST, then it prints "NOT FOUND"
        printf("NOT FOUND\n");
      }else{                             //if the name/word is found in the BST, then it prints "FOUND"
        printf("FOUND\n");
      }
    }
//condition to check if user typed preorder and if so calls the function bst_print_preorder
    else if(strcmp("preorder", cmd)== 0){
      if(echo){                          //prints "preorder" to terminal if user turned echo on
        printf("preorder\n");
      }
      bst_print_preorder(&tree);
    }
//condition to check if user typed save and if so calls the function bst_save to save the current BST to the file specified
    else if(strcmp("save", cmd)== 0){
      fscanf(stdin, "%s", cmd);          //reads the file name that the BST will be saved to
      if(echo){                          //prints "save <filename>" to terminal if user turned echo on
        printf("save %s\n", cmd);
      }
      bst_save(&tree, cmd);
    }
//condition to check if the user typed load and if so calls the function bst_load to read the data from the file to a BST
    else if(strcmp("load", cmd)== 0){
      fscanf(stdin, "%s", cmd);          //reads the file name that the BST will be formed from
      if(echo){                          //prints "load <filename>" to terminal if user turned echo on
        printf("load %s\n", cmd);
      }
      bst_load(&tree, cmd);
    }
//condition to catch any unknown commands
    else{
      if(echo){                         //prints the users incorrect input to terminal if user turned echo on
        printf("%s\n", cmd);
      }
      printf("Unknown command '%s'\n", cmd);
    }
  }
  bst_clear(&tree);                  //calls upon bst_clear to clear the current BST before ending the program
  return 0;
}
