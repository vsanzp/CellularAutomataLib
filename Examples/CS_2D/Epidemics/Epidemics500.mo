within CellularAutomataLib.Examples.CS_2D.Epidemics;
model Epidemics500
  EpidemicsCA epidemicsCA(                name = "Epidemics", X = 500, Y = 500, init_cells = {{250, 250}})                    annotation (
    Placement(transformation(extent = {{-24, -4}, {20, 40}})));
  Components.Animation animation(WindowX=500, WindowY=500, redeclare function
      SetDisplayFunction =                                                                       SetDisplay)
    annotation (Placement(transformation(extent={{-80,20},{-60,40}})));
equation
  connect(epidemicsCA.Space, animation.Space) annotation (Line(points={{0.2,42.2},
          {0.2,50},{-70,50},{-70,41}}, color={0,0,0}));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}})),
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model that includes the EpidemicsCA with an Animation model, using space of 500x500 cells.</p>
</html>"));
end Epidemics500;
