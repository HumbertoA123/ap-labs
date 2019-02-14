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

int main () {
    
    file1 = fopen("/Users/Humberto/Desktop/example.c", "r+");
    file2 = fopen("/Users/Humberto/Desktop/result.c", "w");
    
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
