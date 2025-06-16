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

#ifndef LBM
#define LBM

#include <CellularAutomataLib.c>
#include <CellularAutomataLib-animation.c>


/************************************
 C2Q9 LBM 
***********************************/
typedef struct D2Q9State{
    int x,y; // cell coordinates
    int solid; // 0 void, 1 solid
    double f[9]; // distribution function
    double rho; // density
    double ux,uy; // directional velocities
    double u; // norm vel
}D2Q9State;


void * D2Q9DefaultState(){
    D2Q9State *s;
    int i;
    s = (D2Q9State*)malloc(sizeof(D2Q9State));
    s->solid = 0;
    for(i=0;i<9;i++)
	s->f[i] = 0;
    s->rho = 0;
    s->ux = 0;
    s->uy = 0;
    return (void*)s;
}

int D2Q9Default(void* space){
    CS_InitDefault(space,&D2Q9DefaultState);
    return 1;
}

void D2Q9InitialEq1(void*cellstate){
    D2Q9State *s;
    s = (D2Q9State*)cellstate;
    int i;
    double irho = 1.0; // initial rho
    double iux = 0.0;  // initial ux
    double iuy = 0.0;  // initial uy
    int cx[9] = {0,1,0,-1,0,1,-1,-1,1}; // lattice velocities in x
    int cy[9] = {0,0,1,0,-1,1,1,-1,-1}; // lattice velocities in y

    
    if (!s->solid){
	// compute equilibrium distributions (WolfGladrow pag 200)
	double c_u[9];
	for(i=0;i<9;i++)
	    c_u[i] = cx[i]*iux + cy[i]*iuy;
	double u_2 = iux*iux + iuy*iuy;
	double w[9] = {4.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/36.0,1.0/36.0,1.0/36.0,1.0/36.0};
	for(i=0;i<9;i++)
	    s->f[i] = w[i] * irho * (1.0 + 3.0*c_u[i] + 4.5*c_u[i]*c_u[i] - 1.5*u_2);
	// update macroscopic quantities (density and velocity)
	s->rho = s->f[0] + s->f[1] + s->f[2] + s->f[3] + s->f[4] + s->f[5] + s->f[6] + s->f[7] + s->f[8];
	s->ux = ((s->f[1] + s->f[5] + s->f[8]) - (s->f[3] + s->f[6] + s->f[7])) / (s->rho);
	s->uy = ((s->f[2] + s->f[5] + s->f[6]) - (s->f[4] + s->f[7] + s->f[8])) / (s->rho); 	
    }
}

void D2Q9InitialEq2(void*cellstate){
    D2Q9State *s;
    s = (D2Q9State*)cellstate;
    int i;
    double irho = 1.0; // initial rho
    double iux = 0.5;  // initial ux
    double iuy = 0.5;  // initial uy
    double cx[9] = {0.0,1.0,0.0,-1.0,0.0,1.0,-1.0,-1.0,1.0}; // lattice velocities in x
    double cy[9] = {0.0,0.0,1.0,0.0,-1.0,1.0,1.0,-1.0,-1.0}; // lattice velocities in y
    
    if (!s->solid){
	// compute equilibrium distributions (WolfGladrow pag 200)
	double c_u[9];
	for(i=0;i<9;i++)
	    c_u[i] = 0.5;//cx[i]*iux + cy[i]*iuy;
	double u_2 = iux*iux + iuy*iuy;
	double w[9] = {4.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/36.0,1.0/36.0,1.0/36.0,1.0/36.0};
	for(i=0;i<9;i++)
	    s->f[i] = w[i] * irho * (1.0 + 3.0*c_u[i] + 4.5*c_u[i]*c_u[i] - 1.5*u_2);
	// update macroscopic quantities (density and velocity)
	s->rho = s->f[0] + s->f[1] + s->f[2] + s->f[3] + s->f[4] + s->f[5] + s->f[6] + s->f[7] + s->f[8];
	s->ux = ((s->f[1] + s->f[5] + s->f[8]) - (s->f[3] + s->f[6] + s->f[7])) / (s->rho);
	s->uy = ((s->f[2] + s->f[5] + s->f[6]) - (s->f[4] + s->f[7] + s->f[8])) / (s->rho); 	
    }
}

void D2Q9InitialSimpleWave(void* space,int modx, int mody, int modz){
    int i,j,k;
    srand(time(NULL));
    for(i=1;i<=modx;i++)
	for(j=1;j<=mody;j++)
	    for(k=1;k<=modz;k++)
		CS_Init(space, i, j, k, &D2Q9InitialEq1);
    CS_Init(space, (modx/2)+1, (mody/2)+1, 1, &D2Q9InitialEq2);
    return;
}


double computePoiseuille(int iY) {
    double y = (double)(iY-1);
    double L = (double)(50-1); // ly = 50
    double uMax = 0.05;
    
    return 4.*uMax / (L*L) * (L*y-y*y);
}

/*int computeEquilibrium(void *cellstate){
    D2Q9State *s;
    s = (D2Q9State*)cellstate;
    int i;
    double irho = 1.0; // initial rho
    double iux = computePoiseuille(s->y);  // initial ux
    double iuy = 0.0;  // initial uy
    double cx[9] = {0,1.0,0,-1.0,0,1.0,-1.0,-1.0,1.0}; // lattice velocities in x
    double cy[9] = {0,0,1.0,0,-1.0,1.0,1.0,-1.0,-1.0}; // lattice velocities in y
    
    double c_u[9];
    for(i=0;i<9;i++)
	c_u[i] = cx[i]*iux + cy[i]*iuy;
    double u_2 = iux*iux + iuy*iuy;
    double w[9] = {4.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/36.0,1.0/36.0,1.0/36.0,1.0/36.0};
    for(i=0;i<9;i++)
	s->f[i] = w[i] * irho * (1.0 + 3.0*c_u[i] + 4.5*c_u[i]*c_u[i] - 1.5*u_2);
    // update macroscopic quantities (density and velocity)
    s->rho = s->f[0] + s->f[1] + s->f[2] + s->f[3] + s->f[4] + s->f[5] + s->f[6] + s->f[7] + s->f[8];
    s->ux = ((s->f[1] + s->f[5] + s->f[8]) - (s->f[3] + s->f[6] + s->f[7])) / (s->rho);
    s->uy = ((s->f[2] + s->f[5] + s->f[6]) - (s->f[4] + s->f[7] + s->f[8])) / (s->rho);
    s->u = sqrt((s->ux*s->ux)+(s->uy*s->uy));
    return 0;
    }*/


void D2Q9InitialPoiseuille(void*cellstate){
    D2Q9State *s;
    s = (D2Q9State*)cellstate;
     int i;
    double irho = 1.0; // initial rho
    double iux = computePoiseuille(s->y);  // initial ux
    double iuy = 0.0;  // initial uy
    double cx[9] = {0,1.0,0,-1.0,0,1.0,-1.0,-1.0,1.0}; // lattice velocities in x
    double cy[9] = {0,0,1.0,0,-1.0,1.0,1.0,-1.0,-1.0}; // lattice velocities in y
    
    if (!s->solid){
	// compute equilibrium distributions (WolfGladrow pag 200)
	double c_u[9];
	for(i=0;i<9;i++)
	    c_u[i] = cx[i]*iux + cy[i]*iuy;
	double u_2 = iux*iux + iuy*iuy;
	double w[9] = {4.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/36.0,1.0/36.0,1.0/36.0,1.0/36.0};
	for(i=0;i<9;i++)
	    s->f[i] = w[i] * irho * (1.0 + 3.0*c_u[i] + 4.5*c_u[i]*c_u[i] - 1.5*u_2);
	// update macroscopic quantities (density and velocity)
	s->rho = s->f[0] + s->f[1] + s->f[2] + s->f[3] + s->f[4] + s->f[5] + s->f[6] + s->f[7] + s->f[8];
	s->ux = ((s->f[1] + s->f[5] + s->f[8]) - (s->f[3] + s->f[6] + s->f[7])) / (s->rho);
	s->uy = ((s->f[2] + s->f[5] + s->f[6]) - (s->f[4] + s->f[7] + s->f[8])) / (s->rho);
	s->u = sqrt((s->ux*s->ux)+(s->uy*s->uy));
    }
}

void D2Q9Solid(void* cellstate){
    D2Q9State *s;
    int i;
    s = (D2Q9State*)cellstate;
    s->solid = 1;
    /*    for(i=0;i<9;i++)
	s->f[i] = 0.0;
    s->rho = 0.0;
    s->ux = 0.0;
    s->uy = 0.0;*/
    return;
}


void D2Q9InitialUnsteady(void* space,int modx, int mody, int modz){
    int i,j,k;
    int obsx = modx/5;
    int obsy = mody/2;
    int obsr = mody/10+1;
    D2Q9State *s;
    srand(time(NULL));
    for(i=1;i<=modx;i++)
	for(j=1;j<=mody;j++)
	    for(k=1;k<=modz;k++){
		s = (D2Q9State*)CS_GetState(space,i,j,k);
		s->x = i-1; // set cell coordinates
		s->y = j-1;
		CS_Init(space,i,j,k,&D2Q9InitialPoiseuille);
		if (j == 1 || j == mody)
		    CS_Init(space, i, j, k, &D2Q9Solid);
		else if ((i-obsx)*(i-obsx) + (j-obsy)*(j-obsy) <= obsr*obsr) // set obstacle
		    CS_Init(space, i, j, k, &D2Q9Solid);
	    }
    return;
}





//******************************************************************************
// DISPLAY
// double COLOR display (void* space, int x,int y, int z, double* SCALARVALUE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
double D2Q9Display(void *space, int x, int y, int z, double* scalar, double* vx, double *vy, double*vz){
    D2Q9State *cs;
    cs = (D2Q9State*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates (starting at 1)
    // set out to the desired value calculated from the state variables
    if (cs == NULL){
	return  (double)ColorToInt(BLANK); // transparent	
    }else{
	if (cs->solid){
	    return (double)ColorToInt(BLACK); // solid as black
	}else{
	    if (cs->rho == 0)
		return (double)ColorToInt(WHITE); // empty cell as white
	    else{
		*scalar = (double)cs->rho;
		*vx = cs->ux;
		*vy = cs->uy;
		*vz = 0;
		//ModelicaFormatMessage("u[%d,%d] = %lf\n",x,y,cs->u);
		return (double)ColorToInt(Fade(BLUE,cs->u*20));
	    }
	}
    }
}

void D2Q9SetDisplay(void *animation,void * space){
    CS_SetDisplay(animation,space, &D2Q9Display);   
    return;
}



//***********************************************************************************
// TRANSITION FUNCTION
void *D2Q9transition(void* cellstate, int x, int y, int z, void** neighbor_states, int n_neighbors, void** inputs, int n_inputs, int *inputs_rcv){
    D2Q9State *out;
    D2Q9State *aux;
    D2Q9State *cs;
    D2Q9State **ne;
    double **in;
    int i;
    int nsum;
    double obsr = 6; // obstacle radius
    double Re = 100;        // Reynolds number
    double uMax = 0.02;
    double nu = uMax * 2.*obsr / Re;  // kinematic fluid viscosity
    double omega = 1. / (3*nu+1./2.);      // relaxation parameter
    //double omega = 0.5; // collision frecuency
    double feq[9]; // equilibrium distrib
    double cx[9] = {0.0,1.0,0.0,-1.0,0.0,1.0,-1.0,-1.0,1.0}; // lattice velocities in x
    double cy[9] = {0.0,0.0,1.0,0.0,-1.0,1.0,1.0,-1.0,-1.0}; // lattice velocities in y

    cs = (D2Q9State *)cellstate; // cell state
    ne = (D2Q9State **)neighbor_states; // neigbors cell state
    in = (double **)inputs;
    out = (D2Q9State *)malloc(sizeof(D2Q9State));
    aux = (D2Q9State *)malloc(sizeof(D2Q9State));
    
    out->solid = cs->solid;
    
    // Lattice velocities and neighbors (n_neighbors == 8)
    //
    //  2 |     3    | 4
    // ------------------
    //    | 6   2   5|
    //    |   \ | /  |
    //  1 | 3 - 0 - 1| 5
    //    |   / | \  |
    //    | 7   4   8|    
    // -----------------
    //  0 |     7    | 6
    
    if (out->solid){
	// bounce-back particles
	out->f[0] = 0.0;//cs->f[0];
	out->f[1] = (ne[5] != NULL && !ne[5]->solid) ? ne[5]->f[3] : 0.0;//cs->f[1];
	out->f[2] = (ne[3] != NULL && !ne[3]->solid) ? ne[3]->f[4] : 0.0;//cs->f[2];
	out->f[3] = (ne[1] != NULL && !ne[1]->solid) ? ne[1]->f[1] : 0.0;//cs->f[3];
	out->f[4] = (ne[7] != NULL && !ne[7]->solid) ? ne[7]->f[2] : 0.0;//cs->f[4];
	out->f[5] = (ne[4] != NULL && !ne[4]->solid) ? ne[4]->f[7] : 0.0;//cs->f[5];
	out->f[6] = (ne[2] != NULL && !ne[2]->solid) ? ne[2]->f[8] : 0.0;//cs->f[6];
	out->f[7] = (ne[0] != NULL && !ne[0]->solid) ? ne[0]->f[5] : 0.0;//cs->f[7];
	out->f[8] = (ne[6] != NULL && !ne[6]->solid) ? ne[6]->f[6] : 0.0;//cs->f[8];
	
    }else{
	// INPUTS
	//for(i=0;i<n_inputs;i++)
	//    if(inputs_rcv[i]){
	//	//rcv[i] = 1;
	//	out->f[(int)*in[i]] = 1;
	//    }

	// stream from neighbors
	out->f[0] = cs->f[0];
	out->f[1] = (ne[1] != NULL) ? ne[1]->f[1] : 0.0;//cs->f[1];
	out->f[2] = (ne[7] != NULL) ? ne[7]->f[2] : 0.0;//cs->f[2];
	out->f[3] = (ne[5] != NULL) ? ne[5]->f[3] : 0.0;//cs->f[3];
	out->f[4] = (ne[3] != NULL) ? ne[3]->f[4] : 0.0;//cs->f[4];
	out->f[5] = (ne[0] != NULL) ? ne[0]->f[5] : 0.0;//cs->f[5];
	out->f[6] = (ne[6] != NULL) ? ne[6]->f[6] : 0.0;//cs->f[6];
	out->f[7] = (ne[4] != NULL) ? ne[4]->f[7] : 0.0;//cs->f[7];
	out->f[8] = (ne[2] != NULL) ? ne[2]->f[8] : 0.0;//cs->f[8];	

	/*	if (x == 0){
	    out->f[1] += 0.01;
	    out->f[3] -= 0.01;
	}else if (x == 249){
	    out->f[1] -= 0.01;
	    out->f[3] += 0.01;
	    }*/
	
	// update local density and velocities
	out->rho = out->f[0] + out->f[1] + out->f[2] + out->f[3] + out->f[4] + out->f[5] + out->f[6] + out->f[7] + out->f[8];
	out->ux = ((out->f[1] + out->f[5] + out->f[8]) - (out->f[3] + out->f[6] + out->f[7])) / (out->rho);
	out->uy = ((out->f[2] + out->f[5] + out->f[6]) - (out->f[4] + out->f[7] + out->f[8])) / (out->rho); 
	out->u = sqrt((out->ux*out->ux)+(out->uy*out->uy));
	

	// compute equilibrium distributions (WolfGladrow pag 200)
	double c_u[9];
	for(i=0;i<9;i++)
	    c_u[i] = cx[i]*out->ux + cy[i]*out->uy;
	double u_2 = out->ux*out->ux + out->uy*out->uy;
	double w[9] = {4.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/9.0,1.0/36.0,1.0/36.0,1.0/36.0,1.0/36.0};
	for(i=0;i<9;i++)
	    feq[i] = w[i] * out->rho * (1.0 + 3.0*c_u[i] + 4.5*c_u[i]*c_u[i] - 1.5*u_2);

	// BGK collision
	for(i=0;i<9;i++){
	    out->f[i] = (1.0-omega)*out->f[i] + omega*feq[i];
	}

    }
    return (void *)out;
}

int D2Q9Step(void* space){
    return CS_Step(space,&D2Q9transition);
}

#endif
