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

#ifndef FURNACE
#define FURNACE

#include <CellularAutomataLib.c>
#include <CellularAutomataLib-animation.c>

/****************************************/
/* FURNACE CELLULAR AUTOMATA       */
/****************************************/

//**************************************
// Cell state
typedef struct FURState{
    double t; // temp. of the cell
}FURState;



//**************************************
// CA WRAPPER FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * FURDefaultState(){
    FURState *s;
    s = (FURState *)malloc(sizeof(FURState));
    
    s->t = 0;
    return (void *)s;
}
// function to set default values in the cellular space
int FURDefault(void *space){
    CS_InitDefault(space,&FURDefaultState);
    return 1;
}

// Function that describes the state of initialized cells
void FURInitialState(void *cellstate){
    FURState *s;
    s = (FURState *)cellstate;
    
    s->t = 1;  // initial temp.
    return;
}
// initializing function for the selected cell
void FURInitial(void* space, int modx, int mody, int modz){
    CS_Init(space, modx, mody, modz, &FURInitialState);
    return;
}

//***************************************************
// RULE FUNCTION
void *furnace(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    FURState *out;
    FURState *cs;
    FURState **ne;
    FURState **in;
    
    cs = (FURState *)cellstate;
    ne = (FURState **)neighbor_states;
    in = (FURState **)inputs;
    out = (FURState *)malloc(sizeof(FURState));
    
    sum = 0;
    for(i=0;i<n_neighbors;i++){
        if(neighbor_states[i] != NULL){
            sum += ne[i]->t;
        }
    }

     
    out->t = cs->t;
     if (cs->t > sum/n_neighbors)
	 out->t = cs->t; // keep current temp.
    else 
        out->t = (sum/n_neighbors); // average temp. of neighbors

 
    if (in != NULL)
	for (i=0;i<n_inputs;i++)
	    if (inputs_rcv[i] > 0)
		out->t = in[i]->t; // assign termperature of input
    
    if (out->t == cs->t)
	return NULL;
    else    
	return (void *)out;
}
int FURStep(void* space){
    return CS_Step(space,&furnace);
    //return 1;
}

//***************************************************************************
// DISPLAY
// Function that returns the value to display in the graphical animation
double FURDisplay(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    FURState *cs;

    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (FURState *)cell->cellstate;
	if (cs->t <= 0)
	    return (double)ColorToInt(BLACK); // black for 0 temp cells
	else
	    return (double)ColorToInt((Color){255,255*cs->t,0,255}); // from red to yellow depending on the value of t	
    }
}
int FURSetDisplay(void*animation,void* space){
    CS_SetDisplay(animation,space,&FURDisplay);
    return 1;
}


/*********************************************/
// External input function
void FURExtInput(void* space,int x, int y, int z, double value,int input_id){
    FURState* inp;

    inp = (FURState *)malloc(sizeof(FURState));
    inp->t = value; // set temp with the value of the input
    CS_SetInput(space,x,y,z,(void*)inp,input_id);

    return;
}

// Output Function
double FUROutput(void* space, int x, int y, int z){
    FURState* s;

    s = (FURState *)CS_GetState(space,x,y,z);
    return s->t; // return current cell temp.
}

// Input function
void FURSetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    FURState* s;
    FURState* inp;
    
    inp = (FURState *)malloc(sizeof(FURState));
    s = (FURState *)CS_GetState(Fspace,Fx,Fy,Fz);
    inp->t = s->t; // use cell state as input
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)inp,input_id);
}

#endif
