within CellularAutomataLib.Examples.CS_2D.C17;
model TaskC "ARGESIM C17 Task C"
    extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Interfaces.*;
  FHPSIRRearrange fHPSIR(name = "FHPSIR") annotation (
    Placement(transformation(extent = {{-60, 40}, {-40, 60}})));
  OutputRegion SIRrearrangeI(XFromRange = {0,100}, YFromRange = {0,100}, Output_type = 4, output_rate = 1, redeclare
      function ExtOutput =                                                                                                    FHPOutputI)
                                                                                                                                          annotation (
    Placement(transformation(extent = {{-60, 66}, {-40, 86}})));
  eqmodel Eqnmodel(I(start = 1000), R(start = 0), S(start = 40000)) annotation (
    Placement(transformation(extent = {{-60, -40}, {-40, -20}})));
  FHPSIR fHPSIR1(name = "FHPSIR") annotation (
    Placement(transformation(extent={{32,40},{52,60}})));
  OutputRegion SIR(XFromRange = {0,100}, YFromRange = {0,100}, Output_type = 4, output_rate = 1, redeclare
      function ExtOutput =                                                                                          FHPOutputI)
                                                                                                                                annotation (
    Placement(transformation(extent = {{32, 66}, {52, 86}})));
  diffeqmodel Diffeqmodel(S(start = 40000), I(start = 1000), r = 0.00003) annotation (
    Placement(transformation(extent = {{-60, 0}, {-40, 20}})));
equation
  connect(fHPSIR.Space, SIRrearrangeI.FROM) annotation (
    Line(points={{-49,61},{-49,68},{-56.2,68},{-56.2,76}},
                                          color = {0, 0, 255}, smooth = Smooth.None));
  connect(fHPSIR1.Space, SIR.FROM) annotation (
    Line(points={{43,61},{43,68},{35.8,68},{35.8,76}},
                                        color = {0, 0, 255}, smooth = Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model that implements the Task C of the benchmark. This model compares the FHP model, with and without rearrangement, with both equation models.</p>
</html>"));
end TaskC;
