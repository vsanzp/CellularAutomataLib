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

#ifndef S3
#define S3

#include <CellularAutomataLib.c>


/****************************************/
/* SIMPLE 3D CELLULAR AUTOMATA       */
/****************************************/

//**************************************
// Cell state 
typedef struct S3State{
    int v;
}S3State;

//**************************************
// CA WRAPPER FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * S3DefaultState(){
    S3State *s;
    s = (S3State *)malloc(sizeof(S3State));
    
    s->v = 0;
    return (void *)s;
}

// function to set default values in the cellular space
int S3Default(void *state){
    CS_InitDefault(state,&S3DefaultState);
    return 1; 
}

// Function that describes the state of initialized cells
void S3InitialState(void* cellstate){
    S3State *s;
    s = (S3State*)cellstate;
    s->v = 4;   
    return;
}


// initializing function for the selected cell
void S3Initial(void* space, int x, int y, int z){
    CS_Init(space, x, y, z, &S3InitialState);
    return;
}

// Function that describes the state of initialized cells
void S3RandomInitialState(void* cellstate){
    S3State *s;
    
    s = (S3State *)cellstate;
    /* Intializes random number generator */
    
    s->v = random() % 2;
    return;
}


// initializing function for the selected cell
void S3RandomInitial(void* space, int modx, int mody, int modz){
    int i,j,k;
    for(i=1;i<=modx;i++)
	for(j=1;j<=mody;j++)
	    for(k=1;k<=modz;k++){
		CS_Init(space, i, j, k, &S3RandomInitialState);
	    }
    return;
}


//***********************************************************************
// TRANSITION FUNCTION
void* clouds1(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    int sum,i;
    S3State *out;
    S3State *cs;
    S3State **ne;
    S3State **in;
    
    cs = (S3State *)cellstate;
    ne = (S3State **)neighbor_states;
    in = (S3State **)inputs;
    out = (S3State *)malloc(sizeof(S3State));
    
    sum = 0;
    // sum = number of neighbors alive
    for(i=0;i<n_neighbors;i++){
        if(neighbor_states[i] != NULL){
            sum += ne[i]->v;
        }
    }
    
    out->v = cs->v;
    // DEAD and 13-19 neighbors -> ALIVE
    if (!cs->v && sum >= 13 && sum <= 19)
        out->v = 1;
    else if (cs->v && sum < 13) // ALIVE and less than 13 negibhors -> DEAD
        out->v = 0;
    
    if(cs->v == out->v)
	return NULL;
    else
        return (void *)out;
}


int S3Clouds1Step(void* space){
    return CS_Step(space,&clouds1);
}

//***********************************************************************
//***********************************************************************
//***********************************************************************



//***********************************************************************
// TRANSITION FUNCTION
void* rule445(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    int sum,i;
    S3State *out;
    S3State *cs;
    S3State **ne;
    S3State **in;
    
    cs = (S3State *)cellstate;
    ne = (S3State **)neighbor_states;
    in = (S3State **)inputs;
    out = (S3State *)malloc(sizeof(S3State));
    
    sum = 0;
    // sum = number of neighbors alive
    for(i=0;i<n_neighbors;i++){
        if(neighbor_states[i] != NULL){
            sum += ne[i]->v;
        }
    }
    
    out->v = cs->v;
    // DEAD and 4 neighbors -> ALIVE
    if (!cs->v && sum == 4)
        out->v = 4;
    else if (cs->v == 1 && sum != 4) // ALIVE and diff than 4 neighbors -> DEAD
        out->v = 0;
    else
	out->v = cs->v - 1;
    
    if(cs->v == out->v)
	return NULL;
    else
        return (void *)out;
}


int S3445Step(void* space){
    return CS_Step(space,&rule445);
}

#endif
