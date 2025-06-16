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

#ifndef GOL
#define GOL

#include <CellularAutomataLib.c>
#include <CellularAutomataLib-animation.c>

/****************************************/
/* GAME OF LIFE CELLULAR AUTOMATA       */
/****************************************/

//**************************************
// Cell state
typedef struct GOLState{
    int v;
}GOLState;

//**************************************
// CA WRAPPER FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * GOLDefaultState(){
    GOLState *s;
    s = (GOLState *)malloc(sizeof(GOLState));
    
    s->v = 0; // dead by default
    return (void *)s;
}

// function to set default values in the cellular space
int GOLDefault(void *state){
    CS_InitDefault(state,&GOLDefaultState);
    return 1; 
}

// Function used to set a cell alive
void GOLInitialState(void *cellstate){
    GOLState *s;
    s = (GOLState*)cellstate;
    s->v = 1; // alive
    return;
}
// initializing function for the selected cell
void GOLInitial(void* space, int modx, int mody, int modz){
    CS_Init(space, modx, mody, modz, &GOLInitialState);
    return;
}

// Function that describes the state of initialized cells
void GOLRandomInitialState(void *cellstate){
    GOLState *s;
    time_t t;
    
    s = (GOLState *)cellstate;
    s->v = random() % 2; // 50% prob. to be alive
    return;
}
// initializing function for the selected cell
void GOLRandomInitial(void* space, int modx, int mody, int modz){
    int i,j;
    /* Intializes random number generator */
    //    srand((unsigned) time(&t));    
    for(i=1;i<=modx;i++)
	for(j=1;j<=mody;j++){
	    CS_Init(space, i, j, modz, &GOLRandomInitialState);
	}
    return;
}

//***************************************************
// RULE FUNCTION
void* gol(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    int sum,i;
    GOLState *out;
    GOLState *cs;
    GOLState **ne;
    GOLState **in;
    
    cs = (GOLState *)cellstate;
    ne = (GOLState **)neighbor_states;
    in = (GOLState **)inputs;
    out = (GOLState *)malloc(sizeof(GOLState));

    sum = 0;
    for(i=0;i<n_neighbors;i++){
        if(neighbor_states[i] != NULL){
            sum += ne[i]->v;
        }
    }
    
    out->v = cs->v;
    if (!cs->v && sum == 3)
        out->v = 1;
    else if (cs->v && (sum < 2 || sum > 3 ) )
        out->v = 0;
    
    // external inputs

    if (out->v == 0 && n_inputs > 0 && (inputs_rcv[0] || inputs_rcv[1] || inputs_rcv[2])){
	for(int i=0;i<n_inputs;i++){
	    if(inputs_rcv[i])
		out->v += in[i]->v;
	}
    }
    out->v = fmin(out->v,1.0); // limit v to 1
    
    
	if(cs->v == out->v)
	    return NULL;
    else
	return (void *)out;
}

int GOLStep(void* space){
    return CS_Step(space,&gol);
    //return 1;
}

//********************************************************************
// DISPLAY
// Function that returns the value to display in the graphical animation
double GOLDisplay(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    GOLState *cs;

    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (GOLState *)cell->cellstate;
	if (cs->v)
	    return(double)ColorToInt(DARKBLUE); // alive in DARKBLUE
	else
	    return(double)ColorToInt(WHITE);  // dead in wHITE
    }
}
int GOLSetDisplay(void*animation,void *space){
    CS_SetDisplay(animation,space, &GOLDisplay);   
    return 1;
}


//*********************************************************************************+
// returns the state of cell x
double GOLOutput(void* space, int modx, int mody, int modz){
    GOLState* state;
    
    state = (GOLState *)CS_GetState(space,modx,mody,modz);
    return (double) state->v;
}


void GOLExtInit(void* space, int modx, int mody, int modz, double value){
    GOLState* state;
    
    state = (GOLState *)CS_GetState(space,modx, mody, modz);
    state->v = value;
    CS_SetState(space,modx,mody,modz,state);
    return;
}

void GOLExtInput(void* space, int modx, int mody, int modz, double value,int input_id){
    GOLState* inp;

    inp = (GOLState *)malloc(sizeof(GOLState));
    inp->v = value;
    CS_SetInput(space,modx,mody,modz,(void*)inp,input_id);
    return;
}


#endif
