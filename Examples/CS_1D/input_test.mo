within CellularAutomataLib.Examples.CS_1D;
model input_test "Simple input test"
  CSR30 cSR30_1(
    n_inputs=0,
    wrapped_borders=0,
    name="Rule30_FROM",
    X=3,
    init_cells=[2],
    initial_step=0.1)
    annotation (Placement(transformation(extent={{-96,-18},{-38,22}})));
  CSR30 cSR30_2(
    n_inputs=1,
    wrapped_borders=0,
    name="Rule30_TO",
    X=10,
    init_cells=[2],
    initial_step=0.1)
    annotation (Placement(transformation(extent={{24,-10},{82,30}})));
   CellularAutomataLib.Components.InputRegion inputRegion(
    redeclare function SetInput = RSetInput,
    XFromRange={3,3},
    XTo=8) annotation (Placement(transformation(extent={{-20,22},{0,42}})));
  Components.Animation animation(
    initial_step=0.1,
    WindowX=10,
    WindowY=10,
    redeclare function SetDisplayFunction = RSetDisplay)
    annotation (Placement(transformation(extent={{78,58},{98,78}})));
equation
  connect(cSR30_1.Space, inputRegion.FROM) annotation (
    Line(points={{-64.1,24},{-64.1,32},{-15,32}},
                                          color = {0, 0, 255}, smooth = Smooth.None));
  connect(inputRegion.TO, cSR30_2.Space) annotation (
    Line(points={{-5,32},{20,32},{20,42},{55.9,42},{55.9,32}},
                                        color = {0, 0, 255}, smooth = Smooth.None));
  connect(cSR30_2.Space, animation.Space) annotation (Line(points={{55.9,32},
          {56,32},{56,79},{88,79}},
                                color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=10, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>This model is composed of two cellular spaces (two CSR30  models) that communicate using an Input Region model. </p>
<p>The size of the first space is X=3, and the second X=10. The input region translates the state of cell [3] from the first space to the cell [8] in the second space. </p>
<p>The animation model displays the evolution of the second space. </p>
</html>"));
end input_test;
