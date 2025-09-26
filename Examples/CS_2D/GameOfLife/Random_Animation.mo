within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model Random_Animation "Random GOL model with animation"
  extends Modelica.Icons.Example;
  CSGol_random cSGol_random
    annotation (Placement(transformation(extent={{-58,-10},{-38,10}})));
  CellularAutomataLib.Components.Basic.Animation animation(
    WindowX=100,
    WindowY=100,
    displayDelay=0,
    name="GOL_random",
    save_video=true,              redeclare function SetDisplayFunction =
        GOLSetDisplay)
    annotation (Placement(transformation(extent={{-22,-10},{-2,10}})));
equation
  connect(cSGol_random.Space, animation.Space) annotation (Line(points={{-47,11},
          {-48,11},{-48,16},{-12,16},{-12,11}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_random model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
</html>"),
    experiment(StopTime=250, __Dymola_Algorithm="Dassl"));
end Random_Animation;
