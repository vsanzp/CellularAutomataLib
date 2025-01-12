within CellularAutomataLib.Examples.CS_2D.CHIPS.SignalGenerators;
model noiseGen
  import Modelica.Constants.*;
  constant Real m = 2^31 - 1;
  constant Real a = 7^5;
  constant Real c = 10;
  parameter Modelica.Units.SI.Time Ts = 0.1 "sampling time";
  parameter Real amp = 0.01 "amplitude";
  parameter Real Tf = 1 "1st order filter TC";
  discrete Real x;
  discrete Real u;
  Modelica.Blocks.Interfaces.RealOutput y annotation (
    Placement(transformation(extent = {{60, -22}, {100, 22}}, rotation = 0)));
algorithm
  when noEvent(sample(0, Ts)) then
    x := (a*x + c) - div((a*x + c), m)*m;
    u := (x/2e9 - 0.5)*amp;
    y := (Tf*y + Ts*u)/(Tf + Ts);
  end when;
  when initial() then
    x := 1.0;
  end when;
  annotation (
    Icon(graphics={  Rectangle(extent = {{-100, 100}, {100, -100}}, lineColor = {0, 0, 0}, fillColor = {215, 215, 215}, fillPattern = FillPattern.Solid), Text(extent = {{-100, 76}, {84, -62}}, lineColor = {0, 0, 0}, fillColor = {215, 215, 215}, fillPattern = FillPattern.Solid, textString = "Noise")}));
end noiseGen;
