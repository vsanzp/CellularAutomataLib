within CellularAutomataLib.Examples.CS_2D.Furnace;
model FurnaceOutput "Furnace model with output"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.Interfaces.*;
  CSFurnace fur(X = 20, Y = 20, n_inputs = 1) annotation (
    Placement(transformation(extent = {{-38, 24}, {2, 64}})));
  ExtInputRegion inputRegion(
    XToRange={1,7},
    YToRange={20,20},                  Input_type = 5, q_t = 0.1,                                     redeclare
      function ExtInput =
        FURExtInput)                                                                                                                                     annotation (
    Placement(transformation(extent = {{-66, 52}, {-46, 72}})));
  Modelica.Blocks.Sources.Constant const(k=1)   annotation (
    Placement(transformation(extent = {{-88, 52}, {-68, 72}})));
  OutputRegion outputAVG(
    XFromRange={1,15},
    YFromRange={20,20},  output_rate = 1,                                    redeclare
      function ExtOutput =
        FURExtOutput,                                                                                                                         Output_type = 1) annotation (
    Placement(transformation(extent = {{12, 50}, {42, 74}})));
  Animation animation(
    WindowX=20,
    WindowY=20,
    redeclare function SetDisplayFunction = FURSetDisplay)
    annotation (Placement(transformation(extent={{16,2},{36,22}})));
equation
  connect(const.y, inputRegion.u) annotation (
    Line(points = {{-67, 62}, {-64, 62}}, color = {0, 0, 127}, smooth = Smooth.None));
  connect(inputRegion.TO, fur.Space) annotation (
    Line(points={{-50,62},{-34,62},{-34,66},{-16,66}},
                                          color = {0, 0, 255}, smooth = Smooth.None));
  connect(outputAVG.FROM, fur.Space) annotation (
    Line(points={{17.7,62},{6,62},{6,66},{-16,66}},
                                         color = {0, 0, 255}, smooth = Smooth.None));
  connect(animation.Space, fur.Space) annotation (Line(points={{26,23},
          {26,46},{8,46},{8,62},{6,62},{6,66},{-16,66}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=50, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>In this model the FurnaceExtInput model is extended with an ExtOutput model to observe the average temperature of a region of cells.</p>
<p>However, the input region is assigned to the top row (X=1..7, Y =20). and the output is generated from the region (X = 1..15, Y = 20).</p>
</html>"));
end FurnaceOutput;
