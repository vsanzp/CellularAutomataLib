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

#ifndef EPIDEMICS
#define EPIDEMICS

#include <CellularAutomataLib.c>


/****************************************/
/* EPIDEMICS CELLULAR AUTOMATA       */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct EState{
    double N; //total population
    double S; // susceptible
    double I; // infected
    double R; // recovered
}EState;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * DefaultState(){
    EState *s;
    s = (EState *)malloc(sizeof(EState));
    
    //set the default values for state variables
    s->N = 1;
    s->S = 1;
    s->I = 0;
    s->R  = 0;
    return (void *)s;
}

int EDefault(void* space){
    CS_InitDefault(space, &DefaultState);
    return 1;
    
}

// Function that describes the state of initialized cells (non-initialized cells will remain in the default state)
void InitialState(void *cs){
    EState *s;
    s = (EState *)cs;
    
    // set the values of state variables for initialized cells
    s->N = 1;
    s->S = 0.7;
    s->I = 0.3; // initially infected
    s->R  = 0;

    return;
}

// initializing function for the selected cell
void Ini(void* space, int x, int y, int z){
	CS_Init(space, x,y,z, &InitialState);
    return;
}

//***************************************************
// RULE FUNCTION
void *transition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    EState *out;
    EState *cs;
    EState **ne;
    EState **in;
    double epsilon = 0.4;
    double v = 0.6;
    double c = 1;
    double m = 0.5;
    double mu  = c*m*v;
    double sum;
    int i;

    cs = (EState *)cellstate;
    ne = (EState **)neighbor_states;
    in = (EState **)inputs;
    out = (EState *)malloc(sizeof(EState));
    
    // define the behavior of the model during transitions
    sum = 0;
    for(i=0;i<n_neighbors;i++){
	if(neighbor_states[i] != NULL){
	    //sum = sum + (ne[i]->N/cs->N)*mu*ne[i]->I;
	    sum = sum + mu*ne[i]->I;
	}
    }

    out->I = (1-epsilon)*cs->I + v*cs->S*cs->I + cs->S*sum;
    out->S = cs->S - v*cs->S*cs->I -cs->S*sum;
    out->R = cs->R + epsilon*cs->I;

    return (void *)out;
}


int Step(void* space){
    CS_Step(space,&transition);
    return 1;
}

//************************************************************************

// Function that returns the value to display in the graphical animation
double Display(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    EState *cs;
        
    s = (CellSpace*)space;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (EState *)cell->cellstate;
	if (cs == NULL)
	    return (double)ColorToInt(BLANK);
	else
	    return (double)ColorToInt(Fade(YELLOW,cs->I)); //
    }
}


int SetDisplay(void *space){
    //double  (*display)(void*,int,int,int,double*,double*,double*,double*) = &CHIPDisplay;
    CS_SetDisplay(space, &Display);   
    return 1;
}

/*********************************************/

//**************************************
// INTERFACE FUNCTIONS


// function initialize a cell using an external value
void ExtInit(void* space,int x, int y, int z, double value){
    EState* s;

    s = (EState *)CS_GetState(space,x,y,z);
    // assign external value to the state variables
    s->I = value;
    CS_Init(space,x,y,z,NULL);
    return;
}


// Function to set a new input to a cell, from other cellular space
void SetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    EState* s;
    EState* inp;
    
    inp = (EState *)malloc(sizeof(EState));
    s = (EState *)CS_GetState(Fspace,Fx,Fy,Fz);
    *inp = *s;
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)inp,input_id);
}


// function to set an external value as an input to a cell
void ExtInput(void* space,int x, int y, int z, double value,int input_id){
    EState* inp;

    inp = (EState *)malloc(sizeof(EState));
    //convert the external value to values of the state variables
    inp->I = value;

    CS_SetInput(space,x,y,z,(void*)inp,input_id);

    return;
}

// function to convert the state of a cell into a double value
double OutputS(void* space, int x, int y, int z){
    double out;
    EState* s;
    
    s = (EState *)CS_GetState(space,x,y,z);
    
    out = s->S;
    
    return out;
}

// function to convert the state of a cell into a double value
double OutputI(void* space, int x, int y, int z){
    double out;
    EState* s;
    
    s = (EState *)CS_GetState(space,x,y,z);
    
    out = s->I;
    
    return out;
}

// function to convert the state of a cell into a double value
double OutputR(void* space, int x, int y, int z){
    double out;
    EState* s;
    
    s = (EState *)CS_GetState(space,x,y,z);
    
    out = s->R;
    
    return out;
}

#endif
