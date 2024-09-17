#ifndef GENERATE_SEQUENCE_H_INCLUDED
#define GENERATE_SEQUENCE_H_INCLUDED
//char* GenerateNewSequence(char*SeqArray,char* sequence,char*structure,int*starray,int*hparray,int*size);
char* GenerateNewSequence(char*SeqArray,char* sequence,char*generaedStructure,int*starray,int*hparray,int*mlarray,int*size);
char * GeneratingNewSubSequences(int lenght,int kind);
char* initialize_sequence(int sequence_lenght,int*starray,int * hparray,int*size);
char* initialize_multiloop_sequence(int sequence_lenght,int*starray,int * hparray,int * mlarray,int *size);
char*initial_RNAInvers(char*structure);
//void set_constraint_sequence(char* sequence,char* constraint_sequence);
void set_constraint_sequence(char* sequence,int * cons_table);
char* check_constraint_sequence(char* target_structure, char* input_constrain_sequence);
int * generat_constrain_seq_matrix(char*target_structure,char*constraint_sequence);
char * generat_random_cons_seq(char*structure);
int * constarin_table(char* constrain_sequence);
#endif // GENERATE_SEQUENCE_H_INCLUDED
