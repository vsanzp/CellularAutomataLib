/*******************************************************************************************
 Author: 
        Victorino Sanz 
        Dpto. Informática y Automática, UNED
        Juan del Rosal, 16
        28040, Madrid
        Spain
        Email: vsanz@dia.uned.es
        http://www.euclides.dia.uned.es/vsanz

 Licensed by Victorino Sanz under the LGPL-3.0 or later
 Copyright © 2024, Victorino Sanz.

This program is free software: you can redistribute it and/or modify it under the terms of 
the GNU Leaser General Public License as published by the Free Software Foundation, either 
version 3 of the License, or  any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Leaser General Public License for more details.

You should have received a copy of the GNU Leaser General Public License along with this 
program. If not, see <https://www.gnu.org/licenses/>.
*********************************************************************************************/

#ifndef C19
#define C19

//#define PI 3.14159265358979323846

#include <CellularAutomataLib.c>


/****************************************/
/* ARGESIM C19 BENCHMARK      */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct POLState{
    double M; // input rate
    double c; // pollution concentration 
}POLState;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * POLDefaultState(){
    POLState *s;
    s = (POLState *)malloc(sizeof(POLState));
        
    //set the default values for state variables
    s->M = 0.0;
    s->c = 0.0;
    
    return (void *)s;
}

int POLDefault(void* space){
    CS_InitDefault(space, &POLDefaultState);
    return 1;
}

// Function that describes the state of initialized cells (non-initialized cells will remain in the default state)
void POLInitialState(void*cs){
    POLState *s;
    s = (POLState *)cs;
    
    //set the default values for state variables
    s->M = 0.002;
    s->c = 0.0;
    //s->c = M;
    //    ModelicaFormatMessage("Initial c = %f\n",s->c);

    return;
}

// initializing function for the selected cell
void POLInitial(void* space, int x, int y, int z){
    CS_Init(space, x,y,z, &POLInitialState);
    return;
}


//***************************************************
// RULE FUNCTION
void *POLtransition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    POLState *out;
    POLState *cs;
    POLState **ne;
    POLState **in;
    int i,j,I,N;
    double u = 0.00001*3600; // m/h
    double alpha = 0.05;
    double lambdaoff = 0;
    double lambdaon = 0.998;//0.99964;
    double R = 1;
    double h = 10;
    double n_e = 0.25;
    double r[n_neighbors];
    double extin;
    double sumin;
    double sumout;

    cs = (POLState *)cellstate;
    ne = (POLState **)neighbor_states;
    in = (POLState **)inputs;
    out = (POLState *)malloc(sizeof(POLState));
    

 

    out->c = 0;
    out->M = cs->M;
    // if (cs->M > 0) // input pollutant
    extin = (cs->M/(h*n_e*u))*3600; //g/h
	
    //else
    //	extin = 0.0;
    
        
    sumin = 0;
    for(i=0;i<n_neighbors;i++){
	if(neighbor_states[i] != NULL){
	    if(i == 3) //neighbors_present[i][1] < col && neighbors_present[i][0] == row)
		sumin += ne[i]->c*u;
	    sumin += ne[i]->c*2*alpha*u;
	}
    }
    
    sumout = 0;
    for(i=0;i<n_neighbors;i++){
	if(neighbor_states[i] != NULL){
	    if(i == 4) //neighbors_present[i][1] > col && neighbors_present[i][0] == row)
		sumout += cs->c*u;
	    sumout += cs->c*2*alpha*u;
	}
    }
    
    out->c = cs->c+extin+sumin-sumout;

    if (in != NULL)
	for (i=0;i<n_inputs;i++)
	    if (inputs_rcv[i] > 0)
		out->c = out->c*lambdaon;

    if (out->c == cs->c)
	return NULL;
    else    
	return (void *)out;
   
}


int POLStep(void* space){
    CS_Step(space,&POLtransition);
    return 1;
}


//******************************************************
// DISPLAY
// Function that returns the value to display in the graphical animation
double Display(void *cell){
    POLState *s;
    double out;
    int i;

    s = (POLState *)cell;
    // set out to the desired value calculated from the state variables
    if (cell == NULL)
	return 0;
    else{
	//ModelicaFormatMessage("display %f\n",s->c);
	return s->c;
    }
}


//********************************************************
// INTERFACE FUNCTIONS

// function to convert the state of a cell into a double value
double Output(void* space, int x, int y, int z){
    double out;
    POLState* s;
    int i;
    
    s = (POLState *)CS_GetState(space,x,y,z);
    
    return s->c;
}

void EInput(void* space, int x, int y, int z,double value,int input_id){
    POLState* s;
    int* i;
    
    i = (int*)malloc(sizeof(int));
    *i = 1;
    
    CS_SetInput(space,x,y,z,(void*)i,input_id);
    return;
}


#endif
