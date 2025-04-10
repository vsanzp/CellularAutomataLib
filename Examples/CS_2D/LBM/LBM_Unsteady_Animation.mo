within CellularAutomataLib.Examples.CS_2D.LBM;
model LBM_Unsteady_Animation
  parameter Integer X = 250;
  parameter Integer Y = 50;
  LBM_Unsteady unsteady(
    X=X,
    Y=Y,
    hex=0,
    wrapped_borders=10)
    annotation (Placement(transformation(extent={{-40,-18},{-20,2}})));
  Components.Animation animation(
    WindowX=X,
    WindowY=Y,
    displayDelay=10000,
    name="Unsteady",
    save_video=true,                                     redeclare function
      SetDisplayFunction =                                                                          LBMDisplay)
    annotation (Placement(transformation(extent={{-2,-20},{18,0}})));
equation
  connect(unsteady.Space, animation.Space)
    annotation (Line(points={{-29,3},{-29,14},{8,14},{8,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes an LBM_Unstead model and an Animation model to simulate the Von Karman vortex street.</p>
</html>"),
    experiment(StopTime=5000, __Dymola_Algorithm="Dassl"));
end LBM_Unsteady_Animation;
