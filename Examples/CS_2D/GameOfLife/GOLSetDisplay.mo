within CellularAutomataLib.Examples.CS_2D.GameOfLife;
function GOLSetDisplay "Fame of Life display function"
  input CellularAutomataLib.Components.ExternalObj.Anim animation;
    input CellularAutomataLib.Components.ExternalObj.CS space;
  external "C" GOLSetDisplay(animation,space);
  annotation (Include = "#include <gol-anim.c>", Documentation(info="<html>
<p>This function is used to display the state of the GOL models in the animations.</p>
</html>"));
end GOLSetDisplay;
