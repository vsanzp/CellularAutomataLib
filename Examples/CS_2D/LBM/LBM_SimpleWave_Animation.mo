within CellularAutomataLib.Examples.CS_2D.LBM;
model LBM_SimpleWave_Animation
  parameter Integer X = 100;
  parameter Integer Y = 100;
  LBM_SimpleWave simpleDiffusion(
    X=X,
    Y=Y,
    hex=0,
    wrapped_borders=11)
    annotation (Placement(transformation(extent={{-40,-18},{-20,2}})));
  Components.Animation animation(
    WindowX=X,
    WindowY=Y,
    displayDelay=100000,                                  redeclare function
      SetDisplayFunction =                                                                          LBMDisplay)
    annotation (Placement(transformation(extent={{-2,-20},{18,0}})));
equation
  connect(simpleDiffusion.Space, animation.Space)
    annotation (Line(points={{-29,3},{-29,14},{8,14},{8,1}},  color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=200, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>Model that includes the LBM_SimpleWave model and an Animation model to generate the graphical animation. The wave starts in the center of the cellular space and propagates. Wrapped boundary conditions are used. A display delay is also used in the animation to better observe the evolution of the wave.</p>
</html>"));
end LBM_SimpleWave_Animation;
