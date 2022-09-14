# Height-balanced-binary-search-tree-C

## How it works

The program starts from an empty tree and grows based on a sequence of insertion and deletion operations. 
Following each insertion/deletion of a tree node, the tree performs rotations in order to be height balanced. 


## Compiling 

gcc -std=c99 -Wvla -Wall -Wshadow -g *.c -o tree

./tree -b operations_input_file tree_output_file


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
