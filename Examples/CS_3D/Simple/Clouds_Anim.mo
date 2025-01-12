within CellularAutomataLib.Examples.CS_3D.Simple;
model Clouds_Anim
  Clouds1 clouds1_1( X=100,Y=100,Z=100)
    annotation (Placement(transformation(extent={{-40,-20},{-20,0}})));
  Components.Animation animation(
    WindowX=100,
    WindowY=100,
    WindowZ=100,
    redeclare function SetDisplayFunction = CloudsDisplay,
    name="Clouds")
    annotation (Placement(transformation(extent={{2,-20},{22,0}})));
equation
  connect(clouds1_1.Space, animation.Space)
    annotation (Line(points={{-29,1},{-29,10},{12,10},{12,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>Model that combines Clouds1 with an Animation model.</p>
</html>"),
    experiment(StopTime=1, __Dymola_Algorithm="Dassl"));
end Clouds_Anim;
