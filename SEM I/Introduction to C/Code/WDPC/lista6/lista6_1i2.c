#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../timer.h"
/// Array
struct Array2D {
    int width, height, orgwidth;
    int *t;
} Array2D;
/// Functions
int getValue(struct Array2D a, int x, int y);
void setValue(struct Array2D a, int x, int y, int val);
void print(struct Array2D a);
void fill (struct Array2D a, int val);
struct Array2D getSubarray(struct Array2D a, int left , int top, int right , int bottom);
struct Array2D newArray(unsigned int width, unsigned int height);
struct Array2D resize_gorsza_wersja (struct Array2D *a, unsigned int width, unsigned int height);
struct Array2D resize (struct Array2D *a, int width, int height);
void freeArray(struct Array2D a);
/// Main
int main(void){
    clock_t begin = clock();
    struct Array2D a = newArray(3,3);
    for (int i = 0; i < 9; i++) a.t[i] = i+1;
    print(a);
    // 1 2 3 4
    // 5 6 7
    // 7 8 9
    putchar('\n');
    resize (&a,4,3); print(a);
    // 1 2 3 3
    // 4 5 6 6
    // 7 8 9 9
    putchar('\n');
    resize (&a,5,2); print(a);
    // 1 2 3 3 3
    // 4 5 6 6 6
    putchar('\n');
    freeArray(a);
    clock_t end = clock();
    e(begin, end);
    return 0;
}
int getValue(struct Array2D a, int x, int y){
    int v = a.t[y*a.orgwidth+x];
    return v;
}/// Get Value
void setValue(struct Array2D a, int x, int y, int val){
    a.t[y*a.width+x] = val;
}/// Set Value
void print(struct Array2D a){
    for(int y = 0; y < a.height;y++){
        for(int x = 0; x<a.width;x++){
            printf("|%d|", getValue(a,x,y));
        }
        putchar('\n');
    }
}/// Print Array
void fill (struct Array2D a, int val){
    for(int y = 0; y < a.height;y++){
        for(int x = 0; x<a.width;x++){
            setValue(a,x,y,val);
        }
    }
}/// Fill Array
struct Array2D getSubarray(struct Array2D s, int left , int top, int right , int bottom){
    s.width = right - left;
    s.height = bottom - top;
    s.t += top*s.orgwidth + left;
    return s;
}/// Struct Array
struct Array2D newArray(unsigned int width, unsigned int height){
    int* ptr;
    ptr = malloc(height*width*sizeof(int));
    struct Array2D h = {width, height, width,ptr};
    return h;
}/// New Array
void freeArray(struct Array2D a){
    free(a.t);
}/// Free Array
struct Array2D resize (struct Array2D *a, int width, int height){
    a->t = realloc(a->t,sizeof(int)*width*height);
    int orgheight = a->height;
    int lewo = width - a->orgwidth;
    if(lewo>0){
        for (int y = 0; y < height - 1; y++) {
            for (int x = 0; x < width; x++) {
                if (x >= a->orgwidth) {
                    for (int ptr = width * height - 1; ptr > y * width + x; ptr--) {
                        a->t[ptr] = a->t[ptr - 1];
                    }
                }
            }
        }//prawo
        for (int y = 0; y < height; y++) {
            for (int x = a->orgwidth; x < width; x++) {
                a->t[y * width + x] = a->t[y * width + x - 1];
            }
        }//prawo
        a->orgwidth = width;
    } else{
        for (int Y = orgheight; Y < height; Y++) {
            for (int X = 0; X < width; X++) {
                a->t[Y*a->orgwidth+X] = a->t[(Y-1)*a->orgwidth+X];
            }
        }//dół
    }
    a->width = width;
    a->height = height;
}//Resize