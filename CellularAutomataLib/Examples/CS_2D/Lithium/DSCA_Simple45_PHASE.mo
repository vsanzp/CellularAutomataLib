within CellularAutomataLib.Examples.CS_2D.Lithium;
model DSCA_Simple45_PHASE
  "DSCA model with animation and 15 degrees offset"
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  parameter Integer X = 100;
  parameter Integer Y = 100;
  DSCA simple15(
    X=X,
    Y=Y,
    hex=0,
    wrapped_borders=00,
    redeclare function Initial = DSCAInitial45)
    annotation (Placement(transformation(extent={{-40,-18},{-20,2}})));
  Animation animation(
    WindowX=X,
    WindowY=Y,
    displayDelay=0,
    name="DSCA Simple45",
    save_video=false,
    redeclare function SetDisplayFunction = DSCADisplayPHASE)
    annotation (Placement(transformation(extent={{-4,-20},{16,0}})));
equation
  connect(simple15.Space, animation.Space)
    annotation (Line(points={{-29,3},{-29,14},{6,14},{6,1}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=2000, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>Model that includes the LBM_SimpleWave model and an Animation model to generate the graphical animation. The wave starts in the center of the cellular space and propagates. Wrapped boundary conditions are used. A display delay is also used in the animation to better observe the evolution of the wave.</p>
</html>"));
end DSCA_Simple45_PHASE;
