#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
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

struct uinput{
	float coefficient;
	int exponent;
	struct uinput *next;
};

// this function returns a piece of memory that contains the struct uinput.  remember to free this memory later
struct uinput *parseInput(char *input){
	struct uinput *data = malloc(sizeof(struct uinput));
	long long len = strlen(input);
	char coefficientstr[len];
	char exponentstr[len];
	int i;
	int j;
	for(i = 0;i < len;i++){
		if(input[i] == 'x'){coefficientstr[i]=0;break;}
		coefficientstr[i] = input[i];
	}
	for(j = i+1;j<len+1;j++){
        	if(input[j] == 0){exponentstr[j-i-1]=0;break;}
	        exponentstr[j-i-1] = input[j];
	}
	data->coefficient = atof(coefficientstr);
	data->exponent = atoi(exponentstr);
	return data;
}

float solveinput(struct uinput *problem, float ax){
	float result = 0;
	float temp;
	printf("%f ",ax);
	while(problem){
		temp = pow(ax,problem->exponent);
		temp *= problem->coefficient;
		result += temp;
		problem = problem->next;
	}
	return result;

}

int main(int argc, char **argv){

//step 0: print out the instructions, then ask the user if he watns a graph and if he wants it to have user specified dimentions;
printf("INSTRUCTIONS: TYPE IN THE EQUATION IN THE FORM OF \'A B C [GRAPH_SIZE]\'. THE PROGRAM WILL AUTOMATICALLY CHOOSE A SIZE IF YOU PUT 0 AS GRAPH_SIZE, DO NOT PUT IN ANY NUMBER IF YOU TURN OFF USER-SPECIFIED GRAPH_SIZE. ON THE GRAPH THE * REPRESENT THE LINE, THE Y IS THE Y-INTERCEPT, THE X IS THE X INTERCEPT, AND THE V IS THE VERTEX. By Aaron Kaufer\n");
int USE_GRAPH_SIZE;
printf("Please type in the correct number. If a nubmer not listed is chosen, then choice (1) will be assumed. (0)I do not want a graph (1)I want a graph with dimentions that the computer specifies. (2)I want a graph with dimentions I specify: ");
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
	int graphSize;
	int i;
	int j;

//step 2: ask the user for the a b and c values
	
	struct uinput *currentinput = 0 ;
	struct uinput *tmp ;

	//scanf("%f %f %f",&a,&b,&c);
	//if(USE_GRAPH_SIZE==2)scanf("%d",&graphSize);
	
	while(1){
		char data[100];
		scanf("%s",data);
		if(strcmp(data,"!") == 0)break;
		tmp = parseInput(data);
		if (currentinput == 0) {
			currentinput = tmp;
			currentinput->next = 0;
		}
		else {
			tmp->next = currentinput;
			currentinput = tmp;
		}
	}


//step 5: if the user did not specify, figure out how big the grid would be by first finding the biggest of the absolute values of: result1,result2,vertex,y-intercept(c). Afterwards double it for apropriate sizing.


	
	int max = 0;
	while(currentinput){
		if(ceil(currentinput->coefficient)>max)max = ceil(currentinput->coefficient);
		currentinput = currentinput->next;
	}
	max = max * 2;
	if(USE_GRAPH_SIZE == 2 && graphSize > 0)max=graphSize*2;
	if(USE_GRAPH_SIZE == 0)max = 2;

//step 6: create two arrays to represent the y coordinates of the line (or only 1 if linear). Note that there will be 2 y values for every x value except for the vertex.
	int linexcoords[max*max];
	int lineycoords[max*max];
	int prevy = (a==0)?0-(max/2):0-(max/2)+ROUND_TO_WHOLE(AOS);
	int linecoordindex = 0;
	for(i = 0;i<max+1;i++){
		int x = (a==0)?i-(max/2):i-(max/2)+ROUND_TO_WHOLE(AOS);
		//linecoords[i] = ROUND_TO_WHOLE((a!=0)?((-1*b)+sqrt(b*b-4*a*(c-y)))/(2*a):(-1*(c-y))/b);
		//linecoords2[i] = ROUND_TO_WHOLE(((-1*b)-sqrt(b*b-4*a*(c-y)))/(2*a));
		linexcoords[linecoordindex] = x;
		lineycoords[linecoordindex] = ROUND_TO_WHOLE(solveinput(currentinput,x));
		linecoordindex++;
		
	int max = (fabs(result1) > fabs(result2) && fabs(result1)>fabs(vertex))?fabs(result1)*2:(fabs(result2)>fabs(result1) && fabs(result2)>fabs(vertex))?fabs(result2)*2:fabs(vertex)*2;
	}

//step 7: create a max*max array of characters. Afterwards loop through both dimentions of the array using variables i and j. Default every single grid square, and then go through and change them if they fit any criteria.
	char grid[max+1][max+1];
	for(i = 0;i<max+1;i++){
		for(j = 0;j<max+1;j++){
			int y = i-(max/2);
			int x = (a==0)?j-(max/2):j-(max/2)+ROUND_TO_WHOLE(AOS);
			grid[i][j]=' '; //Default to ' '. Could easily be changed with little damage. Another good blank space example is '.' 
			if (x == 0)grid[i][j]='|'; //If along the Y axis, '|'. Little priority.
			if (y == 0)grid[i][j]='-'; //If along the X axis, '-'. Little priority.
			if (x == 0 && y == 0)grid[i][j]='+'; //If in center, '+'. Little priority.
			
			if(x == linexcoords[j] && y == lineycoords[j])grid[i][j]='*'; //if aligned with the corresponding line coordinate, '*'. Medium priority.
			

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
