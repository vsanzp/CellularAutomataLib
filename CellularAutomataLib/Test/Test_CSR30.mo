within CellularAutomataLib.Test;
model Test_CSR30 "Test based on R30 CA model"
  extends Modelica.Icons.Example;
  CellularAutomataLib.Examples.CS_1D.CSR30 cSR30_1(initial_step=1)
    annotation (Placement(transformation(extent={{-60,0},{-40,20}})));
  CellularAutomataLib.Components.Interfaces.OutputRegionM O(
    XFromRange={40,60},
    output_rate=1,
    redeclare function ExtOutput = ROutput)
    annotation (Placement(transformation(extent={{-60,38},{-40,58}})));
  constant Integer result[21] = {1,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0}; // at step 12
  Boolean fail( start = false);
algorithm
  when terminal() then
    for i in 1:21 loop
      if result[i] <> integer(O.yM[i,1,1]) then
        Modelica.Utilities.Streams.print( "******* -- TEST FAILED on cell["+String(i+O.XFromRange[1]-1)+"]: is "+String(O.yM[i,1,1])+" instead of "+String(result[i]));
        fail := true;
      end if;
    end for;
    if not fail then
        Modelica.Utilities.Streams.print("*******************");
        Modelica.Utilities.Streams.print("******* -- TEST OK!");
        Modelica.Utilities.Streams.print("*******************");
    end if;
  end when;
equation
  connect(cSR30_1.Space, O.FROM)
    annotation (Line(points={{-49,21},{-56.2,21},{-56.2,48}},
                                                          color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=13, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>This model combines the CSR30 model with the Animation model to generate the graphical animation during the simulation.</p>
<p>The RSetDisplay function is used as Display function.</p>
</html>"));
end Test_CSR30;
