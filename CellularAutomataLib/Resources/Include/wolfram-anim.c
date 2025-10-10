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

#ifndef WOLFRAMANIM
#define WOLFRAMANIM

#include <CellularAutomataLib-animation.c>
#include <wolfram.c>

//*********************************************************
// DISPLAY FUNCTION

 // Function that returns the value to display in the graphical animation
 // double COLOR display (void* space, int x,int y, int z, double* VECTOR_MODULE, double* VECTOR_X, double* VECTOR_Y, double* VECTOR_Z)
 double RDisplay(void *space,int x, int y, int z, double* vmodule, double* vx, double* vy, double* vz){
     CellSpace *s;
     Cell *cell;
     RState *cs;
 
     s = (CellSpace*)space;
     if (vx != NULL) *vx = 0;
     if (vy != NULL) *vy = 0;
     if (vz != NULL) *vz = 0;
     cell = s->M[x][y][z];
 
     if(cell == NULL)
 	return (double)ColorToInt(BLANK); // transparent	;
     else{
 	cs = (RState *)cell->cellstate;
 	if (cs->v)
 	    return(double)ColorToInt(YELLOW); //  yellow for alive cells
 	else
 	    return(double)ColorToInt(BLACK); // black for dead cells
     }
 }

int RSetDisplay(void* animation, void* space){
    double (*display)(void*,int,int,int,double*,double*,double*,double*) = &RDisplay;
    CS_SetDisplay(animation,space,display);
    return 1;
}




#endif
