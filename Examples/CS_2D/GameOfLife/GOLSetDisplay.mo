within CellularAutomataLib.Examples.CS_2D.GameOfLife;
function GOLSetDisplay
  input Anim animation;
    input CS space;
  external "C" GOLSetDisplay(animation,space);
  annotation (Include = "#include <gol.c>", Documentation(info="<html>
<p>This function is used to display the state of the GOL models in the animations.</p>
</html>"));
end GOLSetDisplay;
