#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK          0
#define NOT_GOOD    1
#define EVEN_WORSE  2

int ReadTextFile (const char *pszFileName, char **pplcBuf, long *plSize);

int main (int iArgC, char *apszArgV[]){

    char *pcFile;
    long lSize;
    int iRc;

    if( iArgC < 2){
        printf("Usage: Type a word to encode\n");
        return 1;
    }

    iRc = ReadTextFile("adventures.txt", &pcFile, &lSize);
    if(iRc == OK){
        // pce = pointer char encode ?
        char *pce = apszArgV[1]; // Start of String to encode:
        char *pc = pcFile;

        while (*pce && (pc != NULL) && (pc < (pcFile + lSize))){
            pc = strchr (pc, *pce);
            if( pc != NULL){
               // printf ("Found '%c' in pos %d.\n", *pc, pc - pcFile);
               printf("%d ", pc - pcFile);
                pc += 10;
                pce++;
            }// end if (pc !NULL)
        }// end while
        printf("\n");

        if(*pce) printf("We could not encode the entire word :( \n");

        // We're done ...
        free (pcFile);
    } // end if (iRc == OK)
    else {
        printf("Could not open or read the file.\n");
    }
} // end main

int ReadTextFile(const char *pszFileName, char **ppcBuf, long *plSize){
    int iRc = OK;
    long lSize;
    long lBytesRead;
    FILE *file;

    file = fopen(pszFileName, "rb");
    if(file != NULL){
        if(fseek(file, 0, SEEK_END) == 0){
            lSize = ftell(file);
            rewind(file);
            // We got the size, allocate buffer:
            *ppcBuf = (char *) malloc(lSize + 1);
            if(*ppcBuf){
                //Read the file in one chunk
                lBytesRead = fread(*ppcBuf, sizeof(char), lSize, file);

                if(lBytesRead == lSize){
                    //we got it all!
                    *plSize = lSize;
                    (*ppcBuf)[lSize] = 0; // Add a terminating '\0'
                }// end if(lBytesRead == lSize)
                else{
                    iRc = NOT_GOOD;
                    free(*ppcBuf);
                    *ppcBuf = NULL;
                }
            } // end if( *ppcBuf)
            else{
                iRc = EVEN_WORSE;
            }
        }// end if (fseek(file, ....)
        fclose(file);
    }// emd if(file !=NULL)
    return iRc;
}