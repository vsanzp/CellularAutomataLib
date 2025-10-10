within CellularAutomataLib.Examples.CS_2D.C19;
model TaskB "ARGESIM C19 model Task B"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Interfaces.*;
  Pollution pollution(n_inputs = 2, X = 70) annotation (
    Placement(transformation(extent = {{-12, 0}, {8, 20}})));
  OutputRegion MAXc0(
    XFromRange={10,10},
    YFromRange={20,20},                                              output_rate = 1, redeclare
      function ExtOutput =                                                                                                   ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent = {{26, 42}, {46, 62}})));
  OutputRegion MAXc10(
    XFromRange={20,20},
    YFromRange={20,20},                       output_rate = 1,                         redeclare
      function ExtOutput =                                                                                                  ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent={{26,24},{46,44}})));
  OutputRegion MAXc20(
    XFromRange={30,30},
    YFromRange={20,20},                       output_rate = 1,                         redeclare
      function ExtOutput =                                                                                                    ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent = {{26, 2}, {46, 22}})));
  OutputRegionM C50(
    XFromRange={50,50},
    YFromRange={1,40},                                             output_rate = 1, redeclare
      function ExtOutput =                                                                                                 ExtOutput)
                                                                                                                                      annotation (
    Placement(transformation(extent = {{26, -38}, {46, -18}})));
  ExtInputRegion PlantA(
    XToRange={35,45},
    YToRange={10,20},                                                   Input_type = 5, q_t = 1, redeclare
      function ExtInput =                                                                                                              ExtInput) annotation (
    Placement(transformation(extent = {{-60, 20}, {-40, 40}})));
  ExtInputRegion PlantB(
    XToRange={35,45},
    YToRange={20,30},                           Input_type = 5, q_t = 1,                         input_id = 2, redeclare
      function ExtInput =                                                                                                                            ExtInput) annotation (
    Placement(transformation(extent = {{-60, -20}, {-40, 0}})));
  Modelica.Blocks.Sources.Constant const(k = 2) annotation (
    Placement(transformation(extent = {{-90, 18}, {-70, 38}})));
equation
  connect(pollution.Space, MAXc0.FROM) annotation (
    Line(points={{-1,21},{-1,32},{18,32},{18,52},{29.8,52}},          color = {0, 0, 255}, smooth = Smooth.None));
  connect(pollution.Space, MAXc10.FROM) annotation (
    Line(points={{-1,21},{-1,34},{29.8,34}},      color = {0, 0, 255}, smooth = Smooth.None));
  connect(pollution.Space, MAXc20.FROM) annotation (
    Line(points={{-1,21},{-1,32},{18,32},{18,12},{29.8,12}},          color = {0, 0, 255}, smooth = Smooth.None));
  connect(C50.FROM, pollution.Space) annotation (
    Line(points={{29.8,-28},{18,-28},{18,-26},{-1,-26},{-1,21}},          color = {0, 0, 255}, smooth = Smooth.None));
  connect(PlantA.TO, pollution.Space) annotation (
    Line(points={{-44,30},{-24,30},{-24,21},{-1,21}},          color = {0, 0, 255}, smooth = Smooth.None));
  connect(PlantB.TO, pollution.Space) annotation (
    Line(points={{-44,-10},{-24,-10},{-24,21},{-1,21}},          color = {0, 0, 255}, smooth = Smooth.None));
  connect(const.y, PlantA.u) annotation (
    Line(points = {{-69, 28}, {-64, 28}, {-64, 30}, {-58, 30}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(const.y, PlantB.u) annotation (
    Line(points = {{-69, 28}, {-69, 10}, {-58, 10}, {-58, -10}}, color = {0, 0, 127}, smooth = Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics),
    experiment(StopTime=1300, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Implementation of the Task B of the benchmark. Additionally to Task A, this model also includes two external input functions that activate pollution reduction actions. </p>
</html>"));
end TaskB;
