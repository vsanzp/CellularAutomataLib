within CellularAutomataLib.Examples.CS_2D.TempControl;
model Temp_Animation_ControlE "Temperature controller with heat input located in the south wallSimple temperature diffusion model with animation"
  extends Modelica.Icons.Example;
  parameter Integer x = 30;
  parameter Integer y = 15;
  TempDiff tempDiff(X=x, Y=y,
    n_inputs=1,
    Tstep=1,
    name="Temp Control")
    annotation (Placement(transformation(extent={{0,-24},{20,-4}})));
  Components.Basic.Animation animation(
    WindowHeight=500,
    WindowX=x,
    WindowY=y,
    save_video=true,
    name="TempControlE",                redeclare function SetDisplayFunction =
        TEMPDisplay)
    annotation (Placement(transformation(extent={{26,-22},{46,-2}})));
  Components.Interfaces.ExtInputRegion extInputRegion(
    XToRange={22,22},
    YToRange={5,9},
    Input_type=5,
    start_sample=1,
    redeclare function ExtInput = TEMPExtInput)
    annotation (Placement(transformation(extent={{-22,12},{-2,32}})));
  Components.Interfaces.OutputRegion sensor(
    XFromRange={21,23},
    YFromRange={y - 1,y - 1},
    Output_type=1,
    output_rate=1,
    redeclare function ExtOutput = TEMPExtOutput)
    annotation (Placement(transformation(extent={{24,12},{44,32}})));
  Modelica.Blocks.Continuous.LimPID PID(
    controllerType=Modelica.Blocks.Types.SimpleController.PID,
    yMax=80,
    yMin=15) annotation (Placement(transformation(extent={{-48,12},{-28,32}})));
  Modelica.Blocks.Sources.Step step(
    height=7,
    offset=15,
    startTime=500)
    annotation (Placement(transformation(extent={{-76,12},{-56,32}})));
equation
  connect(tempDiff.Space, animation.Space)
    annotation (Line(points={{11,-3},{10,-3},{10,6},{36,6},{36,-1}},
                                                       color={28,108,200}));
  connect(extInputRegion.TO, tempDiff.Space)
    annotation (Line(points={{-6,22},{11,22},{11,-3}},  color={28,108,200}));
  connect(tempDiff.Space, sensor.FROM) annotation (Line(points={{11,-3},{10,-3},
          {10,22},{27.8,22}}, color={28,108,200}));
  connect(step.y, PID.u_s)
    annotation (Line(points={{-55,22},{-50,22}}, color={0,0,127}));
  connect(sensor.y, PID.u_m) annotation (Line(points={{40,22},{56,22},{56,-34},{
          -38,-34},{-38,10}}, color={0,0,127}));
  connect(PID.y, extInputRegion.u)
    annotation (Line(points={{-27,22},{-20,22}}, color={0,0,127}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=1440, __Dymola_Algorithm="Dassl"));
end Temp_Animation_ControlE;
