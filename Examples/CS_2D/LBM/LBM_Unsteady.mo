within CellularAutomataLib.Examples.CS_2D.LBM;
model LBM_Unsteady "LBM model of an unsteady flow (Von-Karman vortex street)"
  import CellularAutomataLib.Components.Basic.*;
    import CellularAutomataLib.Components.ExternalObj.*;
  extends CellSpace(X = 10, Y = 10, hex = 0, neighborhood = [-1,-1;-1,0;-1,1;0,1;1,1;1,0;1,-1;0,-1], n_inputs = 0, wrapped_borders = 0, Tstep = 1, initial_step = 0, init_cells = [X, Y], name = "Simple Diffusion",
    redeclare function Rule = LBMRule,
    redeclare function Default = LBMDefault,
    redeclare function Initial = LBMInitial);

     function LBMRule "Transition function"
    input CS space;
    output Integer out;

  external"C" out = D2Q9Step(space);
    annotation (
      Include = "#include \"LBM.c\"", Documentation(info="<html>
<p>Transition function</p>
</html>"));
     end LBMRule;

  function LBMDefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = D2Q9Default(space);
    annotation (
      Include = "#include \"LBM.c\"", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end LBMDefault;

  function LBMInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" D2Q9InitialUnsteady(space, x,y,z);
    annotation (
      Include = "#include \"LBM.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end LBMInitial;

  annotation (experiment(StopTime=5, __Dymola_Algorithm="Dassl"),
      Documentation(info="<html>
<p>LBM model to simulate a Von Karman vortex street.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/LBM.c</span></p>
</html>"));
end LBM_Unsteady;
