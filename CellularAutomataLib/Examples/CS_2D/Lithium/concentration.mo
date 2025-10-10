within CellularAutomataLib.Examples.CS_2D.Lithium;
model concentration
  parameter Integer X = 20;
  parameter Integer Y = 20;
  parameter Real Ds = 7.5e-10; // diff. coef. in solution
  parameter Real De = 7.5e-13; // diff. coef. in electrode
  Real deff[X,Y];
  Real hFS[X,Y];
  parameter Real Cs = 7.64e4; // lithium concentration
  parameter Real Co = 1e3; // lithium-ion concentration
  parameter Real d = 5e-6; //grid interval
  parameter Real dt = 0.2;
  Modelica.Blocks.Interfaces.RealVectorInput FS[X,Y]
    annotation (Placement(transformation(extent={{-120,-20},{-80,20}})));
  Modelica.Blocks.Interfaces.RealVectorOutput c[X,Y]
    annotation (Placement(transformation(extent={{80,-20},{120,20}})));
initial equation
  for i in 1:X loop
    for j in 1:Y loop
      c[i,j] = 1;
    end for;
  end for;
equation
  when sample(0,dt) then
  for n in 1:X loop
    for m in 1:Y loop
      deff[n,m] = Ds*hFS[n,m] + De*(1-hFS[n,m]);
      hFS[n,m] = FS[n,m]^3*(6*FS[n,m]^2 - 15*FS[n,m] + 10);
    end for;
  end for;
  for i in 2:X-1 loop
    for j in 2:Y-1 loop
      der(c[i,j]) = deff[i+1,j]*((c[i+1,j]- c[i,j])/2*d*d) + deff[i-1,j]*((c[i-1,j]- c[i,j])/2*d*d) +
                    deff[i,j+1]*((c[i,j+1]- c[i,j])/2*d*d) + deff[i,j-1]*((c[i,j-1]- c[i,j])/2*d*d) -
                    (Cs/Co)*(FS[i,j]-pre(FS[i,j]));
    end for;
  end for;
  for j in 2:Y-1 loop
      der(c[1,j]) = deff[1+1,j]*((c[1+1,j]- c[1,j])/2*d*d) + deff[1,j]*((c[1,j] - c[1,j])/2*d*d) +
                    deff[1,j+1]*((c[1,j+1]- c[1,j])/2*d*d) + deff[1,j-1]*((c[1,j-1]- c[1,j])/2*d*d) -
                    (Cs/Co)*(FS[1,j]-pre(FS[1,j]));
  end for;
  for j in 2:Y-1 loop
      der(c[X,j]) = deff[X,j]*((1 - c[X,j])/2*d*d) + deff[X-1,j]*((c[X-1,j]- c[X,j])/2*d*d) +
                    deff[X,j+1]*((c[X,j+1]- c[X,j])/2*d*d) + deff[X,j-1]*((c[X,j-1]- c[X,j])/2*d*d) -
                    (Cs/Co)*(FS[X,j]-pre(FS[X,j]));
  end for;
  for i in 2:X-1 loop
      der(c[i,1]) = deff[i+1,1]*((c[i+1,1]- c[i,1])/2*d*d) + deff[i-1,1]*((c[i-1,1]- c[i,1])/2*d*d) +
                    deff[i,1+1]*((c[i,1+1]- c[i,1])/2*d*d) + deff[i,1]*((1- c[i,1])/2*d*d) -
                    (Cs/Co)*(FS[i,1]-pre(FS[i,1]));
  end for;
  for i in 2:X-1 loop
      der(c[i,Y]) = deff[i+1,Y]*((c[i+1,Y]- c[i,Y])/2*d*d) + deff[i-1,Y]*((c[i-1,Y]- c[i,Y])/2*d*d) +
                    deff[i,Y]*((1 - c[i,Y])/2*d*d) + deff[i,Y-1]*((c[i,Y-1]- c[i,Y])/2*d*d) -
                    (Cs/Co)*(FS[i,Y]-pre(FS[i,Y]));
  end for;
  der(c[1,1]) = deff[1+1,1]*((c[1+1,1]- c[1,1])/2*d*d) + deff[1,1]*((0 - c[1,1])/2*d*d) +
                deff[1,1+1]*((c[1,1+1]- c[1,1])/2*d*d) + deff[1,1]*((1 - c[1,1])/2*d*d) -
               (Cs/Co)*(FS[1,1]-pre(FS[1,1]));

  der(c[1,Y]) = deff[1+1,Y]*((c[1+1,Y]- c[1,Y])/2*d*d) + deff[1,Y]*((0 - c[1,Y])/2*d*d) +
                deff[1,Y]*((1 - c[1,Y])/2*d*d) + deff[1,Y-1]*((c[1,Y-1]- c[1,Y])/2*d*d) -
                (Cs/Co)*(FS[1,Y]-pre(FS[1,Y]));

  der(c[X,1]) = deff[X,1]*((1 - c[X,1])/2*d*d) + deff[X-1,1]*((c[X-1,1]- c[X,1])/2*d*d) +
                deff[X,1+1]*((c[X,1+1]- c[X,1])/2*d*d) + deff[X,1]*((1 - c[X,1])/2*d*d) -
                (Cs/Co)*(FS[X,1]-pre(FS[X,1]));

  der(c[X,Y]) = deff[X,Y]*((1 - c[X,Y])/2*d*d) + deff[X-1,Y]*((c[X-1,Y]- c[X,Y])/2*d*d) +
                deff[X,Y]*((1 - c[X,Y])/2*d*d) + deff[X,Y-1]*((c[X,Y-1]- c[X,Y])/2*d*d) -
                (Cs/Co)*(FS[X,Y]-pre(FS[X,Y]));
  end when;

  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)));
end concentration;
