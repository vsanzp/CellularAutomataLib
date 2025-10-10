within CellularAutomataLib.Examples.CS_2D.C17;
model TaskA "ARGESIM C17 Task A"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Interfaces.*;
  FHPSIR fHPSIR(name = "FHPSIR") annotation (
    Placement(transformation(extent = {{-60, 40}, {-40, 60}})));
  OutputRegion FHPoutS(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = FHPOutputS)                                                                                        annotation (
    Placement(transformation(extent = {{-80, 66}, {-60, 86}})));
  OutputRegion FHPoutI(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
   redeclare function ExtOutput = FHPOutputI)                                                                                       annotation (
    Placement(transformation(extent = {{-60, 66}, {-40, 86}})));
  OutputRegion FHPoutR(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = FHPOutputR)                                                                                        annotation (
    Placement(transformation(extent = {{-40, 66}, {-20, 86}})));
  eqmodel SIReqn(I(start = 100), R(start = 0), S(start = 15000)) annotation (
    Placement(transformation(extent = {{-60, -40}, {-40, -20}})));
  HPPSIR hPPSIR(name = "HPPSIR") annotation (
    Placement(transformation(extent={{40,38},{60,58}})));
  OutputRegion HPPoutS(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
  redeclare function ExtOutput = HPPOutputS)                                                                                        annotation (
    Placement(transformation(extent = {{20, 66}, {40, 86}})));
  OutputRegion HPPoutI(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
   redeclare function ExtOutput = HPPOutputI)                                                                                       annotation (
    Placement(transformation(extent = {{40, 66}, {60, 86}})));
  OutputRegion HPPoutR(
    XFromRange={1,100},
    YFromRange={1,100},                        Output_type = 4, output_rate = 1,
   redeclare function ExtOutput = HPPOutputR)                                                                                       annotation (
    Placement(transformation(extent = {{60, 66}, {80, 86}})));
equation
  connect(fHPSIR.Space, FHPoutI.FROM) annotation (
    Line(points={{-49,61},{-49,68},{-56.2,68},{-56.2,76}},
                                          color = {0, 0, 255}, smooth = Smooth.None));
  connect(HPPoutS.FROM, hPPSIR.Space) annotation (
    Line(points={{23.8,76},{32,76},{32,59},{51,59}},        color = {0, 0, 255}, smooth = Smooth.None));
  connect(HPPoutI.FROM, hPPSIR.Space) annotation (
    Line(points={{43.8,76},{43.8,59},{51,59}},
                                        color = {0, 0, 255}, smooth = Smooth.None));
  connect(HPPoutR.FROM, hPPSIR.Space) annotation (
    Line(points={{63.8,76},{63.8,59},{51,59}},    color = {0, 0, 255}, smooth = Smooth.None));
  connect(FHPoutS.FROM, fHPSIR.Space) annotation (
    Line(points={{-76.2,76},{-76.2,61},{-49,61}},    color = {0, 0, 255}, smooth = Smooth.None));
  connect(FHPoutR.FROM, fHPSIR.Space) annotation (
    Line(points={{-36.2,76},{-36.2,61},{-49,61}},    color = {0, 0, 255}, smooth = Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model that implements the Task A of the benchmark. It compares the results of the differential equation, the HPP and the FHP models.</p>
</html>"));
end TaskA;
