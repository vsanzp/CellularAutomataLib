within CellularAutomataLib.Examples.CS_2D.Furnace;
model FurnaceExtInput "Furnace model with external input"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.Interfaces.*;
  CSFurnace fur(
    X=20,
    Y=20,
    n_inputs=1,
    initial_step=0)
                annotation (Placement(visible=true, transformation(
        origin={4,-2},
        extent={{-8,30},{32,70}},
        rotation=0)));
  ExtInputRegion extinputRegion(
    XToRange={10,10},
    YToRange={10,10},
    Input_type = 5,
    q_t=1,
    start_sample=0,
    redeclare function ExtInput = FURExtInput)                                                                                                                                        annotation (
    Placement(transformation(extent = {{-54, 48}, {-2, 86}})));
  Modelica.Blocks.Sources.Constant const(k=1)   annotation (
    Placement(transformation(extent={{-88,58},{-68,78}})));
  Animation animation(
    initial_step=0,
    WindowX=20,
    WindowY=20,
    redeclare function SetDisplayFunction = FURSetDisplay)
    annotation (Placement(transformation(extent={{60,40},{80,60}})));
equation
  connect(const.y, extinputRegion.u) annotation (
    Line(points={{-67,68},{-62,68},{-62,67},{-48.8,67}},          color = {0, 0, 127}, smooth = Smooth.None));
  connect(extinputRegion.TO, fur.Space) annotation (
    Line(points={{-12.4,67},{-4.1,67},{-4.1,70},{18,70}},          color = {0, 0, 255}));
  connect(fur.Space, animation.Space) annotation (Line(points={{18,70},
          {18,78},{70,78},{70,61}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=50, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>This model combines the Furnace_animation model with an external input, described using a model from the MSL (a constant signal) and an ExtInput model.</p>
<p>The temperature of the cells that receive the input is assigned with the value of the input.</p>
</html>"));
end FurnaceExtInput;
