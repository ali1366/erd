#ifndef LOADDATA_H_INCLUDED
#define LOADDATA_H_INCLUDED
extern char *Data_Hp_Array[100];
extern char *Data_St_Array[18];
extern char *Data_Ml_Array[90];
extern int count_Array[3][100];
void load_data(char *DB_Path);
void free_data(void);
#endif // LOADDATA_H_INCLUDED
