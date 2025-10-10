within CellularAutomataLib.Examples.CS_2D.Lithium;
model potential
  parameter Integer X = 10;
  parameter Integer Y = 10;
  parameter Real sigma = 1.0;
  parameter Real d = 5e-6;
  parameter Real n = 1;
  parameter Real F = 96487;
  parameter Real dt = 0.2;
  parameter Real phi0 = -0.2;
  parameter Real phi1 = 0.0;
  parameter Real Cs = 7.64e4;
  //Real dphi[X,Y];
  Modelica.Blocks.Interfaces.RealVectorInput FS[X,Y] annotation (Placement(transformation(extent={{-120,
            -20},{-80,20}})));
  Modelica.Blocks.Interfaces.RealVectorOutput phi[X,Y]
    annotation (Placement(transformation(extent={{80,-20},{120,20}})));
initial equation
  for i in 1:X loop
      for j in 1:Y loop
        phi[i,j] = phi0;
      end for;
    end for;
equation
  when sample(0,dt) then
    for i in 2:X-1 loop
      for j in 2:Y-1 loop
        der(phi[i,j]) = sigma*((pre(phi[i+1,j]) + pre(phi[i-1,j]) - 2*pre(phi[i,j]))/d*d) + sigma*((pre(phi[i,j+1]) + pre(phi[i,j-1]) - 2*pre(phi[i,j]))/d*d) - n*F*Cs*((FS[i,j] - pre(FS[i,j]))/dt);
      end for;
    end for;
    der(phi[1,1]) = sigma*((pre(phi[1+1,1]) + phi0 - 2*pre(phi[1,1]))/d*d) + sigma*((pre(phi[1,1+1]) + pre(phi[1,1]) - 2*pre(phi[1,1]))/d*d) - n*F*Cs*((FS[1,1] - pre(FS[1,1]))/dt);
    der(phi[1,Y]) = sigma*((pre(phi[1+1,Y]) + phi0 - 2*pre(phi[1,Y]))/d*d) + sigma*((pre(phi[1,Y]) + pre(phi[1,Y-1]) - 2*pre(phi[1,Y]))/d*d) - n*F*Cs*((FS[1,Y] - pre(FS[1,Y]))/dt);
    der(phi[X,1]) = sigma*((phi1 + pre(phi[X-1,1]) - 2*pre(phi[X,1]))/d*d) + sigma*((pre(phi[X,1+1]) + pre(phi[X,1]) - 2*pre(phi[X,1]))/d*d) - n*F*Cs*((FS[X,1] - pre(FS[X,1]))/dt);
    der(phi[X,Y]) = sigma*((phi1 + pre(phi[X-1,Y]) - 2*pre(phi[X,Y]))/d*d) + sigma*((pre(phi[X,Y]) + pre(phi[X,Y-1]) - 2*pre(phi[X,Y]))/d*d) - n*F*Cs*((FS[X,Y] - pre(FS[X,Y]))/dt);
    for j in 2:Y-1 loop
        der(phi[1,j]) = sigma*((pre(phi[1+1,j]) + pre(phi0) - 2*pre(phi[1,j]))/d*d) + sigma*((pre(phi[1,j+1]) + pre(phi[1,j-1]) - 2*pre(phi[1,j]))/d*d) - n*F*Cs*((FS[1,j] - pre(FS[1,j]))/dt);
    end for;
    for j in 2:Y-1 loop
        der(phi[X,j]) = sigma*((phi1 + pre(phi[X-1,j]) - 2*pre(phi[X,j]))/d*d) + sigma*((pre(phi[X,j+1]) + pre(phi[X,j-1]) - 2*pre(phi[X,j]))/d*d) - n*F*Cs*((FS[X,j] - pre(FS[X,j]))/dt);
    end for;
    for i in 2:X-1 loop
        der(phi[i,1]) = sigma*((pre(phi[i+1,1]) + pre(phi[i-1,1]) - 2*pre(phi[i,1]))/d*d) + sigma*((pre(phi[i,1+1]) + pre(phi[i,1]) - 2*pre(phi[i,1]))/d*d) - n*F*Cs*((FS[i,1] - pre(FS[i,1]))/dt);
    end for;
    for i in 2:X-1 loop
        der(phi[i,Y]) = sigma*((pre(phi[i+1,Y]) + pre(phi[i-1,Y]) - 2*pre(phi[i,Y]))/d*d) + sigma*((pre(phi[i,Y]) + pre(phi[i,Y-1]) - 2*pre(phi[i,Y]))/d*d) - n*F*Cs*((FS[i,Y] - pre(FS[i,Y]))/dt);
      end for;
  end when;

    annotation (Placement(transformation(extent={{-120,-20},{-80,20}})),
                Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)));
end potential;
