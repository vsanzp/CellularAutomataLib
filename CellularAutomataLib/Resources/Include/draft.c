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

#ifndef DRAFT
#define DRAFT

#include <CellularAutomataLib.c>


/****************************************/
/* DRAFT CELLULAR AUTOMATA              */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct State{
    double t; // include any required state variable
}State;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * DefaultState(){
    State *s;
    s = (State *)malloc(sizeof(State)); // the default state must be used to allocate memory for each cell
    
    //set the default values for state variables
    s->t = 0;
    return (void *)s; // always return state as  void*
}

// function to set the default state function in the space
// USED TO REDECLARE Default in CellSpace model
int Default(void *space){
    return CS_InitDefault(space,&DefaultState);
}


// Function that allocates memory and sets the state of initialized cells (non-initialized cells will be created using the default state)
void* InitialState(void *cellstate){ // cell state is received as void*
    State *s;
    s = (State *)cellstate;
    
    // set the values of state variables for initialized cells
    s->t = 1.0;
    return (void*)s; // return updated cell state
}

// initializing function for the selected cell
// USED TO REDECLARE Initial in CellSpace model
void Initial(int space, int x, int y, int z){
    CS_Init(space, x, y, z, &InitialState);
}

//***************************************************
// RULE FUNCTION
void *transition(void* cellstate, int x, int y, int z, void** neighbors_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    State *out;
    State *cs;
    State **ne;
    State **in;
    
    cs = (State *)cellstate;
    ne = (State **)neighbors_states;
    in = (State **)inputs;
    out = (State *)malloc(sizeof(State));
    
    // define the behavior of the model during transitions


    if(cs->t != out->t)
	return (void *⁾)out;
    else
	return NULL; // return null if cell state is not changed during the transition
}

// function used to set the transition/rule used in the simulation step
// USED TO REDECLARE Step FUNCTION IN CellSpace MODEL
int Step(void* space){
    CS_Step(space,&transition);
    return 1;
}

//***************************************************
// DISPLAY FUNCTION

// Function that returns the value to display in the graphical animation
// double COLOR display (void* space, int x,int y, int z, double* VMODULE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
double Display(void *space,int x, int y, int z, double* vmodule, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    State *cs;

    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // return transparent color for non existing cells (colors from Raylib))
    else{
	cs = (State *)cell->cellstate;
	if (cs->t)
	    return(double)ColorToInt(YELLOW); 
	else
	    return(double)ColorToInt(BLACK); 
    }
    
    // if a vector field display is used, return vector values in vmodule, vx, vy and vz

}

// function used to set the functions used in the simulation step
// USED TO REDECLARE Step FUNCTION IN CellSpace MODEL
int SetDisplay(void* space){
    CS_SetDisplay(space,&Display);
    return 1;
}


//**************************************
// INTERFACE FUNCTIONS

// Function to set a new input to a cell, from other cellular space
// USED TO REDECLARE SetInput FUNCTION IN InputRegion MODEL
void SetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    State* s;
    State* inp;
    
    inp = (State *)malloc(sizeof(State));
    // read cell state from FROM space
    s = (State *)CS_GetState(Fspace,Fx,Fy,Fz); 
    // set input variables from cell state
    inp->t = s->t; 
    // set input to TO space
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)inp,input_id); 
}

// function to convert the state of a cell into a double value
// USED TO REDECLARE ExtOutput FUNCTION IN OutputRegion or OutputRegionM MODELS
double ExtOutput(void* space, int x, int y, int z){
    State * s;
    double out;

    // get cell state
    s = (State*)CS_GetState(space,x,y,z); 
    // compute output from cell state
    out = s->t; 
    
    return out;
}


// function initialize a cell using an external value
// USED TO REDECLARE ExtInit FUNCTION IN ExtInitRegion MODEL
void ExtInit(void* space, int x, int y, int z, double value){
    State* s;
    s = (State *)CS_Get(space,x,y,z);

    // assign external value to the state variables
    s->t = value;
    // init cell without function
    CS_Init(space,x,y,z,NULL); 
    return;
}


// function to set an external value as an input to a cell
// USED TO REDECLARE ExtInput FUNCTION IN ExtInputRegion MODEL
void ExtInput(void* space,int x, int y, int z, double value, int input_id){
    State* inp;

    inp = (State *)malloc(sizeof(State));
    //convert the external value to values of the state variables
    inp->t = value;
    // set input
    CS_SetInput(space,x,y,z,(void*)inp,input_id);

    return;
}



#endif
