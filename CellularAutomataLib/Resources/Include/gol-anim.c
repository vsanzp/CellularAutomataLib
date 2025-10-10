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

#ifndef GOLANIM
#define GOLANIM

#include <CellularAutomataLib-animation.c>
#include <gol.c>


/****************************************/
/* GAME OF LIFE CELLULAR AUTOMATA       */
/****************************************/


//********************************************************************
// DISPLAY
// Function that returns the value to display in the graphical animation
double GOLDisplay(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    CellSpace *s;
    Cell *cell;
    GOLState *cs;

    s = (CellSpace*)space;
    if (vx != NULL) *vx = 0;
    if (vy != NULL) *vy = 0;
    if (vz != NULL) *vz = 0;
    cell = s->M[x][y][z];

    if(cell == NULL)
	return (double)ColorToInt(BLANK); // transparent	;
    else{
	cs = (GOLState *)cell->cellstate;
	if (cs->v)
	    return(double)ColorToInt(DARKBLUE); // alive in DARKBLUE
	else
	    return(double)ColorToInt(WHITE);  // dead in wHITE
    }
}
int GOLSetDisplay(void*animation,void *space){
    CS_SetDisplay(animation,space, &GOLDisplay);   
    return 1;
}

#endif
