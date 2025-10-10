within CellularAutomataLib.Examples.CS_2D.Forest;
model ForestFire1000 "Forest fire with animation"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  ForestCA Forest(name = "Forest", n_inputs = 0, wrapped_borders = 3, X = 1000, Y = 1000,                     init_cells = [900, 500]) annotation (
    Placement(transformation(extent = {{-20, -20}, {20, 20}})));
  Animation animation(
    WindowX=1000,
    WindowY=1000,
    redeclare function SetDisplayFunction = SetDisplay)
    annotation (Placement(transformation(extent={{38,10},{58,30}})));
equation
  connect(Forest.Space, animation.Space)
    annotation (Line(points={{2,22},{2,31},{48,31}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=120, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}})),
    Documentation(info="<html>
<p>This model is composed of a ForestCA model and an animation model. The size of the cellular space is set to 1000x1000. The parameters of the fire spread (wind and firefighter actions) remain constant.</p>
</html>"));
end ForestFire1000;
