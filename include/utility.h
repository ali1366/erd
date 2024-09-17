#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED


float runtime(long start,int milistart,long end ,int miliend);
char * merg_string(char*string1,char*string2,char*string3);
char * strpar(char*string,int start,int end);

int findfirst(char* string,int index_start_search,char target);
int findlast(char* string,int index_end_search,char target);
void delete_elements(int*array,int start,int end,int *size);
void delete_string_elements(char*string,int start,int end,int *size);
int sum(int*array,int start,int end);
int rand_diff(int start,int end);
int* find(int*array,char unequal,int comparison_value,int *size);
//int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p);
char * insert_in_string(char *string,char *inserted_string,int start_point,int end_point);

void usage_help(char* name);
void usage(char* name);
float run_RNAfold_probability(char*sequence);
#endif // UTILITY_H_INCLUDED
