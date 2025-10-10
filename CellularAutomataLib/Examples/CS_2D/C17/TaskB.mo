within CellularAutomataLib.Examples.CS_2D.C17;
model TaskB "ARGESIM C17 Task B"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Interfaces.*;
  FHPSIRfull fHPSIRfull(name = "FHPSIRfull") annotation (
    Placement(transformation(extent = {{-60, 38}, {-40, 58}})));
  OutputRegion Ifull(
    XFromRange={1,100},
    YFromRange={1,100},                      Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = FHPOutputI)                                                                                      annotation (
    Placement(transformation(extent = {{-32, 52}, {-12, 72}})));
  eqmodel eqmodel1(S(start = 12000), R(start = 4000)) annotation (
    Placement(transformation(extent = {{40, 40}, {60, 60}})));
  FHPSIRhalf fHPSIRhalf(name = "FHPSIRhalf") annotation (
    Placement(transformation(extent = {{-56, -30}, {-36, -10}})));
  OutputRegion Ihalf(
    XFromRange={1,100},
    YFromRange={1,100},                      Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = FHPOutputI)                                                                                      annotation (
    Placement(transformation(extent = {{-32, -16}, {-12, 4}})));
  FHPSIRborder fHPSIRborder(name = "FHPSIborder") annotation (
    Placement(transformation(extent={{42,-28},{62,-8}})));
  OutputRegion Iborder(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = FHPOutputI)                                                                                        annotation (
    Placement(transformation(extent = {{68, -16}, {88, 4}})));
equation
  connect(fHPSIRfull.Space, Ifull.FROM) annotation (
    Line(points={{-49,59},{-49,62},{-28.2,62}},      color = {0, 0, 255}, smooth = Smooth.None));
  connect(fHPSIRhalf.Space, Ihalf.FROM) annotation (
    Line(points={{-45,-9},{-45,-6},{-28.2,-6}},       color = {0, 0, 255}, smooth = Smooth.None));
  connect(fHPSIRborder.Space, Iborder.FROM) annotation (
    Line(points={{53,-7},{53,-6},{71.8,-6}},       color = {0, 0, 255}, smooth = Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model to implement the Task B of the benchmark. This model compares the evolution of the differential equation and the FHP models, with different vaccination approaches. </p>
</html>"));
end TaskB;
