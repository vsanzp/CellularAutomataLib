within CellularAutomataLib.Examples.CS_2D.Furnace;
model Furnace_Animation "Furnace model with animation"
  extends Modelica.Icons.Example;
  CSFurnace cSFurnace
    annotation (Placement(transformation(extent={{-60,-20},{-40,0}})));
  CellularAutomataLib.Components.Basic.Animation animation(WindowX=50, WindowY=50, redeclare
      function SetDisplayFunction =
        FURSetDisplay)
    annotation (Placement(transformation(extent={{-20,-20},{0,0}})));
equation
  connect(cSFurnace.Space, animation.Space) annotation (Line(points={{-49,1},{-50,
          1},{-50,6},{-10,6},{-10,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model combines a CSFurnace model with the Animation component to generate the animation for the evolution of temperatures.</p>
</html>"),
    experiment(StopTime=200, __Dymola_Algorithm="Dassl"));
end Furnace_Animation;
