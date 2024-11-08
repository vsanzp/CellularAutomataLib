/**
 * Translation to C of the Behave class, by Victorino Sanz (vsanz@dia.uned.es).
 *
 * A modified version of the Behave class by Andreas Bachmann,
 * available at  http://www.geo.unizh.ch/gis/research/edmg/fire/unc.html
 *
 * @author: Andreas Bachman, Victor Olaya
 *
 *
 */
#include <math.h>
#define PI_ 3.14159265358979323846

typedef struct Behave{   
    /**
     * INSTANCE VARS
     */
    
    int isCalculated;
    int canDerive;
    
    // Rothermel's model input variables
    int     fuelModel;
    double  w0_d1; // Fuel loading [kg/m2]
    double  w0_d2;
    double  w0_d3;
    double  w0_lh;
    double  w0_lw;
    double  sv_d1; // surface to volume ratio [1/m]
    double  sv_d2;
    double  sv_d3;
    double  sv_lh;
    double  sv_lw;
    double  depth; // fuel bed depth [m]
    double  rho_p; // particle density [kg/m3]
    double  heat ; // particle low heat content [kJ/kg]
    double  s_t  ; // total mineral content [%]
    double  s_e  ; // effective mineral content [%]
    double  mx   ; // moisture of extinction, dead fuel [%]
    double  m_d1 ; // fuel moisture [%]
    double  m_d2 ;
    double  m_d3 ;
    double  m_lh ;
    double  m_lw ;                                              
    
    double  wsp;         // wind speed [m/s]
    double  wdr;         // wind dir [Degree],Northern wind = 0.0!
    double  slp;         // slope [Degree]
    double  asp;         // aspect [Degree] southfacing = 180 !
    
    // additional variables...
    double  rho_b     ;         // bulk density     [kg/m3]
    double  beta      ;         // packing ratio
    double  beta_opt  ;         // optimal packing ratio
    double  beta_ratio;         // ratio mean/optimal packing ratio
    double  w_n       ;         // net fuel loading
    double  eta_s     ;         // mineral damping coefficient
    double  eta_M     ;         // moisture damping coefficient
    double  xi        ;         // propagating flux ratio
    double  A         ;
    double  gamma     ;         // potential reaction velocity [1/s]
    double  gamma_max ;         // maximum reaction velocity [1/s]
    double  I_r       ;         // reaction intensity [kW/m2]
    double  phi_s     ;         // slope factor
    double  B, C, E   ;
    double  phi_w     ;         // wind factor
    double  phi_t     ;         // combined slope/wind factor
    double  vx, vy, vl;         // Vector components
    double  ecc       ;         // eccentricity
    
    double  asp_r;                     // radians equivalent of asp
    double  slp_r;                     // radians equivalent of slp
    double  wdr_r;                     // radians equivalent of wdr
    double  sdr_r;                     // radians equivalent of sdr
    double  sin_asp;
    double  cos_asp;
    double  sin_wdr;
    double  cos_wdr;
    double  tan_slp;
    
    double  al;
    double  splitDeg, splitRad;
    double  cos_splitRad, sin_splitRad;
    double  alDeg, alRad;
    
    double  sw_d1, sw_d2, sw_d3, sw_lh, sw_lw, sw_d, sw_l, sw_t;
    double  s2w_d, s2w_l, s2w_t;
    double  sw2_d, sw2_l, sw2_t;
    double  swm_d, swm_l, swm_t;
    double  sigma      ;
    double  w0        ;
    double  wn_d1, wn_d2, wn_d3, wn_lh, wn_lw, wn_d, wn_l;
    
    double  eps_d1, eps_d2, eps_d3, eps_lh, eps_lw;
    double  q_d1, q_d2, q_d3, q_lh, q_lw;
    double  hskz;
    
    double  hn_d1, hn_d2, hn_d3, hn_lh, hn_lw;
    double  sumhd, sumhl, sumhdm;
    double  W           ;                                       // W' ratio of "fine" fuel loading
    double  eta_Ml, eta_Md;                                     // damping coefficient
    double  rm_d, rm_l;                                         // moisture ratio
    double  Mf_dead      ;                                       // Moisture content of dead fine fuel
    double  Mx_live      ;                                       // Moisture of extinction of living fuel
    double  dead, live;
    
    // resulting variables
    double  sdr;                                       // spread direction           [degree]
    double  efw;                                       // effective wind speed       [m/s]
    double  hsk;                                       // heat sink term             [kJ/m3]
    double  ros;                                       // rate of spread             [m/s]
    double  tau;                                       // flame residence time       [s]
    double  hpa;                                       // heat release per unit area [kJ/m2]
    double  fzd;                                       // flame zone depth           [m]
    double  fli;                                       // fire line intensity        [kW/m]
    double  fln;                                       // flame length               [m]
}Behave;

double min(double a, double b){
    if (a < b)
	return a;
    else
	return b;
}

void initialValues(Behave *b){
    b->isCalculated = 0;
    b->canDerive    = 1;
    
    // Rothermel's model input variables
    b->fuelModel    = 0;          // fuel model nr
    b->w0_d1        = 0.;         // Fuel loading [kg/m2]
    b->w0_d2        = 0.;
    b->w0_d3        = 0.;
    b->w0_lh        = 0.;
    b->w0_lw        = 0.;
    b->sv_d1        = 0.;         // surface to volume ratio [1/m]
    b->sv_d2        = 357.6115;
    b->sv_d3        = 98.4252;
    b->sv_lh        = 4921.2598;
    b->sv_lw        = 4921.2598;
    b->depth        = 0.;         // fuel bed depth [m]
    b->rho_p        = 512.72341;  // particle density [kg/m3]
    b->heat         = 18606.70194; // particle low heat content [kJ/kg]
    b->s_t          = 5.5;        // total mineral content [%]
    b->s_e          = 1.0;        // effective mineral content [%]
    b->mx           = 0.;         // moisture of extinction, dead fuel [%]
    b->m_d1         = 0.;         // fuel moisture [%]
    b->m_d2         = 0.;
    b->m_d3         = 0.;
    b->m_lh         = 0.;
    b->m_lw         = 0.;
    
    b->wsp          = 0.;         // wind speed [m/s]
    b->wdr          = 0.;         // wind dir [Degree],Northern wind = 0.0!
    b->slp          = 0.;         // slope [Degree]
    b->asp          = 0.;         // aspect [Degree] southfacing = 180 !
    
    b->rho_b        = 0.;         // bulk density     [kg/m3]
    b->beta         = 0.;         // packing ratio
    b->beta_opt     = 0.;         // optimal packing ratio
    b->beta_ratio   = 0.;         // ratio mean/optimal packing ratio
    b->w_n          = 0.;         // net fuel loading
    b->eta_s        = 0.;         // mineral damping coefficient
    b->eta_M        = 0.;         // moisture damping coefficient
    b->xi           = 0.;         // propagating flux ratio
    b->A            = 0.;
    b->gamma        = 0.;         // potential reaction velocity [1/s]
    b->gamma_max    = 0.;         // maximum reaction velocity [1/s]
    b->I_r          = 0.;         // reaction intensity [kW/m2]
    b->phi_s        = 0.;         // slope factor
    b->B            = 0; 
    b->C            = 0; 
    b->E            = 0.;
    b->phi_w        = 0.;         // wind factor
    b->phi_t        = 0.;         // combined slope/wind factor
    b->vx           = 0; 
    b->vy           = 0; 
    b->vl           = 0.;           // Vector components
    b->ecc          = 0;          // eccentricity
    
    
    b->sw_d1=0; 
    b->sw_d2=0; 
    b->sw_d3=0;
    b->sw_lh=0;
    b->sw_lw=0; 
    b->sw_d=0; 
    b->sw_l=0; 
    b->sw_t = 0.;
    b->s2w_d=0;
    b->s2w_l=0; 
    b->s2w_t = 0.;
    b->sw2_d= 0; 
    b->sw2_l= 0;
    b->sw2_t = 0.;
    b->swm_d=0; 
    b->swm_l=0; 
    b->swm_t = 0.;
    b->sigma        = 0.;
    b->w0           = 0.;
        
    b->hn_d1=0; 
    b->hn_d2=0;
    b->hn_d3=0;
    b->hn_lh=0;
    b->hn_lw = 0.;
    b->sumhd=0; 
    b->sumhl=0;
    b->sumhdm = 0.;
    b->W            = 0.;                                       // W' ratio of "fine" fuel loading
    b->eta_Ml=0; 
    b->eta_Md = 0.;                                     // damping coefficient
    b->rm_d=0; 
    b->rm_l = 0.;                                         // moisture ratio
    b->Mf_dead      = 0.;                                       // Moisture content of dead fine fuel
    b->Mx_live      = 0.;                                       // Moisture of extinction of living fuel
    b->dead=0; 
    b->live = 0.;
    
    b->sdr          = 0.;                                       // spread direction           [degree]
    b->efw          = 0.;                                       // effective wind speed       [m/s]
    b->hsk          = 0.;                                       // heat sink term             [kJ/m3]
    b->ros          = 0.;                                       // rate of spread             [m/s]
    b->tau          = 0.;                                       // flame residence time       [s]
    b->hpa          = 0.;                                       // heat release per unit area [kJ/m2]
    b->fzd          = 0.;                                       // flame zone depth           [m]
    b->fli          = 0.;                                       // fire line intensity        [kW/m]
    b->fln          = 0.;                                       // flame length               [m]

}


void setFuelModelValues( double wd1, double wd2, double wd3, double wlh, double wlw, double dep, double sv, double mox, Behave *b) {   
    b->w0_d1 = wd1;
    b->w0_d2 = wd2;
    b->w0_d3 = wd3;
    b->w0_lh = wlh;
    b->w0_lw = wlw;
    b->depth = dep;
    b->sv_d1 = sv;
    b->mx = mox;
    b->w0 = b->w0_d1 + b->w0_d2 + b->w0_d3 + b->w0_lh + b->w0_lw;
    return;
}

int setFuelModel(int model, Behave* b) {
    if (model != b->fuelModel) {
	b->fuelModel = model;
	switch (b->fuelModel) {
	case 1:
	    setFuelModelValues(0.18, 0., 0., 0., 0., 0.3048, 11482.940, 12.,b);
	    break;
	case 2:
	    setFuelModelValues(0.486, 0.243, 0.122, 0.122, 0., 0.3048, 9842.0, 15.,b);
	    break;
	case 3:
	    setFuelModelValues(0.732, 0., 0., 0., 0., 0.762, 4921.2598, 25,b);
	    break;
	case 4:
	    //	    setFuelModelValues(1.218, 0.975, 0.486, 1.218, 0., 1.8288, 6561.67979, 20,b);
	    setFuelModelValues(1.123, 0.899, 0.451, 0., 1.121, 1.8288, 4542, 20,b);
	    break;
	case 5:
	    setFuelModelValues(0.243, 0.122, 0., 0., 0.122, 0.6096, 6561.680, 20,b);
	    break;
	case 6:
	    setFuelModelValues(0.365, 0.608, 0., 0., 0.486, 0.732, 5741.47, 25,b);
	    break;
	case 7:
	    //setFuelModelValues(0.275, 0.645, 0.365, 0., 0.090, 0.762, 5741.47, 40,b);
	    setFuelModelValues(0.253, 0.419, 0.336, 0., 0.083, 0.762, 4693, 40,b);
	    break;
	case 8:
	    setFuelModelValues(0.365, 0.243, 0.6075, 0.0, 0.122,0.06096, 6561.68, 30,b);
	    break;
	case 9:
	    setFuelModelValues(0.7046, 0.0996, 0.03645, 0.0, 0.122,0.06096, 6561.68, 25,b);
	    break;
	      /*  case 10:
	      setFuelmodelValues(0.729, 0.486, 1.215, 0.486, 0.3048, * 25);
	      break;
	      case 11:
	      setFuelmodelValues(0.365, 1.093, 1.3365, 0.0, 0.3048, *, 15);
	      break;
	      case 12:
	      setFuelmodelValues(0.972, 3.402, 4.0095, 0.0, 0.6992,*, 20);
	      break;
	      case 13:
	      setFuelmodelValues(1.701, 5.589, 6.804, 0.0, 0.9144,*, 25);
	      break;*/
	default:
	    return 0;
	}
    }
    else if (model < 1 || model > 13) {
	return 0;
    }
    return 1;
}

void setWindSpeed(double speed, Behave *b) {
    b->wsp = speed;
    return;
}


void setWindDir(double dir,Behave *b){
    b->wdr = dir;
    return;
}


void setSlope(double slope,Behave *b){
    b->slp = slope;
    return;
}


void setAspect(double aspect,Behave *b){
    b->asp = aspect;
    return;
}


void setDeadMoisture1(double moisture,Behave *b){
    b->m_d1 = moisture;
    return;
}


void setDeadMoisture10(double moisture,Behave *b){
    b->m_d2 = moisture;
    return;
}


void setDeadMoisture100(double moisture,Behave *b){
    b->m_d3 = moisture;
    return;
}


void setHerbMoisture(double moisture,Behave *b){
    b->m_lh = moisture;
    return;
}


void setWoodyMoisture(double moisture,Behave *b){
    b->m_lw = moisture;
    return;
}


double toRadians(double d){
    return d*PI_/180;
}

double toDegrees(double d){
    return d*180/PI_;
}

double getRosInDir(double dRos, double dMaxDirection, double dDirection, double dEcc){
    double dDir;
    double out;

    if ((dDir = abs(dMaxDirection - dDirection)) > 180.) {
	dDir = 360. - dDir;
    }
    
    out = (dRos * (1. - dEcc) / (1. - dEcc * cos(toRadians(dDir))));
    return out; 
    
}

/******************************************************************************************************************************
 * calcFuel
 *
 * calculates: - characteristic surface-to-volume ration (sigma) - bulk densities (rho_b) - packing ratios (beta, beta_opt,
 * beta_ratio) - net fuel loadings (wn_..)
 *
 *
 * Exceptions are thrown if - w0 <= 0. no fuel specified - sw_t <= 0. surface-to-voume-ratios not properly specified - depth <=
 * 0. depth of fuel bed not properly specified
 *****************************************************************************************************************************/
void calcFuel(Behave *b){
    
    /* reset all values to 0. ***************************/
    b->sigma = 0.;
    b->rho_b = 0.;
    b->beta = 0.;
    b->beta_opt = 0.;
    b->beta_ratio = 0.;
    // sw_
    b->sw_d1 = 0.;
    b->sw_d2 = 0.;
    b->sw_d3 = 0.;
    b->sw_lh = 0.;
    b->sw_lw = 0.;
    b->s2w_d = 0.;
    b->s2w_l = 0.;
    b->s2w_t = 0.;
    b->sw2_d = 0.;
    b->sw2_l = 0.;
    b->sw2_t = 0.;
    b->swm_d = 0.;
    b->swm_l = 0.;
    //
    b->wn_d1 = 0.;
    b->wn_d2 = 0.;
    b->wn_d3 = 0.;
    b->wn_lh = 0.;
    b->wn_lw = 0.;
    b->wn_d = 0.;
    b->wn_l = 0.;
    /** ********************************************** */
    
    // auxiliary variables
    b->sw_d1 = b->sv_d1 * b->w0_d1;
    b->sw_d2 = b->sv_d2 * b->w0_d2;
    b->sw_d3 = b->sv_d3 * b->w0_d3;
    b->sw_lh = b->sv_lh * b->w0_lh;
    b->sw_lw = b->sv_lw * b->w0_lw;
    b->sw_d  = b->sw_d1 + b->sw_d2 + b->sw_d3;
    b->sw_l  = b->sw_lh + b->sw_lw;
    b->sw_t  = b->sw_d  + b->sw_l;
    //
    b->s2w_d = b->sw_d1 * b->sv_d1 + b->sw_d2 * b->sv_d2 + b->sw_d3 * b->sv_d3;
    b->s2w_l = b->sw_lh * b->sv_lh + b->sw_lw * b->sv_lw;
    b->s2w_t = b->s2w_d + b->s2w_l;
    //
    b->sw2_d = b->sw_d1 * b->w0_d1 + b->sw_d2 * b->w0_d2 + b->sw_d3 * b->w0_d3;
    b->sw2_l = b->sw_lh * b->w0_lh + b->sw_lw * b->w0_lw;
    b->sw2_t = b->sw2_d + b->sw2_l;
    //
    b->swm_d = b->sw_d1 * b->m_d1 + b->sw_d2 * b->m_d2 + b->sw_d3 * b->m_d3;
    b->swm_l = b->sw_lh * b->m_lh + b->sw_lw * b->m_lw;
    
    b->sigma = b->s2w_t / b->sw_t;
    
    /**
     * mean bulk density Rothermel 1972: eq. (74)
     */
    // see further down "beta"
    // rho_b should not be bigger than 0.5 of the particle density
    //
    b->rho_b = b->w0 / b->depth;
    /**
     * packing ratios
     */
    // mean packing ratio
    b->beta = b->rho_b / b->rho_p;
    // should be between 0. and 0.5?
    // in Rothermel 1972, p.18-19, values are between 0 and 0.12
    if ((b->beta > 1) || (b->beta < 0)) {
	printf("Mean packing ration [beta] out of limits [0,1]: %f\n",b->beta);
    }
    
    // optimal packing ratio
    b->beta_opt = 8.8578 * pow(b->sigma, -0.8189);
    
    // ratio mean / optimal packing
    b->beta_ratio = b->beta / b->beta_opt;
    
    /**
     * Net fuel loading Rothermel 1972: eq. (60), adjusted by Albini 1976, p.88
     */
    b->wn_d1 = b->w0_d1 * (1 - b->s_t / 100);
    b->wn_d2 = b->w0_d2 * (1 - b->s_t / 100);
    b->wn_d3 = b->w0_d3 * (1 - b->s_t / 100);
    b->wn_lh = b->w0_lh * (1 - b->s_t / 100);
    b->wn_lw = b->w0_lw * (1 - b->s_t / 100);
    // Rothermel 1972: eq. (59)
    if (b->sw_d > 0) {
	b->wn_d = (1 - b->s_t / 100) * b->sw2_d / b->sw_d;
    }
    if (b->sw_l > 0) {
	b->wn_l = (1 - b->s_t / 100) * b->sw2_l / b->sw_l;
    }
}
//END calcFuel()

/******************************************************************************************************************************
 * moistureDamping ********************************************************************* calculate the moisture damping
 * coefficients for dead and live fuel
 *
 * Exceptions thrown if mx <= 0.
 */
void moistureDamping(Behave *b){
    // reset variables...
    b->hn_d1 = 0.;
    b->hn_d2 = 0.;
    b->hn_d3 = 0.;
    b->hn_lh = 0.;
    b->hn_lw = 0.;
    b->sumhd = 0.;
    b->sumhl = 0.;
    b->sumhdm = 0.;
    b->W = 0.;
    b->Mf_dead = 0.;
    b->Mx_live = 0.;
    b->eta_Ml = 0.;
    b->eta_Md = 0.;
    b->eta_M = 0.;
    
    /**
     * moisture damping coefficient weighting factors for live moisture of extinction...
     *
     * Rothermel (1972): eq. (88) (mx)_living = 2.9W(1-(M_f)_dead/0.3) - 0.226 (min = 0.3)
     *  => Albini (1976): page 89! (mx)_living = 2.9W'(1-(M'_f)_dead/(mx)_dead) - 0.226 (min = mx)
     *
     * -------------------------------------------------------- Ratio of "fine fuel loadings, dead/live W' =
     * SUM(w0_d*exp(-138/sv_d*)/SUM(w0_l*exp(-500/sv_l*) 0.20482 = Multiplier for [pound/ft2] to [kg/m2] -452.76 = -138 / 0.3048
     * -1640.2 = -500 / 0.3048
     */
    if (b->sv_d1 > 0.) {
	b->hn_d1 = 0.20482 * b->w0_d1 * exp(-452.76 / b->sv_d1);
    }
    if (b->sv_d2 > 0.) {
	b->hn_d2 = 0.20482 * b->w0_d2 * exp(-452.76 / b->sv_d2);
    }
    if (b->sv_d3 > 0.) {
	b->hn_d3 = 0.20482 * b->w0_d3 * exp(-452.76 / b->sv_d3);
    }
    if (b->sv_lh > 0.) {
	b->hn_lh = 0.20482 * b->w0_lh * exp(-1640.42 / b->sv_lh);
    }
    if (b->sv_lw > 0.) {
	b->hn_lw = 0.20482 * b->w0_lw * exp(-1640.42 / b->sv_lw);
    }

    // sum up...
    b->sumhd = b->hn_d1 + b->hn_d2 + b->hn_d3;
    b->sumhl = b->hn_lh + b->hn_lw;
    b->sumhdm = b->hn_d1 * b->m_d1 + b->hn_d2 * b->m_d2 + b->hn_d3 * b->m_d3;

    /*
      moisture damping for live fuel
    */
    // calc only if there is any live fuel available...
    // sw_l = sv_lh * w0_lh + sv_lw * w0_lw
    // sw_l > 0 ensures that sumhl > 0
    if (b->sw_l > 0.) {
	// W' ratio of "fine" fuel loading, dead/living
	b->W = b->sumhd / b->sumhl;

	// Moisture content of "fine" dead fuel
	if (b->sumhd > 0) {
            b->Mf_dead = b->sumhdm / b->sumhd;
	}

	// Moisture of extinction of living fuel
	b->Mx_live = (2.9 * b->W * (1 - b->Mf_dead / b->mx) - 0.226) * 100;

	/*
	 * Check for Minimum of Mx_live
	 *        Mx_live = Math.max(Mx_live,mx)
	 *
	 * if Mx_live is lower than mx, we have a problem with the
	 * calculation of the error, as the function is no longer continuos
	 *
	 */
	if (b->Mx_live < b->mx) {
            b->canDerive = 0;
            b->Mx_live = b->mx;
	}
	// dead moisture ratio
	b->rm_l = b->swm_l / (b->sw_l * b->Mx_live);
    }

    // moisture ratios
    // Rothermel (1972): eq. (65) & (66)
    if (b->sw_d > 0) {
	b->rm_d = b->swm_d / (b->sw_d * b->mx);
    }

    // moisture damping coefficient
    // Rothermel (1972): eq. (64)
    // damping coefficients range from 0 to 1 (Rothermel 1972, p.11!).
    // 0 means a moisture ratio rm_* greater than 1, i.e. the moisture
    //   content is higher than the moisture of extinction
    //
    b->eta_Md = 1 - 2.59 * (b->rm_d) + 5.11 * pow(b->rm_d, 2) - 3.52 * pow(b->rm_d, 3);
    b->eta_Ml = 1 - 2.59 * (b->rm_l) + 5.11 * pow(b->rm_l, 2) - 3.52 * pow(b->rm_l, 3);

    // check for eta_* lower than 0;
    if (b->eta_Md < 0) {
	b->eta_Md = 0.;
    }
    if (b->eta_Ml < 0) {
	b->eta_Ml = 0.;
    }

    //
    b->eta_M = b->wn_d * b->eta_Md + b->wn_l * b->eta_Ml;
}


/******************************************************************************************************************************
 * gamma': reaction velocity
 *
 *****************************************************************************************************************************/
void reactionVelocity(Behave *b){
    /**
     * exponent A: => Rothermel 1972 eq.(70), replaced by Albini (1976) (p.88) A = 133 * sigma**-0.7913 ;sigma[1/ft] = 133 *
     * 0.3048**-0.7913 * sigma**-0.7913 ;sigma[1/m] = 340.53 * sigma**-0.7913 ;sigma[1/m]
     */
    b->A = 340.53 * pow(b->sigma, -0.7913);
    /**
     * maximum reaction velocity: => Rothermel 1972: (68), based on (36) conversion: gamma_max [min-1] = 60 gamma_max [s-1]
     * Formulae: gamma_max = sigma**1.5 / (495 + 0.0594* sigma**1.5) counter = sigma**1.5 ;sigma [1/ft] = 1 * Math.pow(0.3048,
     * 1.5) * sigma**1.5 ;sigma [1/m] = 0.16828 * sigma**1.5
     *
     * denominator = 495 + 0.0594 * sigma**1.5 ;sigma[1/ft] = 495*60 + 0.0594*60*0.16828 * sigma**1.5 ;sigma[1/m] = 29700 +
     * 0.5997 * sigma**1.5 ;sigma[1/m]
     */
    b->gamma_max = 0.16828 * pow(b->sigma, 1.5) / (29700 + 0.5997 * pow(b->sigma, 1.5));
    b->gamma = b->gamma_max * pow(b->beta_ratio, b->A) * exp(b->A * (1 - b->beta_ratio));
}


/******************************************************************************************************************************
 * heat sink term
 *
 * Rothermel (1972): eq. (77) + (78)
 *****************************************************************************************************************************/
void heatSink(Behave *b){
    /**
     * Effective heating number: epsilon = exp(-138 / sigma_ft) (14) = exp(-138 / (sigma_m * 0.3048)) conversion! = exp( -452.76 /
     * sigma)
     */

    if (b->sv_d1 > 0.0) {
	b->eps_d1 = exp(-452.76 / b->sv_d1);
    }
    if (b->sv_d2 > 0.0) {
	b->eps_d2 = exp(-452.76 / b->sv_d2);
    }
    if (b->sv_d3 > 0.0) {
	b->eps_d3 = exp(-452.76 / b->sv_d3);
    }
    if (b->sv_lh > 0.0) {
	b->eps_lh = exp(-452.76 / b->sv_lh);
    }
    if (b->sv_lw > 0.0) {
	b->eps_lw = exp(-452.76 / b->sv_lw);
    }
    /**
     * Heat of Preignition: Q_ig, [Btu/lb] = 1.05506 kJ / 0.4535 kg = 2.3265 kJ/kg Q_ig = 250.0 + 1116 * M_f ; M_f [fraction] =
     * 581.5 + 2.3265 *(0.01 * M_f) ; M_f [%]
     */
    b->q_d1 = 581.5 + 25.957 * b->m_d1;
    b->q_d2 = 581.5 + 25.957 * b->m_d2;
    b->q_d3 = 581.5 + 25.957 * b->m_d3;
    b->q_lh = 581.5 + 25.957 * b->m_lh;
    b->q_lw = 581.5 + 25.957 * b->m_lw;

    /**
     * Heat Sink
     */
    b->hskz = b->sw_d1 * b->eps_d1 * b->q_d1 + b->sw_d2 * b->eps_d2 * b->q_d2 + b->sw_d3 * b->eps_d3 * b->q_d3 + b->sw_lh * b->eps_lh * b->q_lh + b->sw_lw * b->eps_lw * b->q_lw;
    b->hsk = b->rho_b * b->hskz / b->sw_t;
}


/******************************************************************************************************************************
 * phi_s: slope factor
 *
 * called from combinedWindAndSlopeFactor()
 *****************************************************************************************************************************/
void slopeFactor(Behave *b) {
    b->slp_r = toRadians(b->slp);
    b->tan_slp = tan(b->slp_r);
    b->phi_s = 5.275 * pow(b->beta, -0.3) * pow(b->tan_slp, 2);
}


/******************************************************************************************************************************
 * phi_w: wind factor
 *
 * called from combinedWindAndSlopeFactor()
 *
 * conversion: sigma [1/ft] = sigma[1/m] * 0.3048! original formulae in Rothermel 1972, eq. XXXXX B = 0.013298 *
 * Math.pow(sigma,0.54); C = 7.47 * Math.exp(-0.06919 * Math.pow(sigma,0.55)); E = 0.715 * Math.exp(0.0001094 * sigma);
 *
 *****************************************************************************************************************************/
void windFactor(Behave *b){
    b->B = 0.02526 * pow(b->sigma * 0.3048, 0.54);
    b->C = 7.47 * exp(-0.133 * pow(b->sigma * 0.3048, 0.55));
    b->E = 0.715 * exp(-0.000359 * 0.3048 * b->sigma);
    b->phi_w = b->C * pow(3.281 * 60 * b->wsp, b->B) * pow(b->beta_ratio, -b->E);
}


/******************************************************************************************************************************
 * phi combined wind and slope factor assumptions: wsp > 0. and/or slp > 0.
 *  -> phi_t
 *****************************************************************************************************************************/
void combinedWindAndSlopeFactor(Behave *b){
    double lwRatio;
       
    // reset values
    b->phi_t = 0.;
    b->vl = 0.;

    // calculate the wind and slope factor
    slopeFactor(b); // -> phi_s
    windFactor(b); // -> phi_w

    // combine the two factors using a vector sum..
    // conversion of input values....
    b->asp_r = toRadians(b->asp);
    b->wdr_r = toRadians(b->wdr);

    // Flip Aspect
    // -> upslope direction is needed
    if (b->asp_r < PI_) {
	b->asp_r = b->asp_r + PI_;
    }
    else {
	b->asp_r = b->asp_r - PI_;
    }

    /*
     * Flip Wind Direction
     * standard meteorological definitions says
     *        winddirection == direction where the wind is blowing FROM
     * for the calculation we need
     *        winddirection == direction where the is blowing TO
     */
    if (b->wdr_r < PI_) {
	b->wdr_r = b->wdr_r + PI_;
    }
    else {
	b->wdr_r = b->wdr_r - PI_;
    }

    /* the following code according to fireLib.c
     * 1. normalize for upslope direction
     * 2. consider differing angle of wind by splitAngle
     */
    b->splitRad = abs(b->wdr_r - b->asp_r) >= PI_ ? b->wdr_r + b->asp_r - 2 * PI_ : b->wdr_r - b->asp_r;
    b->cos_splitRad = cos(b->splitRad);
    b->sin_splitRad = sin(b->splitRad);
    b->vx = b->phi_s + b->phi_w * b->cos_splitRad;
    b->vy = b->phi_w * b->sin_splitRad;
    b->vl = sqrt(b->vx * b->vx + b->vy * b->vy);
    //
    b->al = asin(b->vy / b->vl);
    //
    if (b->vx >= 0.) {
	b->alRad = (b->vy >= 0.) ? b->asp_r + b->al : b->asp_r + b->al + 2 * PI_;
    }
    else {
	b->alRad = b->asp_r - b->al + PI_;
    }
    b->alDeg = toDegrees(b->alRad);
    if (b->alDeg > 360) {
	b->alDeg -= 360.;
    }
    //
    b->sdr = b->alDeg;
    /***************************************************************************************************************************
     * effective windspeed actually this is only the inverse function of phi_w
     **************************************************************************************************************************/
    b->efw = (pow(b->vl / (b->C * pow(b->beta_ratio, -b->E)), 1 / b->B)) / 196.85;
    // rothermel 87: sets an upper limit on
    // the wind multiplication factor
    if (b->efw > 0.024 * b->I_r) {
	b->efw = min(b->efw, 0.024 * b->I_r);
	b->phi_t = b->C * pow(196.85 * b->efw, b->B) * pow(b->beta_ratio, -b->E);
	// flag that derivations are not allowed!
	b->canDerive = 0;
    } else {
	b->phi_t = b->vl;
    }
    //lwRatio = 1. + 0.002840909 * b->efw;
    //ModelicaFormatMessage(" - LWratio = %f\n",lwRatio);
    lwRatio = pow(0.936,0.071271*b->efw) + pow(0.461,-0.04300*b->efw);
    //ModelicaFormatMessage("LWratio = %f\n",lwRatio);
    b->ecc = sqrt(lwRatio * lwRatio - 1.0) / lwRatio;

}

/* void calc(Behave *b){ */
/*     calcRothermel(b); */
/*     return; */
//}


/******************************************************************************************************************************
 * calcRothermel
 *
 * the main logic of rothermel wildfire behaviour calculation
 *
 *****************************************************************************************************************************/
void calcRothermel(Behave *b){
    
    // reset flags
    b->isCalculated = 0;
    b->canDerive = 1;
    
    /* prepare fuel parameters */
    calcFuel(b);
    
    /* mineral damping coefficient:  eta_s */
    /*   Rothermel 1972: eq. (62)  */
    b->eta_s = 0.174 * pow(b->s_e / 100, -0.19);
    
    /* moisture damping coefficient: eta_M */
    moistureDamping(b);
    
    /* reaction velocity: gamma */
    reactionVelocity(b);
    
    /* reaction intensity */
    b->I_r = b->gamma * b->heat * b->eta_s * b->eta_M;
    
    /* propagating flux ratio: xi
       Rothermel 1972: eq. (42)
       Formula:
       with sigma[1/ft]:
       xi = exp[(0.792 + 0.681*            sqrt(sigma))*(beta + 0.1)] /
       (192 + 0.259*sigma)
       with sigma[1/m] :
       xi = exp[(0.792 + 0.681*sqrt(.3048)*sqrt(sigma))*(beta + 0.1)] /
       (192 + 0.259*0.3048*sigma)
    */
    b->xi = exp((0.792 + 0.37597 * sqrt(b->sigma)) * (b->beta + 0.1)) / (192 + 0.0791 * b->sigma);
    
    /* heat sink: hsk */
    heatSink(b);
    
    /* forward rate of spread   */
    /*     no wind and no slope */
    b->ros = b->I_r * b->xi / b->hsk;
    
    /*     wind and slope       */
    combinedWindAndSlopeFactor(b); // -> phi_t
    
    if (b->phi_t > 0.) {
	b->ros = b->I_r * b->xi * (1 + b->phi_t) / b->hsk; // (52), [m/s]
    }
    
    /** ******************************************************************** */
    /* additional fire behaviour results                                   */
    //
    /* flame residence time: tau               */
    /* Anderson 1969, in Albini (1976), p.91:  */
    /* tau = 384/ sigma   [min]                */
    b->tau = 384. * 60 / (b->sigma * 0.3048); // [s]
    
    /* heat release per unit area: hpa */
    b->hpa = b->I_r * b->tau;
    
    /* flame zone depth	*/
    b->fzd = b->ros * b->tau;
    
    /* fireline intensity */
    b->fli = b->I_r * b->fzd;
    
    /* flame length                                   */
    /* based on Byram (1959), in Albini (1976), p. 91 */
    b->fln = 0.0775 * pow(b->fli, 0.46);
    
    /* it's over...*/
    b->isCalculated = 1;
}













