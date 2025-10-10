within CellularAutomataLib.Examples.CS_1D;
model CSR110_Animation "Rule 110 model with animation"
    extends Modelica.Icons.Example;
     import CellularAutomataLib.Components.Basic.*;
  CSR110 cSR110_1(initial_step=1)
    annotation (Placement(transformation(extent={{-60,0},{-40,20}})));
  Animation animation(
    initial_step=0,
    WindowX=100,
    WindowY=100,
    name="WolframR110",
    save_video=true,
  redeclare function SetDisplayFunction = RSetDisplay)
    annotation (Placement(transformation(extent={{-18,-2},{2,18}})));
equation
  connect(cSR110_1.Space, animation.Space) annotation (Line(points={{-49,21},{
          -50,21},{-50,28},{-8,28},{-8,19}},
                                           color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>This model combines the CSR110 model with the Animation model to generate the graphical animation during the simulation.</p>
<p>The RSetDisplay function is used as <i>Display</i> function.</p>
</html>"));
end CSR110_Animation;
