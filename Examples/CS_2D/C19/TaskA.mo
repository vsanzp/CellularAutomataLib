within CellularAutomataLib.Examples.CS_2D.C19;
model TaskA
  import CellularAutomataLib.Components.*;
  Pollution pollution(X = 70) annotation (
    Placement(transformation(extent = {{-58, -2}, {-38, 18}})));
  OutputRegion MAXc0(
    XFromRange={10,10},
    YFromRange={20,20},                                              output_rate = 1, redeclare
      function ExtOutput =                                                                                                   ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent = {{-20, 40}, {0, 60}})));
  OutputRegion MAXc10(
    XFromRange={20,20},
    YFromRange={20,20},                       output_rate = 1,                         redeclare
      function ExtOutput =                                                                                                    ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent = {{-20, 20}, {0, 40}})));
  OutputRegion MAXc20(
    XFromRange={30,30},
    YFromRange={20,20},                       output_rate = 1,                         redeclare
      function ExtOutput =                                                                                                    ExtOutput, Output_type = 2) annotation (
    Placement(transformation(extent={{-20,2},{0,22}})));
  OutputRegionM C50(
    XFromRange={50,50},
    YFromRange={1,40},                                             output_rate = 1, redeclare
      function ExtOutput =                                                                                                 ExtOutput)
                                                                                                                                      annotation (
    Placement(transformation(extent = {{-20, -40}, {0, -20}})));
equation
  connect(pollution.Space, MAXc0.FROM) annotation (
    Line(points={{-47,19},{-47,30},{-28,30},{-28,50},{-10,50}},            color = {0, 0, 255}, smooth = Smooth.None));
  connect(pollution.Space, MAXc10.FROM) annotation (
    Line(points={{-47,19},{-47,30},{-10,30}},        color = {0, 0, 255}, smooth = Smooth.None));
  connect(pollution.Space, MAXc20.FROM) annotation (
    Line(points={{-47,19},{-47,30},{-28,30},{-28,12},{-10,12}},            color = {0, 0, 255}, smooth = Smooth.None));
  connect(C50.FROM, pollution.Space) annotation (
    Line(points={{-10,-30},{-28,-30},{-28,-28},{-47,-28},{-47,19}},            color = {0, 0, 255}, smooth = Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics),
    experiment(StopTime=1200, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Implementation of the Task A of the benchmark. This model includes a Pollution model and several output region models to observe the evolution of the pollutant spread.</p>
</html>"));
end TaskA;
