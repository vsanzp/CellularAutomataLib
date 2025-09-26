within CellularAutomataLib.Examples.CS_2D.Epidemics;
model Epidemics50 "Epidemic model with outputs and animation"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.Interfaces.*;
  EpidemicsCA epidemicsCA(                name = "Epidemics", X = 50, Y = 50, init_cells = {{25, 25}})                        annotation (
    Placement(transformation(extent = {{-24, -2}, {20, 42}})));
  OutputRegion S(
    XFromRange={1,50},
    YFromRange={1,50},
    Output_type=4,                output_rate = 1, redeclare function
      ExtOutput =                                                                         ExtOutputS)
                                                                                                                            annotation (
    Placement(transformation(extent = {{40, 30}, {60, 50}})));
  OutputRegion I(
    XFromRange={1,50},
    YFromRange={1,50},
    Output_type=4,                output_rate = 1, redeclare function
      ExtOutput =                                                                         ExtOutputI)
                                                                                                                            annotation (
    Placement(transformation(extent = {{40, 12}, {60, 32}})));
  OutputRegion R(
    XFromRange={1,50},
    YFromRange={1,50},
    Output_type=4,                output_rate = 1, redeclare function
      ExtOutput =                                                                         ExtOutputR)
                                                                                                                            annotation (
    Placement(transformation(extent = {{40, -6}, {60, 14}})));
  Animation animation(
    WindowX=50,
    WindowY=50,
    displayDelay=5000,
    redeclare function SetDisplayFunction = SetDisplay)
    annotation (Placement(transformation(extent={{-60,18},{-40,38}})));
equation
  connect(epidemicsCA.Space, S.FROM) annotation (
    Line(points={{0.2,44.2},{24,44.2},{24,40},{43.8,40}},       color = {0, 0, 255}, smooth = Smooth.None));
  connect(I.FROM, epidemicsCA.Space) annotation (
    Line(points={{43.8,22},{24,22},{24,44.2},{0.2,44.2}},       color = {0, 0, 255}, smooth = Smooth.None));
  connect(R.FROM, epidemicsCA.Space) annotation (
    Line(points={{43.8,4},{24,4},{24,44.2},{0.2,44.2}},       color = {0, 0, 255}, smooth = Smooth.None));
  connect(animation.Space, epidemicsCA.Space) annotation (Line(points={
          {-50,39},{-50,54},{0.2,54},{0.2,44.2}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=30, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Epidemic model that includes the animation and three output region models to observe the variation of S, I and R.</p>
</html>"));
end Epidemics50;
