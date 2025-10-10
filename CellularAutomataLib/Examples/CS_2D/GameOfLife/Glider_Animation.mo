within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model Glider_Animation "GOL model with glider initialization and animation"
  extends Modelica.Icons.Example;

  CSGol_glider cSGol_glider
    annotation (Placement(transformation(extent={{-58,-20},{-38,0}})));
  Components.Basic.Animation animation(
    WindowX=50,
    WindowY=50,
    displayDelay=0,            redeclare function SetDisplayFunction =
        GOLSetDisplay)
    annotation (Placement(transformation(extent={{-20,-18},{0,2}})));
equation
  connect(cSGol_glider.Space, animation.Space) annotation (Line(points={{-47,1},
          {-48,1},{-48,6},{-10,6},{-10,3}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_glider model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
</html>"),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"));
end Glider_Animation;
