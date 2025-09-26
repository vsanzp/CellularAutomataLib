within CellularAutomataLib.Examples.CS_3D.Simple;
model Rule445_Anim "Rule 445 model with animation"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;

  parameter Integer X= 15;
  parameter Integer Y= 15;
  parameter Integer Z= 15;

  Rule445 rule445_1(X=X,Y=Y,Z=Z) annotation (Placement(transformation(extent={{-40,-20},{-20,0}})));
  Animation animation(
    WindowWidth=1000,
    WindowHeight=1000,
    WindowX=X,
    WindowY=Y,
    WindowZ=Z,
    redeclare function SetDisplayFunction = Display445,
    name="Clouds")
    annotation (Placement(transformation(extent={{2,-18},{22,2}})));
equation
  connect(rule445_1.Space, animation.Space)
    annotation (Line(points={{-29,1},{-29,10},{12,10},{12,3}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>Model that includes a Rule445 model and an Animation model.</p>
</html>"),
    experiment(StopTime=1, __Dymola_Algorithm="Dassl"));
end Rule445_Anim;
