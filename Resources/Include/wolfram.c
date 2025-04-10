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

#ifndef WOLFRAM
#define WOLFRAM

#include <CellularAutomataLib.c>

/****************************************/
/* WOLFRAM RULES CELLULAR AUTOMATA      */
/****************************************/

// data structure to define the binary state (dead or alive) of the cell as a "int"
typedef struct RState{
    int v;
}RState;


// set default state as dead (= 0)
void * RDefaultState(){
    RState *s;
    s = (RState *)malloc(sizeof(RState));
    s->v = 0; // default state to 0
    return (void *)s;
}
// REDECLARES Default IN CellSpace model
int RInitDefault(void* space){
    void* (*defaultState)() = &RDefaultState;
    //    printf("RInitDefault\n");
    CS_InitDefault(space,defaultState);
    return 1;
}

// set initial cells as alive (= 1)
void RInitialState(void *cellstate){
    RState *s;
    s = (RState *)cellstate;
    s->v = 1; // initial state to 1
 }
// REDECLARES Initial IN CellSpace model
void RInit(void* space, int x, int y, int z){
    void  (*initialState)(void*) = &RInitialState;
    //    printf("RInit [%d,%d,%d]\n",x,y,z);
    CS_Init(space, x, y, z, initialState);
}

//*********************************************************
// DISPLAY FUNCTION

// Function that returns the value to display in the graphical animation
// double COLOR display (void* space, int x,int y, int z, double* VECTOR_MODULE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
double RDisplay(void *space,int x, int y, int z, double* vmodule, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    RState *cs;

    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (RState *)cell->cellstate;
	if (cs->v)
	    return(double)ColorToInt(YELLOW); //  yellow for alive cells
	else
	    return(double)ColorToInt(BLACK); // black for dead cells
    }
}

int RSetDisplay(void* space){
    double (*display)(void*,int,int,int,double*,double*,double*,double*) = &RDisplay;
    CS_SetDisplay(space,display);
    return 1;
}



//********************************************************
// RULE FUNCTIONS

void* rule110(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    
    int n0,n1,i;
    RState *out;
    RState *cs;
    RState **ne;
    RState **in;

    cs = (RState *)cellstate;
    ne = (RState **)neighbor_states;
    in = (RState **)inputs;
    out = (RState *)malloc(sizeof(RState));
    
    if (ne[0] != NULL && ne[0]->v > 0)
	n0 = 1;
    else
	n0 = 0;
    
    if (ne[1] != NULL && ne[1]->v > 0)
	n1 = 1;
    else
	n1 = 0;
    
    if(n0 == 1 && cs->v == 1 && n1 == 1){
	out->v = 0;
    }else if(n0 == 1 && cs->v == 1 && n1 == 0){
	out->v = 1;
    }else if(n0 == 1 && cs->v == 0 && n1 == 1){
	out->v = 1;
    }else if(n0 == 1 && cs->v == 0 && n1 == 0){
	out->v = 0;
    }else if(n0 == 0 && cs->v == 1 && n1 == 1){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 1 && n1 == 0){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 0 && n1 == 1){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 0 && n1 == 0){
	out->v = 0;
    }
    

    for(i=0;i<n_inputs;i++){
	//    if(n_inputs > 0){
	if ((in != NULL) && (inputs_rcv[i] > 0)){
	    out->v = in[i]->v;
	}
    }
    
    if(cs->v == out->v)
	return NULL;
    else
	return (void *)out;
}
// Redeclares the Rule function in CellSpace model
int R110Step(void* space){
    void* (*rule)(void*, int, int, int, void**, int, void**, int, int *) = &rule110;

    CS_Step(space,rule);
    return 1;
}


/*************************************************************************/

void* rule30(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){

    int n0,n1,i;
    RState *out;
    RState *cs;
    RState **ne;
    RState **in;
    
    cs = (RState *)cellstate;
    ne = (RState **)neighbor_states;
    in = (RState **)inputs;
    out =(RState *)malloc(sizeof(RState));

    if (ne[0] != NULL && ne[0]->v > 0)
	n0 = 1;
    else
	n0 = 0;
    
    if (ne[1] != NULL && ne[1]->v > 0)
	n1 = 1;
    else
	n1 = 0;
    
    if(      n0 == 1 && cs->v == 1 && n1 == 1){
	out->v = 0;
    }else if(n0 == 1 && cs->v == 1 && n1 == 0){
	out->v = 0;
    }else if(n0 == 1 && cs->v == 0 && n1 == 1){
	out->v = 0;
    }else if(n0 == 1 && cs->v == 0 && n1 == 0){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 1 && n1 == 1){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 1 && n1 == 0){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 0 && n1 == 1){
	out->v = 1;
    }else if(n0 == 0 && cs->v == 0 && n1 == 0){
	out->v = 0;
    }
    
    for(i=0;i<n_inputs;i++){
	//    if(n_inputs > 0){
	if ((in != NULL) && (inputs_rcv[i] > 0)){
	    out->v = in[i]->v;
	}
    }
    
    if(cs->v == out->v)
	return NULL;
    else
	return (void*)out;
}
// Redeclares the Rule function in CellSpace model
int R30Step(void* space){
    void* (*rule)(void*, int, int, int, void**, int, void**, int, int *) = &rule30;
    
    CS_Step(space,rule);
    return 1;
}


// sets the state of FROM cell as input for TO cell
void RSetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    RState* state;
    RState* input;
    
    input = (RState *)malloc(sizeof(RState));
    state = (RState *)CS_GetState(Fspace,Fx,Fy,Fz);
    *input = *state;
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)input,input_id);
    return;
}

// returns the state of cell x
double ROutput(void* space, int x, int y, int z){
    RState* state;


    state = (RState *)CS_GetState(space,x,y,z);
        return (double) state->v;
}

#endif
