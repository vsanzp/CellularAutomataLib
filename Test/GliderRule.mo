within CellularAutomataLib.Test;
model GliderRule "GOL additional rule"
 import CellularAutomataLib.Components.Basic.*;
 import CellularAutomataLib.Components.ExternalObj.*;
extends AdditionalRule(Tstep = 1, initial_step = 0,init_cells = fill(0, 0, 3),
  redeclare function Rule = GOLStep,
  redeclare function Initial = GOLInit);

  function GOLStep
    input CS space;
    output Integer out;
    external "C" out = GOLStep(space);
    annotation (
      Include = "#include <gol.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end GOLStep;

  function GOLInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    external "C" GOLInitial(space, x, y, z);
    annotation (
      Include = "#include <gol.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end GOLInit;
end GliderRule;
