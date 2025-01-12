within CellularAutomataLib.Examples.CS_2D.C17;
model HPPSIR
  import CellularAutomataLib.Components.*;
  extends CellSpace(X = 100, Y = 100, neighborhood = [-1, 0; 0, -1; 0, 1; 1, 0], n_inputs = 0, wrapped_borders = 11, Tstep = 1, initial_step = 0, init_cells = [X, Y], name = "HPPSIR",
   redeclare function Rule = HPPRule,
    redeclare function Default = HPPDefault,
     redeclare function Initial = HPPSIRInitial);
  //[-1, 0; 0, -1; 0, 1; 1, 0],

  function HPPRule "Transition function"
    input CS space;
    output Integer out;

    external "C" out = HPPStep(space);
    annotation (
      Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP transition function</p>
</html>"));
  end HPPRule;

  function HPPDefault "Default state function"
    input CS space;
    output Integer out;

    external "C" out = HPPDefault(space);
    annotation (
      Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP default state function</p>
</html>"));
  end HPPDefault;

  function HPPSIRInitial "Initialization function"
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" HPPSIRInitial(space, x, y);
    annotation (
      Include = "#include <c17hpp.c>", Documentation(info="<html>
<p>HPP initial state function</p>
</html>"));
  end HPPSIRInitial;
  annotation (
    experiment(StopTime = 30),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>CA SIR model using an HPP approach.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/c17hpp.c</span></p>
</html>"));
end HPPSIR;
