within CellularAutomataLib.Examples.CS_2D.Epidemics;
model EpidemicsCA "Epidemic CA model"
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellularAutomataLib.Components.Basic.CellSpace(X = 50, Y = 50, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1], n_inputs = 0, wrapped_borders = 0, Tstep = 1, initial_step = 0, init_cells = {{25, 25}}, name = "Chagas", redeclare
      function Rule =                                                                                                                                                                                                         ERule, redeclare
      function Default =                                                                                                                                                                                                         EDefault, redeclare
      function Initial =                                                                                                                                                                                                         EInitial);
  //[-1, 0; 0, -1; 0, 1; 1, 0],

  function ERule "Transition function"
    input CS space;
    output Integer out;

    external "C" out = Step(space);
    annotation (
      Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end ERule;

  function EDefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = EDefault(space);
    annotation (
      Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end EDefault;

  function EInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" Ini(space, x, y,z);
    annotation (
      Include = "#include <epidemics.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end EInitial;
  annotation (Documentation(info="<html>
<p>This model is used to represent the space where the epidemic is spread. The size of the cellular space is 50x50 with open borders. The cell in the center of the space ([25,25]) is initially set as infected to start the epidemic.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/epidemic.c</span></p>
</html>"));
end EpidemicsCA;
