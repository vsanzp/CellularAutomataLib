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

#ifndef S3ANIM
#define S3ANIM

#include <s3.c>
#include <CellularAutomataLib-animation.c>

/****************************************/
/* SIMPLE 3D CELLULAR AUTOMATA       */
/****************************************/


/***************************************************************************/
/***************************************************************************/
/***************************************************************************/


// Function that returns the value to display in the graphical animation
double S3DisplayClouds(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    S3State *cs;
    
    cs = (S3State*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates
    if(cs == NULL)
	return (double)ColorToInt(BLANK); // transparent
    else{
	if (cs->v)
	    return(double)ColorToInt(Fade(YELLOW,1.0));
	else
	    //	    return(double)ColorToInt(BLACK);
	    return(double)ColorToInt(Fade(BLACK,0.2)); 
    }
}

void SetDisplayClouds(void*animation,void* space){
    CS_SetDisplay(animation,space, &S3DisplayClouds);
    return;
}


//***********************************************************************
//***********************************************************************
//***********************************************************************


//***********************************************************************
// DISPLAY FUNCTION
double S3Display445(void *space,int x, int y, int z, double* scalar, double* vx, double* vy, double* vz){
    S3State *cs;

    cs = (S3State*)CS_GetState(space,x+1,y+1,z+1); // getstate receives Modelica coordinates
    if(cs == NULL)
	return (double)ColorToInt(BLANK); // transparent
    else{
	if (cs->v == 4)
	    return (double)ColorToInt(YELLOW);
	else if (cs->v == 3)
	    return (double)ColorToInt(ORANGE);
	else if (cs->v == 2)
	    return (double)ColorToInt(RED);
	else if (cs->v == 1)
	    return (double)ColorToInt(MAGENTA);
	else
	    return (double)ColorToInt(BLANK);
    }
}

void SetDisplay445(void*animation,void* space){
    CS_SetDisplay(animation,space, &S3Display445);
    return;
}



#endif
