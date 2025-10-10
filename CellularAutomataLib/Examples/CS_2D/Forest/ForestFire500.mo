within CellularAutomataLib.Examples.CS_2D.Forest;
model ForestFire500 "Forest fire model with inputs from the wind, output and animation"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.Interfaces.*;
  ForestCA Forest(name = "Forest", n_inputs = 3, init_cells = [400, 250], X = 500, Y = 500)                     annotation (
    Placement(transformation(extent = {{-20, -20}, {20, 20}})));
  ExtInputRegion Water(
    XToRange={250,500},
    YToRange={250,500},Input_type = 1, redeclare function ExtInput = ExtInput, input_id = 1, q_t = 0.5)                                                     annotation (
    Placement(transformation(extent = {{-62, 16}, {-18, 56}})));
  Modelica.Blocks.Sources.Step water(startTime = 70) annotation (
    Placement(transformation(extent = {{-94, 26}, {-74, 46}})));
  ExtInputRegion WindDir(
    XToRange={1,500},
    YToRange={1,500},                          Input_type = 1, redeclare
      function ExtInput =                                                                            ExtInput, input_id = 2)                         annotation (
    Placement(transformation(extent = {{-62, -20}, {-20, 20}})));
  Modelica.Blocks.Sources.Step winddir(startTime = 50, height = 270) annotation (
    Placement(transformation(extent = {{-94, -10}, {-74, 10}})));
  ExtInputRegion WindSpeed(
    XToRange={1,500},
    YToRange={1,500},                            Input_type = 1, redeclare
      function ExtInput =                                                                              ExtInput, input_id = 3)                         annotation (
    Placement(transformation(extent = {{-62, -56}, {-20, -16}})));
  Modelica.Blocks.Sources.Step windspeed(startTime = 50, height = 3) annotation (
    Placement(transformation(extent = {{-94, -46}, {-74, -26}})));
  OutputRegion FireSize(
    XFromRange={1,500},
    YFromRange={1,500}, Output_type = 5, redeclare function ExtOutput =         ExtOutput, output_rate = 1)                         annotation (
    Placement(transformation(extent = {{24, -16}, {56, 16}})));
  Animation animation(
    WindowX=500,
    WindowY=500,
    redeclare function SetDisplayFunction = SetDisplay)
    annotation (Placement(transformation(extent={{28,36},{48,56}})));
equation
  connect(Water.TO, Forest.Space) annotation (
    Line(points={{-26.8,36},{-20,36},{-20,22},{2,22}},                    color = {0, 0, 255}, smooth = Smooth.None));
  connect(water.y, Water.u) annotation (
    Line(points = {{-73, 36}, {-57.6, 36}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(winddir.y, WindDir.u) annotation (
    Line(points = {{-73, 0}, {-57.8, 0}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(windspeed.y, WindSpeed.u) annotation (
    Line(points = {{-73, -36}, {-57.8, -36}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(WindDir.TO, Forest.Space) annotation (
    Line(points={{-28.4,0},{-20,0},{-20,22},{2,22}},                    color = {0, 0, 255}, smooth = Smooth.None));
  connect(WindSpeed.TO, Forest.Space) annotation (
    Line(points={{-28.4,-36},{-20,-36},{-20,22},{2,22}},                    color = {0, 0, 255}, smooth = Smooth.None));
  connect(FireSize.FROM, Forest.Space) annotation (
    Line(points={{30.08,4.44089e-16},{30.08,22},{2,22}},  color = {0, 0, 255}, smooth = Smooth.None));
  connect(Forest.Space, animation.Space) annotation (Line(points={{2,22},
          {-2,22},{-2,57},{38,57}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=120, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}})),
    Documentation(info="<html>
<p>This model is composed of a ForestCA model combined with three external input region models used to change the direction and speed of the wind and the actions from the firefighters. Also, the model includes an output region model to observe the size of the fire and an animation model.</p>
<p>The size of the cellular space is 500x500, and the fire is started at cell [400,250].</p>
</html>"));
end ForestFire500;
