#ifndef IO
#define IO

/* reads the input file who contains the graph and return a vertex array,
the function changes the variable size too, this way we can have the number of vertices */
Vertex* read_input_file(int* size, char* argv,int* totalCost);
/* sorts the mst array */
void insertion_sort_mst(Edge* MST, int size);
/* function thats makes the first number of a mst edge smaller than the second, for convention */
void adjust_mst(Edge* MST, int size);
/* prints the terminal output (mst cost, total saved, unique mst) */
void print_output(int mstCost, int graphCost, int unique);
/* prints the mst on a file setted in the execution */
void print_output_file(Edge* MST, char* argv, int size);
/* prints the mst on the terminal */
void _print_mst(Edge* MST, int size);

#endif