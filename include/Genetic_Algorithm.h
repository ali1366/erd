#ifndef GENETIC_ALGORITHM_H_INCLUDED
#define GENETIC_ALGORITHM_H_INCLUDED
int *selected_sequence(char *SeqArray,char*structure);
int* selected_structure(char*structure,char*StrArray,int *best_dist);

char * GeneticAl_eval15(char * structure,char*sequence ,char* constrain_sequence);
char * GeneticAl_recursive(char*structure,char*sequence,char* constrain_sequence);
//char * GeneticAl_recursive_hand(char*structure,char*sequence);
char *GneticAl_final(char*structure,char* constrain_sequence);

#endif // GENETIC_ALGORITHM_H_INCLUDED
