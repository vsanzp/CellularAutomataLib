within CellularAutomataLib.Components.Interfaces;
connector CAport "Cellular space connection port"
  CellularAutomataLib.Components.ExternalObj.CS space;
  annotation (Documentation(info="<html>
<p>Connector used to combine multiple CA models. It is used to share a cellular space (<span style=\"font-family: Courier New;\">CellSpace</span>) with other models such as <span style=\"font-family: Courier New;\">Animation</span>, <span style=\"font-family: Courier New;\">AdditionalRule</span> or interface models. </p>
</html>"),
    Icon(graphics={Ellipse(
          extent={{-100,-100},{100,100}},
          lineColor={28,108,200},
          fillColor={0,0,255},
          fillPattern=FillPattern.Solid)}),
    Diagram(graphics={Ellipse(
          extent={{-60,60},{60,-60}},
          lineColor={28,108,200},
          fillColor={0,0,255},
          fillPattern=FillPattern.Solid)}));
end CAport;
