//
//  1-23.c
//  C Practice
//
//  Created by Humberto Atondo on 1/21/19.
//  Copyright © 2019 Humberto Atondo. All rights reserved.
//

#include "1-23.h"
#include <stdio.h>
#include <stdbool.h>

FILE *file1, *file2;
int c;
bool flag1, flag2;

int main (int argc, char **argv) {

    if(argc != 3)
    {
        printf("Invalid number of arguments.\n");
        return -1;
    }
    
    file1 = fopen(argv[1], "r+");
    file2 = fopen(argv[2], "w");
    
    flag1 = false;
    flag2 =  false;
    
    if (file1) {
        while ((c = getc(file1)) != EOF) {
            
            if (c == '/') {
                c = getc(file1);
                
                if (c == '/') {
                    flag1 = true;
                }
                else if (c == '*') {
                    flag2 = true;
                }
            }
            
            if (!flag1 && !flag2) {
                fprintf(file2, "%c", c);
            }
            
            if (c == '\n' && flag1) {
                flag1 = false;
            }
            
            if (c == '*') {
                if ((c = getc(file1)) == '/') {
                    flag2 = false;
                }
                else {
                    fprintf(file2, "%c", c);
                }
               
            }
        }
        
        fclose(file1);
        fclose(file2);
    }
    
    return 0;
}
