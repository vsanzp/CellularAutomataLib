within CellularAutomataLib.Examples.CS_3D.Simple;
model Rule445_Anim
  Rule445 rule445_1
    annotation (Placement(transformation(extent={{-40,-20},{-20,0}})));
  Components.Animation animation(
    WindowX=100,
    WindowY=100,
    WindowZ=100,
    redeclare function SetDisplayFunction = Display445,
    name="Clouds")
    annotation (Placement(transformation(extent={{2,-20},{22,0}})));
equation
  connect(rule445_1.Space, animation.Space)
    annotation (Line(points={{-29,1},{-29,10},{12,10},{12,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>Model that includes a Rule445 model and an Animation model.</p>
</html>"),
    experiment(StopTime=1, __Dymola_Algorithm="Dassl"));
end Rule445_Anim;
