within CellularAutomataLib.Examples.CS_2D.GameOfLife;
model CSGol_random "GOL model with random initalization"
  import CellularAutomataLib.Components.*;
  extends CellSpace(X = 100, Y = 100, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1], wrapped_borders = 11, Tstep = 1, initial_step = 0, init_cells = [X, Y], name = "Game of Life (random init)",
    redeclare function Default = GOLDefault,
    redeclare function Initial = GOLInit,
    redeclare function Rule = GOLStep);

  function GOLDefault
    input CS space;
    output Integer out;

    external "C" out = GOLDefault(space);
    annotation (
      Include = "#include \"gol.c\"", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end GOLDefault;

  function GOLInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" GOLRandomInitial(space, x, y, z);
    annotation (
      Include = "#include \"gol.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end GOLInit;

  function GOLStep
    input CS space;
    output Integer out;

    external "C" out = GOLStep(space);
    annotation (
      Include = "#include \"gol.c\"", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end GOLStep;
  annotation (
    experiment(StopTime = 100), Documentation(info="<html>
<p>This model represents the Game of Life with a random initalization, where 50&percnt; of the cells are set initially alive.</p>
<p>The size of the space is 100x100 with wrapped borders.</p>
<p>Note that only one cell is defined in init_cells ([X,Y]). However, this can be used in the redeclared Initial function (GOLRandomInitial in gol.c) as the dimensions of the space and then initialize all the cells.</p>
<p><span style=\"font-family: Arial;\">The external functions used in the model are included in the file&nbsp;</span><span style=\"font-family: monospace;\">Resources/Include/gol.c</span></p>
</html>"));
end CSGol_random;
