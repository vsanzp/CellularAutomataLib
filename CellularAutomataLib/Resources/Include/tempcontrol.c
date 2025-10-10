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
 Copyright © 2025, Victorino Sanz.

This program is free software: you can redistribute it and/or modify it under the terms of 
the GNU Leaser General Public License as published by the Free Software Foundation, either 
version 3 of the License, or  any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Leaser General Public License for more details.

You should have received a copy of the GNU Leaser General Public License along with this 
program. If not, see <https://www.gnu.org/licenses/>.
*********************************************************************************************/

#ifndef TEMPCONTROL
#define TEMPCONTROL

#define SPACE 0
#define BNEWMANN 1
#define BROBIN 2

#include <CellularAutomataLib.c>
#include <CellularAutomataLib-animation.c>

/**********************************************************/
/* TEMPERATURE CONTROLLER CELLULAR AUTOMATA               */
/**********************************************************/

//**************************************
// Cell state
typedef struct TEMPState{
    int type; // type of cell (space, newmann boundary or robin boundary)
    double t; // temperature
}TEMPState;



//**************************************
// CA WRAPPER FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * TEMPDefaultState(){
    TEMPState *s;
    s = (TEMPState *)malloc(sizeof(TEMPState));
    s->type = SPACE;
    s->t = 20; // celsius , default temp
    return (void *)s;
}

int TEMPDefault(void* space){
    CS_InitDefault(space,&TEMPDefaultState);
    return 1;
}



// Function that describes the state of initialized cells
void TEMPInitialState(void *cs){
    TEMPState *s;
    s = (TEMPState *)cs;
    s->type = SPACE;
    s->t = 60; // celsius,  initial temp 
    return;
}


// Function that describes the state of initialized cells for Robin boundary conditions
void TEMPInitialRobin(void *cs){
    TEMPState *s;
    s = (TEMPState *)cs;
    s->type = BROBIN;
    s->t = 10; // celsius,  initial temp 
    return;
}

// Function that describes the state of initialized cells with Newmann boundary conditions
void TEMPInitialNewmann(void *cs){
    TEMPState *s;
    s = (TEMPState *)cs;
    s->type = BNEWMANN;
    s->t = 20; // celsius,  initial temp 
    return;
}


// Function used to setup the north boundary for the room
void setNorthBoundary(void * space, int modx, int mody, int modz){
    int i;

    for(i=modx/2;i<=modx;i++){
	CS_Init(space, i, mody, modz, &TEMPInitialNewmann);
    }
    return;
}

// Function used to setup the south boundary for the room
void setSouthBoundary(void * space, int modx, int mody, int modz){
    int i;

    for(i=1;i<=modx;i++){
	CS_Init(space, i, 1, modz, &TEMPInitialNewmann);
    }
    return;
}

// Function used to setup the east boundary for the room (as a circle with the center in the middle point of the wall)
void setEastBoundary(void * space, int modx, int mody, int modz){
    int i, j;
    double r;
    double cx = (double)modx;
    double cy = (double)mody/2;

    for(i=modx/2;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    r = sqrt(pow((double)i-cx,2)+pow((double)j-cy,2));
	    if (r < (double)mody/2){
		CS_Init(space, i, j, modz, &TEMPInitialRobin);
	    }
	}
    }
    return;
}

// Function used to setup the west boundary for the room (as a circle with the center in the middle point of the south wall)
void setWestBoundary(void * space, int modx, int mody, int modz){
    int i, j;
    double r;
    double cx = (double)modx/2;
    double cy = 1;
    
    for(i=1;i<=modx/2;i++){
	for(j=1;j<=mody;j++){
	    r = sqrt(pow((double)i-cx,2)+pow((double)j-cy,2));
	    if (r > ((double)modx/2-1.0)){
		CS_Init(space, i, j, modz, &TEMPInitialNewmann);
	    }
	}
    }
    return;
}

// initializing function for the selected cell
void TEMPInitial(void* space, int modx, int mody, int modz){
    setEastBoundary(space,modx,mody,modz);
    setWestBoundary(space,modx,mody,modz);
    setNorthBoundary(space,modx,mody,modz);
    setSouthBoundary(space,modx,mody,modz);
    return;
}

//***************************************************+
// DISPLAY FUNCTION

//******************************************************************************
// DISPLAY
// double COLOR display (void* space, int x,int y, int z, double* SCALARVALUE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
double TEMPDisplay(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    TEMPState *cs;
    cs = (TEMPState*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(WHITE); // transparent	
    }else{
	if (cs->type == BNEWMANN)
	    return (double)ColorToInt(BLACK); // newmann boundary cells in black
	else if (cs->type == BROBIN)
	    return (double)ColorToInt(SKYBLUE); // robin boundary cells in skyblue
	else
	    return (double)ColorToInt(Fade(RED,cs->t/100)); // space cells in shades of red
    }
}

int TEMPSetDisplay(void*animation,void *space){
    CS_SetDisplay(animation,space, &TEMPDisplay);   
    return 1;
}




//***************************************************
// RULE FUNCTION
// Finite difference approach of the Poisson equation for the heat transfer process
void* transition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    TEMPState *out;
    TEMPState *cs;
    TEMPState **ne;
    TEMPState **in;
    double ht = .1;
    double hx = 1;
    double k = 1;
    double sumt;
    
    cs = (TEMPState *)cellstate;
    ne = (TEMPState **)neighbor_states;
    in = (TEMPState **)inputs;
    out = (TEMPState *)malloc(sizeof(TEMPState));


    out->type = cs->type;
    out->t = cs->t;
    
    // EXTERNAL POWER AS INPUT
    if (n_inputs > 0 && inputs_rcv[0] > 0) // cell receives external input
	out->t = in[0]->t;
    else{ // cell not receiving external inputs
	if (cs->type == SPACE){ // only space cells are evaluated
	    sumt = 0;
	    double sumn = 0;
	    double qh = 0;
	    double hh = 1;
	    for(i=0;i<n_neighbors;i++) // observe neighbors
		if(ne[i] != NULL){
		    if (ne[i]->type == BNEWMANN) // newmann boundary
			sumt += 0;
		    else if (ne[i]->type == BROBIN){ // robin boundary
			sumt +=  qh + hh*(ne[i]->t - out->t);
			sumn++;
		    }else{ // space cell
			sumt += ne[i]->t;
			sumn++;
		    }
		}
	    out->t  = out->t + ((k*ht)/(hx*hx))*(sumt - sumn*out->t);
	}
    }
    return (void *)out;
    
}

int TEMPStep(void* space){
    CS_Step(space,&transition);
    return 1;
}

/*********************************************/
// INTERFACE FUNCTIONS
// Function used to set external values as inputs for the CA
void TEMPExtInput(void* space,int x, int y, int z, double value,int input_id){
    TEMPState* inp;
    
    inp = (TEMPState *)malloc(sizeof(TEMPState));
    inp->t = value;
    CS_SetInput(space,x,y, z,(void*)inp,input_id);
    
    return;
}

// Function used to set the value of the temperature in the cell as an output for another model
double TEMPOutput(void* space, int x, int y, int z){
    TEMPState* s;
    
    s = (TEMPState *)CS_GetState(space,x,y,z);
    return s->t;
}


#endif
