within CellularAutomataLib.Test;
model Test_CSR110
  Examples.CS_1D.CSR110 cSR110_1(initial_step=1)
    annotation (Placement(transformation(extent={{-60,0},{-40,20}})));
  Components.OutputRegionM O(
    XFromRange={39,51},
    output_rate=1,
    redeclare function ExtOutput = Test.ROutput)
    annotation (Placement(transformation(extent={{-60,44},{-40,64}})));
  constant Integer result[13] = {0,0,0,1,0,1,1,1,0,0,1,1,0}; // at step 12
  Boolean fail( start = false);
algorithm
  when terminal() then
    for i in 1:13 loop
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
  connect(cSR110_1.Space, O.FROM)
    annotation (Line(points={{-49,21},{-50,21},{-50,54}}, color={0,0,0}));
  annotation (Icon(coordinateSystem(preserveAspectRatio=false)), Diagram(
        coordinateSystem(preserveAspectRatio=false)),
    experiment(StopTime=13, __Dymola_Algorithm="Dassl"),
    Documentation(info="<html>
<p>This model combines the CSR110 model with the Animation model to generate the graphical animation during the simulation.</p>
<p>The RSetDisplay function is used as <i>Display</i> function.</p>
</html>"));
end Test_CSR110;
