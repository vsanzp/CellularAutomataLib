within CellularAutomataLib.Examples.CS_2D.Lithium;
function DSCAInitialBorder "Initialization function"
  input Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z;

  external "C" DSCAInitialBorder(space, x,y,z);
  annotation (
    Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
end DSCAInitialBorder;
