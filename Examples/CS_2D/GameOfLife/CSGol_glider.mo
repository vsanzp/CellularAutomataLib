within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model CSGol_glider "GOL model initialized with a simple glider"
  import CellularAutomataLib.Components.Basic.*;
  extends CellSpace(X = 100, Y = 100, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1], wrapped_borders = 11, Tstep = 1, initial_step = 0, name = "Game of Life (glider)", init_cells = [1, 2; 2, 3; 3, 1; 3, 2; 3, 3],
    redeclare function Initial = GOLInit,
    redeclare function Default = GOLDefault,
    redeclare function Rule = GOLStep);

  function GOLDefault
    input CellularAutomataLib.Components.ExternalObj.CS space;
    output Integer out;
    external "C" out = GOLDefault(space);
    annotation (
      Include = "#include <gol.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end GOLDefault;

  function GOLStep
    input CellularAutomataLib.Components.ExternalObj.CS space;
    output Integer out;
    external "C" out = GOLStep(space);
    annotation (
      Include = "#include <gol.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end GOLStep;

  function GOLInit
    input CellularAutomataLib.Components.ExternalObj.CS space;
    input Integer x;
    input Integer y;
    input Integer z;
    external "C" GOLInitial(space, x, y, z);
    annotation (
      Include = "#include <gol.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end GOLInit;
  annotation (
    experiment(StopTime = 100),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>This model represents the Game of Life with a glider initalization. A Glider is a periodic structure of cells that moves diagonally along the cellular space.</p>
<p>The size of the space is 50x50 with wrapped borders.</p>
<p>In this case, the initial cells are set to <span style=\"font-family: monospace;\">init_cells&nbsp;=&nbsp;[1,&nbsp;2;&nbsp;2,&nbsp;3;&nbsp;3,&nbsp;1;&nbsp;3,&nbsp;2;&nbsp;3,&nbsp;3]</span>, to describe the structure of the glider.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/gol.c</span></p>
</html>"));
end CSGol_glider;
