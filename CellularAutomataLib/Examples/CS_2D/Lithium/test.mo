within CellularAutomataLib.Examples.CS_2D.Lithium;
model test
  concentration3 con
    annotation (Placement(transformation(extent={{0,0},{20,20}})));
        Integer i( start = 1);
        Integer j( start = 1);
algorithm
  when sample(0,1) then
    con.FS[j,10] := con.FS[j,10] + i/10;
    if (con.FS[j,10] >= 1) then
      con.FS[j,10] := 1;
      j := j+1;
      i := 1;
    end if;
    i:=i+1;
  end when;
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)));
end test;
