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

#ifndef CHIPS
#define CHIPS

#include <CellularAutomataLib.c>

/****************************************/
/* CHIP CELLULAR AUTOMATA               */
/****************************************/

//**************************************
// Cell state
typedef struct CHIPState{
    double t;
}CHIPState;



//**************************************
// CA WRAPPER FUNCTIONS

// Function that allocates memory and sets the default state for the cells
void * CHIPDefaultState(){
    CHIPState *s;
    s = (CHIPState *)malloc(sizeof(CHIPState));
    
    s->t = 20; // default temp to 20
    return (void *)s;
}

int CHIPDefault(void* space){
    CS_InitDefault(space,&CHIPDefaultState);
    return 1;
}



// Function that describes the state of initialized cells
void CHIPInitialState(void *cs){
    CHIPState *s;
    s = (CHIPState *)cs;
    
    s->t = 50; // initial temp to 50
    return;
}

// initializing function for the selected cell
void CHIPInitial(void* space, int modx, int mody, int modz){
    CS_Init(space, modx, mody, modz, &CHIPInitialState);
    return;
}

//***************************************************
// RULE FUNCTION

void* singlechip(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    CHIPState *out;
    CHIPState *cs;
    CHIPState **ne;
    CHIPState **in;
    
    
    // neighbors = [-1,0; 0,-1; 0,1; 1,0]
    double derT;
    
    double gamma_to = 100; // coefficient of heat transfer from top (packHI)
    double gamma_bo = 500; // coefficient of heat transfer from bottom (packLO)
    double Pto,Pbo,Pgen; // top and bottom temperatures
    
    double cp=710; //"Average specific heat";
    double ro=2330; //"Average density";
    int rows=10;
    int cols=10;
    double length=0.005; //"layer length (rows)";
    double width=0.005; //"layer width (cols)";
    double thickness=0.0001; //"layer thickness";
    double k=149; //"Thermal conductivity";
    double T; // Temperature 
    // Heat capacity of each volume element
    double c=cp*ro*(length/rows)*(width/cols)*thickness;
    // Thermal conductances between element centres
    double gfrcc=k*(width/cols)*thickness/(length/rows);
    double glrcc=k*(length/rows)*thickness/(width/cols);
    double RATE = 0.001;
    double nT;
    double nderT;
    


    
    cs = (CHIPState *)cellstate;
    ne = (CHIPState **)neighbor_states;
    in = (CHIPState **)inputs;
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    //printf("single chip step [%d,%d,%d]\n",x,y,z);
    
    // CONDUCTION FROM NEIGHBORS
    sum = 0;
    for(i=0;i<n_neighbors;i++)
	if (neighbor_states[i] != NULL){
	    sum += glrcc*(ne[i]->t - cs->t);
	}
    /*  sum = glrcc*(neighbors[1] - T)+
	glrcc*(neighbors[2] - T)+
	gfrcc*(neighbors[0] - T)+
	gfrcc*(neighbors[3] - T);
    */
    
    //  ModelicaFormatMessage("\n");
    //  ModelicaFormatMessage("gfrc=%f, glrcc=%f, sum = %f\n",gfrcc,glrcc,sum);
    
    //printf("received inputs = %d \n",n_inputs);
    // just for testing
    if (n_inputs > 0 && inputs_rcv[0] == 0)
	in[0]->t = cs->t;
    
    
    
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-cs->t);
    //  Pto = gamma_to*(length*width)/(rows*cols)*(inputs[0]-T);
    Pbo  = 0;// gamma_bo*(length*width)/(rows*cols)*(inputs[0]-T);
    

    // EXTERNAL POWER AS INPUT
    //printf("3single chip step [%d,%d,%d]\n",x,y,z);
    
    if (inputs_rcv[2] > 0)
	Pgen = in[2]->t;
    else if (inputs_rcv[3] > 0)
	Pgen = in[3]->t;
    else
	Pgen = 0;

    //printf("4 single chip step [%d,%d,%d]\n",x,y,z);
    
    derT = (sum+Pto+Pbo+Pgen)/c; 
    //ModelicaFormatMessage("input0=%f, T=%f, Pto = %f, Pbo = %f, Pgen = %f, c = %f, dert = %f\n",inputs[0],T,Pto,Pbo,Pgen,c,derT);
    
    /**********************************/
    nT = cs->t + derT*RATE;
    sum = 0;
    
    for(i=0;i<n_neighbors;i++)
	if (neighbor_states[i] != NULL){
	    sum += glrcc*(ne[i]->t - nT);
	    //ModelicaFormatMessage("n[%d] = %f,",i,neighbors[i]);    
	}
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-nT);
    
    nderT = (sum+Pto+Pbo+Pgen)/c; 
    
    /**************************************/
    
    
    // leap-frog 
    out->t = cs->t+RATE*(0.5*(derT+nderT));
    
    // explicit Euler
    //out->t = cs->t+(derT*RATE);
    
    if (out->t == cs->t)
	return NULL;
    else
        return (void *)out;
  
}

int SCHIPStep(void* space){
    CS_Step(space,&singlechip);
    return 1;
}

// Function that returns the value to display in the graphical animation
double CHIPDisplay(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    CHIPState *cs;
    double norm;
    double maxt = 100;
    
    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (CHIPState *)cell->cellstate;
	norm = cs->t/maxt;
	return (double)ColorToInt((Color){255,255*norm,0,255});
    }
}

int CHIPSetDisplay(void *space){
    CS_SetDisplay(space, &CHIPDisplay);   
    return 1;
}




void* chip(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    CHIPState *out;
    CHIPState *cs;
    CHIPState **ne;
    CHIPState **in;
    
    
    // neighbors = [-1,0; 0,-1; 0,1; 1,0]
    double derT;
    
    double gamma_to = 500; // coefficient of heat transfer from top (packHI)
    double gamma_bo = 500; // coefficient of heat transfer from bottom (packLO)
    double Pto,Pbo,Pgen; // top and bottom temperatures
    
    double cp=710; //"Average specific heat";
    double ro=2330; //"Average density";
    int rows=10;
    int cols=10;
    double length=0.005; //"layer length (rows)";
    double width=0.005; //"layer width (cols)";
    double thickness=0.0001; //"layer thickness";
    double k=149; //"Thermal conductivity";
    double T; // Temperature 
    // Heat capacity of each volume element
    double c=cp*ro*(length/rows)*(width/cols)*thickness;
    // Thermal conductances between element centres
    double gfrcc=k*(width/cols)*thickness/(length/rows);
    double glrcc=k*(length/rows)*thickness/(width/cols);
    double RATE = 0.0001;
    double nT;
    double nderT;
    
    
    cs = (CHIPState *)cellstate;
    ne = (CHIPState **)neighbor_states;
    in = (CHIPState **)inputs;
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    
    // CONDUCTION FROM NEIGHBORS
    sum = 0;
    for(i=0;i<n_neighbors;i++)
	if (neighbor_states[i] != NULL){
	    sum += glrcc*(ne[i]->t - cs->t);
	}
    /*  sum = glrcc*(neighbors[1] - T)+
	glrcc*(neighbors[2] - T)+
	gfrcc*(neighbors[0] - T)+
	gfrcc*(neighbors[3] - T);
    */
    
    //  ModelicaFormatMessage("\n");
    //  ModelicaFormatMessage("gfrc=%f, glrcc=%f, sum = %f\n",gfrcc,glrcc,sum);
    
    
    // just for testing
    if (inputs_rcv[0] == 0)
	in[0]->t = cs->t;
    
  
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-cs->t);
    //  Pto = gamma_to*(length*width)/(rows*cols)*(inputs[0]-T);
    Pbo  = 0;// gamma_bo*(length*width)/(rows*cols)*(inputs[0]-T);
    
    // EXTERNAL POWER AS INPUT
    
  if (inputs_rcv[1] > 0)
      Pgen = in[1]->t;
  else if (inputs_rcv[2] > 0)
      Pgen = in[2]->t;
  else
      Pgen = 0;

  
  derT = (sum+Pto+Pbo+Pgen)/c; 
  //ModelicaFormatMessage("input0=%f, T=%f, Pto = %f, Pbo = %f, Pgen = %f, c = %f, dert = %f\n",inputs[0],T,Pto,Pbo,Pgen,c,derT);

  /**********************************/
  nT = cs->t + derT*RATE;
  sum = 0;
  
  for(i=0;i<n_neighbors;i++)
      if (neighbor_states[i] != NULL){
          sum += glrcc*(ne[i]->t - nT);
          //ModelicaFormatMessage("n[%d] = %f,",i,neighbors[i]);    
      }
  Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-nT);
  
  nderT = (sum+Pto+Pbo+Pgen)/c; 
 
  /**************************************/
 
 
   
  //out = (State2D)(T+(derT*RATE));
  //out = (State2D)(T+(nderT*RATE));
  out->t = cs->t+RATE*(0.5*(derT+nderT));

  // explicit
  //out->t = cs->t+(derT*RATE);

  if (out->t == cs->t)
      return NULL;
  else
      return (void *)out;
  
}

int CHIPStep(void* space){
    CS_Step(space,&chip);
    return 1;
}


void* packHI(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    CHIPState *out;
    CHIPState *cs;
    CHIPState **ne;
    CHIPState **in;
    
    
    // neighbors = [-1,0; 0,-1; 0,1; 1,0]
    double derT;
    
    double gamma_to = 100; // coefficient of heat transfer from top (packHI)
    double gamma_bo = 500; // coefficient of heat transfer from bottom (packLO)
    double Pto,Pbo,Pgen; // top and bottom temperatures
    
    double cp=500; //"Average specific heat";
    double ro=800; //"Average density";
    int rows=10;
    int cols=10;
    double length=0.005; //"layer length (rows)";
    double width=0.005; //"layer width (cols)";
    double thickness=0.001; //"layer thickness";
    double k=50; //"Thermal conductivity";
    double T; // Temperature 
    // Heat capacity of each volume element
    double c=cp*ro*(length/rows)*(width/cols)*thickness;
    // Thermal conductances between element centres
    double gfrcc=k*(width/cols)*thickness/(length/rows);
    double glrcc=k*(length/rows)*thickness/(width/cols);
    double RATE = 0.0001;
    double nT;
    double nderT;
    
    
    cs = (CHIPState *)cellstate;
    ne = (CHIPState **)neighbor_states;
    in = (CHIPState **)inputs;
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    
    // CONDUCTION FROM NEIGHBORS
    sum = 0;
    for(i=0;i<n_neighbors;i++)
	if (neighbor_states[i] != NULL){
	    sum += glrcc*(ne[i]->t - cs->t);
	}
    /*  sum = glrcc*(neighbors[1] - T)+
	glrcc*(neighbors[2] - T)+
	gfrcc*(neighbors[0] - T)+
	gfrcc*(neighbors[3] - T);
    */
    
    //  ModelicaFormatMessage("\n");
    //  ModelicaFormatMessage("gfrc=%f, glrcc=%f, sum = %f\n",gfrcc,glrcc,sum);
    
    
    // just for testing
    if (inputs_rcv[0] == 0)
	in[0]->t = cs->t;
    
  
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-cs->t);
    //  Pto = gamma_to*(length*width)/(rows*cols)*(inputs[0]-T);
    //Pbo  = 0;
    Pbo = gamma_bo*(length*width)/(rows*cols)*(in[0]->t-cs->t);
    
    // EXTERNAL POWER AS INPUT
    
  if (inputs_rcv[1] > 0)
      Pgen = in[1]->t;
  else if (inputs_rcv[2] > 0)
      Pgen = in[2]->t;
  else
      Pgen = 0;

  
  derT = (sum+Pto+Pbo+Pgen)/c; 
  //ModelicaFormatMessage("input0=%f, T=%f, Pto = %f, Pbo = %f, Pgen = %f, c = %f, dert = %f\n",inputs[0],T,Pto,Pbo,Pgen,c,derT);

  /**********************************/
  nT = cs->t + derT*RATE;
  sum = 0;
  
  for(i=0;i<n_neighbors;i++)
      if (neighbor_states[i] != NULL){
          sum += glrcc*(ne[i]->t - nT);
          //ModelicaFormatMessage("n[%d] = %f,",i,neighbors[i]);    
      }
  Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-nT);
  
  nderT = (sum+Pto+Pbo+Pgen)/c; 
  /**************************************/
 
 
   
  //out = (State2D)(T+(derT*RATE));
  //out = (State2D)(T+(nderT*RATE));
  out->t = cs->t+RATE*(0.5*(derT+nderT));

  // explicit
  //out->t = cs->t+(derT*RATE);
  
  if (out->t == cs->t)
      return NULL;
  else
    return (void *)out;
  
}

int PACKHIStep(void* space){
    void* (*rule)(void*,int,int,int,void**,int,void**,int,int*) = &packHI;
      
    CS_Step(space,rule);
    return 1;
}



void* packLO(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    double sum;
    int i;
    CHIPState *out;
    CHIPState *cs;
    CHIPState **ne;
    CHIPState **in;
    
    
    // neighbors = [-1,0; 0,-1; 0,1; 1,0]
    double derT;
    
    double gamma_to = 500; // coefficient of heat transfer from top (packHI)
    double gamma_bo = 800; // coefficient of heat transfer from bottom (packLO)
    double Pto,Pbo,Pgen; // top and bottom temperatures
    
    double cp=500; //"Average specific heat";
    double ro=800; //"Average density";
    int rows=10;
    int cols=10;
    double length=0.005; //"layer length (rows)";
    double width=0.005; //"layer width (cols)";
    double thickness=0.001; //"layer thickness";
    double k=50; //"Thermal conductivity";
    double T; // Temperature 
    // Heat capacity of each volume element
    double c=cp*ro*(length/rows)*(width/cols)*thickness;
    // Thermal conductances between element centres
    double gfrcc=k*(width/cols)*thickness/(length/rows);
    double glrcc=k*(length/rows)*thickness/(width/cols);
    double RATE = 0.0001;
    double nT;
    double nderT;
    
    
    cs = (CHIPState *)cellstate;
    ne = (CHIPState **)neighbor_states;
    in = (CHIPState **)inputs;
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    
    // CONDUCTION FROM NEIGHBORS
    sum = 0;
    for(i=0;i<n_neighbors;i++)
	if (neighbor_states[i] != NULL){
	    sum += glrcc*(ne[i]->t - cs->t);
	}
    /*  sum = glrcc*(neighbors[1] - T)+
	glrcc*(neighbors[2] - T)+
	gfrcc*(neighbors[0] - T)+
	gfrcc*(neighbors[3] - T);
    */
    
    //  ModelicaFormatMessage("\n");
    //  ModelicaFormatMessage("gfrc=%f, glrcc=%f, sum = %f\n",gfrcc,glrcc,sum);
    
    
    // just for testing
    if (inputs_rcv[0] == 0)
	in[0]->t = cs->t;
    
  
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-cs->t);
    //  Pto = gamma_to*(length*width)/(rows*cols)*(inputs[0]-T);
    //Pbo  = 0;
    Pbo = gamma_bo*(length*width)/(rows*cols)*(in[0]->t-cs->t);
    
    // EXTERNAL POWER AS INPUT
    
  if (inputs_rcv[1] > 0)
      Pgen = in[1]->t;
  else if (inputs_rcv[2] > 0)
      Pgen = in[2]->t;
  else
      Pgen = 0;

  
  derT = (sum+Pto+Pbo+Pgen)/c; 
  //ModelicaFormatMessage("input0=%f, T=%f, Pto = %f, Pbo = %f, Pgen = %f, c = %f, dert = %f\n",inputs[0],T,Pto,Pbo,Pgen,c,derT);

  /**********************************/
  nT = cs->t + derT*RATE;
  sum = 0;
  
  for(i=0;i<n_neighbors;i++)
      if (neighbor_states[i] != NULL){
          sum += glrcc*(ne[i]->t - nT);
          //ModelicaFormatMessage("n[%d] = %f,",i,neighbors[i]);    
      }
  Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-nT);
  
  nderT = (sum+Pto+Pbo+Pgen)/c; 
 
  /**************************************/
 
 
   
  //out = (State2D)(T+(derT*RATE));
  //out = (State2D)(T+(nderT*RATE));
  out->t = cs->t+RATE*(0.5*(derT+nderT));

  // explicit
  //out->t = cs->t+(derT*RATE);

  if (out->t == cs->t)
      return NULL;
  else
      return (void *)out;
  
}

int PACKLOStep(void* space){
    void* (*rule)(void*,int,int,int,void**,int,void**,int,int*) = &packHI;
      
    CS_Step(space,rule);
    return 1;
}

/*********************************************/

void CHIPExtInput(void* space,int x, int y, int z, double value,int input_id){
    CHIPState* inp;
    
    inp = (CHIPState *)malloc(sizeof(CHIPState));
    inp->t = value;
    CS_SetInput(space,x,y, z,(void*)inp,input_id);
    
    return;
}

void CHIPExtInit(void* space,int x, int y, int z, double value){
    CHIPState* s;

    s = (CHIPState *)CS_GetState(space,x,y,z);
    s->t = value;
    
    return;
}

double CHIPOutput(void* space, int x, int y, int z){
    CHIPState* s;

    s = (CHIPState *)CS_GetState(space,x,y,z);
    return s->t;
}

void CHIPSetInput(void* Fspace, int Fx, int Fy, int Fz, void* Tspace, int Tx, int Ty, int Tz, int input_id){
    CHIPState* s;
    CHIPState* inp;
    
    inp = (CHIPState *)malloc(sizeof(CHIPState));
    s = (CHIPState *)CS_GetState(Fspace,Fx,Fy,Fz);
    *inp = *s;
    CS_SetInput(Tspace,Tx,Ty,Tz,(void*)inp,input_id);
}



// RULE FUNCTIONS

/*

State2D packHI(State2D cellstate, State2D *neighbors, int n_neighbors,int *neighbors_present,State2D *inputs, int n_inputs, int *inputs_rcv){
  State2D sum,out;
  int i;
  // neighbors = [-1,0; 0,-1; 0,1; 1,0]
  double derT;
  
  double gamma_to = 100; // coefficient of heat transfer from top (air)
  double gamma_bo = 500; // coefficient of heat transfer from bottom (chip)
  double Pto,Pbo,Pgen; // top and bottom temperatures
      
  double cp=500; //"Average specific heat";
  double ro=800; //"Average density";
  int rows=10;
  int cols=10;
  double length=0.005; //"layer length (rows)";
  double width=0.005; //"layer width (cols)";
  double thickness=0.001; //"layer thickness";
  double k=50; //"Thermal conductivity";
  double T; // Temperature 
  // Heat capacity of each volume element
  double c=cp*ro*(length/rows)*(width/cols)*thickness;
  // Thermal conductances between element centres
  double gfrcc=k*(width/cols)*thickness/(length/rows);
  double glrcc=k*(length/rows)*thickness/(width/cols);

  sum = glrcc*(neighbors[1] - cellstate)+
      glrcc*(neighbors[2] - cellstate)+
      gfrcc*(neighbors[0] - cellstate)+
      gfrcc*(neighbors[3] - cellstate);

    // just for testing
  if (inputs_rcv[1] == 0)
      inputs[1] = cellstate;
  if (inputs_rcv[0] == 0)
      inputs[0] = cellstate;
  
  Pto = gamma_to*((0.02*0.02)/(rows*cols))*(inputs[1]-cellstate); // AIR
  Pbo  = gamma_bo*((length*width)/(rows*cols))*(inputs[0]-cellstate); // CHIP
  if (inputs_rcv[2] > 0)
      Pgen = inputs[2];
  else if (inputs_rcv[3] > 0)
      Pgen = inputs[3];
  else
      Pgen = 0;
  
 
  derT = (sum+Pto+Pbo+Pgen)/c; 

  out = cellstate + derT;
  return out;

}

int PackHI(int space){
    State2D (*rule)(State2D,State2D*,int,int*,State2D*,int,int*) = &packHI;
  
    CS2D_Step(space,rule);
  return 1;
}


State2D packLO(State2D cellstate, State2D *neighbors, int n_neighbors,int *neighbors_present,State2D *inputs, int n_inputs, int *inputs_rcv){
  State2D sum,out;
  int i;
  // neighbors = [-1,0; 0,-1; 0,1; 1,0]
  double derT;
  
  double gamma_to = 500; // coefficient of heat transfer from top (chip)
  double gamma_bo = 800; // coefficient of heat transfer from bottom (board)
  double Pto,Pbo,Pgen; // top and bottom temperatures
      
  double cp=500; //"Average specific heat";
  double ro=800; //"Average density";
  int rows=10;
  int cols=10;
  double length=0.005; //"layer length (rows)";
  double width=0.005; //"layer width (cols)";
  double thickness=0.001; //"layer thickness";
  double k=50; //"Thermal conductivity";
  double T; // Temperature 
  // Heat capacity of each volume element
  double c=cp*ro*(length/rows)*(width/cols)*thickness;
  // Thermal conductances between element centres
  double gfrcc=k*(width/cols)*thickness/(length/rows);
  double glrcc=k*(length/rows)*thickness/(width/cols);

  sum = glrcc*(neighbors[1] - cellstate)+
      glrcc*(neighbors[2] - cellstate)+
      gfrcc*(neighbors[0] - cellstate)+
      gfrcc*(neighbors[3] - cellstate);

  // just for testing
  if (inputs_rcv[1] == 0)
      inputs[1] = cellstate;
  if (inputs_rcv[0] == 0)
      inputs[0] = cellstate;
  
  Pto = gamma_to*((length*width)/(rows*cols))*(inputs[1]-cellstate); // CHIP
  Pbo  = gamma_bo*((0.02*0.02)/(rows*cols))*(inputs[0]-cellstate); // BOARD
  if (inputs_rcv[2] > 0)
      Pgen = inputs[2];
  else if (inputs_rcv[3] > 0)
      Pgen = inputs[3];
  else
      Pgen = 0;
  
 
  derT = (sum+Pto+Pbo+Pgen)/c; 

  out = cellstate + derT;
  return out;

}

int PackLO(int space){
    State2D (*rule)(State2D,State2D*,int,int*,State2D*,int,int*) = &packLO;
  
    CS2D_Step(space,rule);
  return 1;
}
*/


void* board(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors,void** inputs, int n_inputs, int *inputs_rcv){
    CHIPState *out;
    CHIPState *cs;
    CHIPState **ne;
    CHIPState **in;
    
    double derT;
    double M=10;
    double cp=500;
    double Tstart=25;
    double gamma_to = 800; // coefficient of heat transfer from top (packLO)
    double gamma_bo = 4; // coefficient of heat transfer from bottom (air)
    double Pto,Pbo; // top and bottom temperatures
    int rows = 10;
    int cols = 10;
    double RATE = 0.0001;
    
    cs = (CHIPState *)cellstate;
    ne = (CHIPState **)neighbor_states;
    in = (CHIPState **)inputs;
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    Pto = gamma_to*(0.02*0.02)/(rows*cols)*(in[0]->t-cs->t);
    Pbo = gamma_bo*(2*0.02*0.02)*(in[1]->t-cs->t);
    
    
    derT = (M*cp)/(Pto+Pbo); 
    
    out->t = cs->t +RATE*derT;
    
    if (out->t == cs->t)
	return NULL;
    else
        return (void*)out;
}

int BOARDStep(void* space){
    void* (*rule)(void*,int,int,int,void**,int,void**,int,int*) = &board;
        
    CS_Step(space,rule);
    return 1;
}

void *air(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    //void* air(void* cellstate, void* *neighbors, int n_neighbors,int *neighbors_present,void* *inputs, int n_inputs, int *inputs_rcv){
    CHIPState *out;
    CHIPState *cs;
    
    cs = (CHIPState *)cellstate;  
    out = (CHIPState *)malloc(sizeof(CHIPState));
    
    out->t = 20;  // Air temperature
    
    if (out->t == cs->t)
	return NULL;
    else
	return (void*) out;
}


int AIRStep(void* space){
    void* (*rule)(void*,int,int,int,void**,int,void**,int,int*) = &air;
    
    CS_Step(space,rule);
    return 1;
}


#endif
