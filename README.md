# Height-balanced-binary-search-tree-C

## How it works

The program starts from an empty tree and grows based on a sequence of insertion and deletion operations. 
Following each insertion/deletion of a tree node, the tree performs rotations in order to be height balanced. 


## Compiling 

gcc -std=c99 -Wvla -Wall -Wshadow -g *.c -o tree

./tree -b operations_input_file tree_output_file

- "-b" flag means that you are building the tree

./tree -e tree input file

- "-e" flag means that you are evaluating the tree
- the result with me 3 integers
- 1st integer indicates validity of input file
   - if file cannot be opended value is -1 
   - if file can be opended but wrong file type value is 0 
   - if the file can be opended and correct file type value is 1
- 2nd integer indicates whether the tree is a Binary Search Tree (BST)
   - if tree is BST value is 1
   - if tree not BST value is 0
- 3rd integer indicates whether the tree is height balanced
   - if tree is height balanced value is 1
   - if tree is not height balanced value is 0

## Example Files 

### operations_input_file 
- A file consiting of a key (int) and an ASCII character (char) of either 'i' or 'd'. 
- 'i' for insertion 
- 'd' for deletion

### tree_output_file
- A file consisting of the pre-order tranversal of the constructed hight-balanced tree
- Along with each node, a numerical value is shown providing information for child nodes
   - 0 : no child node exist
   - 1 : right child node exist
   - 2 : left child node exist
   - 3 : both left and right child nodes exist

### Provided example executions 
- Operations_input_file's : ops0.b, ops1.b
   - Text file equivalents are also provided : ops0.txt , ops1.txt
- Tree_output_file : tree0.b, tree1.b 
   - This are expected outputs files, used to compare if program is working as expected 
   - Text file equivalents are also provided : tree0.txt , tree1.txt
