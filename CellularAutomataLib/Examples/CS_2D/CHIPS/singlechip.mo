within CellularAutomataLib.Examples.CS_2D.CHIPS;
model singlechip "Complete Chip CA model with sources, interfaces and animation"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.Interfaces.*;
    parameter Integer X = 10;
  parameter Integer Y = 10;
  parameter Real RATE = 0.001;
  Single_chip Chip(name = "Chip", X = X, Y = Y, init_cells = fill(0, 0, 2), wrapped_borders = 0, initial_step = 0, Tstep = RATE,                                      n_inputs = 4)                     annotation (
    Placement(transformation(extent={{8,-40},{48,-10}})));
  ExtInputRegion Pext1(
    XToRange={1,1},
    YToRange={3,3},    Input_type = 5,                                             q_t = RATE, redeclare
      function ExtInput =
        CHIPExtInput,                                                                                                                              input_id = 3) annotation (
    Placement(transformation(extent={{-16,-28},{4,-8}})));
  ExtInputRegion Pext2(
    XToRange={6,6},
    YToRange={6,6},                                                Input_type = 5, q_t = RATE, redeclare
      function ExtInput =
        CHIPExtInput,                                                                                                                              input_id = 4) annotation (
    Placement(transformation(extent={{-16,-48},{4,-28}})));
  Modelica.Blocks.Math.Gain Pg1(k = 1/100) annotation (
    Placement(transformation(extent = {{-4, -4}, {4, 4}}, rotation = 0, origin = {-20, -18})));
  SignalGenerators.Trapezoid3sin0100 lG1(ampT = 60, risingT = 1, widthT = 5, fallingT = 1, periodT = 10, offsetT = 20, ampS1 = 10, ampS2 = 5, ampS3 = 6, offsetS1 = 0, offsetS2 = 0, offsetS3 = 0, periodS1 = 4, periodS2 = 10, periodS3 = 12) annotation (
    Placement(transformation(extent = {{-7, -6}, {7, 6}}, rotation = 0, origin = {-37, -18})));
  Modelica.Blocks.Math.Gain Pg2(k = 0.5/100) annotation (
    Placement(transformation(extent = {{-4, -4}, {4, 4}}, rotation = 0, origin = {-20, -38})));
  SignalGenerators.Trapezoid3sin0100 lG2(risingT = 1, fallingT = 1, offsetS3 = 3, ampT = 50, widthT = 20, periodT = 50, offsetT = 10, ampS1 = 4, offsetS2 = 0, ampS3 = 0, offsetS1 = 0, ampS2 = 30, periodS2 = 100, periodS1 = 1, periodS3 = 30) annotation (
    Placement(transformation(extent = {{-7.5, -6.5}, {7.5, 6.5}}, rotation = 0, origin = {-36.5, -37.5})));
  ExtInitRegion InitTemp(
    XRange={1,X},
    YRange={1,Y},                            redeclare function ExtInit =
        CHIPExtInit)                                                                                 annotation (
    Placement(transformation(extent = {{-22, 2}, {-2, 22}})));
  Modelica.Blocks.Sources.Constant const(k = 20) annotation (
    Placement(transformation(extent = {{-36, 6}, {-24, 18}})));
  Cair Air(
    X=X,
    Y=Y,   name = "Air",                             init_cells = fill(0, 0, 2), Tstep = RATE,                     n_inputs = 1) annotation (
    Placement(transformation(extent = {{-24, 26}, {8, 46}})));
  InputRegion chipI2Air(
    XFromRange={1,X},
    YFromRange={1,Y},                                                     comm_rate = RATE, redeclare
      function SetInput =
        CHIPSetInput)                                                                                                                           annotation (
    Placement(transformation(extent = {{-20, -10}, {20, 10}}, rotation = 90, origin = {-42, 36})));
  InputRegion Air2Chip(
    XFromRange={1,X},
    YFromRange={1,Y},                              input_id = 1, comm_rate = RATE, redeclare
      function SetInput =
        CHIPSetInput)                                                                                                                        annotation (
    Placement(transformation(extent = {{-20, -10}, {20, 10}}, rotation = 270, origin = {30, 36})));
  OutputRegion chipTEMP(
    XFromRange={1,X},
    YFromRange={1,Y},                       Output_type = 4, output_rate = RATE, redeclare
      function ExtOutput =
        CHIPExtOutput)                                                                                                                       annotation (
    Placement(transformation(extent={{2,2},{24,22}})));
  Animation animation(
    Tstep=RATE,
    WindowX=X,
    WindowY=Y, redeclare function SetDisplayFunction=CHIPSetDisplay)
    annotation (Placement(transformation(extent={{54,-30},{74,-10}})));
equation
  connect(lG1.y, Pg1.u) annotation (
    Line(points = {{-31.4, -18}, {-24.8, -18}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(Pg1.y, Pext1.u) annotation (
    Line(points={{-15.6,-18},{-14,-18}},      color = {0, 0, 127}, smooth = Smooth.None));
  connect(lG2.y, Pg2.u) annotation (
    Line(points = {{-30.5, -37.5}, {-30.5, -38}, {-24.8, -38}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(Pg2.y, Pext2.u) annotation (
    Line(points={{-15.6,-38},{-14,-38}},      color = {0, 0, 127}, smooth = Smooth.None));
  connect(const.y, InitTemp.u) annotation (
    Line(points = {{-23.4, 12}, {-20, 12}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(chipI2Air.TO, Air.Space) annotation (
    Line(points={{-42,48},{-42,52},{-6.4,52},{-6.4,47}},      color = {0, 0, 255}, smooth = Smooth.None));
  connect(Air.Space, Air2Chip.FROM) annotation (
    Line(points={{-6.4,47},{-6.4,52},{30,52},{30,48}},      color = {0, 0, 255}, smooth = Smooth.None));
  connect(chipI2Air.FROM, Chip.Space) annotation (
    Line(points={{-42,24},{-42,0},{30,0},{30,-8.5}},           color = {0, 0, 255}, smooth = Smooth.None));
  connect(Air2Chip.TO, Chip.Space) annotation (
    Line(points={{30,24},{30,-8.5}},                         color = {0, 0, 255}, smooth = Smooth.None));
  connect(InitTemp.TO, Chip.Space) annotation (
    Line(points={{-6,12},{0,12},{0,0},{30,0},{30,-8.5}},             color = {0, 0, 255}, smooth = Smooth.None));
  connect(chipTEMP.FROM, Chip.Space) annotation (
    Line(points={{6.18,12},{0,12},{0,0},{30,0},{30,-8.5}},           color = {0, 0, 255}, smooth = Smooth.None));
  connect(Pext1.TO, Chip.Space) annotation (
    Line(points={{0,-18},{4,-18},{4,-6},{30,-6},{30,-8.5}},              color = {0, 0, 255}, smooth = Smooth.None));
  connect(Pext2.TO, Chip.Space) annotation (
    Line(points={{0,-38},{4,-38},{4,-6},{30,-6},{30,-8.5}},              color = {0, 0, 255}, smooth = Smooth.None));
  connect(Chip.Space, animation.Space) annotation (Line(points={{30,-8.5},
          {30,0},{64,0},{64,-9}},
                            color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=10, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}})),
    Documentation(info="<html>
<p>This model combines a Single_chip and a Cair models to describe the heat diffusion on the chip and the surrounding air. The chip receives external inputs as sources of power. The chip and the air are connected using Input Region models. The output region model is used to observe the evolution of the temperature together with an animation model.</p>
</html>"));
end singlechip;
