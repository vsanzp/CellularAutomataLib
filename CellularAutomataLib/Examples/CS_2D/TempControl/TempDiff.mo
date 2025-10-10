within CellularAutomataLib.Examples.CS_2D.TempControl;
model TempDiff "Temperature diffusion CA model"
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellularAutomataLib.Components.Basic.CellSpace(
    X=10,
    Y=10,
    neighborhood=[-1,0; 0,-1; 0,1; 1,0],
    wrapped_borders=0,
    Tstep=1,
    initial_step=0,
    name="chip",
    init_cells=[X,Y],
    redeclare function Initial = TEMPInit,
    redeclare function Default = TEMPDefault,
    redeclare function Rule = TEMPStep);

  function TEMPDefault "default state function"
    extends Modelica.Icons.Function;
    input CS space;
    output Integer out;

    external "C" out = TEMPDefault(space);
    annotation (
      Include = "#include <tempcontrol.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end TEMPDefault;

  function TEMPInit "Initial state function"
      extends Modelica.Icons.Function;

    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" TEMPInitial(space, x, y, z);
    annotation (
      Include = "#include <tempcontrol.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end TEMPInit;

  function TEMPStep "Transition function"
      extends Modelica.Icons.Function;

    input CS space;
    output Integer out;

    external "C" out = TEMPStep(space);
    annotation (
      Include = "#include <tempcontrol.c>", Documentation(info="<html>
<p>Transition function.</p>
</html>"));
  end TEMPStep;

  //,[-1,0;0,-1;0,1;1,0],
  annotation (
    experiment(StopTime = 200),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Model for the heat diffusion on the chip. </p>
<p>The cellular space has a size of 10x10 with a Von Neumann neighborhood and open borders.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/chip.c</span></p>
</html>"));
end TempDiff;
