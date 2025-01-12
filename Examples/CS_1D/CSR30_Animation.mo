within CellularAutomataLib.Examples.CS_1D;
model CSR30_Animation
  CSR30 cSR30_1(initial_step=0)
    annotation (Placement(transformation(extent={{-60,0},{-40,20}})));
  Components.Animation animation(
    initial_step=0,
    WindowX=100,
    WindowY=100,
    name="Wolfram R30",
  redeclare function SetDisplayFunction = RSetDisplay)
    annotation (Placement(transformation(extent={{-20,0},{0,20}})));
equation
  connect(cSR30_1.Space, animation.Space) annotation (Line(points={{-49,21},
          {-50,21},{-50,28},{-10,28},{-10,21}},
                                           color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>This model combines the CSR30 model with the Animation model to generate the graphical animation during the simulation.</p>
<p>The RSetDisplay function is used as Display function.</p>
</html>"));
end CSR30_Animation;
