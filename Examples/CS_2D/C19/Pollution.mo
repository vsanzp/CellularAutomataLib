within CellularAutomataLib.Examples.CS_2D.C19;
model Pollution
  import CellularAutomataLib.Components.*;
  extends CellSpace(X = 40, Y = 70, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1], n_inputs = 0, wrapped_borders = 0, Tstep = 1, initial_step = 0, init_cells = {{20, 10}}, name = "Pollution",
    redeclare function Rule = POLRule,
    redeclare function Default = POLDefault,
    redeclare function Initial = POLInitial);
  //[-1, 0; 0, -1; 0, 1; 1, 0],

  function POLRule "Transition function"
    input CS space;
    output Integer out;

    external "C" out = POLStep(space);
    annotation (
      Include = "#include <c19.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end POLRule;

  function POLDefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = POLDefault(space);
    annotation (
      Include = "#include <c19.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end POLDefault;

  function POLInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" POLInitial(space, x, y, z);
    annotation (
      Include = "#include <c19.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end POLInitial;
  annotation (
    experiment,
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model to describe the spread of groundwater polutants.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/c19.c</span></p>
</html>"));
end Pollution;
