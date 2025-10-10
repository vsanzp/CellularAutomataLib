within CellularAutomataLib.Examples.CS_2D.CHIPS.SignalGenerators;
model Trapezoid3sinNoise0100 "Heat source model 2"
  Modelica.Blocks.Sources.Trapezoid trapezoid(amplitude = ampT, rising = risingT, width = widthT, falling = fallingT, period = periodT, offset = offsetT, startTime = startTimeT) annotation (
    Placement(transformation(extent = {{-80, 50}, {-60, 70}}, rotation = 0)));
  Modelica.Blocks.Sources.Sine sine1(amplitude = ampS1, f = 1/periodS1, offset = offsetS1, startTime = startTimeS1) annotation (
    Placement(transformation(extent = {{-80, 20}, {-60, 40}}, rotation = 0)));
  Modelica.Blocks.Sources.Sine sine2(amplitude = ampS2, f = 1/periodS2, offset = offsetS2, startTime = startTimeS2) annotation (
    Placement(transformation(extent = {{-80, -10}, {-60, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Sine sine3(amplitude = ampS3, f = 1/periodS3, offset = offsetS3, startTime = startTimeS3) annotation (
    Placement(transformation(extent = {{-80, -40}, {-60, -20}}, rotation = 0)));
  noiseGen noiseGen1(Ts = TsN, amp = ampN, Tf = TfN) annotation (
    Placement(transformation(extent = {{-80, -70}, {-60, -50}}, rotation = 0)));
  parameter Real ampT = 1;
  parameter Modelica.Units.SI.Time risingT = 0;
  parameter Modelica.Units.SI.Time widthT = 0.5;
  parameter Modelica.Units.SI.Time fallingT = 0;
  parameter Modelica.Units.SI.Time periodT = 1;
  parameter Real offsetT = 0;
  parameter Modelica.Units.SI.Time startTimeT = 0;
  parameter Real ampS1 = 1;
  parameter Modelica.Units.SI.Time periodS1 = 1;
  parameter Real offsetS1 = 0;
  parameter Modelica.Units.SI.Time startTimeS1 = 0;
  parameter Real ampS2 = 1;
  parameter Modelica.Units.SI.Time periodS2 = 1;
  parameter Real offsetS2 = 0;
  parameter Modelica.Units.SI.Time startTimeS2 = 0;
  parameter Real ampS3 = 1;
  parameter Modelica.Units.SI.Time periodS3 = 1;
  parameter Real offsetS3 = 0;
  parameter Modelica.Units.SI.Time startTimeS3 = 0;
  parameter Modelica.Units.SI.Time TsN = 0.1;
  parameter Real ampN = 0.01;
  parameter Real TfN = 1;
  Modelica.Blocks.Math.Add3 add31 annotation (
    Placement(transformation(extent = {{-40, 20}, {-20, 40}}, rotation = 0)));
  Modelica.Blocks.Math.Add add1 annotation (
    Placement(transformation(extent = {{-40, -46}, {-20, -26}}, rotation = 0)));
  Modelica.Blocks.Math.Add add2 annotation (
    Placement(transformation(extent = {{0, 14}, {20, 34}}, rotation = 0)));
  Modelica.Blocks.Nonlinear.Limiter lim0100(uMax = 100, uMin = 0) annotation (
    Placement(transformation(extent = {{36, 14}, {56, 34}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation (
    Placement(transformation(extent = {{60, -20}, {100, 20}}, rotation = 0)));
equation
  connect(sine1.y, add31.u2) annotation (
    Line(points = {{-59, 30}, {-42, 30}}, color = {0, 0, 127}));
  connect(trapezoid.y, add31.u1) annotation (
    Line(points = {{-59, 60}, {-50, 60}, {-50, 38}, {-42, 38}}, color = {0, 0, 127}));
  connect(sine2.y, add31.u3) annotation (
    Line(points = {{-59, 6.10623e-16}, {-50, 6.10623e-16}, {-50, 22}, {-42, 22}}, color = {0, 0, 127}));
  connect(sine3.y, add1.u1) annotation (
    Line(points = {{-59, -30}, {-42, -30}}, color = {0, 0, 127}));
  connect(noiseGen1.y, add1.u2) annotation (
    Line(points = {{-62, -60}, {-50, -60}, {-50, -42}, {-42, -42}}, color = {0, 0, 127}));
  connect(add31.y, add2.u1) annotation (
    Line(points = {{-19, 30}, {-2, 30}}, color = {0, 0, 127}));
  connect(add1.y, add2.u2) annotation (
    Line(points = {{-19, -36}, {-14, -36}, {-14, 18}, {-2, 18}}, color = {0, 0, 127}));
  connect(add2.y, lim0100.u) annotation (
    Line(points = {{21, 24}, {34, 24}}, color = {0, 0, 127}));
  connect(lim0100.y, y) annotation (
    Line(points = {{57, 24}, {62, 24}, {62, 1.11022e-15}, {80, 1.11022e-15}}, color = {0, 0, 127}));
  annotation (
    Diagram(graphics),
    Icon(graphics={  Rectangle(extent = {{-100, 100}, {100, -100}}, lineColor = {0, 0, 0}, fillColor = {215, 215, 215}, fillPattern = FillPattern.Solid), Text(extent = {{-84, 54}, {50, -52}}, lineColor = {0, 0, 0}, fillColor = {215, 215, 215}, fillPattern = FillPattern.Solid, textString = "T+3S+N")}));
end Trapezoid3sinNoise0100;
