#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#define max(X,Y) (((X) > (Y)) ? (X) : (Y));


int main(int argc, char* argv[] ){
    // printf("%ld", sizeof(char));
    if(argc == 1){
        printf("No input file\n");
        return 0;
    }
    if(argc > 3){
        printf("Too many flags\n");
        return 0;
    }else{
        // char* localename = setlocale(LC_ALL, NULL);
        // char name[32];
        // strcpy(name, localename);
        // printf("%s\n", name);
        setlocale(LC_ALL, "");
        // localename = setlocale(LC_ALL, NULL);
        // strcpy(name, localename);
        // printf("%s\n", name);
        // printf("%ld\n", sizeof(char));        
        char* filename;
        if(argc == 3) filename = argv[2];
        else filename = argv[1];
        // FILE* fd = filecheck(filename);
        FILE* fd = fopen(filename, "r");
        if(fd == NULL){
            printf("Couldn't open file\n");
            return 0;
        }
        
        wint_t c;
        int bytecount = 0, linecount = 1, wordcount = 0, charcount = 0; 
        int spaceflag = 1;
        
        while((c = fgetwc(fd)) != WEOF){
            if(c == '\n') linecount++;
            charcount++;
            // bytecount++;

            
            if(!iswspace(c) && spaceflag){
                spaceflag = 0;
                wordcount++;
            }else if(iswspace(c) && !spaceflag){
                spaceflag = 1;
            }
            // printf("%lc %X\n", c, c);
            

            
            // printf("%d %d", c, wordcount);
        }
        int fdint = fileno(fd);
        lseek(fdint, 0, SEEK_SET);
        bytecount = lseek(fdint, 0, SEEK_END);
        if(bytecount < 0){
           printf("%s\n", strerror(errno)); 
        }
        fclose(fd);

        // printf("%d", c);
        // printf("%s\n", strerror(errno));
    
        
        char bcw[20], lcw[20], wcw[20];
        
        sprintf(bcw,"%d",bytecount);
        sprintf(lcw,"%d",linecount);
        sprintf(wcw,"%d",wordcount);

        int msize = max(strlen(bcw), strlen(lcw));
        msize = max(msize, strlen(wcw));

        if(argc == 2){
            printf(" %*s %*s %*s %s\n", msize, bcw, msize, lcw, msize, wcw, filename);
            return 0 ;
        }else{
            char s = argv[1][1];
            switch(s){
                case 'c':
                    printf("%*d %s\n", msize, bytecount, filename);
                    break;
                case 'l':
                    printf("%*d %s\n", msize, linecount, filename);
                    break;
                case 'w':
                    printf("%*d %s\n", msize, wordcount, filename);
                    break;
                case 'm':
                    printf("%*d %s\n", msize, bytecount, filename);
                    break;
                default:
                    printf("No such flag\n");
                    break;
            }
            return 0;
        }
    }

}