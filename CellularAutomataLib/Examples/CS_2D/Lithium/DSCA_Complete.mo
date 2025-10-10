within CellularAutomataLib.Examples.CS_2D.Lithium;
model DSCA_Complete "DSCA model with animation and 15 degrees offset"
  parameter Integer x = 40;
  parameter Integer y = 40;
  parameter Real dt = 0.1;
  extends Modelica.Icons.Example;
  import CellularAutomataLib.Components.Basic.*;
  parameter Integer X = x;
  parameter Integer Y = y;
  DSCA simple(
    X=X,
    Y=Y,
    hex=0,
    n_inputs=2,
    wrapped_borders=00,
    Tstep=dt,
    name="DSCA",
    redeclare function Initial=DSCAInitialBorder)
    annotation (Placement(transformation(extent={{-40,-18},{-20,2}})));
  Animation animation(
    Tstep=dt,
    WindowX=X,
    WindowY=Y,
    displayDelay=0,
    name="DSCA Simple",
    save_video=false,
    redeclare function SetDisplayFunction = DSCADisplaySR)
    annotation (Placement(transformation(extent={{-4,-20},{16,0}})));
  concentration3 concentration1(X=x,Y=y,
    dt=dt)
    annotation (Placement(transformation(extent={{-80,20},{-60,40}})));
  potential2 potential1(X=x,Y=y,
    dt=dt)
    annotation (Placement(transformation(extent={{32,20},{52,40}})));
  Components.Interfaces.OutputRegionM outputRegionM(
    XFromRange={1,x},
    YFromRange={1,y},
    output_rate=dt,
    redeclare function ExtOutput = ExtOutputFS)
    annotation (Placement(transformation(extent={{-40,-42},{-20,-22}})));
  Components.Interfaces.ExtInputRegionM conInput(
    input_id=1,
    XToRange={1,x},
    YToRange={1,y},
    interval=dt,
    redeclare function ExtInput=ExtInput)
    annotation (Placement(transformation(extent={{-52,20},{-32,40}})));
  Components.Interfaces.ExtInputRegionM potInput(
    input_id=2,
    XToRange={1,x},
    YToRange={1,y},
    start_sample=0,
    interval=dt,
    redeclare function ExtInput=ExtInput)
    annotation (Placement(transformation(extent={{64,20},{84,40}})));
equation
  connect(outputRegionM.yM[:, :, 1], concentration1.FS) annotation (Line(points
        ={{-24,-32},{-20,-32},{-20,-42},{-80,-42},{-80,30}}, color={0,0,127}));
  connect(outputRegionM.yM[:, :, 1], potential1.FS)
    annotation (Line(points={{-24,-32},{32,-32},{32,30}}, color={0,0,127}));
  connect(potInput.TO, simple.Space) annotation (Line(points={{80,30},{80,52},{-29,
          52},{-29,3}}, color={28,108,200}));
  connect(conInput.TO, simple.Space)
    annotation (Line(points={{-36,30},{-29,30},{-29,3}}, color={28,108,200}));
  connect(animation.Space, simple.Space) annotation (Line(points={{6,1},{6,12},{
          -29,12},{-29,3}}, color={28,108,200}));
  connect(outputRegionM.FROM, simple.Space) annotation (Line(points={{-36.2,-32},
          {-42,-32},{-42,12},{-29,12},{-29,3}}, color={28,108,200}));
  connect(concentration1.c, conInput.uM[:, :, 1])
    annotation (Line(points={{-60,30},{-50,30}}, color={0,0,127}));
  connect(potential1.phi, potInput.uM[:, :, 1])
    annotation (Line(points={{52,30},{66,30}}, color={0,0,127}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=1000, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>Model that includes the LBM_SimpleWave model and an Animation model to generate the graphical animation. The wave starts in the center of the cellular space and propagates. Wrapped boundary conditions are used. A display delay is also used in the animation to better observe the evolution of the wave.</p>
</html>"));
end DSCA_Complete;
