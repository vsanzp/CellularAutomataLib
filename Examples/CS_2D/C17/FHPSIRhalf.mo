within CellularAutomataLib.Examples.CS_2D.C17;
model FHPSIRhalf "FHP model with half distribution"
  import CellularAutomataLib.Components.Basic.*;
  import CellularAutomataLib.Components.ExternalObj.*;

  extends CellSpace(X = 100, Y = 100, neighborhood = [-1, 0; -1, 1; 0, -1; 0, 1; 1, 0; 1, 1], n_inputs = 0, wrapped_borders = 11, Tstep = 1, initial_step = 0,init_cells = [X, Y], name = "FHPSIRhalf",
    redeclare function Rule = FHPRule,
    redeclare function Default = FHPDefault,
    redeclare function Initial = FHPSIRInitial);
  //[-1, 0; 0, -1; 0, 1; 1, 0],

  function FHPRule "Transition function"
    input CS space;
    output Integer out;

    external "C" out = FHPStep(space);
    annotation (
      Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end FHPRule;

  function FHPDefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = FHPDefault(space);
    annotation (
      Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end FHPDefault;

  function FHPSIRInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" FHPSIRInitialHalf(space, x, y, z);
    annotation (
      Include = "#include <c17fhp.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end FHPSIRInitial;
  annotation (
    experiment(StopTime = 30),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>FHP model that includes vaccination individuals in half of the cellular space.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/c17fhp.c</span></p>
</html>"));
end FHPSIRhalf;
