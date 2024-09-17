#include <Split_Structure.h>
#include <utility.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <alloc.h>

/// check structure in terms of open and close parenthesis
int check_brackets(char *line)
{
  int i,o,bonds;

  i=o=bonds=0;
  while( line[i] ){
    switch(line[i]) {
    case '(' :
      o++;
      i++;
      bonds++;
      break;
    case '.' :
      i++;
      break;
    case ')' :
      i++;
      o--;
      if(o<0) return 0;
      break;
    default:
      return 0;
    }
  }
  if (o>0) return 0;
  if (bonds == 0) return 0;
  return 1;
}



void countsplit(int*Count_Sp,int* tajamoi,char * MainStructure,char*structure,int *size)
{
    int Size=strlen(structure);
    int i=1;
    int Count=0;
    int SymbolIndex=0;
    Count_Sp[0]=1;
    Count_Sp[1]=1;
    int currentIndex=1;
    for (currentIndex=1;currentIndex<Size;currentIndex++)
    {
        Count_Sp[currentIndex]=1;
        if(structure[SymbolIndex]==structure[currentIndex])
        Count_Sp[Count]++;
        else
        {
            MainStructure[Count]= structure[SymbolIndex];
            Count++;
            SymbolIndex=currentIndex;
        }
    }
    *size=Count;
    MainStructure[Count]= structure[SymbolIndex];
    MainStructure[Count+1]='\0';
    tajamoi[0]= Count_Sp[0];
    for (i=1;i<strlen(MainStructure);i++)
        tajamoi[i]= Count_Sp[i]+tajamoi[i-1];
//        tajamoi = realloc(tajamoi, ((Count +1) * sizeof(int)));
//        Count_Sp = realloc(Count_Sp, ((Count +1) * sizeof(int)));
}

void split_structure(int*starray,int*hparray,char *structure,int*size)
{

    char *MainStructure=(char*)malloc(strlen(structure) * sizeof(char));
    int *Count_Sp=(int*)malloc(strlen(structure) * sizeof(int));
    int *tajamoi=(int*)malloc(strlen(structure) * sizeof(int));
    countsplit(&Count_Sp[0], &tajamoi[0], MainStructure,structure,size);
    starray=(int *)realloc(starray,(*size+1)*3 * sizeof(int));
    hparray=(int *)realloc(hparray,(*size+1)*2 * sizeof(int));
    hparray[0]=0;
    hparray[*size]=0;
    int i=1;
    int Index=1;
    for (i=0;i<=*size;i++)
    {
        if(MainStructure[i]=='.')
        {
            if(i==0)
            {
                hparray[Index]=1;
                hparray[Index+*size]=Count_Sp[i];
                Index++;
            }
            else
            {
                hparray[Index]=tajamoi[i-1]+1;
                hparray[Index+*size]=Count_Sp[i];
                Index++;
            }
        }
    }
    hparray[0]=Index-1;
    hparray[*size]=Index-1;
    for(i=Index;i<*size;i++)
    {
        hparray[i]=-1;
        hparray[i+*size]=-1;
    }
   // starray[0]=&starraytemp[0];
    int currentIndex=findfirst(MainStructure,0,')');
    int LastOpenPrantes;
    char* IndexSeq;
    int size_Count_Sp=*size;
    int size_tajamoi=*size;
    int size_MainStructure=*size;
    int Diff;
    Index=1;
   while(currentIndex!=-1)
   {
                  LastOpenPrantes=findlast(MainStructure,currentIndex,'(');
                  IndexSeq=strpar(MainStructure,LastOpenPrantes+1,currentIndex-1);
                  free(IndexSeq);
                             Diff=Count_Sp[LastOpenPrantes]-Count_Sp[currentIndex];
                             if(Diff>0)
                             {
                                 if(LastOpenPrantes==0)
                                 {
                                     starray[Index]=  (1+Diff) ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[currentIndex];
                                     Index++;
                                 }
                                 else
                                 {
                                     starray[Index]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[currentIndex];
                                     Index++;
                                 }
                                 Count_Sp[LastOpenPrantes]=Diff;
                                 Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+ sum(&Count_Sp[0],LastOpenPrantes+1,currentIndex-1);
                                 tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                                 //Count_Sp(LastOpenPrantes+2:currentIndex)=[];
                                 delete_elements(&Count_Sp[0],LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                                 tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                                 //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                                 delete_elements(&tajamoi[0],LastOpenPrantes+2,currentIndex,&size_tajamoi);
                                 MainStructure[LastOpenPrantes+1]='$';
                                 //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                                 delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                              }
                              else if(Diff<0)
                              {
                                 if(LastOpenPrantes==0)
                                 {
                                     starray[Index]= 1 ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     Index++;
                                 }
                                 else
                                 {
                                     starray[Index]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     Index++;
                                 }
                                 Count_Sp[currentIndex]=-Diff;
                                 Count_Sp[currentIndex-1]=2*Count_Sp[LastOpenPrantes]+sum(&Count_Sp[0],LastOpenPrantes+1,currentIndex-1);
                                 tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                                 //Count_Sp(LastOpenPrantes:currentIndex-2)=[];
                                 delete_elements(&Count_Sp[0],LastOpenPrantes,currentIndex-2,&size_Count_Sp);
                                 //tajamoi[LastOpenPrantes:currentIndex-2)=[];
                                 delete_elements(&tajamoi[0],LastOpenPrantes,currentIndex-2,&size_tajamoi);
                                 MainStructure[currentIndex-1]='$';
                                 //MainStructure(LastOpenPrantes:currentIndex-2)=[];
                                 delete_string_elements(MainStructure,LastOpenPrantes,currentIndex-2,&size_MainStructure);
                              }
                             else
                             {
                                 if(LastOpenPrantes==0)
                                 {
                                     starray[Index]= 1 ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     Index++;
                                 }
                                 else
                                 {
                                     starray[Index]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[Index+*size]=tajamoi[currentIndex-1]+1;
                                     starray[Index+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     Index++;
                                 }
                                 Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+sum(&Count_Sp[0],LastOpenPrantes+1,currentIndex-1);
                                 //Count_Sp(LastOpenPrantes+1:currentIndex)=[];
                                  delete_elements(&Count_Sp[0],LastOpenPrantes+1,currentIndex,&size_Count_Sp);
                                 tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                                 //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                                 delete_elements(&tajamoi[0],LastOpenPrantes+1,currentIndex,&size_tajamoi);
                                 MainStructure[LastOpenPrantes]='$';
                                 //MainStructure(LastOpenPrantes+1:currentIndex)=[];
                                 delete_string_elements(MainStructure,LastOpenPrantes+1,currentIndex,&size_MainStructure);
                             }
            currentIndex=findfirst(MainStructure,0,')');
    }
    starray[0]=Index-1;
    starray[*size]=Index-1;
    starray[*size*2]=Index-1;
    for(i=Index;i<*size;i++)
    {
        starray[i]=-1;
        starray[i+*size]=-1;
        starray[i+*size*2]=-1;
    }
    free(MainStructure);
    free(Count_Sp);
    free(tajamoi);
}

void splite_structure_multiloop(char* structure,int* MultiLoopIndex,int* MultiloopIndexArray)
{
    int size;
    char *MainStructure=(char*)malloc(strlen(structure) * sizeof(char));
    int *Count_Sp=(int*)malloc(strlen(structure) * sizeof(int));
    int *tajamoi=(int*)malloc(strlen(structure) * sizeof(int));

    countsplit(&Count_Sp[0], &tajamoi[0], MainStructure,structure,&size);
    MultiloopIndexArray=(int*)realloc(MultiloopIndexArray,4*size*sizeof(int));
    MultiLoopIndex=(int*)realloc(MultiLoopIndex,size*sizeof(int));
    int j=0;
    int Index=1;
    int MultiIndex=1;
    int currentIndex=findfirst(MainStructure,0,')');
    int LastOpenPrantes;
    char* IndexSeq;
    int size_Count_Sp=size;
    int size_tajamoi=size;
    int size_MainStructure=size;
    int Diff;
    while(currentIndex!=-1)
    {
    if(MainStructure[currentIndex]==')')
    {
            LastOpenPrantes=findlast(MainStructure,currentIndex,'(');
            IndexSeq=strpar(MainStructure,LastOpenPrantes+1,currentIndex-1);
            Diff=Count_Sp[LastOpenPrantes]-Count_Sp[currentIndex];
            if(strcmp(IndexSeq,".")==0)
            {
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+2];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,currentIndex,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,currentIndex,currentIndex,&size_MainStructure);
                        //tajamoi[LastOpenPrantes+2]=[];
                        //MainStructure[currentIndex]=[];
                }

                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes,&size_MainStructure);
                        //Count_Sp[LastOpenPrantes]=[];
                        //tajamoi[LastOpenPrantes]=[];
                        //MainStructure[LastOpenPrantes]=[];
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        MainStructure[LastOpenPrantes]='$';
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+2,&size_MainStructure);
                        //MainStructure[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                }
            }
            else if(strcmp(IndexSeq,".$.")==0)
            {
                //================
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex]=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+3]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+2)=[];
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+2)=[];
                        MainStructure[LastOpenPrantes+3]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+2,&size_MainStructure);
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+4,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+4,&size_MainStructure);
                }
                //===============
            }
            else if(strcmp(IndexSeq,".$")==0)
            {
                if(Diff>0)
                {
                            Count_Sp[LastOpenPrantes]=Diff;
                            Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                            //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                            tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                            MainStructure[LastOpenPrantes+1]='$';
                            //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                            Count_Sp[currentIndex]=-Diff;
                            Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+ Count_Sp[LastOpenPrantes];
                            //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                            //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                            MainStructure[LastOpenPrantes+2]='$';
                           // MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                            delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                            Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                            MainStructure[LastOpenPrantes]='$';
                            //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else if(strcmp(IndexSeq,"$.")==0)
            {
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex]+Diff;
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                        MainStructure[LastOpenPrantes+2]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else
            {
                 for (j=LastOpenPrantes+1;j<=currentIndex-1;j++)
                 {
                        if(MainStructure[j]=='$')
                        {
                            MultiloopIndexArray[Index]=tajamoi[j-1]+1;
                            MultiloopIndexArray[Index+size]=tajamoi[j];
                            MultiloopIndexArray[Index+size*2]=Count_Sp[j];
                            MultiloopIndexArray[Index+size*3]=0;
                            Index=Index+1;
                        }
                        else
                        {
                            MultiloopIndexArray[Index]=tajamoi[j-1]+1;
                            MultiloopIndexArray[Index+size]=0;
                            MultiloopIndexArray[Index+size*2]=Count_Sp[j];
                            MultiloopIndexArray[Index+size*3]=0;
                            Index=Index+1;
                        }
                 }
                    //Diff=Count_Sp[LastOpenPrantes)-Count_Sp[currentIndex);
                    if(Diff>0)
                    {
                        if(LastOpenPrantes==0)
                        {
                            MultiloopIndexArray[Index]=  (1+Diff) ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex];
                            MultiloopIndexArray[Index+size*2]=Count_Sp[currentIndex];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        else
                        {
                            MultiloopIndexArray[Index]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex];
                            MultiloopIndexArray[Index+size*2]=Count_Sp[currentIndex];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+ sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                    }
                    else if(Diff<0)
                    {
                        if(LastOpenPrantes==0)
                        {
                            MultiloopIndexArray[Index]= 1 ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex]+Diff;
                            MultiloopIndexArray[Index+size*2]=Count_Sp[LastOpenPrantes];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        else
                        {
                            MultiloopIndexArray[Index]=  tajamoi[LastOpenPrantes-1]+1 ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex]+Diff;
                            MultiloopIndexArray[Index+size*2]=Count_Sp[LastOpenPrantes];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[currentIndex-1]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:currentIndex-2)=[];
                        //tajamoi[LastOpenPrantes:currentIndex-2)=[];
                        MainStructure[currentIndex-1]='$';
                        //MainStructure(LastOpenPrantes:currentIndex-2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,currentIndex-2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,currentIndex-2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,currentIndex-2,&size_MainStructure);
                    }
                    else
                    {
                        if(LastOpenPrantes==0)
                        {
                            MultiloopIndexArray[Index]= 1 ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex];
                            MultiloopIndexArray[Index+size*2]=Count_Sp[LastOpenPrantes];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        else
                        {
                            MultiloopIndexArray[Index]=  tajamoi[LastOpenPrantes-1]+1 ;
                            MultiloopIndexArray[Index+size]=tajamoi[currentIndex];
                            MultiloopIndexArray[Index+size*2]=Count_Sp[LastOpenPrantes];
                            MultiloopIndexArray[Index+size*3]=1;
                            MultiLoopIndex[MultiIndex]=Index;
                            Index=Index+1;
                            MultiIndex=MultiIndex+1;
                        }
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        //Count_Sp[LastOpenPrantes+1:currentIndex)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,currentIndex,&size_MainStructure);
                    }
            }
            free(IndexSeq);
    }
    else
    {
        break;
    }


        currentIndex=findfirst(MainStructure,0,')');
    }
    MultiloopIndexArray[0]=  Index ;
    MultiloopIndexArray[size]=Index;
    MultiloopIndexArray[size*2]=Index;
    MultiloopIndexArray[size*3]=Index;
    MultiLoopIndex[0]=MultiIndex;
    MultiLoopIndex[MultiIndex]=size;

    free(MainStructure);
    free(Count_Sp);
    free(tajamoi);
}

void splite_structure_hand(char* structure,int* handIndexArray)
{
    int size;
    char *MainStructure=(char*)malloc(strlen(structure) * sizeof(char));
    int *Count_Sp=(int*)malloc(strlen(structure) * sizeof(int));
    int *tajamoi=(int*)malloc(strlen(structure) * sizeof(int));

    countsplit(&Count_Sp[0], &tajamoi[0], MainStructure,structure,&size);
    handIndexArray=(int*)realloc(handIndexArray,3*size*sizeof(int));

    int j=0;
    //int Index=1;
    int handindex=1;
    int currentIndex=findfirst(MainStructure,0,')');
    int LastOpenPrantes;
    char* IndexSeq;
    int size_Count_Sp=size;
    int size_tajamoi=size;
    int size_MainStructure=size;
    int Diff;
    while(currentIndex!=-1)
    {
    if(MainStructure[currentIndex]==')')
    {
            LastOpenPrantes=findlast(MainStructure,currentIndex,'(');
            IndexSeq=strpar(MainStructure,LastOpenPrantes+1,currentIndex-1);
            Diff=Count_Sp[LastOpenPrantes]-Count_Sp[currentIndex];
            if(strcmp(IndexSeq,".")==0)
            {
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+2];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,currentIndex,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,currentIndex,currentIndex,&size_MainStructure);
                        //tajamoi[LastOpenPrantes+2]=[];
                        //MainStructure[currentIndex]=[];
                }

                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes,&size_MainStructure);
                        //Count_Sp[LastOpenPrantes]=[];
                        //tajamoi[LastOpenPrantes]=[];
                        //MainStructure[LastOpenPrantes]=[];
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        MainStructure[LastOpenPrantes]='$';
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+2,&size_MainStructure);
                        //MainStructure[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                }
            }
            else if(strcmp(IndexSeq,".$.")==0)
            {
                //================
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex]=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+3]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+2)=[];
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+2)=[];
                        MainStructure[LastOpenPrantes+3]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+2,&size_MainStructure);
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+4,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+4,&size_MainStructure);
                }
                //===============
            }
            else if(strcmp(IndexSeq,".$")==0)
            {
                if(Diff>0)
                {
                            Count_Sp[LastOpenPrantes]=Diff;
                            Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                            //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                            tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                            MainStructure[LastOpenPrantes+1]='$';
                            //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                            Count_Sp[currentIndex]=-Diff;
                            Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+ Count_Sp[LastOpenPrantes];
                            //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                            //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                            MainStructure[LastOpenPrantes+2]='$';
                           // MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                            delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                            Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                            MainStructure[LastOpenPrantes]='$';
                            //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else if(strcmp(IndexSeq,"$.")==0)
            {
                if(Diff>0)
                {
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex]+Diff;
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                        MainStructure[LastOpenPrantes+2]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else
            {

                    //Diff=Count_Sp[LastOpenPrantes)-Count_Sp[currentIndex);
                    if(Diff>0)
                    {

                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+ sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                    }
                    else if(Diff<0)
                    {

                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[currentIndex-1]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:currentIndex-2)=[];
                        //tajamoi[LastOpenPrantes:currentIndex-2)=[];
                        MainStructure[currentIndex-1]='$';
                        //MainStructure(LastOpenPrantes:currentIndex-2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,currentIndex-2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,currentIndex-2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,currentIndex-2,&size_MainStructure);
                    }
                    else
                    {

                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        //Count_Sp[LastOpenPrantes+1:currentIndex)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,currentIndex,&size_MainStructure);
                    }
            }
            free(IndexSeq);
    }
    else
    {
        break;
    }


        currentIndex=findfirst(MainStructure,0,')');
    }
    for(j=0;j<strlen(MainStructure);j++)
    {
        if(MainStructure[j]=='$')
        {
            if(j==0)
            {
                handIndexArray[handindex]=  0 ;
                handIndexArray[handindex+size]=Count_Sp[0];
                handIndexArray[handindex+size*2]=0;
                handindex++;
            }
            else
            {
                handIndexArray[handindex]= tajamoi[j-1]+1  ;
                handIndexArray[handindex+size]=tajamoi[j];
                if(MainStructure[j-1]=='.')
                {
                    handIndexArray[handindex+size*2]=Count_Sp[j-1];
                }
                else
                {
                    handIndexArray[handindex+size*2]=0;
                }
                handindex++;
            }

        }
    }
    handIndexArray[0]=  handindex ;
    handIndexArray[handindex]=size;
    handIndexArray[handindex+size]=size;
    handIndexArray[handindex+2*size]=size;

    free(MainStructure);
    free(Count_Sp);
    free(tajamoi);
}

void splite_structure_multiloop_unpair(int*starray,int*hparray,int*mlarray,char *structure,int*size )
{
    char *MainStructure=(char*)malloc(strlen(structure) * sizeof(char));
    int *Count_Sp=(int*)malloc(strlen(structure) * sizeof(int));
    int *tajamoi=(int*)malloc(strlen(structure) * sizeof(int));
    countsplit(&Count_Sp[0], &tajamoi[0], MainStructure,structure,size);
    starray=(int *)realloc(starray,(*size+1)*3 * sizeof(int));
    hparray=(int *)realloc(hparray,(*size+1)*2 * sizeof(int));
    mlarray=(int *)realloc(mlarray,(*size+1)*2 * sizeof(int));
    hparray[0]=0;
    hparray[*size]=0;

    int j=0,i=0;
    //int Index=1;
    int MultiIndex=1;
    int HpIndex=1;
    int StIndex=1;
    int currentIndex=findfirst(MainStructure,0,')');
    int LastOpenPrantes;
    char* IndexSeq;
    int size_Count_Sp=*size;
    int size_tajamoi=*size;
    int size_MainStructure=*size;
    int Diff;
    while(currentIndex!=-1)
    {
        if(MainStructure[currentIndex]==')')
        {
            LastOpenPrantes=findlast(MainStructure,currentIndex,'(');
            IndexSeq=strpar(MainStructure,LastOpenPrantes+1,currentIndex-1);
            Diff=Count_Sp[LastOpenPrantes]-Count_Sp[currentIndex];
            if(strcmp(IndexSeq,".")==0)
            {
                hparray[HpIndex]=tajamoi[LastOpenPrantes]+1;
                hparray[HpIndex+*size]=Count_Sp[LastOpenPrantes+1];
                HpIndex++;
                if(Diff>0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]=  (1+Diff) ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+2];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,currentIndex,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,currentIndex,currentIndex,&size_MainStructure);
                        //tajamoi[LastOpenPrantes+2]=[];
                        //MainStructure[currentIndex]=[];
                }

                else if(Diff<0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        tajamoi[LastOpenPrantes+1]=tajamoi[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes];
                        MainStructure[LastOpenPrantes+1]='$';
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes,&size_MainStructure);
                        //Count_Sp[LastOpenPrantes]=[];
                        //tajamoi[LastOpenPrantes]=[];
                        //MainStructure[LastOpenPrantes]=[];
                }
                else
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                        MainStructure[LastOpenPrantes]='$';
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+2,&size_MainStructure);
                        //MainStructure[LastOpenPrantes+1:LastOpenPrantes+2]=[];
                }
            }
            else if(strcmp(IndexSeq,".$.")==0)
            {
                hparray[HpIndex]=tajamoi[LastOpenPrantes]+1;
                hparray[HpIndex+*size]=Count_Sp[LastOpenPrantes+1];
                HpIndex++;
                hparray[HpIndex]=tajamoi[LastOpenPrantes+2]+1;
                hparray[HpIndex+*size]=Count_Sp[LastOpenPrantes+3];
                HpIndex++;
                if(Diff>0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]=  (1+Diff) ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex]=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+3]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+2)=[];
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+2)=[];
                        MainStructure[LastOpenPrantes+3]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+2,&size_MainStructure);
                }
                else
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2]+Count_Sp[LastOpenPrantes+3];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+4)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+4,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+4,&size_MainStructure);
                }
                //===============
            }
            else if(strcmp(IndexSeq,".$")==0)
            {
                hparray[HpIndex]=tajamoi[LastOpenPrantes]+1;
                hparray[HpIndex+*size]=Count_Sp[LastOpenPrantes+1];
                HpIndex++;
                if(Diff>0)
                {
                            if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]=  (1+Diff) ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                            Count_Sp[LastOpenPrantes]=Diff;
                            Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                            //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                            tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                            MainStructure[LastOpenPrantes+1]='$';
                            //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                            if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                            Count_Sp[currentIndex]=-Diff;
                            Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+ Count_Sp[LastOpenPrantes];
                            //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                            //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                            MainStructure[LastOpenPrantes+2]='$';
                           // MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                            delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                            if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                            Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                            //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                            //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                            MainStructure[LastOpenPrantes]='$';
                            //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                            delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                            delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                            delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else if(strcmp(IndexSeq,"$.")==0)
            {
                hparray[HpIndex]=tajamoi[LastOpenPrantes+1]+1;
                hparray[HpIndex+*size]=Count_Sp[LastOpenPrantes+2];
                HpIndex++;
                if(Diff>0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]=  (1+Diff) ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                }
                else if(Diff<0)
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[LastOpenPrantes+2]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes:LastOpenPrantes+1)=[];
                        tajamoi[currentIndex-1]=tajamoi[currentIndex]+Diff;
                        //tajamoi[LastOpenPrantes:LastOpenPrantes+1)=[];
                        MainStructure[LastOpenPrantes+2]='$';
                        //MainStructure(LastOpenPrantes:LastOpenPrantes+1)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,LastOpenPrantes+1,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,LastOpenPrantes+1,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,LastOpenPrantes+1,&size_MainStructure);
                }
                else
                {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+Count_Sp[LastOpenPrantes+1]+Count_Sp[LastOpenPrantes+2];
                        //Count_Sp[LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:LastOpenPrantes+3)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,LastOpenPrantes+3,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,LastOpenPrantes+3,&size_MainStructure);
                }
            }
            else
            {
                 for (j=LastOpenPrantes+1;j<=currentIndex-1;j++)
                 {
                        if(MainStructure[j]=='.')
                        {
                           mlarray[MultiIndex]=tajamoi[j-1]+1;
                           mlarray[MultiIndex+*size]=Count_Sp[j];
                           MultiIndex++;
                        }
                 }
                    //Diff=Count_Sp[LastOpenPrantes)-Count_Sp[currentIndex);
                    if(Diff>0)
                    {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]=  (1+Diff) ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1+Diff ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[currentIndex];
                                     StIndex++;
                                 }

                        Count_Sp[LastOpenPrantes]=Diff;
                        Count_Sp[LastOpenPrantes+1]=2*Count_Sp[currentIndex]+ sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[LastOpenPrantes]=tajamoi[LastOpenPrantes]-Count_Sp[currentIndex];
                        //Count_Sp[LastOpenPrantes+2:currentIndex)=[];
                        tajamoi[LastOpenPrantes+1]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+2:currentIndex)=[];
                        MainStructure[LastOpenPrantes+1]='$';
                        //MainStructure(LastOpenPrantes+2:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+2,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+2,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+2,currentIndex,&size_MainStructure);
                    }
                    else if(Diff<0)
                    {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[currentIndex]=-Diff;
                        Count_Sp[currentIndex-1]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        tajamoi[currentIndex-1]=tajamoi[currentIndex-1]+Count_Sp[LastOpenPrantes];
                        //Count_Sp[LastOpenPrantes:currentIndex-2)=[];
                        //tajamoi[LastOpenPrantes:currentIndex-2)=[];
                        MainStructure[currentIndex-1]='$';
                        //MainStructure(LastOpenPrantes:currentIndex-2)=[];
                        delete_elements(Count_Sp,LastOpenPrantes,currentIndex-2,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes,currentIndex-2,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes,currentIndex-2,&size_MainStructure);
                    }
                    else
                    {
                        if(LastOpenPrantes==0)
                                 {
                                     starray[StIndex]= 1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                                 else
                                 {
                                     starray[StIndex]=  tajamoi[LastOpenPrantes-1]+1 ;
                                     starray[StIndex+*size]=tajamoi[currentIndex-1]+1;
                                     starray[StIndex+(*size*2)]=Count_Sp[LastOpenPrantes];
                                     StIndex++;
                                 }
                        Count_Sp[LastOpenPrantes]=2*Count_Sp[LastOpenPrantes]+sum(Count_Sp,LastOpenPrantes+1,currentIndex-1);
                        //Count_Sp[LastOpenPrantes+1:currentIndex)=[];
                        tajamoi[LastOpenPrantes]=tajamoi[currentIndex];
                        //tajamoi[LastOpenPrantes+1:currentIndex)=[];
                        MainStructure[LastOpenPrantes]='$';
                        //MainStructure(LastOpenPrantes+1:currentIndex)=[];
                        delete_elements(Count_Sp,LastOpenPrantes+1,currentIndex,&size_Count_Sp);
                        delete_elements(tajamoi,LastOpenPrantes+1,currentIndex,&size_tajamoi);
                        delete_string_elements(MainStructure,LastOpenPrantes+1,currentIndex,&size_MainStructure);
                    }
            }
            free(IndexSeq);
        }
    else
    {
        break;
    }


        currentIndex=findfirst(MainStructure,0,')');
    }

    for (i=1;i<=strlen(MainStructure);i++)
    {
        if(MainStructure[i-1]=='.')
        {
            hparray[HpIndex]=tajamoi[i-1]+1-Count_Sp[i-1];
            hparray[HpIndex+*size]=Count_Sp[i-1];
            HpIndex++;
        }
    }
    hparray[0]=HpIndex-1;
    hparray[*size]=HpIndex-1;
    for(i=HpIndex;i<*size;i++)
    {
        hparray[i]=-1;
        hparray[i+*size]=-1;
    }
    mlarray[0]=MultiIndex-1;
    mlarray[*size]=MultiIndex-1;
    for(i=MultiIndex;i<*size;i++)
    {
        mlarray[i]=-1;
        mlarray[i+*size]=-1;
    }
    starray[0]=StIndex-1;
    starray[*size]=StIndex-1;
    starray[*size*2]=StIndex-1;
    for(i=StIndex;i<*size;i++)
    {
        starray[i]=-1;
        starray[i+*size]=-1;
        starray[i+*size*2]=-1;
    }
    free(MainStructure);
    free(Count_Sp);
    free(tajamoi);
}

/// Return number of open parenthesis in structure.
int open_prantesis(char*structure)
{
    int i=0;
    int j=0;
    for(i=0;i<strlen(structure);i++)
    {
        if(structure[i]=='(')
           {
               j++;
           }
    }
    return j;
}
