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

#ifndef C17FHP
#define C17FHP

#include <CellularAutomataLib.c>


/****************************************/
/* LGCA MODELS (FHP) FOR ARGESIM C17 BENCHMARK      */
/****************************************/

//**************************************
// Cell state
// User may redefine the state of the cell as desired
typedef struct FHPState{
    // particles values 0=empty, 1= susceptible, 2= infected, 3= recovered
    //int nw,ne,w,e,sw,se; // particles 
    int p[6]; // particles {nw,ne,w,e,sw,se}
}FHPState;



//**************************************
// CELLULAR SPACE FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * FHPDefaultState(){
    FHPState *s;
    s = (FHPState *)malloc(sizeof(FHPState));
    int i;
    
    //set the default values for state variables
    for(i=0;i<6;i++)
	s->p[i] = 0;
    
    return (void *)s;
}

int FHPDefault(void* space){
    CS_InitDefault(space, &FHPDefaultState);
    return 1;
    
}


void FHPSIRInitial(void* space, int x, int y, int z){
    int i,j,n,pos,k;
    FHPState *s;
    int iniS = 16000;
    int iniI = 1000;
    int iniR = 0;
    
    srand(time(NULL));
    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniR){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 1){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 3;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }
    
    return;
}

void FHPSIRInitial2(void* space, int x, int y, int z){
    int i,j,n,pos,k;
    FHPState *s;
    int iniS = 40000;
    int iniI = 1000;
    int iniR = 0;
    
    srand(time(NULL));

    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniR){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 1){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 3;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }
    
    return;
}

void FHPSIRInitialFull(void* space, int x, int y, int z){
    int i,j,n,pos,k;
    FHPState *s;
    int iniS = 16000;
    int iniI = 100;
    int iniR = 4000;
    
    srand(time(NULL));
 
    n = 0;
    while(n < iniR){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 3;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%(y/2);
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    
    return;
}

void FHPSIRInitialHalf(void* space, int x, int y, int z){
    int i,j,n,pos,k;
    FHPState *s;
    int iniS = 16000;
    int iniI = 100;
    int iniR = 4000;
    
    srand(time(NULL));

    n = 0;
    while(n < iniR){
	i = rand()%x;
	j = rand()%(y/2);
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 3;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }
    
    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%(y/2);
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    return;
}

void FHPSIRInitialBorder(void* space, int x, int y,int z){
    int i,j,n,pos,k,starti,startj;
    FHPState *s;
    int iniS = 16000;
    int iniI = 100;
    int iniR = 4000;
    
    srand(time(NULL));
    
    n = 0;
    starti = 1;
    startj = 1;
    while(n < iniR){
	i = starti;
	for(j=startj;j<((y/2)-startj);j++){
	    s = CS_GetState(space,i,j,1);
	    for(pos=0;pos<6;pos++){
		if(s->p[pos] ==0){
		    s->p[pos] = 3;
		    n++;
		}
		if(n >= iniR)
		    break;
	    }
	    CS_SetState(space,i,j,1,s);
	}
	if(n >= iniR)
	    break;
	j = (y/2)-startj;
	for(i=starti;i<x-starti;i++){
	    s = CS_GetState(space,i,j,1);
	    for(pos=0;pos<6;pos++){
		if(s->p[pos] == 0){
		    s->p[pos] = 3;
		    n++;
		}
		if(n >= iniR)
		    break;
	    }
	    CS_SetState(space,i,j,1,s);
	}
	if(n >= iniR)
	    break;
	i = x-starti;
	for(j=startj;j<((y/2)-startj);j++){
	    s = CS_GetState(space,i,j,1);
	    for(pos=0;pos<6;pos++){
		if(s->p[pos] ==0){
		    s->p[pos] = 3;
		    n++;
		}
		if(n >= iniR)
		    break;
	    }
	    CS_SetState(space,i,j,1,s);
	}
	if(n >= iniR)
	    break;
	j = startj;
	for(i=starti;i<x-starti;i++){
	    s = CS_GetState(space,i,j,1);
	    for(pos=0;pos<6;pos++){
		if(s->p[pos] ==0){
		    s->p[pos] = 3;
		    n++;
		}
		if(n >= iniR)
		    break;
	    }
	    CS_SetState(space,i,j,1,s);
	}
	starti = starti+1;
	startj = startj+1;
    }
 
   n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%(y/2);
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }


    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    return;
}

#ifndef C17HPP
double uniform(double a, double b)
{
    return rand() / (RAND_MAX + 1.0) * (b - a) + a;
}
#endif

//***************************************************
// RULE FUNCTION
void *transition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    FHPState *out;
    FHPState *aux;
    FHPState *cs;
    FHPState **ne;
    double **in;
    double a = 0.2; // recovery rate
    double r = 0.6; // infection rate
    int i,j,I,N;
    double u;

    cs = (FHPState *)cellstate;
    ne = (FHPState **)neighbor_states;
    in = (double **)inputs;
    out = (FHPState *)malloc(sizeof(FHPState));
    aux = (FHPState *)malloc(sizeof(FHPState));
    
    for(i=0;i<6;i++)
	out->p[i] = 0; 
    


    // PROPAGATION
    for(i=0;i<n_neighbors;i++){
	if(neighbor_states[i] != NULL){ // NW
	    out->p[abs(i-(n_neighbors-1))] = ne[i]->p[abs(i-(n_neighbors-1))];
	}
    }
    
    // COLLISION
    //srand(time(NULL));
    // 2-collisions
    if (out->p[0] && out->p[5] && !out->p[1] && !out->p[2]  && !out->p[3] && !out->p[4]){
	//ModelicaFormatMessage("Collision NW-SE\n");
	// predefined orientation for collision
	out->p[1] = out->p[0];
	out->p[4] = out->p[5];
	// random orientation for collision
	/*if (rand() % 2){
	  out->p[1] = out->p[0];
	  out->p[4] = out->p[5];
	}else{
	  out->p[2] = out->p[0];
	  out->p[3] = out->p[5];
	  }*/
	out->p[0] = 0;
	out->p[5] = 0;
    }else if (out->p[1] && out->p[4] && !out->p[0] && !out->p[2]  && !out->p[3] && !out->p[5]){
	//ModelicaFormatMessage("Collision NE-SW\n");
	// predefined orientation for collision
	out->p[3] = out->p[1];
	out->p[2] = out->p[4];
	// random orientation for collision
	/*if (rand() % 2){
	    out->p[3] = out->p[1];
	    out->p[2] = out->p[4];
	  }else{
	    out->p[0] = out->p[1];
	    out->p[5] = out->p[4];
	    }*/
	out->p[1] = 0;
	out->p[4] = 0;	
    }else if (out->p[2] && out->p[3] && !out->p[0] && !out->p[1]  && !out->p[4] && !out->p[5]){
	//ModelicaFormatMessage("Collision W-E\n");
	// predefined orientation for collision
	out->p[0] = out->p[2];
	out->p[5] = out->p[3];
	// random orientation for collision
	/*if (rand() % 2){
	  out->p[0] = out->p[2];
	  out->p[5] = out->p[3];
	  }else{
	  out->p[1] = out->p[2];
	  out->p[4] = out->p[3];
	  }*/
	out->p[2] = 0;
	out->p[3] = 0;	
    // 3-collisions
    }else if (out->p[0] && out->p[3] && out->p[4] && !out->p[1]  && !out->p[2] && !out->p[5]){ 
	//ModelicaFormatMessage("Collision NW-E-SW\n");
	// predefined orientation for collision
	out->p[1] = out->p[0];
	out->p[5] = out->p[3];
	out->p[2] = out->p[4];
	// random orientation for collision
	/*if (rand() % 2){
	out->p[1] = out->p[0];
	out->p[5] = out->p[3];
	out->p[2] = out->p[4];
	}else{
	out->p[2] = out->p[0];
	out->p[1] = out->p[3];
	out->p[5] = out->p[4];
	    }*/
	out->p[0] = 0;
	out->p[3] = 0;	
	out->p[4] = 0;	
    }else if (out->p[1] && out->p[2] && out->p[5] && !out->p[0]  && !out->p[3] && !out->p[4]){ 
	//ModelicaFormatMessage("Collision NW-E-SW\n");
	// predefined orientation for collision
	out->p[3] = out->p[1];
	out->p[0] = out->p[2];
	out->p[4] = out->p[5];
	// random orientation for collision
	/*if (rand() % 2){
	out->p[3] = out->p[1];
	out->p[2] = out->p[2];
	out->p[4] = out->p[5];
	}else{
	out->p[0] = out->p[1];
	out->p[4] = out->p[2];
	out->p[3] = out->p[5];
	    }*/
	out->p[1] = 0;
	out->p[2] = 0;	
	out->p[5] = 0;	
    }


    

    // DISEASE SPREAD
    // Infection
    I = 0;
    for(i=0;i<6;i++)
	if(out->p[i] == 2)
	    I++;
    for(i=0;i<6;i++){
	u = uniform(0,1);
	if(I && out->p[i] == 1 && u <= r)//(1-pow(1-r,I)))
	    out->p[i] = 2;
    }
    
    // Recovery    
    for(i=0;i<6;i++){
	u = uniform(0,1);
	if(out->p[i] == 2 && u <= a)
	    out->p[i] = 3;
    }
    
    for(i=0;i<6;i++){
	if(cs->p[i] != out->p[i])
	    return (void *)out;
    }
    return NULL;
    
}


int FHPStep(void* space){
    return CS_Step(space,&transition);
 }



//*********************************************************************
// RULE FUNCTION
void *transitionR(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    FHPState *out;
    FHPState *aux;
    FHPState *cs;
    FHPState **ne;
    double **in;
    double a = 0.2; // recovery rate
    double r = 0.3; // infection rate
    int i,j,I,N;
    double u;

    cs = (FHPState *)cellstate;
    ne = (FHPState **)neighbor_states;
    in = (double **)inputs;
    out = (FHPState *)malloc(sizeof(FHPState));
    aux = (FHPState *)malloc(sizeof(FHPState));
    
    for(i=0;i<6;i++)
	out->p[i] = 0; 
   

    // PROPAGATION
    for(i=0;i<n_neighbors;i++){
	if(neighbor_states[i] != NULL){ // NW
	    out->p[abs(i-(n_neighbors-1))] = ne[i]->p[abs(i-(n_neighbors-1))];
	}
    }
 
    // COLLISION
    //srand(time(NULL));
    // 2-collisions
    if (out->p[0] && out->p[5] && !out->p[1] && !out->p[2]  && !out->p[3] && !out->p[4]){
	//ModelicaFormatMessage("Collision NW-SE\n");
	// predefined orientation for collision
	out->p[1] = out->p[0];
	out->p[4] = out->p[5];
	// random orientation for collision
	/*if (rand() % 2){
	  out->p[1] = out->p[0];
	  out->p[4] = out->p[5];
	}else{
	  out->p[2] = out->p[0];
	  out->p[3] = out->p[5];
	  }*/
	out->p[0] = 0;
	out->p[5] = 0;
    }else if (out->p[1] && out->p[4] && !out->p[0] && !out->p[2]  && !out->p[3] && !out->p[5]){
	//ModelicaFormatMessage("Collision NE-SW\n");
	// predefined orientation for collision
	out->p[3] = out->p[1];
	out->p[2] = out->p[4];
	// random orientation for collision
	/*if (rand() % 2){
	    out->p[3] = out->p[1];
	    out->p[2] = out->p[4];
	  }else{
	    out->p[0] = out->p[1];
	    out->p[5] = out->p[4];
	    }*/
	out->p[1] = 0;
	out->p[4] = 0;	
    }else if (out->p[2] && out->p[3] && !out->p[0] && !out->p[1]  && !out->p[4] && !out->p[5]){
	//ModelicaFormatMessage("Collision W-E\n");
	// predefined orientation for collision
	out->p[0] = out->p[2];
	out->p[5] = out->p[3];
	// random orientation for collision
	/*if (rand() % 2){
	  out->p[0] = out->p[2];
	  out->p[5] = out->p[3];
	  }else{
	  out->p[1] = out->p[2];
	  out->p[4] = out->p[3];
	  }*/
	out->p[2] = 0;
	out->p[3] = 0;	
    // 3-collisions
    }else if (out->p[0] && out->p[3] && out->p[4] && !out->p[1]  && !out->p[2] && !out->p[5]){ 
	//ModelicaFormatMessage("Collision NW-E-SW\n");
	// predefined orientation for collision
	out->p[1] = out->p[0];
	out->p[5] = out->p[3];
	out->p[2] = out->p[4];
	// random orientation for collision
	/*if (rand() % 2){
	out->p[1] = out->p[0];
	out->p[5] = out->p[3];
	out->p[2] = out->p[4];
	}else{
	out->p[2] = out->p[0];
	out->p[1] = out->p[3];
	out->p[5] = out->p[4];
	    }*/
	out->p[0] = 0;
	out->p[3] = 0;	
	out->p[4] = 0;	
    }else if (out->p[1] && out->p[2] && out->p[5] && !out->p[0]  && !out->p[3] && !out->p[4]){ 
	//ModelicaFormatMessage("Collision NW-E-SW\n");
	// predefined orientation for collision
	out->p[3] = out->p[1];
	out->p[0] = out->p[2];
	out->p[4] = out->p[5];
	// random orientation for collision
	/*if (rand() % 2){
	out->p[3] = out->p[1];
	out->p[2] = out->p[2];
	out->p[4] = out->p[5];
	}else{
	out->p[0] = out->p[1];
	out->p[4] = out->p[2];
	out->p[3] = out->p[5];
	    }*/
	out->p[1] = 0;
	out->p[2] = 0;	
	out->p[5] = 0;	
    }
    
    // DISEASE SPREAD
    // Infection
    I = 0;
    for(i=0;i<6;i++)
	if(out->p[i] == 2)
	    I++;
    for(i=0;i<6;i++){
	u = uniform(0,1);
	if(I && out->p[i] == 1 && u <= r)// (1-pow(1-r,I)))
	    out->p[i] = 2;
    }
    
    // Recovery    
    for(i=0;i<6;i++){
	u = uniform(0,1);
	if(out->p[i] == 2 && u <= a)
	    out->p[i] = 3;
    }

    for(i=0;i<6;i++){
	if(cs->p[i] != out->p[i])
	    return (void *)out;
    }
    return NULL;
}


void FHPSIRRearrange(void* space, int x, int y){
    int i,j,n,pos,k;
    FHPState *s;
    int iniS = 0;
    int iniI = 0;
    int iniR = 0;
    
    
    for(i=1;i<=x;i++)
	for(j=1;j<=y;j++){
	    s = CS_GetState(space,i,j,1);
	    for(pos=0;pos<6;pos++){
		if(s->p[pos] == 1)
		    iniS++;
		else if(s->p[pos] == 2)
		    iniI++;
		else if(s->p[pos] == 3)
		    iniR++;
	    }
	}
    
    srand(time(NULL));
    
    n = 0;
    while(n < iniS){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 1;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniI){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 2;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }

    n = 0;
    while(n < iniR){
	i = rand()%x;
	j = rand()%y;
	s = CS_GetState(space,i+1,j+1,1);
	k=1;
	pos = rand()%6;
	while(k<7 && s->p[pos] != 0){
	    pos = (pos+1)%6;
	    k++;
	}
	if (k < 7){
	    s->p[pos] = 3;
	    n++;
	}
	CS_SetState(space,i+1,j+1,1,s);
    }
    
    return;
}

int FHPStepR(void* space){
    CS_Step(space,&transitionR);
    FHPSIRRearrange(space,100,100);
    return 1;
}



/*********************************************/

//**************************************
// INTERFACE FUNCTIONS

// function to convert the state of a cell into a double value
double OutputS(void* space, int x, int y,int z){
    double out;
    FHPState* s;
    int i;
    
    s = (FHPState *)CS_GetState(space,x,y,1);
    
    out = 0;
    for(i=0;i<6;i++)
	if (s->p[i] == 1)
	    out++;
    
    return out;
}

// function to convert the state of a cell into a double value
double OutputI(void* space, int x, int y, int z){
    double out;
    FHPState* s;
    int i;
    
    s = (FHPState *)CS_GetState(space,x,y,1);
    out = 0;
    for(i=0;i<6;i++)
	if (s->p[i] == 2)
	    out++;
	
    return out;
}

// function to convert the state of a cell into a double value
double OutputR(void* space, int x, int y,int z){
    double out;
    FHPState* s;
    int i;

    s = (FHPState *)CS_GetState(space,x,y,1);
    out = 0;
    for(i=0;i<6;i++)
	if (s->p[i] == 3)
	    out++;
    
    return out;
}

#endif
