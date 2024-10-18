#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include <ctype.h>

//*************************************************************************************************************** */
/*
typedef struct {
    int size_str = 0;
    char *str = NULL;
} Line;
*/
//******************************************************************************************************************
size_t FileSize(FILE *fp)
{
    struct stat buf;
    fstat(fileno(fp), &buf);
    return buf.st_size;
}



int Inputer(const char* file_name, char** ptr, size_t* size)
{
    FILE* fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("FILERROR1");
    }

    *size = FileSize(fp);

    *ptr = (char*) calloc(*size, sizeof(char));

    if (*ptr == NULL)
    {
        printf("MEMERROR");
    }

    if (fread(*ptr, 1, *size, fp) != *size)
        printf("INPUTERROR");

    fclose(fp);
}



int StringSeparator(char *ptr, size_t size, char ***strings, int *num_lines)
{
    *strings = (char **) calloc(size, sizeof(char*));

    if (*strings == NULL)
    {
        printf("MEMERROR");
    }

    (*strings)[0] = ptr;

    *num_lines = 1;

    for (size_t i = 0; i < size; i++)
    {
        if (ptr[i] == '\r')
        {
            ptr[i] = '\0';
        }

        if (ptr[i] == '\n')
        {
            ptr[i] = '\0';
            (*strings)[*num_lines - 1] = &(ptr[i + 1]);
            (*num_lines) += 1;
        }
    }
}
//********************************************************************************************************************
int CMP(char* strings[], int a, int b)
{
    size_t i = 0;
    size_t j = 0;
    int ans = 0;

    while(strings[a][i] != '\0' && strings[b][j] != '\0')
    {

        if(!isalpha(strings[a][i]))
        {
            i++;
            continue;
        }

        if(!isalpha(strings[b][j]))
        {
            j++;
            continue;
        }


        if((toupper(strings[a][i])) > (toupper(strings[b][j])))
        {
            ans = 1;
        }

        if((toupper(strings[a][i])) < (toupper(strings[b][j])))
        {
            ans = -1;
        }


        if(ans != 0)
        {
            break;
        }

        i++;
        j++;
    }


    if((ans == 0) && (i != j))
    {
        ans = (i - j) / abs(i - j);
    }
    return ans;
}

int CMPr(char *strings[], int a, int b)
{
    size_t i = 0;
    size_t j = 0;
    size_t size_a = 0;
    size_t size_b = 0;
    int ans = 0;

    while(strings[b][i] != '\0')
    {
        i++;
    }

    while(strings[a][i] != '\0')
    {
        j++;
    }

    size_a = i;
    size_b = j;

    i--;
    j--;


    while((i != 0) && (j != 0))
    {

        if(!isalpha(strings[a][i]))
        {
            i--;
            continue;
        }

        if(!isalpha(strings[b][j]))
        {
            j--;
            continue;
        }

        if((toupper(strings[a][i])) > (toupper(strings[b][j])))
        {
            ans = 1;
        }

        if((toupper(strings[a][i])) < (toupper(strings[b][j])))
        {
            ans = -1;
        }


        if(ans != 0)
        {
            break;
        }

        i--;
        j--;
    }

    if((ans == 0) && (size_a != size_b))
    {
        ans = (size_a - size_b) / abs(size_a - size_b);
    }
    return ans;


}
//************************************************************************************************************************ */
void Swap(char *arr[], int i){
    char *temp;
    temp = arr[i];
    arr[i] = arr[i + 1];
    arr[i + 1] = temp;
}

void BubleSort(char *arr[], int number_of_lines){
    for(int i = 0; i < number_of_lines - 1; i++){
        for(int j = 0; j < number_of_lines - i - 1; j++){
            if (CMP(arr, j, j + 1) < 0){
                Swap(arr, j);
            }
        }
    }
}

void BubleSortReverse(char *arr[], int number_of_lines){
    for(int i = 0; i < number_of_lines - 1; i++){
        for(int j = 0; j < number_of_lines - i - 1; j++){
            if (CMPr(arr, j, j + 1) < 0){
                Swap(arr, j);
            }
        }
    }
}

//************************************************************************************************************************

int OutputSort(const char* file, char** strings, int num_lines)
{
    FILE* output = fopen(file, "a");

    if (output == NULL)
    {
        printf("FILERROR2\n");
    }

    for (int i = 0; i < num_lines; i++)
        fprintf(output, "%s\n", strings[i]);

    fclose(output);
}

int OutputOrigin(const char* file, char** ptr, size_t size)
{
    FILE* output = fopen(file, "a");

    if (output == NULL)
    {
        printf("FILERROR3\n");
    }

    for (int i = 0; i < size; i++)
    {
        if (*ptr[i] == '\0')
            {
            putc('\r', output);
            putc('\n', output);
            i++;
            }

        else
            putc(*ptr[i], output);
    }

    fclose(output);
}


//********************************************************************************************************************
int main()
{

    size_t size = 0;

    char* ptr = NULL;

    int num_lines = 0;

    char** strings;

    Inputer("Onegin.txt", &ptr, &size);

    StringSeparator(ptr, size, &strings, &num_lines);

    BubleSort(strings, num_lines);

    OutputSort("Output.txt", strings, num_lines);

    BubleSortReverse(strings, num_lines);

    OutputSort("Output.txt", strings, num_lines);

    OutputOrigin("Output.txt", ptr, size);

    free(ptr);
    free(strings);
}
