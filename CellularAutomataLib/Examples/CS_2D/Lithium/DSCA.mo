within CellularAutomataLib.Examples.CS_2D.Lithium;
model DSCA "Decentralized Square Cellular Automata"
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellSpace(
    X=10,
    Y=10,
    hex=0,
    neighborhood=[1,0;1,1;0,1;-1,1;-1,0;-1,-1;0,-1;1,-1],
    n_inputs=0,
    wrapped_borders=00,
    Tstep=1,
    initial_step=0,
    init_cells=[X,Y],
    name="Simple Diffusion",
    redeclare function Rule = DSCARule,
    redeclare function Default = DSCADefault,
    redeclare function Initial = DSCAInitial);

     function DSCARule "Transition function"
       input CS space;
       output Integer out;

     external"C" out = DSCAStep(space);
       annotation (
      Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Transition function</p>
</html>"));
     end DSCARule;

  function DSCADefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = DSCADefault(space);
    annotation (
      Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end DSCADefault;

  function DSCAInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" DSCAInitial0(space, x,y,z);
    annotation (
      Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end DSCAInitial;

  annotation (experiment(StopTime=5, __Dymola_Algorithm="Dassl"),
      Documentation(info="<html>
<p>Model that simulates the growth process of lithium dentrites.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/lithium.c</span></p>
</html>"));
end DSCA;
