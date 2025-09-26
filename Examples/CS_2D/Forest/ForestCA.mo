within CellularAutomataLib.Examples.CS_2D.Forest;
model ForestCA "Forest fire CA model"
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellSpace(X = 30, Y = 30, neighborhood = [-1, -1; -1, 0; -1, 1; 0, 1; 1, 1; 1, 0; 1, -1; 0, -1], n_inputs = 0, wrapped_borders = 0, Tstep = 1, initial_step = 0, init_cells = [X, Y], name = "ForestCA",
    redeclare function Rule = FRule,
    redeclare function Default = FDefault,
    redeclare function Initial = FInitial);
  //[-1, 0; 0, -1; 0, 1; 1, 0],

  function FRule "Transition function"
    input CS space;
    output Integer out;

    external "C" out = Step(space);
    annotation (
      Include = "#include <forest.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end FRule;

  function FDefault
    input CS space;
    output Integer out;

    external "C" out = FDefault(space);
    annotation (
      Include = "#include <forest.c>",
      Library = "m",
      Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end FDefault;

  function FInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" Ini(space, x, y, z);
    annotation (
      Include = "#include <forest.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end FInitial;
  annotation (
    experiment(StopTime = 300),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Forest fire spread model. The model behavior is computed using the Rothermel model from an external C file. Fire spread also depends on wind direction and speed, and firefighting actions (pouring water). See transition function for details.</p>
<p>The fire is initally active in a single cell.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/forest.c</span></p>
</html>"));
end ForestCA;
