#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// #include<unistd.h>
#include<sys/stat.h>
#include<stdbool.h>

char* ext[3] = {".inp\0", ".cmd\0", "."};
char* extnames[3] ={"Input","cmd"};

char* ConcatExt(char* extention, char* filename, char* filenameext, int i)
{
    strcpy(filenameext, ".\\");
    strcat(filenameext, filename);
    strcat(filenameext, "\\");
    if(extention == ext[1])
    {
        strcat(filenameext, extnames[2]);
    }
    strcat(filenameext, filename);
    strcat(filenameext, extention); 
    return filenameext;
}

void Makedemdir(char FileName[])
{
    // int check;
    char filenameext[100];
  
    // check = mkdir(FileName,0777);
    mkdir(FileName,0777);
} 

char* Getcomment(int i)
{
    char* comments[] ={"REM", "//", "#"};
    char comm [10];
    // printf("%d %s", i, extnames[i]);

    return (i == 1 ? comments[0] : ((!strcmp(extnames[i], "py") ? comments[2] : comments[1])));
}
void Pycmd (FILE* fptr, char* FileName)
{
    fprintf(fptr, "%s%s%s", "set OUTPUT_PATH=.\\", FileName, ".out\n");
    fprintf(fptr,"%s%s%s%s%s", "py ", FileName, ".py < ", FileName, ".inp\n" );
    fprintf(fptr, "type %%OUTPUT_PATH%%");
}

void Ccmd (FILE* fptr, char* FileName)
{
    fprintf(fptr, "%s%s%s", "set OUTPUT_PATH=.\\", FileName, ".out\n");
    fprintf(fptr,"%s%s%s%s", FileName, ".exe < ", FileName, ".inp\n" );
    fprintf(fptr, "type %%OUTPUT_PATH%%");
}

void Jscmd (FILE* fptr, char* FileName)
{
    fprintf(fptr, "%s%s%s", "set OUTPUT_PATH=.\\", FileName, ".out\n");
    fprintf(fptr,"%s%s%s%s%s", "node ", FileName, ".js < ", FileName, ".inp\n" );
    fprintf(fptr, "type %%OUTPUT_PATH%%");
}

void Jcmd (FILE* fptr)
{

}

void Callfun (FILE* fptr, char* FileName)
{
    if(!strcmp(ext[2], ".py"))
    {
        Pycmd (fptr, FileName);
    }
    else
    {
        if(!strcmp(ext[2], ".js"))
        {
            Jscmd (fptr, FileName);
        }
        else
        {
            if(!strcmp(ext[2], ".c"))
            {
                Ccmd (fptr, FileName);
            }
            else
            {
                printf("I am in the Callfun about to call jcmd and i shouldnt be here\n");
                //Jcmd (fptr, FileName);
            }
        }

    }

}



void Writetofiles(char* filenameext, int i, char* FileName)
{
    FILE* fptr;
    fptr = fopen(filenameext, "w");

    if(i == 0)
        ;
    else
    {   
        // printf("\n");
        // printf(Getcomment(i));
        fprintf(fptr, "%s %s %s %s",Getcomment(i), "This ", extnames[i], "file is made by JV\n" );
        if(i == 1)
        {
            Callfun (fptr, FileName);
            // fprintf(fptr, "%s %s %s", "set OUTPUT_PATH=.\\", FileName, ".out\n");
        }
    }
    fclose(fptr);
}

bool fexists(char* filename)
{
    struct stat buff;
    return (stat(filename, &buff) == 0);
}

void Makedemfiles(char FileName[])
{
    char filenameext[100];
    FILE *fptr;
    int i ;
    // printf("Hello\n");
    for( i = 0; i < 3; ++i)
    {
        printf("\n");
        printf(ConcatExt(ext[i], FileName, filenameext, i));
        if (! (fexists(filenameext)))
        {
            // fptr = fopen(filenameext, "w");
            Writetofiles(filenameext, i, FileName);
        // fclose(fptr);
        }
        
    }
}

void main(int argc, char* argv[])
{
    
    printf("%d %s %s", argc, argv[1], argv[2]);
    
    strcat(ext[2], argv[1]);
    extnames[2] = argv[1]; 
    Makedemdir(argv[2]);
    Makedemfiles(argv[2]);
    //TODO:Check for ignoring case
}
