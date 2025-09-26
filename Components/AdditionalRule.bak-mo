within CellularAutomataLib.Components;
partial model AdditionalRule
  parameter Real Tstep = 1 "Duration time for each step/cicle";
  parameter Real initial_step = 0 "Time for starting the cicles";
  parameter Integer max_step = Modelica.Constants.Integer_inf "Maximum number of steps";
  parameter Integer[:, :] init_cells = fill(0, 0, 3);
  Integer sumactive(start = 0);
  Real mean;
  CAport Space annotation (Placement(transformation(extent={{-10,100},{10,120}}),
        iconTransformation(extent={{-10,100},{10,120}})));
  Integer active;
  Integer step( start= 0);

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

algorithm
  when time >= initial_step then
    for i in 1:size(init_cells, 1) loop
      if size(init_cells,2) == 1 then
        Initial(Space.space,init_cells[i,1],1,1);
      elseif size(init_cells,2) == 2 then
        Initial(Space.space,init_cells[i,1],init_cells[i,2],1);
      else
        Initial(Space.space,init_cells[i,1],init_cells[i,2],init_cells[i,3]);
      end if;
    end for;
  end when;
equation
  when sample(initial_step, Tstep) and pre(step) < max_step then
    //Modelica.Utilities.Streams.print("TIME ="+String(time));
    //sumactive = Rule(s);
    active = Rule(Space.space);
    if (active == 0) then
      terminate("NO ACTIVE CELLS");
    end if;
    sumactive = pre(sumactive) + active;
    mean = if time > 0 then sumactive/(time + 1) else sumactive;
    step = pre(step)+1;
  end when;
  annotation (
    Documentation(info="<html>
<p><i><span style=\"font-family: Arial;\">CellularAutomataLib</i>&nbsp;also includes the&nbsp;</span><span style=\"font-family: Courier New;\">AdditionalRule</span><span style=\"font-family: Arial;\">&nbsp;model to facilitate the application of multiple transition rules to the same cellular space. This model can be used to perform an additional transtition for the cells, simultaneously to the transition already performed by the&nbsp;</span><span style=\"font-family: Courier New;\">CellSpace</span><span style=\"font-family: Arial;\">&nbsp;model, or to sequentially apply different transition rules to the same space while maintaining the evolution of the cells in the space among different transitions.</span></p>
<p><span style=\"font-family: Arial;\">Note that for simultaneous transitions, the order in which the different rules are applied depends on the Modelica simulation algorithm.</span></p>
<p><span style=\"font-family: Arial;\">In order to sequentially apply the additional rule, the model includes the&nbsp;</span><span style=\"font-family: Courier New;\">initial_step</span><span style=\"font-family: Arial;\">,&nbsp;</span><span style=\"font-family: Courier New;\">Tstep</span><span style=\"font-family: Arial;\">&nbsp;and&nbsp;</span><span style=\"font-family: Courier New;\">max_step</span><span style=\"font-family: Arial;\">&nbsp;parameters to define the time to start the execution of the rule, the interval between steps and the maximum number of steps to be performed (these parameters are analogous to those in the&nbsp;</span><span style=\"font-family: Courier New;\">CellSpace</span><span style=\"font-family: Arial;\">&nbsp;model).</span></p>
<p><span style=\"font-family: Arial;\">The&nbsp;</span><span style=\"font-family: Courier New;\">AdditionalRule</span><span style=\"font-family: Arial;\">&nbsp;model includes an&nbsp;</span><span style=\"font-family: Courier New;\">Initial</span><span style=\"font-family: Arial;\">&nbsp;function, that can be used to re-initialize the state of the selected cells, and a&nbsp;</span><span style=\"font-family: Courier New;\">Rule</span><span style=\"font-family: Arial;\">&nbsp;function, that corresponds to the transition function. Both functions need to be defined using external C code and redeclared when instantiating the model.</span></p>
</html>"),
    Diagram(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}, initialScale = 0.1), graphics),
    experiment(StopTime = 1000),
    __Dymola_experimentSetupOutput,
    Icon(coordinateSystem(preserveAspectRatio = false, extent = {{-100, -100}, {100, 100}}), graphics={Text(
          extent={{-100,98},{100,-60}},
          textColor={28,108,200},
          textString="Rule"), Text(
          extent={{100,-100},{-100,-60}},
          textColor={0,0,0},
          textString="%name")}));
end AdditionalRule;
