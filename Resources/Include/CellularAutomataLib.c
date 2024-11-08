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

You should have received a copy of the  GNU Leaser General Public License along with this 
program. If not, see <https://www.gnu.org/licenses/>.
*********************************************************************************************/

#ifndef CELLULARAUTOMATALIB
#define CELLULARAUTOMATALIB

#define OFFSET 10

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <raylib.h>



#ifdef _WIN32
      #include <windows.h>
#endif

int mod (int a, int b){
  int ret;
  
  if(b < 0) //you can check for b == 0 separately and do what you want
    return mod(-a, -b);   
  ret = a % b;
  if(ret < 0)
    ret+=b;
  return ret;
}

// ****************************************************
// ****************************************************
// ****************************************************
// 
// 1D | 2D | 3D CELLULAR AUTOMATA/
//
// ****************************************************
// ****************************************************
// ****************************************************

/* data types */

typedef struct Cell{
    void* cellstate; // state of the cell
    int x; // x coord in 3D space 
    int y; // y coord in 3D space
    int z; // z coord in 3D space
    int active; // boolean flag to set cell as active or not
    int n_neighbors; // number of neighbors
    struct Cell **neighbors; // references to neighbors
    int n_inputs; // number of inputs
    void** inputs; // received external inputs
    int *inputs_rcv; // boolean map of active external inputs
} Cell;

typedef struct CS{
    Cell ****M; // matrix of cells in the space 
    Cell **A; // array of active cells
    int n_A; // number of active cells
    int X; // X size 
    int Y; // Y size 
    int Z; // Z size
    int hex; // hexagonal 2D space
    int ndims; // number of dimensions of the space
    int storehistory; // flag to store and plot history
    double **hist; // 1D history of states
    int n_hist; // number of steps recorded in the history
    int displayDelay; // delay to display animation in gnuplot
    int **neighborhood; // topology of the neighborhood  (even neighborhood for hex spaces)
    int **oddneighborhood; // for hex space
    int n_neighbors; // number of neighbors
    int n_inputs; // number of inputs
    int plot_animation; // boolean flag to display graphical animation or not
    int plot_vector; // boolean flag to generate a vector space instead of scalar
    double sq; // square size for the raylib animation
    int wX,wY,wZ; // number of cells in each dimension of the animation window
    int wrapped_borders; // space boundary configuration (like bitwise mask but using int: hundred for X, tens for Y and unit for Z)
    int wrapx, wrapy,wrapz;
    double (*display)(void*,int,int,int,double*,double*,double*,double*); // COLOR display(space,x,y,z,vectormodule,coord_x,coord_y,coord_z), returns COLOR and double* params as VECTOR_MODULE, VECTOR_COORD_X, VECTOR_COORD_Y, VECTOR_COORD_Z for cell[x][y][z]
    Camera2D camera2; // camera for 2D animations
    Camera3D camera3; // camera for 3D animations
    FILE * gp; // gnuplot terminal file descriptor
}CellSpace;


/* ###################################################*/


// Creates a new inactive cell located at position [x,y,z] in the space, with NULL inputs
Cell* CS_NewCell(void* space,int x, int y, int z, void *state){
    CellSpace *s;
    Cell *cell;
    int nx,ny,nz;
    int i,j,k;

    s =(CellSpace *)space;
    cell = malloc(sizeof(Cell));
    cell->cellstate = state;
    cell->x = x;
    cell->y = y;
    cell->z = z;
    cell->active = 0;
    cell->n_neighbors = s->n_neighbors;
    cell->n_inputs = s->n_inputs;

    cell->inputs = malloc(s->n_inputs*sizeof(void*));
    cell->inputs_rcv = malloc(s->n_inputs*sizeof(int));
    for(i=0;i<s->n_inputs;i++){
	cell->inputs[i] = NULL;
	cell->inputs_rcv[i] = 0;
    }
    
    return cell;
}

// sets the pointers to neighbors for the cell located at [x,y,z]
// neighbors outside the space with not wrapped borders are set to NULL
void CS_SetNeighbors(void* space,int x, int y, int z){
    CellSpace *s;
    Cell *cell;
    int nx,ny,nz;
    int i,j,k;
    int setnull;
    
    s = (CellSpace *)space;
    cell = s->M[x][y][z];

    cell->neighbors = (Cell**)malloc(s->n_neighbors*sizeof(Cell*));
    for(i=0;i<s->n_neighbors;i++){
	setnull = 0;
	if((s->hex && !(y % 2)) || !s->hex){
	    nx = x + s->neighborhood[i][0];
	}else{
	    nx = x + s->oddneighborhood[i][0];
	}
	if (s->wrapx){
	    if (nx < 0)
		nx = s->X + nx;
	    else if (nx >= s->X)
		nx = 0 + (nx - s->X);
	}else if ((nx < 0) || (nx >= s->X)) { 
	    cell->neighbors[i] = NULL;
	    setnull = 1;
	}
	if(s->ndims > 1 && !setnull){ // 2D
	    if((s->hex && !(y % 2)) || !s->hex){
		ny = y + s->neighborhood[i][1];
	    }else{
		ny = y + s->oddneighborhood[i][1];
	    }
	    if (s->wrapy){
		if (ny < 0)
		    ny = s->Y + ny;
		else if (ny >= s->Y)
		    ny = 0 + (ny - s->Y);
	    }else if ((ny < 0) || (ny >= s->Y)) { 
		cell->neighbors[i] = NULL;
		setnull = 1;
	    }
	}else
	    ny = y;
	if (s->ndims > 2 && !setnull){ // 3D
	    nz = z + s->neighborhood[i][2];
	    if (s->wrapz){
		if (nz < 0)
		    nz = s->Z + nz;
		else if (nz >= s->Z)
		    nz = 0 + (nz - s->Z);
	    }else if ((nz < 0) || (nz >= s->Z)) { 
		cell->neighbors[i] = NULL;
		setnull = 1;
	    }
	}else
	    nz = z;
	if (!setnull){
	    cell->neighbors[i] = s->M[nx][ny][nz];
	}
    }
}


// Function used to create and populate a new cellular space. It is used as constructor for the external object, that is returned as a void pointer
void* CS_Create(int X, int Y, int Z, int hex, int *neighborhood, size_t n1, size_t n2, int n_inputs, int wrapped_borders){
    CellSpace *s;
    int i,j,k;
    int wrapped;
    int res;
    int screenWidth;
    int screenHeight;

    ModelicaFormatMessage("CREATE\n");
    
    s = (CellSpace *)malloc(sizeof(CellSpace));
    s->A = (Cell**)malloc(X*Y*Z*sizeof(Cell*));
    s->n_A = 0; // no initially active cells
    s->X = X;
    s->Y = Y;
    s->Z = Z;
    s->hex = hex;
    s->ndims = 0;
    s->display = NULL;
    if (X>1) s->ndims++;
    if (Y>1) s->ndims++;
    if (Z>1) s->ndims++;
    s->n_inputs = n_inputs;
    // CONFIGURE NEIGHBORHOOD
    if(hex){ // hexagonal lattice in 2D?
	n1 = 6; // force six neighbors
	n2 = 2; // in a 2D lattice
    }
    s->n_neighbors = n1;
    s->neighborhood = (int **)malloc(sizeof(int *)*n1);
    if (hex)
	s->oddneighborhood = (int **)malloc(sizeof(int *)*6); // force to 6 neighbors in hex space
    if (n2 != s->ndims){
	//terminate("coordinates of neighborhood not matching number of dimensions of the space\n");
    }
    for(i=0;i<n1;i++){
        s->neighborhood[i] = (int *)malloc(sizeof(int)*n2);
	if(hex)
	    s->oddneighborhood[i] = (int *)malloc(sizeof(int)*2); // only for 2D hex spaces
    }
    j = 0;
    for(i=0;i<n1*n2;i+=n2){
	s->neighborhood[j][0] = neighborhood[i];
	if (n2 > 1) // 2D
	    s->neighborhood[j][1] = neighborhood[i+1];
	if (n2 > 2)  // 3D
	    s->neighborhood[j][2] = neighborhood[i+2];
	j++;
    }


    if(hex){// force neighborhood for hex spaces, even and odd rows have different neighbor coordinates
	printf("FORCING HEX NEIGHBORS");
	s->neighborhood[0][0] = -1; s->neighborhood[0][1] = 1;
	s->neighborhood[1][0] = 0; s->neighborhood[1][1] = 1;
	s->neighborhood[2][0] = 1; s->neighborhood[2][1] = 0;
	s->neighborhood[3][0] = 0; s->neighborhood[3][1] = -1;
	s->neighborhood[4][0] = -1; s->neighborhood[4][1] = -1;
	s->neighborhood[5][0] = -1; s->neighborhood[5][1] = 0;
	s->oddneighborhood[0][0] = 0; s->oddneighborhood[0][1] = 1;
	s->oddneighborhood[1][0] = 1;  s->oddneighborhood[1][1] = 1;
	s->oddneighborhood[2][0] = 1;  s->oddneighborhood[2][1] = 0;
	s->oddneighborhood[3][0] = 1;  s->oddneighborhood[3][1] = -1;
	s->oddneighborhood[4][0] = 0; s->oddneighborhood[4][1] = -1;
	s->oddneighborhood[5][0] = -1; s->oddneighborhood[5][1] = 0;
	
	/*	for(i=0;i<6;i++){
	    if(s->neighborhood[i][1] != 0){ // y coord != 0 -> x+1;
		s->oddneighborhood[i][0] = s->neighborhood[i][0]+1;
		s->oddneighborhood[i][1] = s->neighborhood[i][1];
	    }else{
		s->oddneighborhood[i][0] = s->neighborhood[i][0];
		s->oddneighborhood[i][1] = s->neighborhood[i][1];
	    }
	    }*/
    }
 
    s->storehistory = 0;
    s->hist = NULL;
    s->n_hist = 0;
    s->plot_animation = 0; 

    // CONFIGURE SPACE BOUNDARIES
    ModelicaFormatMessage("wrapped_borders = %d \n",wrapped_borders);
    wrapped = wrapped_borders; // wrapped_borders defines a binary mask for wrapping XYZ
    // 000 nothing wrapped
    // 100 X wrapped
    // 010 Y wrapped
    // 001 Z wrapped
    if (Y > 1 && Z > 1){
	wrapped = wrapped_borders == 8 ? 10 : wrapped; // 010 == 8, since 010 is octal number
	wrapped = wrapped_borders == 9 ? 11 : wrapped; // 011 == 9, since 011 is octal number
    }
    if (Z > 1){
	//	res = div(wrapped,10);
	res = wrapped%10;
	s->wrapz = res == 0 ? 0 : 1; // wrap Z?
	wrapped = wrapped/10;
	ModelicaFormatMessage("WRAP Z = %d\n",s->wrapz);
    }
    if (Y > 1){
	//res = div(wrapped,10);
	res = wrapped%10;
	s->wrapy = res == 0 ? 0 : 1; // wrap Y?
	wrapped = wrapped/10;
	ModelicaFormatMessage("WRAP Y = %d\n",s->wrapy);
    }
    //res = div(wrapped,10);
    res = wrapped%10;
    s->wrapx = res == 0 ? 0 : 1; // wrap X?
    ModelicaFormatMessage("WRAP X = %d\n",s->wrapx);
    
    // populate space with new cells
    s->M = (Cell ****)malloc(X*sizeof(Cell***));
    for(i=0;i<X;i++){
	s->M[i] = (Cell ***)malloc(Y*sizeof(Cell**));
	for(j=0;j<Y;j++){
	    s->M[i][j] = (Cell **)malloc(Z*sizeof(Cell*));
	    for(k=0;k<Z;k++){
		s->M[i][j][k] = CS_NewCell((void*)s,i,j,k,NULL); // null cell states (later states will be set either to default or to initial values)
	    }
	}
    }

    // set references to neighbors for all cells in the space
    for(i=0;i<X;i++){
	for(j=0;j<Y;j++){
	    for(k=0;k<Z;k++)
		CS_SetNeighbors((void*)s,i,j,k); 
	}
    }

    ModelicaFormatMessage("END CREATE\n");
    return (void *)s;
}

int CS_InitAnimation(void* space, int winWidth, int winHeight, int wX, int wY, int wZ, int vector, int displayDelay, const char *name){
    CellSpace* s;
    //int screenWidth, screenHeight;
    int cellsize;
    
    //printf("CS_plot\n");

    ModelicaFormatMessage("INIT ANIMATION\n");
    
    s = (CellSpace*) space;

    s->plot_vector = vector;
    s->wX = wX;
    s->wY = wY;
    s->wZ = wZ;

    s->displayDelay = displayDelay;
    s->plot_animation = 1;
    s->storehistory = wY > 0;
    
    if (s->ndims == 1 || s->ndims == 2){ // 1D or 2D animation using raylib
	//screenWidth = fmin((wX*SQUARESIZE)+2*OFFSET,winMaxWidth);
	//screenHeight = fmin((wY*SQUARESIZE)+2*OFFSET,winMaxHeight); 
	s->sq = (winWidth-(2*OFFSET))/(double)wX;
	s->camera2.target = (Vector2){0.0,0.0};
	s->camera2.offset = (Vector2){0,winHeight};
	s->camera2.rotation = 0.0;
	s->camera2.zoom = 1.0;
	InitWindow(winWidth, winHeight,name);
	//SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second	
    }else if (s->ndims == 3){
	//	s->squaresize = 1.0f;//((WIDTH-(2*OFFSET)))/(double)X;
	s->sq = 0.1f; //(((WIDTH-(2*OFFSET)))/(double)X)/10;
	//printf("SQ = %lf\n",((WIDTH-(2*OFFSET)))/(double)X);
	//screenWidth = winMaxWidth;
	//screenHeight = winMaxHeight;
	InitWindow(winWidth, winHeight,name);
	// s->camera3.position = (Vector3){s->squaresize*10, s->squaresize*10, s->squaresize*10 }; // Camera3 position
	s->camera3.position = (Vector3){wX, wY, wZ}; // Camera3 position
	//	s->camera3.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera3 position
	s->camera3.target = (Vector3){ 0.0, 0.0, 0.0 };      // Camera3 looking at point
	s->camera3.up = (Vector3){ 0.0, s->sq*10, 0.0 };          // Camera3 up vector (rotation towards target)
	s->camera3.fovy = 45.0;                                // Camera3 field-of-view Y
	s->camera3.projection = CAMERA_ORTHOGRAPHIC;//CAMERA_PERSPECTIVE;             // Camera3 projection type
	DisableCursor();                    // Limit cursor to relative movement inside the window
	//SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second	
    }
    ModelicaFormatMessage("END INIT ANIMATION\n");
}

// double COLOR display (void* space, int x,int y, int z, double* VMODULE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
int CS_SetDisplay(void* space, double (*display)(void*,int,int,int,double*,double*,double*,double*)){
    CellSpace* s;

    ModelicaFormatMessage("SET DISPLAY\n");
    
    s = (CellSpace*) space;
    s->display = display;
    
    ModelicaFormatMessage("END SET DISPLAY\n");

    return 0;
}

// OriginBottomLeft: transform (x,y) coordinates from the space into raylib Vector2 coordinates with origin in the bottom-left part of the window (instead of the top-left, as default) 
Vector2 OBLrec(double sq, double x, double y){ 
    return (Vector2){(x*sq),-1*(sq+(y*sq))};
}

Vector2 OBLhexodd(double sq, double x, double y){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    return (Vector2){sq/2+(x*sq),-1*(sq/2+(y*(sq-ap)))};
}

Vector2 OBLhexeven(double sq, double x, double y){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    return (Vector2){sq/2+(x*sq)+sq/2,-1*(sq/2+(y*(sq-ap)))};
}

int DrawVectorodd(double sq, double x, double y, double vx, double vy, double color){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    double vm = sqrt(vx*vx+vy*vy);
    double vecx = vx;
    double vecy = vy;

    if (vm > 1){ // limit vector to squaresize
	vecy = (vecy/vm);
	vecx = (vecx/vm);
    }

    vecx = (vx/vm);
    vecy = (vy/vm);

    vm = (sq/25)*vm;
    
    /*DrawLineEx((Vector2){(x*sq)+sq/2,-1*(y*(sq-ap)+sq/2)},
	       (Vector2){sq/2+(x*sq)+(vecy*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecx*(sq/2)))},
	       vm*2,
	       GetColor((int)color));*/

    DrawLineEx((Vector2){(x*sq)+sq/2,-1*(y*(sq-ap)+sq/2)},
	       (Vector2){(x*sq)+sq/2+(vecx*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecy*(sq/2)))},
	       vm*4,
	       GetColor((int)color));
    

    //DrawCircle(s->sq/2+(i*s->sq)+(vy*(s->sq/2)),-1*(s->sq/2+(j*(s->sq-ap))+(vx*(s->sq/2))),(vm*4)/s->sq,GetColor((int)vcolor));

    return 0;
}


int DrawVectoreven(double sq, double x, double y, double vx, double vy, double color){
    double ap =  sq-(sqrt(3)/2)*sq; // apothem for hex grids
    double vm = sqrt(vx*vx+vy*vy);
    double vecx = vx;
    double vecy = vy;

    if (vm > 1){ // limit vector to squaresize
	vecy = (vecy/vm);
	vecx = (vecx/vm);
    }
    vm = (sq/25)*vm;

    vecx = (vx/vm);
    vecy = (vy/vm);
    
    /*DrawLineEx((Vector2){sq/2+(sq/2)+(x*sq),-1*(sq/2+(y*(sq-ap)))},
	       (Vector2){sq/2+(sq/2)+(x*sq)+(vecy*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecx*(sq/2)))},
	       vm*2,GetColor((int)color));
    */
    DrawLineEx((Vector2){sq/2+(sq/2)+(x*sq),-1*(sq/2+(y*(sq-ap)))},
	       (Vector2){sq/2+(sq/2)+(x*sq)+(vecx*(sq/2)),-1*(sq/2+(y*(sq-ap))+(vecy*(sq/2)))},
	       vm*4,
	       GetColor((int)color));

    
    //DrawCircle(s->sq/2+(s->sq/2)+(i*s->sq)+(vy*(s->sq/2)),-1*(s->sq/2+(j*(s->sq-ap))+(vx*(s->sq/2))),(vm*4)/s->sq,GetColor((int)vcolor));

    return 0;
}


// double COLOR display (void* space, int x,int y, int z, double* SCALARVALUE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
int CS_Plot(void* space){
    CellSpace* s;
    Cell *cell;
    int i,j,k;
    double vm,vcolor;
    double ap;
    double VAL;
    double COLOR;
    double VX,VY,VZ;
    
    // ModelicaFormatMessage("PLOT\n");
    
    s = (CellSpace*) space;
    // 1D - plot animation for new states
    //printf("NDIMS = %d\n",s->ndims);

    if(s->display == NULL){
	ModelicaFormatMessage("PLOT ERROR: Display function not found\n");
	exit(-2);
    }
    
    if(s->ndims == 1){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode2D(s->camera2);
	if(s->storehistory){
	    s->n_hist++;
	    s->hist = (double**)realloc((double**)s->hist,sizeof(double*)*s->n_hist);
	    s->hist[s->n_hist-1] = (double*)malloc(sizeof(double)*s->X);
	    if (s->hist == NULL) exit(-1);
	    // store current states in history    
	    for (i=0;i<s->wX;i++){
		COLOR = s->display(space,i,0,0,&VAL,&VX,&VY,&VZ);
		s->hist[s->n_hist-1][i] = COLOR;
	    }
	}
	// PLOT history, including current state
	for(i=0;i<s->n_hist-1;i++){
	    for(j=0;j<s->wX;j++){
		DrawRectangleV(OBLrec(s->sq,j,i), (Vector2){s->sq,s->sq}, GetColor((int)s->hist[i][j]));
	    }
	}
	EndMode2D();
	EndDrawing();
    }
    // 2D - plot animation for new states
    if(s->ndims == 2){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode2D(s->camera2);
	//	  ModelicaFormatMessage("[");
	ap = s->sq-(sqrt(3)/2)*s->sq; // apothem for hex grids
	for (i=0;i<s->wX;i++){
	    for(j=0;j<s->wY;j++){
		cell = s->M[i][j][s->wZ-1];
		if (cell != NULL){
		    // cell present in space, draw state.
		    COLOR = s->display(space,i,j,0,&VAL,&VX,&VY,&VZ);
		    if (s->hex){ // hexagonal lattice
			if(s->plot_vector){ // vector field
			    if(!(j%2)){ //odd rows
				DrawPoly(OBLhexodd(s->sq,i,j), 6, (s->sq/2), 0, WHITE);
				DrawVectorodd(s->sq,i,j,VX,VY,COLOR);
			    }else{ // even rows
				DrawPoly(OBLhexeven(s->sq,i,j), 6, (s->sq/2) , 0,WHITE);
				DrawVectoreven(s->sq,i,j,VX,VY,COLOR);
			    }
			}else{
			    if(!(j%2))
				DrawPoly(OBLhexodd(s->sq,i,j), 6, (s->sq/2), 0, GetColor((int)COLOR));
			    else
				DrawPoly(OBLhexeven(s->sq,i,j), 6, (s->sq/2) , 0, GetColor((int)COLOR));
			}
		    }else{ // square lattice
			if(s->plot_vector){
			    DrawVectorodd(s->sq,i,j,VX,VY,COLOR);
			}else{
			    DrawRectangleV(OBLrec(s->sq,i,j), (Vector2){s->sq,s->sq}, GetColor((int)COLOR));
			}
		    }
		}else{// cell not present, print default
		    if(s->hex)
			if(!(j%2))
			    DrawPoly(OBLhexodd(s->sq,i,j), 6, (s->sq/2), 0, BLANK);
			else
			    DrawPoly(OBLhexeven(s->sq,i,j), 6, (s->sq/2), 0, BLANK);
		    else
			DrawRectangleV(OBLrec(s->sq,i,j), (Vector2){s->sq,s->sq}, BLANK);
		}
	    }
	}
	usleep(s->displayDelay);
	EndMode2D();
	EndDrawing();
    }
    
    // 3D - plot animation for new states
    if(s->ndims == 3){
	// Update
	//----------------------------------------------------------------------------------
	UpdateCamera(&s->camera3, CAMERA_THIRD_PERSON);
	
	if (IsKeyDown('Z')) s->camera3.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	//----------------------------------------------------------------------------------
	
	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
	
	ClearBackground(RAYWHITE);
	
	BeginMode3D(s->camera3);
	
	// Paint 3D Matrix
	for(i=0;i<s->wX;i++){
	    for(j=0;j<s->wY;j++){
		for(k=0;k<s->wZ;k++){
		    cell = s->M[i][j][k];
		    COLOR = s->display(space,i,j,k,&VAL,&VX,&VY,&VZ);
		    if (cell != NULL){
			// cell present in space, print state.
			DrawCubeV((Vector3){i*s->sq,j*s->sq,k*s->sq},(Vector3){s->sq,s->sq,s->sq},GetColor((int)COLOR));
		    }else{// cell not present, print default
			DrawCubeV((Vector3){i*s->sq,j*s->sq,k*s->sq},(Vector3){s->sq,s->sq,s->sq},BLANK);
			
		    }
		}
	    }
	}
	EndMode3D();
	usleep(s->displayDelay);
	EndDrawing();
    }

    //ModelicaFormatMessage("END PLOT\n");
    return 1;
}



int CS_Delete(void* space){
  CellSpace *s;
  Cell *cell;
  int i,j,k;
  
  s =(CellSpace *)space;

  ModelicaFormatMessage("CS_Delete\n");

  s->storehistory = 0;
  // Wait for animation window to close
  if(s->plot_animation){
      while(!WindowShouldClose())
	  CS_Plot(space);
      CloseWindow();
  }
  
  // free memory
  for(i=0;i<s->X;i++){
      for(j=0;j<s->Y;j++){
	  for(k=0;k<s->Z;k++){
	      cell = s->M[i][j][k];
	      s->M[i][j][k] = NULL;
	      free(cell);
	  }
	  free(s->M[i][j]);
      }
      free(s->M[i]);
  }
  free(s->M);
  free(s->A);
  free(s->neighborhood);
  if(s->hex)
      free(s->oddneighborhood);
  free(s);
  return 1;
}

void* CS_CellState(void* space, int modx, int mody, int modz){
  CellSpace *s;
  Cell *cell;
  int x = modx-1;
  int y = mody-1;
  int z = modz-1;
  
  s =(CellSpace *)space;
  if (s->M[x][y][z] != NULL)
      return s->M[x][y][z]->cellstate;
  else
      return NULL;
}

void CS_InsertCell(void* space, Cell* cell, int modx, int mody, int modz){
  CellSpace *s;
  int x = modx-1;
  int y = mody-1;
  int z = modz-1;
  int i,j,k;
  
  s = (CellSpace *)space;
  cell->x = x;
  cell->y = y;
  cell->z = z;
  if (s->M[x][y][z] != NULL)
      free(s->M[x][y][z]);
  s->M[x][y][z] = cell;
}

Cell* CS_ActiveCell(void *space, Cell* cell){
  CellSpace *s;
  int i,j,k;
  
  s =(CellSpace *)space;

  //printf("ACTIVE CELL (n_A=%d)\n",s->n_A);
  if (!cell->active){
      cell->active = 1;
      s->n_A++;
      /*      if(s->n_A > s->max_A){
	  s->max_A = s->max_A*2;
	  s->A = (Cell **)realloc(s->A,s->max_A*sizeof(Cell*));
	  }*/
      s->A[s->n_A-1] = cell;
  }
  //printf("end active\n");
  return cell;
}

// Function used initialize the state of the selected cell to a given value returned by initialState()
// Note that this function receives Modelica coordinates for the cells (that start at 1).
// Initialized cells are set active and will perform a transition in the next simulation step.
Cell* CS_Init(void* space, int modx, int mody, int modz, void (*initialState)(void*)){
  CellSpace *s;
  Cell *cell;
  int x = modx-1;
  int y = mody-1;
  int z = modz-1;
  int nx,ny,nz;
  int i,j,k;
  void * aux;

  //printf("INIT [%d,%d,%d]\n",modx,mody,modz);
  s =(CellSpace *)space;
  if (s->M[x][y][z] != NULL){
      cell = s->M[x][y][z];
      initialState(cell->cellstate);
  }else
      cell = NULL;
    CS_ActiveCell(space,cell);

    //printf("end init\n");
  return cell;
}


// Function used to set the state of each cell to its default value
// defaultState() must allocate new memory space for the state.
void CS_InitDefault(void *space, void* (*defaultState)()){
    CellSpace *s;
    Cell *cell;
    int i,j,k;
    
    s =(CellSpace *)space;
    for(i=0;i<s->X;i++)
	for(j=0;j<s->Y;j++)
	    for(k=0;k<s->Z;k++){
		s->M[i][j][k]->cellstate = defaultState();
	    }
}

void CS_SetState(void* space, int modx, int mody, int modz, void* newstate){
    CellSpace *s;
    Cell *cell;
    int x = modx-1;
    int y = mody-1;
    int z = modz-1;
    int nx,ny,nz;
    int i,j,k;
    
    s =(CellSpace *)space;
    if (s->M[x][y][z] == NULL){ // cell not in the space
	cell = CS_NewCell(space,modx,mody,modz,newstate);
    }else{
	cell = s->M[x][y][z];
	cell->cellstate = newstate;
    }
    CS_ActiveCell(space,cell);      
}

void CS_SetInput(void* space, int modx, int mody, int modz, void* value, int input_id){
    CellSpace *s;
    Cell *cell;
    int x = modx-1;
    int y = mody-1;
    int z = modz-1;
    int nx,ny,nz;
    int i,j,k;
    
    s =(CellSpace *)space;
    if (s->M[x][y][z] != NULL){ // cell in the space
	cell = s->M[x][y][z];
	if (cell->inputs[input_id-1] != NULL) // free previous input
	    free(cell->inputs[input_id-1]);
	cell->inputs[input_id-1] = value;
	cell->inputs_rcv[input_id-1] = 1;
    }
    CS_ActiveCell(space,cell);      
}

void *CS_GetState(void* space, int modx, int mody, int modz){
  CellSpace *s;
  Cell *cell;
  int x = modx-1;
  int y = mody-1;
  int z = modz-1;
  int i,j,k;
  
  s =(CellSpace *)space;
  if (s->M[x][y][z] != NULL){ // cell in the space
      return s->M[x][y][z]->cellstate;
  }else
      return NULL;
}

int CS_SizeX(void* space){
  CellSpace *s;
  s =(CellSpace *)space;
  return s->X;
}

int CS_SizeY(void* space){
  CellSpace *s;
  s =(CellSpace *)space;
  return s->Y;
}

int CS_SizeZ(void* space){
  CellSpace *s;
  s =(CellSpace *)space;
  return s->Z;
}

// Function used to perform one simulation step in the cellular space
// Only active cells and their neighbors are evaluated in each step
int CS_Step(void* space,
	    void* (*rule)(void*,int,int,int,void**,int,void**,int,int*)){
    CellSpace *s;
    Cell *cell;
    
    void **new_states;
    int i,j,k;
    //int nA;
    void **neighbor_states;
    int n_neighbors;
    Cell** new_A;
    //int max_new_A;
    int new_n_A = 0;
    //cell_list* lchange;
    int change;
    int active;
    int cs;
    
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    
    s =(CellSpace *)space;
   
    //ModelicaFormatMessage("STEP (active = %d) \n",s->n_A);
	
    // step only for active cells
    if (s->n_A > 0){
	// Set neighbors of current active cells also active.
	/*nA = s->n_A;
	for(i=0;i<nA;i++){
	    for(k=0;k<s->n_neighbors;k++){
		if(s->A[i]->neighbors[k] != NULL && !s->A[i]->neighbors[k]->active){
		    CS_ActiveCell(space,s->A[i]->neighbors[k]);
		}
	    }         
	    }*/

	// dynamic memory for the state of neighbors
	neighbor_states = (void **)malloc(sizeof(void *)*s->n_neighbors);
	// memory for the new cellstates
	new_states = (void**)malloc(sizeof(void*)*s->X*s->Y*s->Z);  
	//max_new_A = s->max_A;
	new_A = (Cell**)malloc(sizeof(Cell*)*s->X*s->Y*s->Z);
	new_n_A = 0;
	//---------------    ModelicaFormatMessage("Number Active %d\n",s->n_A);
	active = s->n_A;
	//printf("active %d \n",active);
	for(i=0;i<s->n_A;i++){
	    //sleep(1);
	    // join neighbors states before executing the rule function
	    for(k=0;k<s->n_neighbors;k++){
		if (s->A[i]->neighbors[k] != NULL){ // neighbor present
		    if(i<active) CS_ActiveCell(space,s->A[i]->neighbors[k]); // set neighbor of initially active also active
		    neighbor_states[k] = s->A[i]->neighbors[k]->cellstate;  // current state of neighbor
		}else{
		    neighbor_states[k] = NULL; // neighbor not present
		}
	    }
	    cell = s->A[i];
	    // calculate new state using user defined rule function
	    //ModelicaFormatMessage("STEP %d of %d:  [%d,%d]\n",i,s->n_A,cell->x,cell->y);
	    new_states[i] = rule(cell->cellstate,cell->x,cell->y,cell->z,neighbor_states,s->n_neighbors,cell->inputs,s->n_inputs,cell->inputs_rcv);
	    //new_states[i] = new_cell_state;
	    
	    // deactivate inputs
	    for (k=0;k<s->n_inputs;k++){
		free(s->A[i]->inputs[k]);
		s->A[i]->inputs[k] = NULL;
		s->A[i]->inputs_rcv[k] = 0;
	    }
	}
	//	ModelicaFormatMessage("UPDATE NEW STATES (n_A=%d)\n",s->n_A);

	// update cellstates
	for(i=0;i<s->n_A;i++){
	    cell = s->A[i];
	    //printf("cell[%d] = %p :  newstates[%d] = %p\n",i,cell,i,new_states[i]);
	    //if(cell != NULL && new_states[i] != NULL){
	    if(cell != NULL && new_states[i] != NULL){
		// keep cell active if state changed
		cell->active=1;
		new_n_A++;
		/*		if (new_n_A > s->max_A){
		    s->max_A = s->max_A*2;
		    new_A = (Cell **)realloc(new_A,s->max_A*sizeof(Cell*));
		    }*/
		new_A[new_n_A-1] = cell;
		// update cell state
		free(cell->cellstate);
		cell->cellstate = new_states[i];
		//cell->cellstate = new_states[i];
		//new_states[i] = NULL;

		
	    }else
		cell->active = 0;
	}

	//ModelicaFormatMessage("PLOT \n");
	
	//	CS_plot(s,displayS,displayV);

	//ModelicaFormatMessage("FREE \n");
	
	free(s->A);
	s->A = new_A;
	s->n_A = new_n_A;
	free(new_states);
	free(neighbor_states);
    }
    
    //ModelicaFormatMessage("END OF STEP : ACTIVE = %d\n",active);
    
    gettimeofday(&tv2, NULL);
    
    //    printf ("step exec. time %f\n",
    //	    (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
    //	    (double) (tv2.tv_sec - tv1.tv_sec));

    //    ModelicaFormatMessage("END STEP\n");
    return s->n_A;
}



#endif


