within CellularAutomataLib.Examples.CS_2D.CHIPS;
model Single_chip
  import CellularAutomataLib.Components.*;
  extends CellSpace(
    X=10,
    Y=10,
    neighborhood=[-1,0; 0,-1; 0,1; 1,0],
    wrapped_borders=0,
    Tstep=1,
    initial_step=0,
    name="chip",
    init_cells={{i,1} for i in 1:Y},
    redeclare function Initial = CHIPInit,
    redeclare function Default = CHIPDefault,
    redeclare function Rule = SCHIPStep);

  function SCHIPStep
    input CS space;
    output Integer out;

    external "C" out = SCHIPStep(space);
    annotation (
      Include = "#include <chip.c>", Documentation(info="<html>
<p>Transition function.</p>
</html>"));
  end SCHIPStep;

  function CHIPDefault
    input CS space;
    output Integer out;

    external "C" out = CHIPDefault(space);
    annotation (
      Include = "#include <chip.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end CHIPDefault;

  function CHIPInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" CHIPInitial(space, x, y, z);
    annotation (
      Include = "#include <chip.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end CHIPInit;

  //,[-1,0;0,-1;0,1;1,0],
  annotation (
    experiment(StopTime = 200),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model for the heat diffusion on the chip. </p>
<p>The cellular space has a size of 10x10 with a Von Neumann neighborhood and open borders.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/chip.c</span></p>
</html>"));
end Single_chip;
