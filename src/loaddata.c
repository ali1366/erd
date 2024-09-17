#include "loaddata.h"
#include <utility.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utils.h"


///-----------------------------------------------------------
/// Global arrays include pools of RNA sub-sequences
/// corresponding to different components with different lengths
///
char *Data_Hp_Array[100];
char *Data_St_Array[18];
char *Data_Ml_Array[90];
int count_Array[3][100];
/// ---------------------------------------------------



/// ---------------------------------------------------
/// Load data from DB3
///
void load_data(char *DB_Path)
{
    FILE *pFile;
    char *fName,*fLine,*nLine;
    char str[3];
    int number, i=1,j=1,k=0;
    for(i=1;i<18;i++)
    {
        sprintf(str, "%d", i);
        fName=merg_string("DB3//Stem//stem",str,".txt");
        pFile=fopen(fName,"r");
        if(pFile == NULL) perror ("Error opening file");
        else
        {
            fLine=get_line(pFile);
            fLine[strlen(fLine)]='\0';
            number=atoi(fLine);
            count_Array[0][i]=number;
            free(fLine);
            Data_St_Array[i]=(char*)malloc((i*2*number+2)*sizeof(char));
            Data_St_Array[i][0]='*';
            Data_St_Array[i][i*2*number+1]='\0';
            for(j=1;j<=number;j++)
            {
             nLine=get_line(pFile);
             nLine[strlen(nLine)]='\0';
              for(k=0;k<2*i;k++)
              {
                  Data_St_Array[i][(j-1)*2*i+k+1]=nLine[k];
              }
              free(nLine);
            }
            free(fName);
            fclose(pFile);
        }
    }

    for(i=1;i<100;i++)
    {
        sprintf(str, "%d", i);
        fName=merg_string(".//DB3//Hp//Hp",str,".txt");
        pFile=fopen(fName,"r");
        if(pFile == NULL) perror ("Error opening file");
        else
        {
            fLine=get_line(pFile);
            fLine[strlen(fLine)]='\0';
            number=atoi(fLine);
            count_Array[1][i]=number;
            free(fLine);
            Data_Hp_Array[i]=(char*)malloc((i*number+2)*sizeof(char));
            Data_Hp_Array[i][0]='*';
            Data_Hp_Array[i][i*number+1]='\0';
            for(j=1;j<=number;j++)
            {
             nLine=get_line(pFile);
             nLine[strlen(nLine)]='\0';
              for(k=0;k<i;k++)
              {
                  Data_Hp_Array[i][(j-1)*i+k+1]=nLine[k];
              }
              free(nLine);
            }
            free(fName);
            fclose(pFile);
        }
    }


    for(i=1;i<90;i++)
    {
        sprintf(str, "%d", i);
        fName=merg_string(".//DB3//Ml//Ml",str,".txt");
        pFile=fopen(fName,"r");
        if(pFile == NULL) perror ("Error opening file");
        else
        {
            fLine=get_line(pFile);
            fLine[strlen(fLine)]='\0';
            number=atoi(fLine);
            count_Array[2][i]=number;
            free(fLine);
            Data_Ml_Array[i]=(char *)malloc((i*number+2)*sizeof(char));
            Data_Ml_Array[i][0]='*';
            Data_Ml_Array[i][i*number+1]='\0';
            for(j=1;j<=number;j++)
            {
             nLine=get_line(pFile);
             nLine[strlen(nLine)]='\0';
              for(k=0;k<i;k++)
              {
                  Data_Ml_Array[i][(j-1)*i+k+1]=nLine[k];
              }
              free(nLine);
            }
            free(fName);
            fclose(pFile);
        }
    }
}

/// -------------------------------------------------------
/// Free allocated memory to load_data function.
///
void free_data(void)
{
    int i;
    for(i=0;i<18;i++)
    {
        free(Data_St_Array[i]);
    }

    for(i=0;i<90;i++)
    {
        free(Data_Ml_Array[i]);
    }

    for(i=0;i<100;i++)
    {
        free(Data_Hp_Array[i]);
    }
}
