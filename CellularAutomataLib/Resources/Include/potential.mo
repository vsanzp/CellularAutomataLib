model potential
  parameter Integer X = 10;
  parameter Integer Y = 10;
  parameter Real sigma = 1.0;
  parameter Real d = 5e-6;
  parameter Real n = 1;
  parameter Real F = 96487;
  parameter Real dt = 0.1;
  parameter Real phi0 = -0.2;
  parameter Real phi1 = 0.0;
  parameter Real Cs = 7.64e4;
  Real dFS[X,Y]; // difference between solid fase ratios in dt intervals
  Modelica.Blocks.Interfaces.RealVectorInput FS[X,Y] "solid fase ratio from CA" annotation (Placement(transformation(extent={{-120,
            -20},{-80,20}})));
  Modelica.Blocks.Interfaces.RealVectorOutput phi[X,Y] "potential"
    annotation (Placement(transformation(extent={{80,-20},{120,20}})));
initial equation 
  for i in 1:X loop
      for j in 1:Y loop
        phi[i,j] = phi0;
      end for;
    end for;
equation 
    when sample(0,dt) then
    for i in 1:X loop
      for j in 1:Y loop
        dFS[i,j] =  FS[i,j]-pre(FS[i,j]);
      end for;
    end for;
  end when;

    for i in 2:X-1 loop
      for j in 2:Y-1 loop
        der(phi[i,j]) = sigma*((phi[i+1,j] + phi[i-1,j] - 2*phi[i,j])/(d*d)) + sigma*((phi[i,j+1] + phi[i,j-1] - 2*phi[i,j])/(d*d)) - (n*F*Cs*dFS[i,j]);
      end for;
    end for;
    // boundary conditions
    der(phi[1,1]) = sigma*((phi[1+1,1] + phi0 - 2*phi[1,1])/(d*d)) + sigma*((phi[1,1+1] + phi[1,1] - 2*phi[1,1])/(d*d)) - (n*F*Cs*dFS[1,1]);
    der(phi[1,Y]) = sigma*((phi[1+1,Y] + phi0 - 2*phi[1,Y])/(d*d)) + sigma*((phi[1,Y] + phi[1,Y-1] - 2*phi[1,Y])/(d*d)) - (n*F*Cs*dFS[1,Y]);
    der(phi[X,1]) = sigma*((phi1 + phi[X-1,1] - 2*phi[X,1])/(d*d)) + sigma*((phi[X,1+1] + phi[X,1] - 2*phi[X,1])/(d*d)) - (n*F*Cs*dFS[X,1]);
    der(phi[X,Y]) = sigma*((phi1 + phi[X-1,Y] - 2*phi[X,Y])/(d*d)) + sigma*((phi[X,Y] + phi[X,Y-1] - 2*phi[X,Y])/(d*d)) - (n*F*Cs*dFS[X,Y]);
    for j in 2:Y-1 loop
        der(phi[1,j]) = sigma*((phi[1+1,j] + phi0 - 2*phi[1,j])/(d*d)) + sigma*((phi[1,j+1] + phi[1,j-1] - 2*phi[1,j])/(d*d)) - (n*F*Cs*dFS[1,j]);
    end for;
    for j in 2:Y-1 loop
        der(phi[X,j]) = sigma*((phi1 + phi[X-1,j] - 2*phi[X,j])/(d*d)) + sigma*((phi[X,j+1] + phi[X,j-1] - 2*phi[X,j])/(d*d)) - (n*F*Cs*dFS[X,j]);
    end for;
    for i in 2:X-1 loop
        der(phi[i,1]) = sigma*((phi[i+1,1] + phi[i-1,1] - 2*phi[i,1])/(d*d)) + sigma*((phi[i,1+1] + phi[i,1] - 2*phi[i,1])/(d*d)) - (n*F*Cs*dFS[i,1]);
    end for;
    for i in 2:X-1 loop
        der(phi[i,Y]) = sigma*((phi[i+1,Y] + phi[i-1,Y] - 2*phi[i,Y])/(d*d)) + sigma*((phi[i,Y] + phi[i,Y-1] - 2*phi[i,Y])/(d*d)) - (n*F*Cs*dFS[i,Y]);
      end for;


    annotation (Placement(transformation(extent={{-120,-20},{-80,20}})),
                Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)));
end potential;
