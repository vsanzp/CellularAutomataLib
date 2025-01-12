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

#ifndef FOREST
#define FOREST

#include <CellularAutomataLib.c>
#include <Behave.c>

/****************************************/
/* FOREST CELLULAR AUTOMATA       */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct State{
    Behave *b;
    int s; //  cell state (0 unburned, 1 burning, 2 burned)
    int wet; // 0 not wet, 1 wet
    double windspeed;
    int winddir;
    double slope;
    int timetoWet; // time to wet
    int *timetoSpread; // number of steps to reach neighbors
    int fuelmodel;
}State;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * DefaultState(){
    State *s;
    s = (State *)malloc(sizeof(State));
    
    //set the default values for state variables
    s->s = 0; // unburned
    s->wet = 0; // not wet
    s->windspeed = 8;//2.2352; 
    s->winddir = 180; // blows FROM south
    s->slope = 0;
    s->timetoWet = 9999; //
    s->timetoSpread = NULL;
    s->fuelmodel = 4;

    s->b = (Behave *)malloc(sizeof(Behave));
    initialValues(s->b);
    setFuelModel(s->fuelmodel,s->b);
    setWindSpeed(s->windspeed,s->b);
    setWindDir(s->winddir,s->b);
    setSlope(s->slope,s->b);
    calcRothermel(s->b);     
    return (void *)s;
}

int FDefault (void * space){
    CS_InitDefault(space, &DefaultState);
    return 1;
}

// Function that describes the state of initialized cells (non-initialized cells will remain in the default state)
void InitialState(void *cs){
    State *s;
    s = (State*) cs;
    // set the values of state variables for initialized cells
    s->s = 1; // cell burning
    return;
}

// initializing function for the selected cell
void Ini(void* space, int x, int y, int z){
    int i,j;
    
    CS_Init(space, x, y, z, &InitialState);
    
    return;
}

//***************************************************************************************
// RULE FUNCTION
void *transition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    State *out;
    State *cs;
    State **ne;
    double **in;
    int ne_burning; // num of neighbors burning
    int ne_n; // num of neigbors
    double R[8];
    double D = 15; // distance between neighbors
    int i;

    cs = (State *)cellstate;
    ne = (State **)neighbor_states;
    in = (double **)inputs;
    out = (State *)malloc(sizeof(State));
    
    // define the behavior of the model during transitions
    
    *out = *cs;

    //calcRothermel(out->b); 
    if(n_inputs > 0){
	// INPUT[2] and INPUT[3] wind direction and speed changed
	if (inputs_rcv[1]){ // direction
	    out->winddir = *in[1]; //	
	}
	if (inputs_rcv[2]){ // speed
	    out->windspeed = *in[2]; // 
	}
	
	// INPUT[1] water poured or firefighting action
	if (inputs_rcv[0]){
	    out->timetoWet = *in[0]; // reset time to wet value
	    if (out->s == 0) // if unburned, set to wet
		out->wet = 1;
	}
	if (out->timetoWet <= 0)
	    out->wet = 1;    
	out->timetoWet--;

	// re-calculate Rothermel model 
	setWindSpeed(out->windspeed,out->b);
	setWindDir(out->winddir,out->b);
	calcRothermel(out->b);    	
    }

    // ACTIONS
    if (out->s == 0 && !out->wet){ // unburned and not wet
	// Spread from neighbor
	for(i=0;i<n_neighbors;i++){
	    if(neighbor_states[i] != NULL){
		if(ne[i]->timetoSpread != NULL)
		    if(ne[i]->timetoSpread[mod(i+4,n_neighbors)] == 0 && !out->wet){ // not wet and fire spread from neighbor
			out->s = 1; //starts burning
		    }
	    }
	}
    }else if (cs->s == 1){ // burning
	if(out->timetoSpread == NULL){ // just started burning
	    out->timetoSpread = (int *)malloc(sizeof(int)*n_neighbors);
	    for(i=0;i<n_neighbors;i++){
		R[i] = getRosInDir(out->b->ros,out->b->sdr,-45+(i*45),out->b->ecc);
		if (i % 2){
		    out->timetoSpread[i] = (D/R[i]); // linear connection between cells
		}else{
		    out->timetoSpread[i] = (sqrt(2*pow(D,2))/R[i]); // diagonal connection between cells
		}	
	    }
	}else{ // continue burning
	    for(i=0;i<n_neighbors;i++){
		out->timetoSpread[i]--;
	    }	
	}
	if(!out->wet){
	    ne_burning = 0; 
	    for(i=0;i<n_neighbors;i++){
		if (ne[i]->s > 0 || ne[i]->wet) // neighbor burning, burned or wet
		    ne_burning++;
	    }
	    if(ne_burning == n_neighbors) //
		out->s = 2; // to burned because all neighbors are burning, burned or wet
	}else{
	    out->s = 2; // to burned due to wet
	}
    }else if (out->s == 2){ // burned
    }
    
    if (out->s == 2 || out->s == 0)
	return NULL;
    else    
	return (void *)out;
}

int Step(void* space){
    CS_Step(space,&transition);
    return 1;
}

//******************************************************************
// Function that returns the value to display in the graphical animation
double Display(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    State *cs;
    
    cs = (State *)CS_GetState(space,x+1,y+1,z+1);

    if(cs == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{

	if (cs->wet)
	    return (double)ColorToInt(BLUE);
	if (cs->s == 1)
	    return (double)ColorToInt(RED);
	else if(cs->s == 2)
	    return (double)ColorToInt(BLACK);
	else
	    return (double)ColorToInt(GREEN);
    }
}

int SetDisplay(void *space){
    CS_SetDisplay(space, &Display);   
    return 1;
}

/*********************************************/

//**************************************
// INTERFACE FUNCTIONS


// function initialize a cell using an external value
void ExtInit(void* space,int x, int y, int z, double value){
    State* s;

    s = (State *)CS_GetState(space,x,y,z);
    // assign external value to the state variables
    s->s = value;
    CS_SetState(space,x,y,z,s);
    return;
}


// Function to set a new input to a cell, from other cellular space
void SetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    State* s;
    State* inp;
    
    inp = (State *)malloc(sizeof(State));
    s = (State *)CS_GetState(Fspace,Fx,Fy,Fz);
    *inp = *s;
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)inp,input_id);
}


// function to set an external value as an input to a cell
void ExtInput(void* space,int x, int y, int z, double value,int input_id){
    double* inp;

    inp = (double *)malloc(sizeof(double));
    //convert the external value to values of the state variables
    *inp = value;

    CS_SetInput(space,x,y,z,(void*)inp,input_id);

    return;
}

// function to convert the state of a cell into a double value
double Output(void* space, int x, int y, int z){
    State* cs;
    
    cs = CS_GetState(space,x,y,z);
    return (double)(cs->s);
}

#endif
