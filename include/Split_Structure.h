#ifndef SPLIT_STRUCTURE_H_INCLUDED
#define SPLIT_STRUCTURE_H_INCLUDED
int check_brackets(char *Structure);
void countsplit(int*Count_Sp,int* tajamoi,char * MainStructure,char*structure,int *size);
void split_structure(int*starray,int*hparray,char *structure,int*size);
void splite_structure_multiloop(char* Structure,int* MultiLoopIndex,int* MultiloopIndexArray);
void splite_structure_hand(char* structure,int* handIndexArray);
void splite_structure_multiloop_unpair(int*starray,int*hparray,int*mlarray,char *structure,int*size );
int open_prantesis(char*structure);
#endif // SPLIT_STRUCTURE_H_INCLUDED
