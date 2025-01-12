within CellularAutomataLib.Components;
model Animation
  parameter Real Tstep = 1 "Duration time for each step/cicle";
  parameter Real initial_step = 0 "Time for starting the cicles";
  parameter Integer max_step = Modelica.Constants.Integer_inf "Maximum number of steps";
  parameter Integer WindowWidth = 1000 "Window width";
  parameter Integer WindowHeight = 1000 "Window height";
  parameter Integer WindowX = 1 "number of animation cells in the X axis";
  parameter Integer WindowY = 1 "number of animation cells in the Y axis";
  parameter Integer WindowZ = 1 "number of animation cells in the Z axis";
  parameter Integer Vector = 0 "0 scalar, 1 vector";
  parameter Real displayDelay = 0 "Animation update delay (in microseconds)";
  parameter String name = "CA_Animation";
  CAport Space annotation (Placement(transformation(extent={{-10,100},{10,120}}),
        iconTransformation(extent={{-10,100},{10,120}})));
  Integer step( start= 0);

  replaceable function SetDisplayFunction
    input CS space;
  end SetDisplayFunction;

  function StepPlot "Display function"
    input CS space;
    external "C" CS_Plot(space);
    annotation (Include = "#include <CellularAutomataLib.c>");
  end StepPlot;

  function InitAnimation
    input CS s;
    input Integer WindowWidth;
    input Integer WindowHeight;
    input Integer wX;
    input Integer wY;
    input Integer wZ;
    input Integer vector;
    input Real displayDelay;
    input String name;
    external "C" CS_InitAnimation(s,WindowWidth,WindowHeight,wX,wY,wZ,vector,displayDelay,name);
    annotation (Include = "#include <CellularAutomataLib.c>");
  end InitAnimation;

initial algorithm
    InitAnimation(Space.space,WindowWidth,WindowHeight,WindowX,WindowY,WindowZ,Vector,displayDelay,name);
    SetDisplayFunction(Space.space);
algorithm
  when sample(initial_step, Tstep) and pre(step) < max_step then
    StepPlot(Space.space);
    step :=pre(step) + 1;
  end when;
  annotation (
    Documentation(info="<html>
<p><i><span style=\"font-family: Arial;\">CellularAutomataLib</i>&nbsp;supports the generation of a graphical animation during the simulation, to display the evolution of the cellular space. If desired, the graphical animation can be generated using the&nbsp;</span><span style=\"font-family: Courier New;\">Animation</span><span style=\"font-family: Arial;\">&nbsp;model connected to the&nbsp;</span><span style=\"font-family: Courier New;\">CellSpace&nbsp;</span><span style=\"font-family: Arial;\">(using the&nbsp;</span><span style=\"font-family: Courier New;\">CAport</span><span style=\"font-family: Arial;\">&nbsp;connectors in both models). The Raylib library is used to generate the graphics of the animation.</span></p>
<p><span style=\"font-family: Arial;\">The&nbsp;</span><span style=\"font-family: Courier New;\">Animation</span><span style=\"font-family: Arial;\">&nbsp;model includes parameters to describe the size of the animation window (</span><span style=\"font-family: Courier New;\">WindowHeigth</span><span style=\"font-family: Arial;\">&nbsp;and&nbsp;</span><span style=\"font-family: Courier New;\">WindowWidth</span><span style=\"font-family: Arial;\">) and to describe the number of cells that will be displayed in each dimension (</span><span style=\"font-family: Courier New;\">WindowX</span><span style=\"font-family: Arial;\">,&nbsp;</span><span style=\"font-family: Courier New;\">WindowY</span><span style=\"font-family: Arial;\">,&nbsp;</span><span style=\"font-family: Courier New;\">WindowZ</span><span style=\"font-family: Arial;\">). Usually, the number of displayed cells will be equal to those of the cellular space, but this model also supports the representation of aggregate states of multiple cells of the cellular space as a single cell in the animation.</span></p>
<p><span style=\"font-family: Arial;\">The model also includes three functions used to manage the animation:&nbsp;</span><span style=\"font-family: Courier New;\">SetDisplayFunction</span><span style=\"font-family: Arial;\">&nbsp;is used to associate a display function with the cellular space;&nbsp;</span><span style=\"font-family: Courier New;\">StepPlot</span><span style=\"font-family: Arial;\">&nbsp;is the function used to actually display the state of the cells during each step; and&nbsp;</span><span style=\"font-family: Courier New;\">InitAnimation</span><span style=\"font-family: Arial;\">&nbsp;that is used to initialize the animation window.</span></p>
<p><span style=\"font-family: Arial;\">The animation is initialized using the parameters of the model and the&nbsp;</span><span style=\"font-family: Courier New;\">InitAnimation</span><span style=\"font-family: Arial;\">&nbsp;function. The user needs to redeclare the&nbsp;</span><span style=\"font-family: Courier New;\">SetDisplayFunction</span><span style=\"font-family: Arial;\">&nbsp;with his own display function to define how the state of the cells will be displayed. After that, the animation is periodically updated, following the intervals indicated by the&nbsp;</span><span style=\"font-family: Courier New;\">Tstep</span><span style=\"font-family: Arial;\">&nbsp;and&nbsp;</span><span style=\"font-family: Courier New;\">intial_step</span><span style=\"font-family: Arial;\">&nbsp;parameters, using the&nbsp;</span><span style=\"font-family: Courier New;\">StepPlot</span><span style=\"font-family: Arial;\">&nbsp;function. Currently, only one animation window per simulation is supported.</span></p>
</html>"),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}, initialScale = 0.1), graphics),
    experiment(StopTime = 1000),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={Text(
          extent={{-100,100},{100,0}},
          textColor={28,108,200},
          textString="Animation"),
                              Text(
          extent={{100,-100},{-100,-60}},
          textColor={0,0,0},
          textString="%name"),
        Rectangle(
          extent={{-10,14},{10,-6}},
          lineColor={255,255,0},
          fillColor={0,0,0},
          fillPattern=FillPattern.Solid),
        Rectangle(
          extent={{10,-6},{30,-26}},
          lineColor={255,255,0},
          fillColor={0,0,0},
          fillPattern=FillPattern.Solid),
        Rectangle(
          extent={{-10,-26},{10,-46}},
          lineColor={255,255,0},
          fillColor={0,0,0},
          fillPattern=FillPattern.Solid),
        Rectangle(
          extent={{-30,-26},{-10,-46}},
          lineColor={255,255,0},
          fillColor={0,0,0},
          fillPattern=FillPattern.Solid),
        Rectangle(
          extent={{10,-26},{30,-46}},
          lineColor={255,255,0},
          fillColor={0,0,0},
          fillPattern=FillPattern.Solid)}));
end Animation;
