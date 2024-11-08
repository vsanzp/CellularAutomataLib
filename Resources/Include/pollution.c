/**********************************************************
* Author: 
*        Victorino Sanz 
*        Dpto. Informática y Automática, UNED
*        Juan del Rosal, 16
*        28040, Madrid
*        Spain
*        Email: vsanz@dia.uned.es
*
* Licensed by Victorino Sanz under the Modelica License 2
* Copyright © 2013, Victorino Sanz.
* 
***********************************************************/

#ifndef POLLUTION
#define POLLUTION

#include <CellularAutomataLib.c>
#include <math.h>

/****************************************/
/* AIR POLLUTION CELLULAR AUTOMATA      */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct POLState{
    double P; // pollution
    double wind_coef;
    int wind_dir;
    double diffusion_coef;
}POLState;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * POLDefaultState(){
    POLState *s;
    s = (POLState *)malloc(sizeof(POLState));
    
    //set the default values for state variables
    s->P = 0; // no pollution
    s->wind_coef = 0;
    s->wind_dir = 0;
    s->diffusion_coef = 0.5;

    return (void *)s;
}

// function call from Modelica code to set default states
int POLDefault (void * space){
    void*  (*defaultState)() = &POLDefaultState;
    //    CS2D_SetDefault(space, defaultState);
    CS2D_InitDefault(space, defaultState);
    return 1;
}

// Function that describes the state of initialized cells (non-initialized cells will remain in the default state)
void * POLInitialState(){
    POLState *s;
    s = POLDefaultState();
    // set the values of state variables for initialized cells
    s->P = 200; 
    
    return (void *)s;
}

// initializing function for the selected cells from Modelica
void POLInitial(void *space, int row, int col){
    void*  (*initialState)() = &POLInitialState;
    void*  (*defaultState)() = &POLDefaultState;
    int i,j;
    
    CS2D_Init(space, row, col, initialState);
    return;
}

//***************************************************
// RULE FUNCTION
void *pollution(int *change, void* cellstate, int row, int col, void** neighbors, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    POLState *out; // output state
    POLState *cs; // current state
    POLState **ne; // neighbors state
    double **in; // inputs    int i;
    int i;
    
    cs = (POLState *)cellstate;
    ne = (POLState **)neighbors;
    in = (double **)inputs;
    out = (POLState *)malloc(sizeof(POLState));

    double Pdiffout=0,Pwindout=0;
    double Pin=0,Pdiffin=0,Pwindin=0;
   
    out->P = cs->P;
    out->wind_dir = cs->wind_dir;
    out->wind_coef = cs->wind_coef;
    out->diffusion_coef = cs->diffusion_coef;
    
 
    // EXTERNAL INPUTS ***
    // define the behavior of the model during transitions
    // pollution from external inputs
    if (in != NULL)
	for (i=0;i<n_inputs;i++){
	    if (inputs_rcv[i] > 0){
		Pin += *in[i];
	    }
	}
    
    // DIFFUSION ***
    // Reduce current P due to diffusion to neighbors
    Pdiffout = cs->P*cs->diffusion_coef;
    //    out->P -= cs->P*cs->diffusion_coef;
    // increase current P diffused from neighbors
    for (i=0;i<n_neighbors;i++){
	if(neighbors[i] != NULL){
	    //Pdiffin += (1/n_neighbors)*ne[i]->diffusion_coef*ne[i]->P;
	    Pdiffin += 0.125*ne[i]->diffusion_coef*ne[i]->P;
	}
    }

    // transport by wind *********
    // REDUCE CURRENT P DUE TO WIND TRANSPORT
    //Pwindout = (cs->P-Pdiffout)*cs->wind_coef;
    Pwindout = cs->P*cs->wind_coef;
    //    out->P -= out->P*cs->wind_coef;
    // receive P transported by wind
    for (i=0;i<n_neighbors;i++){
	if(neighbors[i] != NULL){
	    if (abs(i-ne[i]->wind_dir) == 4){
		//if (ne[i]->wind_dir == 7-i){
		//Pwindin += ne[i]->wind_coef*(ne[i]->P-(ne[i]->P*ne[i]->diffusion_coef));
		Pwindin += ne[i]->wind_coef*ne[i]->P;
	    }
	}
    }

    out->P = cs->P + Pin - Pdiffout + Pdiffin - Pwindout + Pwindin;
    
    if (out->P == cs->P)
    	*change = 0;
    else
	*change = 1;
    return (void *)out;
}

// Function that returns the value to display in the graphical animation
double POLDisplay(void *cell){
    POLState *s;
    double out;

    s = (POLState *)cell;
    // set out to the desired value calculated from the state variables
    if (cell == NULL)
	out = 0;
    else
	out = s->P;
    
    return out;
}

// STEP function called form MODELICA to perfom CA steps
int POLStep(void* space){
    void* (*rule)(int *, void*,int,int,void**,int,void**,int,int*) = &pollution;
    double (*display)(void*) = &POLDisplay;
    
    return CS2D_Step(space,rule,display);
    //return 1;
}

/*********************************************/

//**************************************
// INTERFACE FUNCTIONS


// function initialize a cell using an external value
void POLWindDirInit(void* space,int row, int col, double value){
    POLState* s;

    s = (POLState *)CS2D_GetState(space,row,col);
    // assign external value to the state variables
    s->wind_dir = value;
    CS2D_SetState(space,row,col,s);
    return;
}

// function initialize a cell using an external value
void POLWindCoefInit(void* space,int row, int col, double value){
    POLState* s;

    s = (POLState *)CS2D_GetState(space,row,col);
    // assign external value to the state variables
    s->wind_coef = value;
    CS2D_SetState(space,row,col,s);
    return;
}


// function to set an external value as an input to a cell
void POLExtSource(void* space,int row, int col, double value,int input_id){
    double* inp;

    inp = (double *)malloc(sizeof(double));
    //convert the external value to values of the state variables
    *inp = value;

    CS2D_SetInput(space,row,col,(void*)inp,input_id);

    return;
}

void POLExtInput(void* space,int row, int col, double value,int input_id){
    POLState* inp;

    //ModelicaFormatMessage("POL ext input [%d,%d] = %lf, id = %d\n",row,col,value,input_id);
    inp = (POLState *)malloc(sizeof(POLState));
    inp->P = value;
    CS2D_SetInput(space,row,col,(void*)inp,input_id);
    //ModelicaFormatMessage("POL ext input END \n");
    return;
}

#endif
