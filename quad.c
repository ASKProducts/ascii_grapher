#include <stdio.h>
#include <math.h>
double storage;
#define ROUND_TO_WHOLE(_NUM_) ((modf(_NUM_,&storage)<0.5)?floor(_NUM_):ceil(_NUM_))

/*
.........................TABLE OF CONTENTS..........................
STEP 0.................................INSTRUCTIONS AND USER CHOICES
STEP 1...................................DEFINING THE MAIN VARIABLES
STEP 2....................................GETTING DATA FROM THE USER
STEP 3.....................................CALCULATING STARTING DATA
STEP 4....................................PRINTING OUT STARTING DATA
STEP 5......................................FIGURE OUT SIZE OF GRAPH
STEP 6............................DISCOVER THE VERTECIES OF THE LINE
STEP 7.......................................FILL OUT THE GRID ARRAY
STEP 8......................................PRINT OUT THE GRID ARRAY
*/

int main(int argc, char **argv){

//step 0: print out the instructions, then ask the user if he watns a graph and if he wants it to have user specified dimentions;
printf("INSTRUCTIONS: TYPE IN THE EQUATION IN THE FORM OF \'A B C [GRAPH_SIZE]\'. THE PROGRAM WILL AUTOMATICALLY CHOOSE A SIZE IF YOU PUT 0 AS GRAPH_SIZE, DO NOT PUT IN ANY NUMBER IF YOU TURN OFF USER-SPECIFIED GRAPH_SIZE. ON THE GRAPH THE * REPRESENT THE LINE, THE Y IS THE Y-INTERCEPT, THE X IS THE X INTERCEPT, AND THE V IS THE VERTEX. By Aaron Kaufer\n");
int USE_GRAPH_SIZE;
printf("Please type in the correct number. If a nubmer not listed is chosen, then choice (1) will be assumed. (0)I do not want a graph (1)I want a graph with dimentions that the computer specifies. (2)I want a graph with dimentions I specify. (3)I want a graph in which I specify the scale: ");
scanf("%d",&USE_GRAPH_SIZE);
printf("You may now begin typing your equations.\n");

while(1){

//step 1: predefine all of the variables
	float a = 0;
	float b = 0;
	float c = 0;
	float result1;
	float result2;
	float AOS;
	float vertex;
	float yint = 0;
	int graphSize;
	int i;
	int j;

//step 2: ask the user for the a b and c values
	scanf("%f %f %f",&a,&b,&c);
	graphSize=1;
	if(USE_GRAPH_SIZE==2 || USE_GRAPH_SIZE==3)scanf("%d",&graphSize);

//step 3: calculate the x intercepts (result1,result2) using the quadratic formula (or just solving linearly). Calculate the x location of the axis of symmetry (AOS). Find the Y coordinate of the vertex by plugging the AOS back into the classic equation.
	result1 = (a!=0)?((-1*b)+sqrt(b*b-4*a*c))/(2*a):(-1*c)/b;
	result2 = ((-1*b)-sqrt(b*b-4*a*c))/(2*a);
	AOS = (-b)/(2*a);
	vertex = a*AOS*AOS+b*AOS+c;
	yint=c;

//step 4: print out that data
	printf("X-intercepts = %f and %f, Y-intercept = %f, vertex = (%f,%f)\n",result1,result2,c,AOS,vertex);
	if(USE_GRAPH_SIZE==3){
                result1 /= graphSize;
                result2 /= graphSize;
                AOS /= graphSize;
                vertex /= graphSize;
                yint /=graphSize;
        }

//step 5: if the user did not specify, figure out how big the grid would be by first finding the biggest of the absolute values of: result1,result2,vertex,y-intercept(c). Afterwards double it for apropriate sizing.
	int max = (fabs(result1) > fabs(result2) && fabs(result1)>fabs(vertex))?fabs(result1)*2:(fabs(result2)>fabs(result1) && fabs(result2)>fabs(vertex))?fabs(result2)*2:fabs(vertex)*2;
	if(fabs(yint)>max)max=fabs(c)*2;
	if(a==0)max = max * 2;
	if(USE_GRAPH_SIZE == 2 && graphSize > 0)max=graphSize*2;
	//if(USE_GRAPH_SIZE == 3)max *= graphSize;
	if(USE_GRAPH_SIZE == 0)max = 2;

//step 6: create two arrays to represent the y coordinates of the line (or only 1 if linear). Note that there will be 2 y values for every x value except for the vertex.
	int linecoords[max+1];
	int linecoords2[max+1];
	for(i = 0;i<max+1;i++){
		int y = i-(max/2);
		if(USE_GRAPH_SIZE==3)y*=graphSize;
		linecoords[i] = ROUND_TO_WHOLE((a!=0)?((-1*b)+sqrt(b*b-4*a*(c-y)))/(2*a):(-1*(c-y))/b)/(USE_GRAPH_SIZE==3)?graphSize:1;
		linecoords2[i] = ROUND_TO_WHOLE(((-1*b)-sqrt(b*b-4*a*(c-y)))/(2*a))/(USE_GRAPH_SIZE==3)?graphSize:1;
	}

//step 7: create a max*max array of characters. Afterwards loop through both dimentions of the array using variables i and j. Default every single grid square, and then go through and change them if they fit any criteria.
	char grid[max+1][max+1];
	for(i = 0;i<max+1;i++){
		for(j = 0;j<max+1;j++){
			int y = i-(max/2);
			int x = (a==0)?j-(max/2):j-(max/2)+ROUND_TO_WHOLE(AOS);
			grid[i][j]='*'; //Default to ' '. Could easily be changed with little damage. Another good blank space example is '.' 
			if (x == 0)grid[i][j]='|'; //If along the Y axis, '|'. Little priority.
			if (y == 0)grid[i][j]='-'; //If along the X axis, '-'. Little priority.
			if (x == 0 && y == 0)grid[i][j]='+'; //If in center, '+'. Little priority.
			
			if(x == linecoords[i] || x == linecoords2[i])grid[i][j]=' '; //if aligned with the corresponding line coordinate, '*'. Medium priority.

			if (x == 0 && y == ROUND_TO_WHOLE(yint))grid[i][j]='Y'; //If Y intercept, 'Y'. High priority.
			if (y == 0 && x == ROUND_TO_WHOLE(result1))grid[i][j]='X'; //If X-intercept 'X'. High priority.
			if (y == 0 && x == ROUND_TO_WHOLE(result2))grid[i][j]='X'; //If X-intercept 'X'. High priority
			if (x == ROUND_TO_WHOLE(AOS) && y == ROUND_TO_WHOLE(vertex))grid[i][j]='V'; //If vertex, 'V'. High priority.
		}
	}

//step 8: loop through the array once more to print it out. There is a ' ' after each character to balance out the drawing, and a '\n' after every line.
	for(i = 0;i<max+1;i++){
		for(j=0;j<max+1;j++){
			printf("%c ",grid[max-i][j]);
		}
		printf("\n");
	}
}
}

