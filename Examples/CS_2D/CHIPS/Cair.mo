within CellularAutomataLib.Examples.CS_2D.CHIPS;
model Cair "Chip surrounding air CA model"
  import CellularAutomataLib.Components.ExternalObj.*;
  extends CellularAutomataLib.Components.Basic.CellSpace(X = 10, Y = 10, neighborhood = [-1, 0; 0, -1; 0, 1; 1, 0], wrapped_borders = 0, Tstep = 1, initial_step = 0,init_cells = {{1, i} for i in 1:X}, redeclare
      function Initial =                                                                                                                                                                                                         CHIPInit, redeclare
      function Default =
        CHIPDefault,                                                                                                                                                                                                        redeclare
      function Rule =                                                                                                                                                                                                         AIRStep);

  function AIRStep
    input CS space;
    output Integer out;

    external "C" out = AIRStep(space);
    annotation (
      Include = "#include <chip.c>");
  end AIRStep;

  function CHIPDefault
    input CS space;
    output Integer out;

    external "C" out = CHIPDefault(space);
    annotation (
      Include = "#include <chip.c>");
  end CHIPDefault;

  function CHIPInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" CHIPInitial(space, x, y, z);
    annotation (
      Include = "#include <chip.c>");
  end CHIPInit;
  annotation (
    experiment(StopTime = 200),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>The external functions used in the model are included in the file<span style=\"font-family: monospace;\"> Resources/Include/chip.c</span></p>
</html>"));
end Cair;
