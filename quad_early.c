#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
    printf("INSTRUCTIONS: TYPE IN THE QUADRATIC IN THE FORM OF \'A B C\'. ON THE GRAPH THE * REPRESENT THE LINE, THE y IS THE Y-INTERCEPT, THE x IS THE X INTERCEPT, AND THE v IS THE VERTEX. By Aaron Kaufer\n");
    
   while(1){
     //step 1: predefine all of the variables
    float a = 0;
    float b = 0;
    float c = 0;
    float result1;
    float result2;
    float AOS;
    float vertex;
    int i;
    int j;
    
    //step 2: ask the user for the a b and c values
    scanf("%f %f %f",&a,&b,&c);
    
    //step 3: calculate the x intercepts (result1,result2) using the quadratic formula. Calculate the x location of the axis of symmetry (AOS). Find the Y coordinate of the vertex by plugging the AOS back into the classic equation.
    result1 = ((-1*b)+sqrt(b*b-4*a*c))/(2*a);
    result2 = ((-1*b)-sqrt(b*b-4*a*c))/(2*a);
    AOS = (-b)/(2*a);
    vertex = a*AOS*AOS+b*AOS+c;
    
    //step 4: print out that data
    printf("X-intercepts = %f and %f, Y-intercept = %f, vertex = (%f,%f)\n",result1,result2,c,AOS,vertex);
    
    //step 5: figure out how big the grid would be by first finding the biggest of the absolute values of: result1,result2,vertex,y-intercept(c). Afterwards double it and add two for apropriate sizing.
    int max = (fabs(result1) > fabs(result2) && fabs(result1)>fabs(vertex))?fabs(result1)*2+2:(fabs(result2)>fabs(result1) && fabs(result2)>fabs(vertex))?fabs(result2)*2+2:fabs(vertex)*2+2;
    if(fabs(c)>max)max=fabs(c)*2+2;
    
    //step 6: create two arrays to represent the y coordinates of the line. Note that there will be 2 y values for every x value except for the vertex.
    int linecoords[max];
    int linecoords2[max];
    for(i = 0;i<max;i++){
        int y = i-(max/2);
        linecoords[i] = ((-1*b)+sqrt(b*b-4*a*(c-y)))/(2*a);
        linecoords2[i] = ((-1*b)-sqrt(b*b-4*a*(c-y)))/(2*a);
    }
    
    //step 7: create a max*max array of characters. Afterwards loop through both dimentions of the array using variables i and j. Default every single grid square, and then go through and change them if they fit any criteria.
    char grid[max+1][max+1];
    for(i = 0;i<max+1;i++){
        for(j = 0;j<max+1;j++){
            int y = i-(max/2);
            int x = j-(max/2);
            grid[i][j]=' '; //Default to ' '. Could easily be changed with little damage. Another good blank space example is '.'
            if (x == 0)grid[i][j]='|'; //If along the Y axis, '|'. Little priority.
            if (y == 0)grid[i][j]='-'; //If along the X axis, '-'. Little priority.
            if (x == 0 && y == 0)grid[i][j]='+'; //If in center, '+'. Little priority.
            
            if(x == linecoords[i] || x == linecoords2[i])grid[i][j]='*'; //if aligned with the corresponding line coordinate, '*'. Medium priority.
            
            if (x == 0 && y == (int)c)grid[i][j]='Y'; //If Y intercept, 'Y'
            if (y == 0 && x == (int)result1)grid[i][j]='X'; //If X-intercept 'X'
            if (y == 0 && x == (int)result2)grid[i][j]='X'; //If X-intercept 'X'
            if (x == (int)AOS && y == (int)vertex)grid[i][j]='V'; //If vertex, 'V'
        }
    }
    
    //step 8: loop through the array once more to print it out. There is a ' ' after each character to balance out the drawing, and a '\n' after every line.
    for(i = 0;i<max+1;i++){
        for(j=1;j<max+1;j++){
            printf("%c ",grid[max-i][j]);
        }
        printf("\n");
    }
}
}
