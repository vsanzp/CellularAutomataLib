within CellularAutomataLib.Examples.CS_2D.Furnace;
model FurnaceInput
  import CellularAutomataLib.Components.*;
  CSFurnace fur1(X = 20, Y = 20, n_inputs = 1, name = "Furnace 1") annotation (
    Placement(transformation(extent={{-40,38},{0,78}})));
  ExtInputRegion ExternalInputRegion(
    XToRange={1,7},
    YToRange={20,20},
    Input_type=5,
    q_t=0.1,
    start_sample=0,
    redeclare function ExtInput = FURExtInput)
    annotation (Placement(transformation(extent={{-66,70},{-46,90}})));
  Modelica.Blocks.Sources.Constant const(k=1)   annotation (
    Placement(transformation(extent={{-92,70},{-72,90}})));
  CSFurnace fur2(X = 20, Y = 20, n_inputs = 1, name = "Furnace 2") annotation (
    Placement(transformation(extent={{34,-26},{74,14}})));
  InputRegion inputRegion(
    XFromRange={1,10},
    YFromRange={1,10},
    XTo=10,
    YTo=10,
    redeclare function SetInput = FURSetInput)
    annotation (Placement(transformation(extent={{20,70},{40,90}})));
  Components.Animation animation(
    WindowX=20,
    WindowY=20,
    redeclare function SetDisplayFunction = FURSetDisplay)
    annotation (Placement(transformation(extent={{0,-16},{20,4}})));
equation
  connect(const.y, ExternalInputRegion.u) annotation (Line(
      points={{-71,80},{-64,80}},
      color={0,0,127},
      smooth=Smooth.None));
  connect(ExternalInputRegion.TO, fur1.Space) annotation (Line(
      points={{-53,80},{-18,80}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(fur1.Space, inputRegion.FROM) annotation (Line(
      points={{-18,80},{25,80}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(inputRegion.TO, fur2.Space) annotation (Line(
      points={{35,80},{56,80},{56,16}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(animation.Space, fur2.Space) annotation (Line(points={{10,5},{
          10,26},{56,26},{56,16}},  color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=50, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>In this model two CSFurnace models are combined. The first model receives an externa input, analogous to the FurnaceExtInput model. The second furnace model receives an input from the firt furnace model, where the cells from the region (X=1..10, Y=1..10) are used as input for the equivalent region starting at (X=10, Y=10), so the region (X=10...20, Y=10..20) will receive the input.</p>
</html>"));
end FurnaceInput;
