within CellularAutomataLib.Examples.CS_2D.TempControl;
model Temp_Animation_ControlS "Temperature controller with heat input located in the south wallSimple temperature diffusion model with animation"
  extends Modelica.Icons.Example;
  parameter Integer x = 30;
  parameter Integer y = 15;
  TempDiff tempDiff(X=x, Y=y,
    n_inputs=1,
    Tstep=1,
    name="Temp Control")
    annotation (Placement(transformation(extent={{-20,-2},{0,18}})));
  Components.Basic.Animation animation(
    WindowHeight=500,
    WindowX=x,
    WindowY=y,
    save_video=true,
    name="TempControlS",                redeclare function SetDisplayFunction =
        TEMPDisplay)
    annotation (Placement(transformation(extent={{8,0},{28,20}})));
  Components.Interfaces.ExtInputRegion extInputRegion(
    XToRange={5,10},
    YToRange={2,2},
    Input_type=5,
    start_sample=1,
    redeclare function ExtInput = TEMPExtInput)
    annotation (Placement(transformation(extent={{-36,34},{-16,54}})));
  Components.Interfaces.OutputRegion sensor(
    XFromRange={21,23},
    YFromRange={y - 1,y - 1},
    Output_type=1,
    output_rate=1,
    redeclare function ExtOutput = TEMPExtOutput)
    annotation (Placement(transformation(extent={{4,34},{24,54}})));
  Modelica.Blocks.Continuous.LimPID PID(
    controllerType=Modelica.Blocks.Types.SimpleController.PID,
    yMax=80,
    yMin=15) annotation (Placement(transformation(extent={{-62,34},{-42,54}})));
  Modelica.Blocks.Sources.Step step(
    height=7,
    offset=15,
    startTime=500)
    annotation (Placement(transformation(extent={{-94,34},{-74,54}})));
equation
  connect(tempDiff.Space, animation.Space)
    annotation (Line(points={{-9,19},{-10,19},{-10,28},{18,28},{18,21}},
                                                       color={28,108,200}));
  connect(extInputRegion.TO, tempDiff.Space)
    annotation (Line(points={{-20,44},{-9,44},{-9,19}}, color={28,108,200}));
  connect(tempDiff.Space, sensor.FROM) annotation (Line(points={{-9,19},{-10,19},
          {-10,44},{7.8,44}}, color={28,108,200}));
  connect(step.y, PID.u_s) annotation (Line(points={{-73,44},{-64,44}},
                     color={0,0,127}));
  connect(sensor.y, PID.u_m) annotation (Line(points={{20,44},{34,44},{34,-12},
          {-52,-12},{-52,32}},                 color={0,0,127}));
  connect(PID.y, extInputRegion.u)
    annotation (Line(points={{-41,44},{-34,44}}, color={0,0,127}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=1440, __Dymola_Algorithm="Dassl"));
end Temp_Animation_ControlS;
