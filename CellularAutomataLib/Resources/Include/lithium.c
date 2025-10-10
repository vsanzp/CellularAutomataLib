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

#ifndef LITHIUM
#define LITHIUM

#define LIQUID 0
#define INTER 1
#define SOLID 2
#define PI 3.14159
#define U 1e-6

#include <CellularAutomataLib.c>
#include <CellularAutomataLib-animation.c>


/************************************
 DSCA CA State
***********************************/
typedef struct DSCAState{
    double x,y; // cell center coordinates
    double cellsize; // cell size
    double sqx, sqy; // coordinates of the square center
    double theta; // deflection angle
    double l; // length of the half diagonal of the square
    double fs; // solid phase ratio
    double maxlcrit; // critical square size to capture all neighbors
    int cap[8]; // captured neighbors
    double lnew[8]; // l for new squares in captured neighbors
    double sqxnew[8]; // x center for new squares
    double sqynew[8]; // y center for new squares
    double dcenter[8]; // distance to neighbors centers
    double lcrit[8]; // max l to capture neighbors
    double theta0[8]; // minimum growth angle to neighbor center
    double theta2[8]; // angle between growth direction and neighbor center
    int phase; // 0 liquid, 1 interface, 2 solid
    double c;
    double eta;
    double sr; // solidification ratio
}DSCAState;


void * DSCADefaultState(){
    DSCAState *s;
    s = (DSCAState*)malloc(sizeof(DSCAState));
    s->phase = LIQUID; // liquid by default
    s->x = 0;
    s->y = 0;
    s->cellsize = 5e-6; // m cell size;
    s->sqx = 0;
    s->sqy = 0; // coordinates of the square center
    s->theta = 0; // deflection angle
    s->l = 0; // length of the half diagonal of the square
    s->fs = 0; // solid phase ratio
    s->maxlcrit = 0; // critical square size to capture all neighbors
    for (int i =0;i<8;i++){
	s->cap[i] = 0; // no captured neighbors
	s->lnew[i] = 0;
	s->sqxnew[i] = 0;
	s->sqynew[i] = 0;
	s->dcenter[i] = 0;
	s->lcrit[i] = 0;
	s->theta0[i] = 0;
	s->theta2[i] = 0;
    }
    s->c = 0;
    s->eta = 0;
    s->sr = 0;
    return (void*)s;
}

int DSCADefault(void* space){
    CS_InitDefault(space,&DSCADefaultState);
    return 1;
}

void computeInitial(DSCAState *s, DSCAState *ne, int ne_i){
    int k;
    double l,lcrit,dist,mindist,cx,cy,mincx,mincy;
    double theta,theta1;
    if (ne != NULL){
	//ModelicaFormatMessage("-- NE[%d]: cell[%.12lf,%.12lf], ne[%.12lf,%.12lf]\n",ne_i,s->x,s->y,ne->x,ne->y);
	s->dcenter[ne_i] = sqrt(pow(ne->x - s->sqx,2.0) + pow(ne->y - s->sqy,2.0)); // distance to neighbor center from square center
	//ModelicaFormatMessage("dcenter = %.12lf\n",s->dcenter[ne_i]);
	mindist = -1;
	// calculate closest growth direction to neighbor center
	for(k=0;k<4;k++){
	    //	    cx = s->sqx + s->dcenter[ne_i]*cos(s->theta+(PI/2*k)); // use dcenter as l
	    cx = s->sqx + cos(s->theta+(PI/2*k)); 
	    //cy = s->sqy + s->dcenter[ne_i]*sin(s->theta+(PI/2*k)); // use dcenter as l
	    cy = s->sqy + sin(s->theta+(PI/2*k)); 
	    dist = sqrt(pow(cx - ne->x,2.0) + pow(cy - ne->y,2.0));
	    if (dist < mindist || mindist < 0){
		mincx = cx;
		mincy = cy;
		mindist = dist;
	    }
	}
	theta = atan2((mincy - s->sqy) , (mincx - s->sqx));
	s->theta0[ne_i] = theta;
	//ModelicaFormatMessage("theta = atan[%.12lf], [%.12lf] = %.12lf\n",mincy - s->sqy, mincx - s->sqx,theta);
	theta1 = atan2((ne->y - s->sqy) , (ne->x - s->sqx)); // angle of connection between square center and neighbor center
	//ModelicaFormatMessage("theta2 = atan[%.12lf], [%.12lf] = %.12lf\n",ne->y - s->sqy, ne->x - s->sqx,theta1);
	// angle between neighbor center and growth direction
	if ((theta < 0 && theta1 > 0) || (theta > 0 && theta1 < 0))
	    s->theta2[ne_i] =  fabs(theta + theta1); 
	else
	    s->theta2[ne_i] =  fabs(theta - theta1); 
	s->lcrit[ne_i] = (s->dcenter[ne_i] * sin(3*PI/4 - s->theta2[ne_i])) / sin(PI/4);
	s->maxlcrit = fmax(s->maxlcrit,s->lcrit[ne_i]);
	//ModelicaFormatMessage("theta = %.9lf, theta1 = %.9lf, theta2 = %.9lf, lcrit = %.9lf, maxlcrit = %.9lf\n", theta,theta1,s->theta2[ne_i],s->lcrit[ne_i], s->maxlcrit);
    }   
    return;
}

void DSCAInitialINTER(void*cellstate){
    DSCAState *s;
    double u;
    s = (DSCAState*)cellstate;
    s->phase = INTER; // interface
    s->sqx = s->x;
    s->sqy = s->y;
    s->l = 0;
    s->fs = 0;
}

void DSCAInitial0(void* space,int modx, int mody, int modz){
    int i,j,k,n;
    DSCAState *s;
    DSCAState *ne;
    int ni[8] = {1,1,0,-1,-1,-1,0,1};
    int nj[8] = {0,1,1,1,0,-1,-1,-1};
    srand(time(NULL));
    for(i=1;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    for(k=1;k<=modz;k++){
		s = (DSCAState*)CS_GetState(space,i,j,k);
		s->x = (i-1)*s->cellsize + s->cellsize/2;
		s->y = (j-1)*s->cellsize + s->cellsize/2;
		s->theta = 0;
	    }
	}
    }
    CS_Init(space,modx/2,mody/2,1, &DSCAInitialINTER);
    s = (DSCAState*)CS_GetState(space,modx/2,mody/2,1);
    for(n=0;n<8;n++){
	ne = (DSCAState*)CS_GetState(space,(modx/2)+ni[n],(mody/2)+nj[n],1);
	computeInitial(s,ne,n);
    }
    
    return;
}

void DSCAInitial15(void* space,int modx, int mody, int modz){
    int i,j,k,n;
    DSCAState *s;
    DSCAState *ne;
    int ni[8] = {1,1,0,-1,-1,-1,0,1};
    int nj[8] = {0,1,1,1,0,-1,-1,-1};
    srand(time(NULL));
    for(i=1;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    for(k=1;k<=modz;k++){
		s = (DSCAState*)CS_GetState(space,i,j,k);
		s->x = (i-1)*s->cellsize + s->cellsize/2;
		s->y = (j-1)*s->cellsize + s->cellsize/2;
		s->theta = PI/12;
	    }
	}
    }
    CS_Init(space,modx/2,mody/2,1, &DSCAInitialINTER);
    s = (DSCAState*)CS_GetState(space,modx/2,mody/2,1);
    for(n=0;n<8;n++){
	ne = (DSCAState*)CS_GetState(space,(modx/2)+ni[n],(mody/2)+nj[n],1);
	computeInitial(s,ne,n);
    }
    
    return;
}

void DSCAInitial30(void* space,int modx, int mody, int modz){
    int i,j,k,n;
    DSCAState *s;
    DSCAState *ne;
    int ni[8] = {1,1,0,-1,-1,-1,0,1};
    int nj[8] = {0,1,1,1,0,-1,-1,-1};
    srand(time(NULL));
    for(i=1;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    for(k=1;k<=modz;k++){
		s = (DSCAState*)CS_GetState(space,i,j,k);
		s->x = (i-1)*s->cellsize + s->cellsize/2;
		s->y = (j-1)*s->cellsize + s->cellsize/2;
		s->theta = PI/6;
	    }
	}
    }
    CS_Init(space,modx/2,mody/2,1, &DSCAInitialINTER);
    s = (DSCAState*)CS_GetState(space,modx/2,mody/2,1);
    for(n=0;n<8;n++){
	ne = (DSCAState*)CS_GetState(space,(modx/2)+ni[n],(mody/2)+nj[n],1);
	computeInitial(s,ne,n);
    }
    
    return;
}

void DSCAInitial45(void* space,int modx, int mody, int modz){
    int i,j,k,n;
    DSCAState *s;
    DSCAState *ne;
    int ni[8] = {1,1,0,-1,-1,-1,0,1};
    int nj[8] = {0,1,1,1,0,-1,-1,-1};
    srand(time(NULL));
    for(i=1;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    for(k=1;k<=modz;k++){
		s = (DSCAState*)CS_GetState(space,i,j,k);
		s->x = (i-1)*s->cellsize + s->cellsize/2;
		s->y = (j-1)*s->cellsize + s->cellsize/2;
		s->theta = PI/4;
	    }
	}
    }
    CS_Init(space,modx/2,mody/2,1, &DSCAInitialINTER);
    s = (DSCAState*)CS_GetState(space,modx/2,mody/2,1);
    for(n=0;n<8;n++){
	ne = (DSCAState*)CS_GetState(space,(modx/2)+ni[n],(mody/2)+nj[n],1);
	computeInitial(s,ne,n);
    }
    
    return;
}

void DSCAInitialBorder(void* space,int modx, int mody, int modz){
    int i,j,k,n;
    DSCAState *s;
    DSCAState *ne;
    int ni[8] = {1,1,0,-1,-1,-1,0,1};
    int nj[8] = {0,1,1,1,0,-1,-1,-1};
    srand(time(NULL));
    for(i=1;i<=modx;i++){
	for(j=1;j<=mody;j++){
	    for(k=1;k<=modz;k++){
		s = (DSCAState*)CS_GetState(space,i,j,k);
		s->x = (i-1)*s->cellsize + s->cellsize/2;
		s->y = (j-1)*s->cellsize + s->cellsize/2;
		s->theta = 0;
	    }
	}
    }
    CS_Init(space,modx/4,mody/2,1, &DSCAInitialINTER);
    s = (DSCAState*)CS_GetState(space,modx/4,mody/2,1);
    for(n=0;n<8;n++){
	ne = (DSCAState*)CS_GetState(space,(modx/4)+ni[n],(mody/2)+nj[n],1);
	computeInitial(s,ne,n);
    }
    
    return;
}

//******************************************************************************
// DISPLAY
// double COLOR display (void* space, int x,int y, int z, double* SCALARVALUE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
double DSCADisplayPHASE(void *space, int x, int y, int z, double* scalar, double* vx, double *vy, double*vz){
    DSCAState *cs;
    cs = (DSCAState*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(BLANK); // transparent	
    }else{
	if (cs->phase == SOLID)
	    return (double)ColorToInt(BLUE); // solid cell as blue
	else if (cs->phase == INTER){
	    return (double)ColorToInt(YELLOW); // interface cell as white
	    //return (double)ColorToInt(Fade(BLUE,cs->u*20));
	}else
	    return (double)ColorToInt(BLACK); // liquid cell as black
    }
}

void DSCASetDisplayPHASE(void *animation,void * space){
    CS_SetDisplay(animation,space, &DSCADisplayPHASE);   
    return;
}

double DSCADisplayFS(void *space, int x, int y, int z, double* scalar, double* vx, double *vy, double*vz){
    DSCAState *cs;
    cs = (DSCAState*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(BLANK); // transparent	
    }else{
	if (cs->phase == SOLID)
	    return (double)ColorToInt(BLUE); // solid cell as blue
	else if (cs->phase == INTER){
	    //return (double)ColorToInt(YELLOW); // interface cell as white
	    return (double)ColorToInt(Fade(YELLOW,cs->fs));
	}else
	    return (double)ColorToInt(BLACK); // liquid cell as black
    }
}

void DSCASetDisplayFS(void *animation,void * space){
    CS_SetDisplay(animation,space, &DSCADisplayFS);   
    return;
}

double DSCADisplaySR(void *space, int x, int y, int z, double* scalar, double* vx, double *vy, double*vz){
    DSCAState *cs;
    cs = (DSCAState*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(BLUE); // transparent	
    }else{
	if (cs->phase == SOLID || cs->phase == INTER)
	    return (double)ColorToInt(Fade(RED,cs->sr));
	else
	    return (double)ColorToInt(BLUE);
    }
}

void DSCASetDisplaySR(void *animation,void * space){
    CS_SetDisplay(animation,space, &DSCADisplaySR);   
    return;
}

double DSCADisplayC(void *space, int x, int y, int z, double* scalar, double* vx, double *vy, double*vz){
    DSCAState *cs;
    cs = (DSCAState*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(BLANK); // transparent	
    }else{
	return (double)ColorToInt(Fade(BLUE,cs->c)); // 
    }
}

void DSCASetDisplayC(void *animation,void * space){
    CS_SetDisplay(animation,space, &DSCADisplayC);   
    return;
}



//***********************************************************************************
// TRANSITION FUNCTION
void *DSCAtransition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    DSCAState *out;
    DSCAState *aux;
    DSCAState *cs;
    DSCAState **ne;
    double **in;

    double l1,l2,h; 
    double dside; // distance to sq side
    double ibv;
    double r;
    double sumfs;
    double u; // growth rate
    double i0 = 30*1e-3*1e4; // A/m2 - mA/cm2
    double gamma = 0.6; // J/m2
    double c0 = 1e3; // mol/m3
    double R =  8.3143; // J/mol K ideal gas constant 
    double T = 358.15; // K Abs. Temperature (85ºC)
    double F = 96487; // C/mol Faraday constant
    double V =  1.2998 * 1e-5; // m3/mol
    double alpha = 1/2; // transfer coeff.
    double mw = 6.941*1e-3; // kg/mol - g/mol lithium molar mass
    double rho = 0.534*1e-3*1e6; // kg/m3 - g/cm3 density of lithium
    //**
    double D = 5e-12;
    double t0 = 0.3;
    //**
	int i,sumcap;
	//double lcrit;
    //double theta;
    
    cs = (DSCAState *)cellstate; // cell state
    ne = (DSCAState **)neighbor_states; // neigbors cell state
    in = (double **)inputs;
    out = (DSCAState *)malloc(sizeof(DSCAState));
    aux = (DSCAState *)malloc(sizeof(DSCAState));
    
    out->phase = cs->phase;
    out->x = cs->x;
    out->y = cs->y;
    out->cellsize = cs->cellsize;
    out->sqx = cs->sqx;
    out->sqy = cs->sqy;
    out->theta = cs->theta;
    out->l = cs->l;
    out->fs = cs->fs;
    out->maxlcrit = cs->maxlcrit; 
    for(i=0;i<n_neighbors;i++){
	out->cap[i] = cs->cap[i]; 
	out->lnew[i] = cs->lnew[i]; 
	out->sqxnew[i] = cs->sqxnew[i];
	out->sqynew[i] = cs->sqynew[i];
	out->dcenter[i] = cs->dcenter[i];
	out->theta0[i] = cs->theta0[i];
	out->theta2[i] = cs->theta2[i];
	out->lcrit[i] = cs->lcrit[i]; 
    }
    if (n_inputs > 0){
	if (inputs_rcv[0] == 1)
	    out->c = *in[0]; // local concentration (input 1)
	if  (inputs_rcv[1] == 1)
	    //    c = in[0];
	    out->eta = *in[1]; // potential (input 2)
    }else{
	// set inputs
	out->c = 1; // local concentration (input 1)
	//    c = in[0];
	out->eta = -0.2; // potential (input 2)
	//eta = in[1];
    }
    int j;
    //double cx, cy, mincx, mincy, dist, mindist;
    if (out->phase == INTER) { // only interface cells are evaluated to capture neighbors
	//ModelicaFormatMessage("cell[%d,%d]: phase = %d, l = %.8lf, fs = %lf, maxlcrit= %.8lf\n",x,y,out->phase,out->l,out->fs,out->maxlcrit);
	sumcap = 0;
	for(i=0;i<n_neighbors;i++){ // evaluate each neighbor
	    if (ne[i] != NULL && out->cap[i] == 0 && ne[i]->phase == LIQUID){ // only not already captured liquid neighbors
		
		dside = (out->l*sin(PI/4)) / (sin(3*PI/4 - out->theta2[i]));  // sine theorem, growth length in the direction of neighbor center

		h = sqrt(out->l*out->l*2);
		l1 = (out->l * sin(out->theta2[i])) / (sin(3*PI/4 - out->theta2[i])); // sine theorem
		l2 = h - l1;
		dside = sqrt((l1*l1 + l2*l2)/2); // stewart theorem

		//ModelicaFormatMessage("cell[%d,%d]: ne[%d]: theta = %.12lf, theta2 %.12lf\n",x,y,i,out->theta, out->theta2[i]);
		//ModelicaFormatMessage("cell[%d,%d]: ne[%d]: dcenter = %.12lf, dside = %.12lf, l = %.12lf, lcrit[%d] = %.12lf\n",x,y, i,out->dcenter[i], dside, out->l,i,out->lcrit[i]);

		// neighbor captured? compute l and new square center
		if (dside >= out->dcenter[i]){ 
		    out->cap[i] = 1; 
		    out->lnew[i] = (fmin(l1,sqrt(2)*out->cellsize)+fmin(l2,sqrt(2)*out->cellsize)) / sqrt(2);
		    out->lnew[i] = sqrt(out->lnew[i]*out->lnew[i]/2);
		    //out->lnew[i] = U; // REMOVE!!
		    out->sqxnew[i] = out->sqx + ((out->l - out->lnew[i]) * cos(out->theta0[i]));
		    out->sqynew[i] = out->sqy + ((out->l - out->lnew[i]) * sin(out->theta0[i]));
		    //ModelicaFormatMessage("NE[%d] captured (cell [%d,%d]): l1 = %.8lf, l2 = %.8lf, lnew = %.8lf, sqxnew = %lf, sqynew = %lf\n",i,x, y,l1,l2,out->lnew[i],out->sqxnew[i],out->sqynew[i]);
		}
	    }else if (ne[i] != NULL && ne[i]->phase != LIQUID){
		//out->cap[i] = 1;
	    }
	    sumcap += out->cap[i];
	}
	out->fs = fmin(1.0,out->l / out->maxlcrit);
	out->sr = (out->fs * sumcap) / n_neighbors;
	
	if (out->fs >= 1){ // SOLID if FS reaches 1
	    //out->fs = 1.0;
	    //if (sum == n_neighbors){ // SOLID if all neighbors captured
	    out->phase = SOLID;
	    //ModelicaFormatMessage("************** SOLID   cell[%d,%d] phase = %d, FS = %lf\n",x,y,out->phase, out->fs);
	    //ModelicaFormatMessage(" SOLID --------------------------------------------------------------------------------\n");
	    return (void *)out;
	}
	// calculate square growth rate if still INTER
	if (out->phase == INTER){ // interface cell
	    sumfs = 0;
	    for(i=0;i<n_neighbors;i++){
		if(ne[i] != NULL)
		    sumfs += ne[i]->fs;
	    }
	    r = 1 / ((1/out->cellsize) * (1 - (2/(n_neighbors+1))*(out->fs + sumfs)));
	    ibv = i0 * exp((2*gamma*V)/(r*R*T)) * (exp((alpha*F*out->eta)/(R*T)) - (out->c/c0)*exp(((1-alpha)*F*out->eta)/(R*T)));
	    u =  (mw/rho) * (ibv/F);
	    //u = U; // REMOVE!!!
	    out->l += u; // square growth
	    //ModelicaFormatMessage("cell[%d,%d]: v = %.9lf, r = %.9lf, ibv = %.9lf, u = %.9lf, l = %.9lf\n",v, x,y,r,ibv,u,out->l);
	    out->fs = fmin(1.0,out->l / out->maxlcrit);
	    out->sr = (out->fs * sumcap) / n_neighbors;
	}
    }else if(out->phase == LIQUID){ // LIQUID cell may become INTER
	for(i = 0; i<n_neighbors;i++){ // check neighbors
	    if (ne[i] != NULL){
		if (ne[i]->cap[(i+4)%8] == 1){ // neighbor captured this cell
		    //out->cap[i] = 1;
		    out->phase = INTER;
		    out->sqx = ne[i]->sqxnew[(i+4)%8];
		    out->sqy = ne[i]->sqynew[(i+4)%8];
		    out->l = ne[i]->lnew[(i+4)%8];
		    out->fs = 0;
		    for (j = 0 ; j<n_neighbors;j++)
			computeInitial(out,ne[j],j);
		    break;
		}
	    }
	}
    }
    //ModelicaFormatMessage("**************  cell[%d,%d] phase = %d, FS = %lf\n",x,y,out->phase, out->fs);
    //ModelicaFormatMessage("--------------------------------------------------------------------------------\n");
    
     if (out->phase != INTER)
    	return NULL; // only inter cells (and their neighbors) are evaluated
    else
	return (void *)out;
}

int DSCAStep(void* space){
    return CS_Step(space,&DSCAtransition);
}

//********************************************************
// INTERFACE FUNCTIONS

// function to convert the state of a cell into a double value
double OutputFS(void* space, int x, int y, int z){
    double out;
    DSCAState* s;
    int i;
    
    s = (DSCAState *)CS_GetState(space,x,y,z);
    
    return s->fs;
}

void EInput(void* space, int x, int y, int z,double value,int input_id){
    DSCAState* s;
    double* input;
    
    input = (double*)malloc(sizeof(double));
    *input = value;
    
    CS_SetInput(space,x,y,z,(void*)input,input_id);
    return;
}


#endif
