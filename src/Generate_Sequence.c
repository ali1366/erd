#include <Generate_Sequence.h>
#include <utility.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Split_Structure.h>
#include <utils.h>

///-----------------------------------------------------------
/// Global arrays include pools of RNA sub-sequences
/// corresponding to different components with different lengths
///
char *Data_Hp_Array[90];
char *Data_St_Array[18];
char *Data_Ml_Array[90];
int count_Array[3][100];
///------------------------------------------------------------


time_t Global_Time;

/// ----------------------------------------------------------
/// This function generate new sub-sequence .
/// This sub-sequence is geven from DB3 (pools of RNA sub-sequences
/// corresponding to different components with different lengths).
///
char * GeneratingNewSubSequences(int lenght,int kind)
{
    char * subseq=(char*)malloc(((kind%3)*lenght+1)*sizeof(char));
    subseq[(kind%3)*lenght]='\0';
    int i=0,j=0;
    int denominator=0,remind=0;
    int switchindex=0;
    if(kind==2)
    {
        if(lenght<18)
        {
                if(count_Array[0][lenght]>30)
                {
                    switchindex =rand_diff(1,count_Array[0][lenght]);
                    for(i=0;i<lenght;i++)
                    {
                        subseq[i]=Data_St_Array[lenght][(switchindex-1)*2*lenght+i+1];
                        subseq[2*lenght-i-1]=Data_St_Array[lenght][2*switchindex*(lenght)-i];
                    }
                }
                else
                {
                  if(rand_diff(1,1000)>500)
                  {
                    switchindex =rand_diff(1,count_Array[0][lenght]);
                    for(i=0;i<lenght;i++)
                    {
                        subseq[i]=Data_St_Array[lenght][(switchindex-1)*2*lenght+i+1];
                        subseq[2*lenght-i-1]=Data_St_Array[lenght][2*switchindex*(lenght)-i];
                    }
                  }
                  else
                  {
                      denominator=lenght/3;
                      remind=lenght%3;
                      for(j=0;j<3;j++)
                      {
                          switchindex=rand_diff(1,count_Array[0][denominator]);
                          for(i=0;i<denominator;i++)
                            {
                                subseq[j*denominator+i]=Data_St_Array[denominator][(switchindex-1)*2*denominator+i+1];
                                subseq[2*lenght-(j)*denominator-i-1]=Data_St_Array[denominator][2*switchindex*(denominator)-i];
                            }
                      }
                      if(remind!=0)
                      {
                         switchindex=rand_diff(1,count_Array[0][remind]);
                         for(i=0;i<remind;i++)
                         {
                            subseq[3*denominator+i]=Data_St_Array[remind][(switchindex-1)*2*remind+i+1];
                            subseq[2*lenght-(3)*denominator-i-1]=Data_St_Array[remind][2*switchindex*(remind)-i];
                         }
                      }

                  }
                }
        }
        else
        {
            if(kind==2)
            {
                denominator=lenght/3;
                remind=lenght%3;
                for(j=0;j<3;j++)
                {
                    switchindex=rand_diff(1,count_Array[0][denominator]);
                    for(i=0;i<denominator;i++)
                    {
                        subseq[j*denominator+i]=Data_St_Array[denominator][(switchindex-1)*2*denominator+i+1];
                        subseq[2*lenght-(j)*denominator-i-1]=Data_St_Array[denominator][2*switchindex*(denominator)-i];
                    }
                }
                if(remind!=0)
                {
                    switchindex=rand_diff(1,count_Array[0][remind]);
                    for(i=0;i<remind;i++)
                    {
                        subseq[3*denominator+i]=Data_St_Array[remind][(switchindex-1)*2*remind+i+1];
                        subseq[2*lenght-(3)*denominator-i-1]=Data_St_Array[remind][2*switchindex*(remind)-i];
                    }
                }
            }
        }
    }
    else if(kind==1)
    {
        switchindex =rand_diff(1,count_Array[1][lenght]);
                    for(i=0;i<lenght;i++)
                    {
                        subseq[i]=Data_Hp_Array[lenght][(switchindex-1)*lenght+i+1];
                    }
    }
    else
    {
         switchindex =rand_diff(1,count_Array[2][lenght]);
                    for(i=0;i<lenght;i++)
                    {
                        subseq[i]=Data_Ml_Array[lenght][(switchindex-1)*lenght+i+1];
                    }
    }
     return (char *)subseq;
}


/// ----------------------------------------------------------
/// This function generate new sub-sequence .
/// This sub-sequence generated randomly.
///
/*
char * GeneratingNewSubSequences(int lenght,int kind)
{
    char * subseq=(char*)malloc(((kind%3)*lenght+1)*sizeof(char));
    subseq[(kind%3)*lenght]='\0';
    int i=0;
    int switchindex=0;
    if(kind==2)
    {
        for(i=0;i<lenght;i++)
        {
           //switchindex =rand_diff(0,10000);
            switchindex =rand()%10001;
            if(switchindex<3001)
            {
                subseq[i]='G';
                subseq[2*lenght-i-1]='C';
            }
            else if(switchindex<6001)
            {
                subseq[i]='C';
                subseq[2*lenght-i-1]='G';
            }
            else if(switchindex<8001)
            {
                subseq[i]='A';
                subseq[2*lenght-i-1]='U';
            }
            else
            {
                subseq[i]='U';
                subseq[2*lenght-i-1]='A';
            }
        }
    }
    else
    {
        if(lenght<30)
        {
            for(i=0;i<lenght;i++)
            {
                switchindex =rand()%10001;
                if(switchindex<3001)
                {
                    subseq[i]='A';
                }
                else if(switchindex<6001)
                {
                    subseq[i]='U';
                }
                else if(switchindex<8001)
                {
                    subseq[i]='C';
                }
                else
                {
                    subseq[i]='G';
                }
            }
        }
        else
        {
            time(&Global_Time);
            for(i=0;i<lenght;i++)
            {
                switchindex =rand()%10001;
                if(switchindex<5001)
                {
                    subseq[i]='A';
                }
                else if(switchindex<7001)
                {
                    subseq[i]='U';
                }
                else if(switchindex<8501)
                {
                    subseq[i]='C';
                }
                else
                {
                    subseq[i]='G';
                }
            }
        }
    }
    return (char *)subseq;
}
*/


/// ----------------------------------------------------------
/// This function generate new sequence for evolutionary algorithm population.
///
char* GenerateNewSequence(char*SeqArray,char* sequence,char*generaedStructure,int*starray,int*hparray,int*mlarray,int*size)
{
    char *SubSeq=NULL;
    char *SubSeqTemp=NULL;
    int SizeStem=starray[0];
    int SizeHp=hparray[0];
    int SizeMl=mlarray[0];
    int totalSize=SizeStem+SizeHp+SizeMl;
    int *distance=(int*)malloc((totalSize+1)*sizeof(int));
    int *graterThanOne=NULL;
    int tempDistance=0;
    const unsigned short StKind=2;
    const unsigned short HpKind=1;
    const unsigned short MlKind=4;
    int *selectedIndex=(int*)malloc(6*sizeof(int));
    int st_temp_size=0;
    int HpNearPair_front=0;
    int HpNearPair_back=0;
    int *HpNearPair=NULL;
    //int StNearHp_front=0;
    int *StNearHp=NULL;
    int i=1;
    int j=0;
    distance[0]=totalSize;
    for (i=1;i<=SizeStem;i++)
    {
        for (j=0;j<=starray[i+*size*2]-1;j++)
        {
            if(generaedStructure[starray[i]+j-1]!='(')
                tempDistance++;

            if(generaedStructure[starray[i+*size]+j-1]!=')')
                tempDistance++;

        }
        distance[i]=tempDistance;
        tempDistance=0;
    }

    for (i=SizeStem+1;i<=SizeStem+SizeHp;i++)
    {
        for (j=0;j<=hparray[i-SizeStem+*size]-1;j++)
        {

            if(generaedStructure[hparray[i-SizeStem]+j-1]!='.')
                tempDistance=tempDistance+1;
        }
        distance[i]=tempDistance;
        tempDistance=0;
    }

    for (i=SizeStem+SizeHp+1;i<=totalSize;i++)
    {
        for (j=0;j<=mlarray[i-(SizeStem+SizeHp)+*size]-1;j++)
        {

            if(generaedStructure[mlarray[i-(SizeStem+SizeHp)]+j-1]!='.')
                tempDistance=tempDistance+1;
        }
        distance[i]=tempDistance;
        tempDistance=0;
    }

    graterThanOne= find(&distance[0],'>',0,&totalSize);
    selectedIndex[0]=graterThanOne[0];
    for(i=0;i<=4;i++)
    {
        for(j=0;j<(strlen(sequence));j++)
        {

            SeqArray[i*(strlen(sequence)+1)+j]=sequence[j];

        }
        SeqArray[(i+1)*(strlen(sequence)+1)-1]='\0';
    }
    for (i=1;i<=5;i++)
    {
        if(graterThanOne[0]!=0)
        {
            selectedIndex[i]=graterThanOne[rand_diff(1,graterThanOne[0])];
        }
        else
        {
            return (char *)&SeqArray[0];
        }
    }
    free(graterThanOne);
    free(distance);

    for (i=1;i<=5;i++)
    {

        if( selectedIndex[i]<=SizeStem)
        {
            st_temp_size=starray[selectedIndex[i]+((*size)*2)];
            SubSeq= GeneratingNewSubSequences(st_temp_size , StKind);
            SubSeqTemp=strpar(SubSeq,0,st_temp_size-1);
            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[selectedIndex[i]]-1,st_temp_size-1+starray[selectedIndex[i]]-1);
            free(SubSeqTemp);
            SubSeqTemp=strpar(SubSeq,st_temp_size,2*st_temp_size-1);
            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[selectedIndex[i]+(*size)]-1,st_temp_size-1+starray[selectedIndex[i]+(*size)]-1);
            free(SubSeqTemp);
            free(SubSeq);
            if(starray[selectedIndex[i]+*size*2]==1)
            {
                 HpNearPair=malloc(2*sizeof(int));
                 if(rand_diff(1,1000)>499)
                 {
                    HpNearPair[0]=0;
                    for(j=1;j<=mlarray[0];j++)
                    {
                       if((mlarray[j]+mlarray[j+*size]-1)==(starray[selectedIndex[i]]-1))
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(mlarray[HpNearPair_front+*size] , MlKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,mlarray[HpNearPair_front]-1,mlarray[HpNearPair_front+*size]-1+mlarray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                    //--------------
                    HpNearPair[0]=0;
                    for(j=1;j<=mlarray[0];j++)
                    {
                       if((mlarray[j]+mlarray[j+*size]-1)==(starray[selectedIndex[i]+*size]-1))
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(mlarray[HpNearPair_front+*size] , MlKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,mlarray[HpNearPair_front]-1,mlarray[HpNearPair_front+*size]-1+mlarray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                    HpNearPair[0]=0;
                    for(j=1;j<=hparray[0];j++)
                    {
                       if((hparray[j]+hparray[j+*size]-1)==(starray[selectedIndex[i]]-1))
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(hparray[HpNearPair_front+*size] , HpKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,hparray[HpNearPair_front]-1,hparray[HpNearPair_front+*size]-1+hparray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                     HpNearPair[0]=0;
                    //---------------
                    for(j=1;j<=hparray[0];j++)
                    {
                       if((hparray[j]+hparray[j+*size]-1)==(starray[selectedIndex[i]+*size]-1))
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(hparray[HpNearPair_front+*size] , HpKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,hparray[HpNearPair_front]-1,hparray[HpNearPair_front+*size]-1+hparray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                 }
                else
                {
                    //------------
                    HpNearPair[0]=0;
                    for(j=1;j<=hparray[0];j++)
                    {

                       if(hparray[j]==starray[selectedIndex[i]]+1)
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(hparray[HpNearPair_front+*size] , HpKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,hparray[HpNearPair_front]-1,hparray[HpNearPair_front+*size]-1+hparray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                    //---------------
                    HpNearPair[0]=0;
                    for(j=1;j<=hparray[0];j++)
                    {
                       if(hparray[j]==starray[selectedIndex[i]+*size]+1)
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_back=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(hparray[HpNearPair_back+*size] , HpKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,hparray[HpNearPair_back]-1,hparray[HpNearPair_back+*size]-1+hparray[HpNearPair_back]-1);
                            free(SubSeq);
                    }
                    //-----------
                    HpNearPair[0]=0;
                    for(j=1;j<=mlarray[0];j++)
                    {
                       if(mlarray[j]==starray[selectedIndex[i]]+1)
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_front=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(mlarray[HpNearPair_front+*size] , MlKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,mlarray[HpNearPair_front]-1,mlarray[HpNearPair_front+*size]-1+mlarray[HpNearPair_front]-1);
                            free(SubSeq);
                    }
                    //-----------
                    HpNearPair[0]=0;
                    for(j=1;j<=mlarray[0];j++)
                    {
                       if(mlarray[j]==(starray[selectedIndex[i]+*size]+1))
                       {
                           HpNearPair[1]=j;
                           HpNearPair[0]=1;
                           break;
                       }
                    }
                    if(HpNearPair[0]>0)
                    {
                            HpNearPair_back=HpNearPair[1];
                            SubSeq= GeneratingNewSubSequences(mlarray[HpNearPair_back+*size] ,MlKind);
                            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,mlarray[HpNearPair_back]-1,mlarray[HpNearPair_back+*size]-1+mlarray[HpNearPair_back]-1);
                            free(SubSeq);
                    }
                }

                free(HpNearPair);
            }
        }

        else if(selectedIndex[i]<=(SizeStem+SizeHp))
        {
            SubSeq= GeneratingNewSubSequences(hparray[selectedIndex[i]-SizeStem+*size] , HpKind);
            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,hparray[selectedIndex[i]-SizeStem]-1,hparray[selectedIndex[i]-SizeStem+*size]-1+hparray[selectedIndex[i]-SizeStem]-1);
            free(SubSeq);

            if(hparray[selectedIndex[i]-SizeStem+*size]==1)
            {
                StNearHp=find(&starray[0],'=',hparray[selectedIndex[i]-SizeStem]+1,size);
                if(StNearHp[0]>0)
                {
                    if(StNearHp[1]!=*size)
                    {
                        st_temp_size=starray[StNearHp[1]+*size*2];
                        SubSeq= GeneratingNewSubSequences( st_temp_size, StKind);
                        SubSeqTemp=strpar(SubSeq,0,st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]]-1,st_temp_size-1+starray[StNearHp[1]]-1);
                        free(SubSeqTemp);
                        SubSeqTemp=strpar(SubSeq,st_temp_size,2*st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]+(*size)]-1,st_temp_size-1+starray[StNearHp[1]+(*size)]-1);
                        free(SubSeqTemp);
                        free(SubSeq);
                    }
                }
                free(StNearHp);

                StNearHp=find(&starray[0]+*size,'=',hparray[selectedIndex[i]-SizeStem]+1,size);
                if(StNearHp[0]>0)
                {
                    if(StNearHp[1]!=*size)
                    {
                        st_temp_size=starray[StNearHp[1]+*size*2];
                        SubSeq= GeneratingNewSubSequences( st_temp_size, StKind);
                        SubSeqTemp=strpar(SubSeq,0,st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]]-1,st_temp_size-1+starray[StNearHp[1]]-1);
                        free(SubSeqTemp);
                        SubSeqTemp=strpar(SubSeq,st_temp_size,2*st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]+(*size)]-1,st_temp_size-1+starray[StNearHp[1]+(*size)]-1);
                        free(SubSeqTemp);
                        free(SubSeq);
                    }
                }
                free(StNearHp);
            }
        }
        else
        {
            SubSeq= GeneratingNewSubSequences(mlarray[selectedIndex[i]-(SizeStem+SizeHp)+*size] , MlKind);
            insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeq,mlarray[selectedIndex[i]-(SizeStem+SizeHp)]-1,mlarray[selectedIndex[i]-(SizeStem+SizeHp)+*size]-1+mlarray[selectedIndex[i]-(SizeStem+SizeHp)]-1);
            free(SubSeq);

            if(mlarray[selectedIndex[i]-(SizeStem+SizeHp)+*size]==1)
            {
                StNearHp=find(&starray[0],'=',mlarray[selectedIndex[i]-(SizeStem+SizeHp)]+1,size);
                if(StNearHp[0]>0)
                {
                    if(StNearHp[1]!=*size)
                    {
                        st_temp_size=starray[StNearHp[1]+*size*2];
                        SubSeq= GeneratingNewSubSequences( st_temp_size, StKind);
                        SubSeqTemp=strpar(SubSeq,0,st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]]-1,st_temp_size-1+starray[StNearHp[1]]-1);
                        free(SubSeqTemp);
                        SubSeqTemp=strpar(SubSeq,st_temp_size,2*st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]+(*size)]-1,st_temp_size-1+starray[StNearHp[1]+(*size)]-1);
                        free(SubSeqTemp);
                        free(SubSeq);
                    }
                }
                free(StNearHp);

                StNearHp=find(&starray[0]+*size,'=',mlarray[selectedIndex[i]-(SizeStem+SizeHp)]+1,size);
                if(StNearHp[0]>0)
                {
                    if(StNearHp[1]!=*size)
                    {
                        st_temp_size=starray[StNearHp[1]+*size*2];
                        SubSeq= GeneratingNewSubSequences( st_temp_size, StKind);
                        SubSeqTemp=strpar(SubSeq,0,st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]]-1,st_temp_size-1+starray[StNearHp[1]]-1);
                        free(SubSeqTemp);
                        SubSeqTemp=strpar(SubSeq,st_temp_size,2*st_temp_size-1);
                        insert_in_string(&SeqArray[0]+(i-1)*(strlen(sequence)+1),SubSeqTemp,starray[StNearHp[1]+(*size)]-1,st_temp_size-1+starray[StNearHp[1]+(*size)]-1);
                        free(SubSeqTemp);
                        free(SubSeq);
                    }
                }
                free(StNearHp);
            }
        }
    }
    free(selectedIndex);
    return (char *)&SeqArray[0];
}


char* initialize_sequence(int sequence_lenght,int*starray,int * hparray,int *size)
{
    char* sequence=(char*)malloc ((sequence_lenght+1)*sizeof(char));
    int i=0;
    int StKind=2;
    int HpKind=1;
    int SubSeq_size=0;
    int SizeHp=hparray[0];
    int SizeSt=starray[0];
    char*SubSeq;
    char*SubSeqTemp;
    for(i=1;i<=SizeSt;i++)
    {
        SubSeq_size=starray[i+*size*2];
        SubSeq= GeneratingNewSubSequences( SubSeq_size, StKind);
        SubSeqTemp=strpar(SubSeq,0,SubSeq_size-1);
        insert_in_string(sequence,SubSeqTemp,starray[i]-1,SubSeq_size-1+starray[i]-1);
        free(SubSeqTemp);
        SubSeqTemp=strpar(SubSeq,SubSeq_size,2*SubSeq_size-1);
        insert_in_string(sequence,SubSeqTemp,starray[i+(*size)]-1,SubSeq_size-1+starray[i+(*size)]-1);
        free(SubSeqTemp);
        free(SubSeq);
    }

    for(i=1;i<=SizeHp;i++)
    {
        SubSeq= GeneratingNewSubSequences(hparray[i+*size] , HpKind);
        insert_in_string(sequence,SubSeq,hparray[i]-1,hparray[i+*size]-1+hparray[i]-1);
        free(SubSeq);
    }
    sequence[sequence_lenght]='\0';
    return sequence;
}


/// ------------------------------------------------------------
/// Assign a compatible RNA sequence to the given target structure.
/// To do this, the target structure is decomposed to its
/// structural components and based on the type and length of each component,
/// a sub-sequence is randomly picked from the corresponding pool.
///
char* initialize_multiloop_sequence(int sequence_lenght,int*starray,int * hparray,int * mlarray,int *size)
{
    char* sequence=(char*)malloc ((sequence_lenght+1)*sizeof(char));
    int i=0;
    int StKind=2;
    int HpKind=1;
    int MlKind=4;
    int SubSeq_size=0;
    int SizeHp=hparray[0];
    int SizeSt=starray[0];
    int SizeMl=mlarray[0];
    char*SubSeq;
    char*SubSeqTemp;
    for(i=1;i<=SizeSt;i++)
    {
        SubSeq_size=starray[i+*size*2];
        SubSeq= GeneratingNewSubSequences( SubSeq_size, StKind);
        SubSeqTemp=strpar(SubSeq,0,SubSeq_size-1);
        insert_in_string(sequence,SubSeqTemp,starray[i]-1,SubSeq_size-1+starray[i]-1);
        free(SubSeqTemp);
        SubSeqTemp=strpar(SubSeq,SubSeq_size,2*SubSeq_size-1);
        insert_in_string(sequence,SubSeqTemp,starray[i+(*size)]-1,SubSeq_size-1+starray[i+(*size)]-1);
        free(SubSeqTemp);
        free(SubSeq);
    }

    for(i=1;i<=SizeHp;i++)
    {
        SubSeq= GeneratingNewSubSequences(hparray[i+*size] , HpKind);
        insert_in_string(sequence,SubSeq,hparray[i]-1,hparray[i+*size]-1+hparray[i]-1);
        free(SubSeq);
    }
    for(i=1;i<=SizeMl;i++)
    {
        SubSeq= GeneratingNewSubSequences(mlarray[i+*size] , MlKind);
        insert_in_string(sequence,SubSeq,mlarray[i]-1,mlarray[i+*size]-1+mlarray[i]-1);
        free(SubSeq);
    }
    sequence[sequence_lenght]='\0';
    return sequence;
}


/// ------------------------------------------------------------
/// Assign a compatible RNA sequence to the given target structure.
/// This RNA sequence generate randomly.
///
char*initial_RNAInvers(char*structure)
{
    //srand(time(0));
    int size_str=strlen(structure);
    int size;
    int *starray=(int*)malloc(size_str *3* sizeof(int));
    int *hparray=(int*)malloc(size_str *2* sizeof(int));
    int *mlarray=(int*)malloc(size_str *2* sizeof(int));
    splite_structure_multiloop_unpair(starray,hparray,mlarray,structure,&size );

    char*sequence=(char*)malloc((size_str+1)*sizeof(char));
    int i=0,j=0;
    int randnumber;
    sequence[size_str]='\0';
//    for(i=0;i<size_str;i++)
//    {
//        sequence[i]='A';
//    }
    for(i=0;i<size_str;i++)
    {
       if(structure[i]=='.')
       {
            randnumber=rand_diff(0,1000);
            if(randnumber<300)
            {
                sequence[i]='A';
            }
            else if(randnumber<600)
            {
                sequence[i]='U';
            }
            else if(randnumber<800)
            {
                sequence[i]='C';
            }
            else
            {
                sequence[i]='G';
            }
       }
    }
    for(i=1;i<=starray[0];i++)
    {
        for(j=0;j<starray[i+size*2];j++)
        {
          randnumber=rand_diff(0,1000);
            if(randnumber<150)
            {

                sequence[starray[i]+j-1]='A';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='U';
            }
            else if(randnumber<300)
            {
                sequence[starray[i]+j-1]='U';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='A';
            }
            else if(randnumber<580)
            {
                sequence[starray[i]+j-1]='G';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='C';
            }
            else if(randnumber<860)
            {
                sequence[starray[i]+j-1]='C';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='G';
            }
            else if(randnumber<930)
            {
                sequence[starray[i]+j-1]='U';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='G';
            }
            else if(randnumber<1001)
            {
                sequence[starray[i]+j-1]='C';
                sequence[starray[i+size]-1+starray[i+size*2]-j-1]='G';
            }
        }
    }

    free(starray);
    starray=NULL;
    free(hparray);
    hparray=NULL;
    free(mlarray);
    mlarray=NULL;
    return sequence;
}


void set_constraint_sequence(char* sequence,int*cons_table)
{
    int i;
    for(i=1;i<cons_table[0]*2;i+=2)
    {

            sequence[cons_table[i]]=(char)cons_table[i+1];

    }
}

/// ----------------------------------------------------------------
/// constraint sequence checked be compatible with target structure.
///
char* check_constraint_sequence(char* target_structure, char* input_constrain_sequence)
{
    int i;
    int min_size=strlen(target_structure);
    if(min_size>strlen(input_constrain_sequence))
    {
        min_size=strlen(input_constrain_sequence);
    }
    else if(min_size<strlen(input_constrain_sequence))
    {
        printf("Invalid Sequence constraint : Lenght of sequence constraint is biger than lenghth of target structure  ");
    }
    short*pair_table=make_pair_table(target_structure);
    char*constrain_sequence=(char*)malloc((strlen(target_structure)+1)*sizeof(char));
    for(i=0;i<pair_table[0];i++)
    {
        constrain_sequence[i]='N';
    }
    constrain_sequence[strlen(target_structure)]='\0';
    for(i=0;i<min_size;i++)
    {
        if(input_constrain_sequence[i]=='A'||input_constrain_sequence[i]=='c'||input_constrain_sequence[i]=='C'||input_constrain_sequence[i]=='a'||input_constrain_sequence[i]=='g'||input_constrain_sequence[i]=='G'||input_constrain_sequence[i]=='u'||input_constrain_sequence[i]=='U')
        {
            constrain_sequence[i]=input_constrain_sequence[i];
        }
        if(pair_table[i+1]>0)
        {
            if(input_constrain_sequence[i]=='A'||input_constrain_sequence[i]=='a')
            {

                constrain_sequence[pair_table[i+1]-1]='U';
            }
            else if(input_constrain_sequence[i]=='U'||input_constrain_sequence[i]=='u')
            {
                constrain_sequence[pair_table[i+1]-1]='A';
            }
            else if(input_constrain_sequence[i]=='G'||input_constrain_sequence[i]=='g')
            {
                constrain_sequence[pair_table[i+1]-1]='C';
            }
            else if(input_constrain_sequence[i]=='C'||input_constrain_sequence[i]=='c')
            {
                constrain_sequence[pair_table[i+1]-1]='G';
            }

        }
    }
    return constrain_sequence;
}


int * generat_constrain_seq_matrix(char*target_structure,char*constraint_sequence)
{
    int space_index=0;
    int space_index2=0;
    char*number_temp;
    int number_of_constrain=0;
    int * constraint_matrix=(int*)malloc(strlen(constraint_sequence)*sizeof(int));
    short*pair_table=make_pair_table(target_structure);
    space_index=findfirst(constraint_sequence,0,' ');
    while(space_index!=-1)
    {
        switch(constraint_sequence[space_index-1])
        {
            case 'A':
            case 'a':
                    constraint_matrix[number_of_constrain+1]=1;

                break;
            case 'c':
            case 'C':
                    constraint_matrix[number_of_constrain+1]=2;

                break;
            case 'g':
            case 'G':
                    constraint_matrix[number_of_constrain+1]=3;

                break;
            case 'u':
            case 'U':
                    constraint_matrix[number_of_constrain+1]=4;

                break;
        }
        space_index2=findfirst(constraint_sequence,space_index+1,' ');
        number_temp=strpar(constraint_sequence,space_index+1,space_index2);
        constraint_matrix[number_of_constrain+2]=atoi(number_temp);
        free(number_temp);
        number_of_constrain+=2;
        space_index=findfirst(constraint_sequence,space_index2+1,' ');
        if(pair_table[constraint_matrix[number_of_constrain]]>0)
        {
            if(constraint_matrix[number_of_constrain-1]==1)
            {
                constraint_matrix[number_of_constrain+1]=4;
            }
            else if(constraint_matrix[number_of_constrain-1]==2)
            {
                constraint_matrix[number_of_constrain+1]=3;
            }
            else if(constraint_matrix[number_of_constrain-1]==3)
            {
                constraint_matrix[number_of_constrain+1]=2;
            }
            else if(constraint_matrix[number_of_constrain-1]==4)
            {
                constraint_matrix[number_of_constrain+1]=1;
            }
            constraint_matrix[number_of_constrain+2]=pair_table[constraint_matrix[number_of_constrain]];
            number_of_constrain+=2;
        }

    }
    constraint_matrix[0]=number_of_constrain/2;

    return constraint_matrix;
}

char * generat_random_cons_seq(char*structure)
{
    char *cons_seq=(char*)malloc((strlen(structure)+1)*sizeof(char));
    short * pair_table=make_pair_table(structure);
    int i=0;
    int random_nucluec;
    int random_position;

    for(i=0;i<strlen(structure);i++)
    {
        cons_seq[i]='N';
    }

    cons_seq[strlen(structure)]='\0';

    for(i=1;i<=strlen(structure)/10;i++)
    {
        random_position=rand_diff(0,strlen(structure)-1);
        random_nucluec=rand_diff(1,4);
        while(cons_seq[random_position]=='A'||cons_seq[random_position]=='C'||cons_seq[random_position]=='G'||cons_seq[random_position]=='U')
        {
            random_position++;
            if(random_position==strlen(structure))
            {
                random_position=0;
            }
        }
        if(random_nucluec==1)
        {
            cons_seq[random_position]='A';
            if(pair_table[random_position+1]!=0)
            {
                i++;
                cons_seq[pair_table[random_position+1]-1]='U';
            }
        }
        else if(random_nucluec==2)
        {
            cons_seq[random_position]='C';
            if(pair_table[random_position+1]!=0)
            {
                i++;
                cons_seq[pair_table[random_position+1]-1]='G';
            }
        }
        else if(random_nucluec==3)
        {
            cons_seq[random_position]='G';
            if(pair_table[random_position+1]!=0)
            {
                i++;
                random_nucluec=rand_diff(1,4);
                if(random_nucluec>1)
                {
                    cons_seq[pair_table[random_position+1]-1]='C';
                }
                else
                {
                    cons_seq[pair_table[random_position+1]-1]='U';
                }

            }
        }
        else if(random_nucluec==4)
        {
            cons_seq[random_position]='U';
            if(pair_table[random_position+1]!=0)
            {
                i++;
                random_nucluec=rand_diff(1,4);
                if(random_nucluec>1)
                {
                    cons_seq[pair_table[random_position+1]-1]='A';
                }
                else
                {
                    cons_seq[pair_table[random_position+1]-1]='G';
                }
            }
        }
    }
    free(pair_table);
    return cons_seq;
}

int * constarin_table(char* constrain_sequence)
{
    int i=0;
    int size=strlen(constrain_sequence);
    int constrain_number=0;
    for(i=0;i<size;i++)
    {
        if(constrain_sequence[i]!='N')
        {
            constrain_number++;
        }

    }
    int* cons_table=(int*)malloc((constrain_number*2+1)*sizeof(int));

    cons_table[0]=constrain_number;

    constrain_number=1;
    for(i=0;i<size;i++)
    {
        if(constrain_sequence[i]!='N')
        {
            cons_table[constrain_number]=i;
            cons_table[constrain_number+1]=(int)constrain_sequence[i];

            constrain_number+=2;
        }

    }

    return cons_table;
}
