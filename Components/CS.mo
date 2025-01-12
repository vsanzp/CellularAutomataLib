within CellularAutomataLib.Components;
class CS
  extends ExternalObject;

  function constructor
    input Integer X "Size in X";
    input Integer Y "Size in Y";
    input Integer Z "Size in Z";
    input Integer hex "flag for hexagonal 2D space";
    input Integer[:,:] neighborhood "Topology of the neighborhood";
    input Integer n1 = size(neighborhood, 1) "Number of neighbors";
    input Integer n2 = size(neighborhood, 2); // coordinates per neighbor
    input Integer n_inputs = 0 "Number of inputs";
    input Integer wrapped_borders "1 if border is wrapped, 0 otherwise";
    output CS s "Reference to the created space";
  external "C" s = CS_Create(X, Y, Z, hex, neighborhood, n1, n2, n_inputs, wrapped_borders);
    annotation (
      Include = "#include <CellularAutomataLib.c>",
      Library = "raylib",
      Documentation(info="<html>
<p>CS constructor function</p>
</html>"));
  end constructor;

  function destructor
    input CS s;

    external "C" CS_Delete(s);
    annotation (
      Include = "#include <CellularAutomataLib.c>", Documentation(info="<html>
<p>CS destructor function</p>
</html>"));
  end destructor;
equation

  annotation (Documentation(info="<html>
<p>The CS model corresponds to the extenal object, defined in C, that is used to represent the cellular space.</p>
<p>The constructor and destructor functions are automatically executed when instatiating this class, and their C code is contained in the <span style=\"font-family: Courier New;\">cellularautomatalib.c</span> file.</p>
</html>"));
end CS;
