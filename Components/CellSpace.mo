within CellularAutomataLib.Components;
partial model CellSpace
  parameter Integer X = 1 "Number of rows";
  parameter Integer Y = 1 "Number of columns";
  parameter Integer Z = 1 "Number of columns";
  parameter Integer hex = 0 "Hexagonal 2D lattice";
  parameter Integer[:, :] neighborhood = [-1,1,-1;0,1,-1;1,1,-1;-1,0,-1;0,0,-1;1,0,-1;-1,-1,-1;0,-1,-1;1,-1,-1;
                                          -1,1,0;0,1,0;1,1,0;-1,0,0;1,0,0;-1,-1,0;0,1,0;1,-1,0;
                                          -1,1,1;0,1,1;1,1,1;-1,0,1;0,0,1;1,0,1;-1,-1,1;0,-1,1;1,-1,1];
  parameter Integer n_inputs = 0 "number of inputs (from other CA or external)";
  parameter Integer wrapped_borders = 111 "mask for XYZ wrapped borders";
  parameter Real Tstep = 1 "Duration time for each step/cicle";
  parameter Real initial_step = 0 "Time for starting the cicles";
  parameter Integer max_step = Modelica.Constants.Integer_inf "Maximum number of steps";
  parameter Integer[:, :] init_cells = fill(0, 0, 3);
  parameter String name = "CA";
  Integer sumactive(start = 0);
  Real mean;

  replaceable function Default "Function to define default state for cells"
    input CS space "Reference to the space";
  end Default;

  replaceable function Initial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
  end Initial;

  replaceable function Rule "Transition function"
    input CS space;
    output Integer out;
  end Rule;

  CS s=CS(
      X,
      Y,
      Z,
      hex,
      neighborhood,
      size(neighborhood, 1),
      size(neighborhood, 2),
      n_inputs,
      wrapped_borders);
  //Boolean init(start=false, fixed=true);
  CAport Space annotation (Placement(transformation(extent={{0,100},{20,120}}),
        iconTransformation(extent={{0,100},{20,120}})));
  Integer active;
  Integer step( start= 0);
initial algorithm
//when initial() and not init then
  Default(s);
  for i in 1:size(init_cells, 1) loop
    if size(init_cells,2) == 1 then
      Initial(s,init_cells[i,1],1,1);
    elseif size(init_cells,2) == 2 then
      Initial(s,init_cells[i,1],init_cells[i,2],1);
    else
      Initial(s,init_cells[i,1],init_cells[i,2],init_cells[i,3]);
    end if;
  end for;
  Modelica.Utilities.Streams.print("INIT FINISHED");
//init := true;
//end when;
equation
  Space.space = s;
algorithm
    when sample(initial_step, Tstep) and pre(step) < max_step then
    Modelica.Utilities.Streams.print("TIME ="+String(time));
    //sumactive = Rule(s);
    active := Rule(s);
    if (active == 0) then
      terminate("NO ACTIVE CELLS");
    end if;
    sumactive := pre(sumactive) + active;
    mean := if time > 0 then sumactive/(time + 1) else sumactive;
    step := pre(step)+1;
  end when;
  annotation (
    Documentation(info="<html>
<p>This model represents a multi-dimensional cellular automaton. It includes a CS model to represent the cellular space and the functions (<i>Initial</i>, <i>Default</i> and <i>Rule</i>) required to simulate the automaton.</p>
<p>The parameters of the model are:</p>
<ul>
<li><span style=\"font-family: Courier New;\">X</span>, <span style=\"font-family: Courier New;\">Y</span> and <span style=\"font-family: Courier New;\">Z</span>, that are used to define the dimensions of the space.</li>
<li><span style=\"font-family: Courier New;\">hex</span>, is used to define the geometry of each cell in 2D spaces (eigher squared or hexagonal).</li>
<li><span style=\"font-family: Courier New;\">neighborhood</span>, that defines the relative coordinates of the neighbors.</li>
<li><span style=\"font-family: Courier New;\">n_inputs</span>, sets the number of external inputs connected to the automaton.</li>
<li><span style=\"font-family: Courier New;\">wrapped_borders</span>, is a boolean mask for each dimension of the space to define the boundary condition, either open or wrapped (e.g., 101 sets X as wrapped, Y as open and Z as wrapped).</li>
<li><span style=\"font-family: Courier New;\">Tstep</span>, defines the interval between simulation steps.</li>
<li><span style=\"font-family: Courier New;\">initial_step</span>, defines the time to start the steps</li>
<li><span style=\"font-family: Courier New;\">max_step</span>, defines the maximum number of steps to be performed.</li>
<li><span style=\"font-family: Courier New;\">init_cells</span>, is used define the subset of cells that will be initialized at the beginning of the simulation.</li>
<li><span style=\"font-family: Courier New;\">name</span>, is used to identify the automaton.</li>
</ul>
<p><br>The simulation of the automaton is as follows:</p>
<ol>
<li>At the beginning of the simulation the CS constructor function is used to create the cellular space with the parameters of the model. </li>
<li>The <i>Default</i> function is used to allocate memory for the cells and set their default state. After that, the <i>Initial</i> function is used to initialize the cells with <span style=\"font-family: Courier New;\">init_cells</span>. </li>
<li>The simulation steps are periodically executed starting at time = <span style=\"font-family: Courier New;\">initial_step</span>, and with <span style=\"font-family: Courier New;\">Tstep</span> intervals. The <i>Rule</i> function is executed once for each simulation step.</li>
<li>The steps are performed until the simulation time is completed or the number of steps performed reaches <span style=\"font-family: Courier New;\">max_step</span>.</li>
</ol>
</html>"),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}, initialScale = 0.1), graphics),
    experiment(StopTime = 1000),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={  Rectangle(extent={{-100,60},
              {60,-80}},                                                                                                                            lineColor={28,108,
              200}),                                                                                                                                                          Line(points={{-80,60},
              {-80,-80}},                                                                                                                                                                                            color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-60,60},
              {-60,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-40,60},
              {-40,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{-20,60},
              {-20,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{0,60},{
              0,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{20,60},
              {20,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points={{40,60},
              {40,-80}},                                                                                                                                                                                                        color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,60},  rotation = 270), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,40},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,20},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,0},   rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None,                  rotation = 90,
          origin={-20,-20}),                                                                                                                                                                                                        Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,-40},  rotation = 90), Line(points = {{0, 80}, {0, -80}}, color={28,108,
              200},                                                                                                                                                                                                        smooth = Smooth.None, origin={-20,-60},  rotation = 90), Text(extent={{-80,-80},
              {80,-120}},                                                                                                                                                                                                        lineColor={0,0,0},       textString = "%name"), Text(extent={{-100,12},
              {60,-28}},                                                                                                                                                                                                        lineColor={0,0,0},
          textString="[%X x %Y x %Z]"),
        Line(points={{-100,60},{-80,80},{-60,100}}, color={28,108,200}),
        Line(points={{60,60},{80,80},{100,100}}, color={28,108,200}),
        Line(points={{60,-80},{80,-60},{100,-40}}, color={28,108,200}),
        Line(points={{-60,100},{100,100}}, color={28,108,200}),
        Line(points={{-80,60},{-60,80},{-40,100}}, color={28,108,200}),
        Line(points={{-60,60},{-40,80},{-20,100}}, color={28,108,200}),
        Line(points={{-40,60},{-20,80},{0,100}}, color={28,108,200}),
        Line(points={{-20,60},{0,80},{20,100}}, color={28,108,200}),
        Line(points={{0,60},{20,80},{40,100}}, color={28,108,200}),
        Line(points={{20,60},{40,80},{60,100}}, color={28,108,200}),
        Line(points={{40,60},{60,80},{80,100}}, color={28,108,200}),
        Line(points={{60,40},{80,60},{100,80}}, color={28,108,200}),
        Line(points={{60,20},{80,40},{100,60}}, color={28,108,200}),
        Line(points={{60,0},{80,20},{100,40}}, color={28,108,200}),
        Line(points={{60,-20},{80,0},{100,20}}, color={28,108,200}),
        Line(points={{60,-40},{80,-20},{100,0}}, color={28,108,200}),
        Line(points={{60,-60},{80,-40},{100,-20}}, color={28,108,200}),
        Line(points={{100,100},{100,-40}}, color={28,108,200}),
        Line(points={{70,70},{70,-70}}, color={28,108,200}),
        Line(points={{90,90},{90,-50}}, color={28,108,200}),
        Line(points={{80,80},{80,-60}}, color={28,108,200}),
        Line(points={{70,70},{-90,70}}, color={28,108,200}),
        Line(points={{80,80},{-80,80}}, color={28,108,200}),
        Line(points={{90,90},{-70,90}}, color={28,108,200})}));
end CellSpace;
