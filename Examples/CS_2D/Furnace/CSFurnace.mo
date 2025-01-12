within CellularAutomataLib.Examples.CS_2D.Furnace;
model CSFurnace "Furnace model"
  import CellularAutomataLib.Components.*;
  extends CellSpace(X = 50, Y = 50, neighborhood = [-1, -1; -1, 0; -1, 1; 0, -1; 0, 1; 1, -1; 1, 0; 1, 1],
  wrapped_borders = 0, Tstep = 1, initial_step = 0, name = "Furnace", init_cells = {{i, 1} for i in 1:X},
     redeclare function Initial = FURInit,
     redeclare function Default = FURDefault,
     redeclare function Rule = FURStep);

  function FURStep
    input CS space;
    output Integer out;

    external "C" out = FURStep(space);
    annotation (
      Include = "#include <furnace.c>", Documentation(info="<html>
<p>Transition function</p>
</html>"));
  end FURStep;

  function FURDefault
    input CS space;
    output Integer out;

    external "C" out = FURDefault(space);
    annotation (
      Include = "#include <furnace.c>", Documentation(info="<html>
<p>Default state function</p>
</html>"));
  end FURDefault;

  function FURInit
    input CS space;
    input Integer x;
    input Integer y;
    input Integer z;

    external "C" FURInitial(space,x,y,z);
    annotation (
      Include = "#include <furnace.c>", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
  end FURInit;
  annotation (
    experiment(StopTime=100, __Dymola_Algorithm="Dassl"),
    __Dymola_experimentSetupOutput,
    Documentation(info="<html>
<p>Simple model for heat diffusion. Each cell stores its current temperature. Each cell temperature is updated with the average temperature of its neighbors.</p>
<p>The cellular space has a size of 50x50 and only the first row (Y=1) is initalized. The initial temperature of these cells remains constant during the simulation.</p>
<p><br>The external functions used in the model are included in the file <span style=\"font-family: monospace;\">Resources/Include/furnace.c</span></p>
</html>"));
end CSFurnace;
