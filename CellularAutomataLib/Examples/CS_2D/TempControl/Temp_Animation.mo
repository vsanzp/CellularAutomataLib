within CellularAutomataLib.Examples.CS_2D.TempControl;
model Temp_Animation "Simple temperature diffusion model with animation"
  extends Modelica.Icons.Example;
  parameter Integer x = 30;
  parameter Integer y = 15;
  TempDiff tempDiff(X=x, Y=y,
    Tstep=1)
    annotation (Placement(transformation(extent={{-20,-2},{0,18}})));
  Components.Basic.Animation animation(
    WindowHeight=500,
    WindowX=x,
    WindowY=y,
    displayDelay=100000,                redeclare function SetDisplayFunction =
        TEMPDisplay)
    annotation (Placement(transformation(extent={{20,0},{40,20}})));
equation
  connect(tempDiff.Space, animation.Space)
    annotation (Line(points={{-9,19},{-9,21},{30,21}}, color={28,108,200}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)));
end Temp_Animation;
