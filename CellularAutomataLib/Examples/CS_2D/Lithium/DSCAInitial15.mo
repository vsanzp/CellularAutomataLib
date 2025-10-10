within CellularAutomataLib.Examples.CS_2D.Lithium;
function DSCAInitial15 "Initialization function"
  input Components.ExternalObj.CS space;
  input Integer x;
  input Integer y;
  input Integer z;

  external "C" DSCAInitial15(space, x,y,z);
  annotation (
    Include = "#include \"lithium.c\"", Documentation(info="<html>
<p>Initial state function</p>
</html>"));
end DSCAInitial15;
