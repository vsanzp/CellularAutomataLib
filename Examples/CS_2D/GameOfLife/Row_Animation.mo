within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model Row_Animation
  CSGol_row cSGol_row
    annotation (Placement(transformation(extent={{-46,-20},{-26,0}})));
  Components.Animation animation(
    WindowWidth=500,
    WindowHeight=500,            WindowX=20, WindowY=20,
    displayDelay=100000,                                 redeclare function
      SetDisplayFunction =
        GOLSetDisplay)
    annotation (Placement(transformation(extent={{0,-18},{20,2}})));
equation
  connect(cSGol_row.Space, animation.Space) annotation (Line(points={{-35,1},{-36,
          1},{-36,10},{10,10},{10,3}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    Documentation(info="<html>
<p>This model includes a CSGol_row model combined with the Animation model in order to generate the graphical animation during the simulation.</p>
<p>Note that in this model the graphical animation is delayed to facilitate the observation of simulation (d<span style=\"font-family: monospace;\">isplayDelay=100000).</span></p>
</html>"),
    experiment(StopTime=50, __Dymola_Algorithm="Dassl"));
end Row_Animation;
