within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model CSGol_row "GOL model initialized with a row"
  import CellularAutomataLib.Components.Basic.*;
  extends CellSpace(X = 20, Y = 20, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1], wrapped_borders = 00, Tstep = 1, initial_step = 0, name = "Game of Life (row)", init_cells = [10, 5; 10, 6; 10, 7; 10, 8; 10, 9; 10, 10; 10, 11; 10, 12; 10, 13; 10, 14],
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
<p>his model represents the Game of Life with a row initalization. Similarly to the glider, the row is a periodic structure of the cells but in this case it remains static in the same position of the space.</p>
<p>The size of the space is 20x20 with open borders.</p>
<p>In this case, the initial cells are set to <span style=\"font-family: monospace;\">init_cells&nbsp;=&nbsp;[10,&nbsp;5;&nbsp;10,&nbsp;6;&nbsp;10,&nbsp;7;&nbsp;10,&nbsp;8;&nbsp;10,&nbsp;9;&nbsp;10,&nbsp;10;&nbsp;10,&nbsp;11;&nbsp;10,&nbsp;12;&nbsp;10,&nbsp;13;&nbsp;10,&nbsp;14]</span>, to describe the structure of the row.</p>
<p>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/gol.c</span></p>
</html>"));
end CSGol_row;
