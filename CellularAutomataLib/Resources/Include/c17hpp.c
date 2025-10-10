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


#ifndef C17HPP
#define C17HPP

#include <CellularAutomataLib.c>


/****************************************/
/* LGCA MODELS (HPP) FOR ARGESIM C17 BENCHMARK      */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct HPPState{
    // particles values 0=empty, 1= susceptible, 2= infected, 3= recovered
    int n; // north particle 
    int e; // east particle
    int w; // west particle
    int s; // south particle
}HPPState;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * HPPDefaultState(){
    HPPState *s;
    s = (HPPState *)malloc(sizeof(HPPState));
    
    //set the default values for state variables
    s->n = 0;
    s->e = 0;
    s->w = 0;
    s->s = 0;
    return (void *)s;
}

int HPPDefault(void* space){
	CS_InitDefault(space, &HPPDefaultState);
    return 1;
    
}


void HPPSIRInitial(void* space, int x, int y){
    int i,j,n,k,pos;
    int iniS = 16000;
    int iniI = 100;
    int iniR = 0;
    HPPState *s;
    
    srand(time(NULL));
    
    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k = 1;
	pos = rand()%4;
	while(k<5){
	    if(pos == 0 && s->n == 0){
		s->n = 1;
		break;
	    }else if (pos == 1 && s->w == 0){
		s->w = 1;
		break;
	    }else if (pos == 2 && s->e == 0){
		s->e = 1;
		break;
	    }else if (pos == 3 && s->s == 0){
		s->s = 1;
		break;
	    }else{
		pos = (pos+1)%4;
		k++;
	    }
	}
	if (k<5)
	    n++;
	CS_SetState(space,i+1,j+1,1,s);
    }
    
    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k = 1;
	pos = rand()%4;
	while(k<5){
	    if(pos == 0 && s->n == 0){
		s->n = 2;
		break;
	    }else if (pos == 1 && s->w == 0){
		s->w = 2;
		break;
	    }else if (pos == 2 && s->e == 0){
		s->e = 2;
		break;
	    }else if (pos == 3 && s->s == 0){
		s->s = 2;
		break;
	    }else{
		pos = (pos+1)%4;
		k++;
	    }
	}
	if (k<5)
	    n++;
	CS_SetState(space,i+1,j+1,1,s);
    }

   n = 0;
   while(n < iniR){
       i = rand()%x;
       j = rand()%y;
       s = CS_GetState(space,i+1,j+1,1);
       k = 1;
       pos = rand()%4;
       while(k<5){
	   if(pos == 0 && s->n == 1){
	       s->n = 3;
	       break;
	   }else if (pos == 1 && s->w == 1){
	       s->w = 3;
	       break;
	   }else if (pos == 2 && s->e == 1){
	       s->e = 3;
	       break;
	   }else if (pos == 3 && s->s == 1){
	       s->s = 3;
	       break;
	   }else{
	       pos = (pos+1)%4;
	       k++;
	   }
       }
       if (k<5)
	   n++;
       CS_SetState(space,i+1,j+1,1,s);
   }
   return;
}


#ifndef C17FHP
double uniform(double a, double b)
{
    return rand() / (RAND_MAX + 1.0) * (b - a) + a;
}
#endif

//***************************************************
// RULE FUNCTION
void *HPPtransition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    HPPState *out;
    HPPState *aux;
    HPPState *cs;
    HPPState **ne;
    HPPState **in;
    double a = 0.2; // recovery rate
    double r = 0.6; // infection rate
    int i,I;
    double u;

    cs = (HPPState *)cellstate;
    ne = (HPPState **)neighbor_states;
    in = (HPPState **)inputs;
    out = (HPPState *)malloc(sizeof(HPPState));
    aux = (HPPState *)malloc(sizeof(HPPState));
    
    // Order declared for neighbors (W,S,E,N)

    // PROPAGATION
    out->w = 0;
    out->s = 0;
    out->e = 0;
    out->n = 0;
    if(neighbor_states[0] != NULL){ // N
	out->s = ne[0]->s;
    }
    if(neighbor_states[1] != NULL){ // W
	out->e = ne[1]->e;
    }
    if(neighbor_states[2] != NULL){ // E
	out->w = ne[2]->w;
    }
    if(neighbor_states[3] != NULL){ // S
	out->n = ne[3]->n;
    }

    //srand(time(NULL));
    // COLLISION
    if (out->w && out->e && !out->n && !out->s){
	//ModelicaFormatMessage("Collision WE\n");
	// predefined orientation for collision
	out->n = out->w;
	out->s = out->e;
	// random orientation for collision
	//ModelicaFormatMessage("Rand 50% = %d\n",rand()%2);
	/*if (rand() % 2){
	    out->n = out->w;
	    out->s = out->e;
	}else{
	    out->s = out->w;
	    out->n = out->e;
	    }*/
	out->w = 0;
	out->e = 0;
    }else if (out->n && out->s && !out->w && !out->e){
	//ModelicaFormatMessage("Collision NS\n");
	// predefined orientation for collision
	out->w = out->n;
	out->e = out->s;
	// random orientation for collision
	/*if (rand() % 2){
	    out->w = out->n;
	    out->e = out->s;
	}else{
	    out->e = out->n;
	    out->w = out->s;
	    }*/
	out->n = 0;
	out->s = 0;	
    }
    
    // DISEASE SPREAD
    // Infection
    I = 0;
    if(out->n == 2)
	I++;
    if(out->w == 2)
	I++;
    if(out->e == 2)
	I++;
    if(out->s == 2)
	I++;
    u = uniform(0,1);
    if(I && out->n == 1 && u <= r)//(1-pow(1-r,I)))
	out->n = 2;
    u = uniform(0,1);
    if(I && out->w == 1 && u <= r)//(1-pow(1-r,I)))
	out->w = 2;
    u = uniform(0,1);
    if(I && out->e == 1 && u <= r)//(1-pow(1-r,I)))
	out->e = 2;
    u = uniform(0,1);
    if(I && out->s == 1 && u <= r)//(1-pow(1-r,I)))
	out->s = 2;
    
    // Recovery    
    u = uniform(0,1);
    if(out->n == 2 && u <= a ){
	out->n = 3;
    }
    u = uniform(0,1);
    if(out->w == 2 && u <= a ){
	out->w = 3;
    }
    u = uniform(0,1);
    if(out->e == 2 && u <= a ){
	out->e = 3;
    }
    u = uniform(0,1);
    if(out->s == 2 && u <= a )
	out->s = 3;
    
    
    if(cs->n != out->n)
       return (void *)out;
   if(cs->s != out->s)
       return (void *)out;
   if(cs->e != out->e)
       return (void *)out;
   if(cs->w != out->w)
       return (void *)out;
   
   return NULL;
}


int HPPStep(void* space){
    CS_Step(space,&HPPtransition);
    return 1;
}


//**************************************
// INTERFACE FUNCTIONS

// function to convert the state of a cell into a double value
double HPPOutputS(void* space, int x, int y, int z){
    double out;
    HPPState* s;
    int i;
    
    s = (HPPState *)CS_GetState(space,x,y,1);
    
    out = 0;
    if (s->n == 1)
	out++;
    if (s->w == 1)
	out++;
    if (s->e == 1)
	out++;
    if (s->s == 1)
	out++;
    
    return out;
}

// function to convert the state of a cell into a double value
double HPPOutputI(void* space, int x, int y, int z){
    double out;
    HPPState* s;
    int i;
    
    s = (HPPState *)CS_GetState(space,x,y,1);
    out = 0;
    if (s->n == 2)
	out++;
    if (s->w == 2)
	out++;
    if (s->e == 2)
	out++;
    if (s->s == 2)
	out++;
	
    return out;
}

// function to convert the state of a cell into a double value
double HPPOutputR(void* space, int x, int y, int z){
    double out;
    HPPState* s;
    int i;
    
    s = (HPPState *)CS_GetState(space,x,y,1);
    out = 0;
    if (s->n == 3)
	out++;
    if (s->w == 3)
	out++;
    if (s->e == 3)
	out++;
    if (s->s == 3)
	out++;
    
    return out;
}


#endif
